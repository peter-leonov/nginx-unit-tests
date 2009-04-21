#!/usr/bin/env perl

while (<>)
{
	/\w+ (\w) _(\S+)/;
	push @tests, $2 if $1 eq "T";
}

print "#define TESTS {" . join(", ", @tests) . ", ((void*)0)}\n";
print "#define TESTS_DEFS ", join "; ", map { "extern int $_ ();" } @tests;
print "\n\n";