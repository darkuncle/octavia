/*
 * MinUnit: A minimal C unit test "framework" based on
 * http://www.jera.com/techinfo/jtns/jtn002.html.
 */


/*
 * Turning __LINE__ into a string, from
 * http://www.decompile.com/cpp/faq/file_and_line_error_string.htm.
 */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)


extern unsigned int tests_passed, tests_failed;

#define mu_assert(message, test) do {  \
      if (!(test)) {                   \
            return message ": " AT;    \
      }                                \
} while (0)


#define mu_run_test(test) do {                                                \
      printf("%s\n", STRINGIFY(test));                                        \
      char * msg = test();                                                    \
      if (msg) {                                                              \
            tests_failed++;                                                   \
            fprintf(stderr, "TEST FAILED: %s (%s)\n", STRINGIFY(test), msg);  \
      } else {                                                                \
            tests_passed++;                                                   \
      }                                                                       \
} while (0)


/*
 * Example MinUnit usage.
 *

unsigned int tests_passed = 0, tests_failed = 0;

int foo = 7;
int bar = 4;

char * test_foo(void) {
    mu_assert("error, foo != 7", foo == 7);
    return 0;
}

char * test_bar(void) {
    mu_assert("error, bar != 5", bar == 5);
    return 0;
}

int main(int argc, char * argv []) {
    mu_run_test(test_foo);
    mu_run_test(test_bar);

    printf("%u tests passed, %u tests failed, %u total tests\n",
           tests_passed, tests_failed, tests_passed + tests_failed);

    return 0 != tests_failed;
}

*/

