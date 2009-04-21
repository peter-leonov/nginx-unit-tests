typedef int (*test_t) ();

struct testing_test_t
{
	int done;
	int ok;
	int skipped;
	test_t func;
};


extern int
testing_run_tests (test_t *tests, char ** names);

extern void
test ();


// #define TEST(name, code) void name () code