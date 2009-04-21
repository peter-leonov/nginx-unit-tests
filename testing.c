#include <stdio.h>
#include "testing.h"

int testing_total_done = 0;
int testing_total_ok = 0;
int testing_total_skipped = 0;

int testing_run_tests (test_t *tests)
{
	size_t i;
	
	for (i = 0;; i++)
	{
		test_t test;
		test = tests[i];
		
		if (test != NULL)
			printf("%d\n", test());
		else
			break;
	}
	printf("%zu tests done.\n", i);
	return 0;
}
