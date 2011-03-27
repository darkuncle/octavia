#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


/**
 * Reduce double consonants like "ll" to just one, e.g. "l". Treat "ck" as
 * "kk".
 */
dynamic char * reduce_double_consonants(const char * string) {
      size_t lngth = strlen(string);
      char * r = allocate(lngth + 1, sizeof(char));
      char prvs = '\0';

      for (size_t i = 0, j = 0; i < lngth; i++) {
            if (prvs) {
                  if (prvs == string[i]) {
                        // Do nothing.
                  } else if ('c' == prvs && 'k' == string[i]) {
                        j--;
                        r[j] = string[i];
                        j++;
                  } else {
                        r[j] = string[i];
                        j++;
                  }

                  prvs = string[i];
            }
            else {
                  prvs = r[j] = string[i];
                  j++;
            }
      }

      return r;
}


int is_vowel(char c) {
      switch (tolower(c)) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                  return 1;
            default:
                  return 0;
      }
}


/**
 * Remove all vowels, except for initial vowels and non-"e" final vowels.
 */
dynamic char * disemvowel(char * string) {
      size_t lngth = strlen(string);

      if ('e' == string[lngth - 1]) {
            string[lngth - 1] = '\0';
            lngth--;
      }

      char * r = allocate(lngth + 1, sizeof(char));

      for (size_t i = 0, j = 0; i < lngth; i++) {
            if (0 == i || (lngth - 1) == i || ! is_vowel(string[i])) {
                  r[j] = string[i];
                  j++;
            }
      }

      return r;
}


int main(int count, char * arguments []) {

      char * tsts [] = { "bucket", "hello", "aurora", "euphonia", "gaggle", "chumpkin", "crackle" };

      for (size_t i = 0; i < sizeof tsts / sizeof(char *); i++) {
            char * a = reduce_double_consonants(tsts[i]),
                 * b = disemvowel(a);
            printf("'%s' --> '%s' --> '%s'\n", tsts[i], a, b);
      }

      for (int i = 1; i < count; i++) {
            char * a = reduce_double_consonants(arguments[i]),
                 * b = disemvowel(a);
            printf("'%s' --> '%s' --> '%s'\n", arguments[i], a, b);
      }

      return 0;
}

