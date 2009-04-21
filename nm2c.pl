#!/usr/bin/env perl

while (<>)
{
	/\w+ (\w) _(\S+)/;
	push @tests, $2 if $1 eq "T";
}


@tests = grep { !$seen{$_}++ } @tests;

print "#define TEST_FUNCS {" . join(", ", @tests) . ", ((void*)0)}\n";
print "#define TEST_NAMES {" . join(", ", map { qq{"$_"} } @tests) . ", ((void*)0)}\n";
print "#define TEST_DEFS ", join "; ", map { "extern int $_ ();" } @tests;
print "\n\n";