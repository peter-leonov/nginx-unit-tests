typedef void (*test_t) ();

extern int
testing_run_tests (test_t *tests, char ** names);

// #define OK(name, code) void name () code