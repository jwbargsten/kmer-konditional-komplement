#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;


inline char complement(char element)
{
  static const char charMap[] =
  {
    'T', 'V', 'G', 'H', '\0', '\0', 'C', 'D', '\0', '\0', 'M', '\0', 'K',
    'N', '\0', '\0', '\0', 'Y', 'S', 'A', 'A', 'B', 'W', '\0', 'R', '\0'
  };

  return charMap[toupper(element) - 'A'];
}

void reverse_complement(string& kmer, long kmer_size);

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);

  long kmer_size = 0;

  ifstream in(argv[1]);
  if(!in || in.bad()) {
    cerr << "Supply the right arguments, you idiot! " << argv[0]  << " [FILENAME]" << endl;
    exit(1);
  }

  string line;
  long kmer_cnt;

  long min_cnt;
  long max_cnt;

  if(argc > 2) {
    min_cnt = atoi(argv[2]);
  } else {
    min_cnt = -1;
  }

  if(argc > 3) {
    max_cnt = atoi(argv[3]);
  } else {
    max_cnt = -1;
  }


  // get the kmer_size from first line
  streampos sp = in.tellg();
  getline(in, line);
  in.seekg(sp);

  kmer_size = line.find_first_of(" \t");

  if(min_cnt > 0 && max_cnt > 0 && min_cnt > max_cnt) {
    cerr << "Min is bigger than max. Go back to elementary school, NOW!" << endl;
    exit(1);
  }

  if(kmer_size < 0) {
    cerr << "The square root of the kmer length is complex. THIS IS NOT ACCEPTABLE!" << endl;
    exit(1);

  } else if(kmer_size == 0) {
    cerr << "42 divided by the supplied kmer length is undefined, so am I!" << endl;
    exit(1);

  } else if(kmer_size % 2 == 0) {
    cerr << "Even kmers are evil!" << endl;
    exit(1);

  } else if(kmer_size > 1000) {
    cerr << "Do you want to assembly alien genomes or why do you need kmers longer than 1000?" << endl;
    exit(1);
  }

  long t_kmer_cnt = 0;
  long u_kmer_cnt = 0;

  // yes, thats correct.
  long middle = kmer_size/2;

  while (!getline(in, line).eof()) {

    // |-- kmer_size --|
    // ATCTAGCTAGCTTAGCT 5
    // * line.c_str()
    //                   * + kmer_size + 1

    kmer_cnt = strtol(line.c_str() + kmer_size + 1, NULL, 10);

    if(min_cnt > 0) {
      if(kmer_cnt <= min_cnt)
        continue;
      if(max_cnt > 0 && kmer_cnt >= max_cnt)
        continue;
    }

    t_kmer_cnt += kmer_cnt;
    u_kmer_cnt++;

    if(line[middle] == 'G' || line[middle] == 'T' || line[middle] == 'g' || line[middle] == 't') {
      reverse_complement(line, kmer_size);
    }

    std::puts(line.c_str());
  }
  in.close();

  printf("+\t%ld\t%ld\t%ld\n", t_kmer_cnt, u_kmer_cnt, kmer_size);

  return 0;
}

void reverse_complement(string& kmer, long kmer_size)
{
  char tmp;
  long middle = kmer_size/2;
  long i;
  for(i = 0; i < middle; i++) {
    tmp = kmer[kmer_size - 1 - i];
    kmer[kmer_size - 1 -i ] = complement(kmer[i]);
    kmer[i] = complement(tmp);
  }
  kmer[middle] =  complement(kmer[middle]);

  return;
}
