/**
 * This file is in the public domain. It was written by Chris Palmer
 * (http://noncombatant.org/), although perhaps he should not admit that.
 */

#include "util.h"


dynamic char * format(const char * f, ...) {
      char * s;
      va_list ap;  

      va_start(ap, f);

      if (-1 == vasprintf(&s, f, ap))
            logger(Fatal, "Could not format message: '%s'", strerror(errno));

      va_end(ap);

      return s;
}


Boolean string_is_empty(const char * string) {
      return Null == string || '\0' == string[0];
}


Boolean string_is_lower(const char * string) {
      if (! string)
            return False;

      while (*string) {
            if (isupper(*string))
                  return False;
            string++;
      }

      return True;
}


Boolean string_is_spaces(const char * string) {
      if (! string)
            return False;

      while (*string) {
            if (! isspace(*string))
                  return False;
            string++;
      }

      return True;
}


void replace_char(char * string, char x, char y) {
      if (! string)
            return;

      while (*string) {
            if (x == *string)
                  *string = y;
            string++;
      }
}


dynamic void * allocate(size_t count, size_t size) {
      void * p = calloc(count, size);

      if (! p)
            logger(Fatal, "Could not allocate memory");

      return p;
}


void free_list(List * list) {
      while (list) {
            List * n = list->next;

            if (list->key_is_dynamic)
                  free(list->key.p);

            if (list->value_is_dynamic)
                  free(list->value.p);

            if (list->this_is_dynamic)
                  free(list);

            list = n;
      }
}


long long int parse_integer(const char * string) {
      if (! string)
            goto error;

      errno = 0;

      char * end;
      long long int i = strtoll(string, &end, 0);

      if (end == string)
            goto error;

      return i;

error:
      errno = EINVAL;
      return 0;
}


/**
 * By Kragen Sitaker. http://canonical.org/~kragen/strlen-utf8.html
 */
size_t utf8_count(const char * string) {
      size_t i = 0, j = 0;

      while (string[i]) {
            if ((string[i] & 0xc0) != 0x80)
                  j++;
          i++;
      }

      return j;
}


void logger(Priority priority, const char * format, ...) {
      // Log to the console if syslogd(8) is unavailable, and log the process ID
      // in any case.
      static int Options = LOG_CONS | LOG_PID,
                 Facility = LOG_USER;
      static char Identifier [] = "octavia";

      static Boolean have_opened_log = False;

      if (! have_opened_log) {
            openlog(Identifier, Options, Facility);
            have_opened_log = True;
      }

      va_list ap;  

      va_start(ap, format);

#ifdef _BSD_SOURCE
      vsyslog(priority, format, ap);
#else
      char * msg;

      if (-1 == vasprintf(&msg, format, ap)) {
            fprintf(stderr, "logger: '%s'\n", strerror(errno));
            abort();
      }

      syslog(priority, "%s", msg);
      release(msg);
#endif

      va_end(ap);

      if (Fatal == priority)
            abort();
}

