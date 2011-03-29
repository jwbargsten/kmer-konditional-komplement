#!/usr/bin/env perl

use warnings;
use strict;

use Data::Dumper;
use Carp;

use feature ':5.10';

use Benchmark qw(:all);
cmpthese(
    10,
    {  
        #'python_ed' => 'system("python ed/test.py ed/test.in >test.ed")',
        'cpp_jvh'   => 'system("./kmer_reverse_complement <ed/test.in >test.jvh")',
        'cpp_jwb'   => 'system("./kmer ed/test.in >test.jb")',
    }
);

