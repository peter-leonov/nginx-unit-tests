#include "testing.h"

TESTS_DEFS;
static test_t tests[] = TESTS;

int main () { return testing_run_tests(tests); }