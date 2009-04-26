#!/usr/bin/env perl

while (<>)
{
	($type, $name) = /\w+ (\w) _(\S+)/;
	push @tests, $name if $type eq "T" and $name =~ /_t$/;
}


@tests = grep { !$seen{$_}++ } @tests;

print "#define TEST_FUNCS {" . join(", ", @tests) . ", ((void*)0)}\n";
print "#define TEST_NAMES {" . join(", ", map { qq{"$_"} } @tests) . ", ((void*)0)}\n";
print "#define TEST_DEFS ", join "; ", map { "extern void $_ ()" } @tests;
print "\n\n";