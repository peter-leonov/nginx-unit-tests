#include "testing.h"

TEST_DEFS;

static test_t     test_funcs[] = TEST_FUNCS;
static char      *test_names[] = TEST_NAMES;

int main () { return testing_run_tests(test_funcs, test_names); }