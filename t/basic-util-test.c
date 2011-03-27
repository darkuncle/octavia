#include "util.h"

int main(int count, char * arguments []) {
      printf("sizeof PointyInt: %zu\n", sizeof(PointyInt));
      printf("sizeof void *: %zu\n", sizeof(void *));
      printf("size of long long int: %zu\n", sizeof(long long int));
      printf("sizeof List: %zu\n", sizeof(List));

      for (int i = 0; i < count; i++) {
            long long int x = parse_integer(arguments[i]);
            printf("integer value of '%s': %lld (error: %d)\n", arguments[i], x, EINVAL == errno);
            printf("strlen: %zu utf8_count: %zu\n", strlen(arguments[i]), utf8_count(arguments[i]));
      }

      printf("%s\n", format("%p is a goat", main));

      return 0;
}

