import sys
from fasta_library import _reverseComplement as reverse_complement

# read kmer table file
kmer_table = sys.argv[1]
input = open(kmer_table, "r")

# store counts
total_kmer  = 0
unique_kmer = 0

# read line
line = input.readline()

# first line: determine kmer length and middle position
# ASSUMPTION: kmer has uneven length
kmer_length = len(line.strip().split()[0])
kmer_middle = (kmer_length - 1) / 2

# as long as there are more kmers in the file
while line:

    # split line
    attr = line.strip().split()

    # parse attributes
    kmer  = attr[0]
    count = int(attr[1])

    # increment counters
    total_kmer  += count
    unique_kmer += 1

    # reverse complement the kmer if needed
    if kmer[kmer_middle] in ("G", "T"):
        kmer = reverse_complement(kmer)

    # print output to stdout
    print kmer, count
    
    # read next line
    line = input.readline()

# print counts line
print "\t".join(("+", str(total_kmer), str(unique_kmer), str(kmer_length)))

# close input file handle
input.close()

