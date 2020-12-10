#! /usr/bin/perl
use strict;
use warnings;

my $bits = $ARGV[0];

my $count = 0;
for(0 .. (1 << $bits) - 1) {
    my $str = sprintf "%0${bits}b", $_;
    if (index($str, '000') == -1) {
        ++$count;
    }
}

print "$count\n";
