.PHONY: all

all:
	#normal
	g++ -O3 -fomit-frame-pointer -march=native -o kmer kmer.cpp
	#debug version
	g++ -O3 -pg -march=native -o kmer_gp kmer.cpp
