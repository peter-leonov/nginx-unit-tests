#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "testing.h"
#include "assert.h"

int testing_total_done = 0;
int testing_total_ok = 0;
int testing_total_skipped = 0;

int testing_run_tests (test_t *tests, char ** names)
{
	size_t i;
	
	assert(tests);
	assert(names);
	
	for (i = 0;; i++)
	{
		test_t test;
		char *name;
		pid_t child;
		
		test = tests[i];
		name = names[i];
		
		if (test != NULL && name != NULL)
		{
			printf("%s: ", name);
			fflush(stdout);
			
			child = fork();
			if (child < 0)
			{
				fprintf(stderr, "%s\n", "cant fork, exiting");
				_exit(1);
			}
			else if (child)
			{
				wait(NULL);
				printf("\n");
			}
			else
			{
				test();
				printf("ok");
				fflush(stdout);
				_exit(0);
			}
		}
		else
			break;
	}
	printf("%zu tests done.\n", i);
	return 0;
}
