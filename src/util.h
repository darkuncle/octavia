/**
 * This file is in the public domain. It was written by Chris Palmer
 * (http://noncombatant.org/), although perhaps he should not admit that.
 */

#ifndef UTIL_H
#define UTIL_H

#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>


// Strangle the goats in their sleep:
#undef strcat
#define strcat STRCAT_IS_BANNED
#undef strcpy
#define strcpy STRCPY_IS_BANNED
#undef sprintf
#define sprintf SPRINTF_IS_BANNED
#undef snprintf
#define snprintf SNPRINTF_IS_BANNED
#undef strncat
#define strncat STRNCAT_IS_BANNED
#undef strncpy
#define strncpy STRNCPY_IS_BANNED
#undef strdup
#define strdup STRDUP_IS_BANNED
#undef strndup
#define strndup STRNDUP_IS_BANNED
#undef strlcat
#define strlcat STRLCAT_IS_BANNED
#undef strlcpy
#define strlcpy STRLCPY_IS_BANNED


typedef enum {
      False = 0,
      True = 1
} Boolean;


#define Null NULL
#define dynamic


#define min(x, y) ((x) <= (y) ? (x) : (y))
#define max(x, y) ((x) >= (y) ? (x) : (y))


typedef union {
      void * p;
      int64_t i;
} PointyInt;


/**
 * Generic container type. Can contain two integer or pointer values, and
 * has a pointer to the next List. If you want a doubly-linked list, you
 * could use .key or .value to point to the previous member of the list.
 * .this_is_dynamic, .key_is_dynamic, and .value_is_dynamic (booleans) tell
 * you if you need to free(3) them.
 */
typedef struct List {
      PointyInt key;
      PointyInt value;
      int this_is_dynamic:1;
      int key_is_dynamic:1;
      int value_is_dynamic:1;
      struct List * next;
} List;


typedef int (* ListComparator)(List *, List *);


/**
 * Returns a string constructed from the format specifier f. Caller must
 * free.
 */
dynamic char * format(const char * f, ...);


/**
 * Returns True if string is Null or if the first byte is NUL; returns False
 * otherwise.
 */
Boolean string_is_empty(const char * string);


/**
 * Returns True if all alphabetic characters in the string are lowercase;
 * False otherwise. Returns False if string is Null.
 */
Boolean string_is_lower(const char * string);


/**
 * Returns True if all characters in the string are spaces; False otherwise.
 * Returns False if string is Null.
 */
Boolean string_is_spaces(const char * string);


/**
 * In string, replaces all instances of x with y. Does nothing if
 * string_is_empty.
 */
void replace_char(char * string, char x, char y);


/**
 * A checked calloc(3). Calls abort(3) on allocation failure.
 */
dynamic void * allocate(size_t count, size_t size);


/**
 * free(3)s the memory pointed to by pointer, and sets pointer to Null.
 * Evaluates pointer multiple times, and logs Fatal if pointer is Null.
 */
#define release(pointer)            \
      if (Null == (pointer))        \
            logger(Fatal, "Attempt to release(Null) at %s:%d", __FILE__, __LINE__);    \
      free((pointer));              \
      (pointer) = Null;


/**
 * Frees a List, also freeing the keys and values of each item in the
 * list if necessary.
 */
void free_list(List * list);


/**
 * Returns the first item in list for which compare returns 0.
 */
List * search_list(List * list, ListComparator compare);


/**
 * Returns the first item in list whose key is bytewise-identical to key.
 */
List * search_list_string(List * list, const char * key);


/**
 * Parses string as an integer, in any of bases 8, 10, 16, and returns the
 * integer value. Sets errno to EINVAL and returns 0 in case of parse
 * failure.
 */
long long int parse_integer(const char * string);


/**
 * Assumes string is a UTF-8 string and returns the number of characters in
 * it.
 */
size_t utf8_count(const char * string);


/**
 * Priorities for logging messages to syslog(3).
 */
typedef enum {
      Fatal      = LOG_CRIT,
      Error      = LOG_ERR,
      Warning    = LOG_WARNING,
      Notice     = LOG_NOTICE,
      Info       = LOG_INFO,
      Debug      = LOG_DEBUG
} Priority;

/**
 * Using syslog(3), log the formatted message at the given level of
 * priority. Fatal messages also cause program abort(3).
 */
void logger(Priority priority, const char * format, ...);

#endif

