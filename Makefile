.PHONY: all

all:
	g++ -O3 -fomit-frame-pointer -march=native -o kmer kmer.cpp
	g++ -O3 -pg -march=native -o kmer_gp kmer.cpp
