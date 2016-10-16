#include <boost/program_options.hpp>
#include "mm/ug_bitext.h"
#include <string>

using namespace std;
using namespace Moses;
using namespace sapt;

namespace po=boost::program_options;
typedef L2R_Token<SimpleWordId> Token;
typedef mmBitext<Token> mmbitext;
typedef Bitext<Token>::tsa tsa;

string bname, L1, L2, Q1, Q2;
size_t maxhits;
void interpret_args(int ac, char* av[]);

int main(int argc, char* argv[])
{
  mmTtrack<Token> T;
  T.open(argv[1]);
  size_t ctr_S = 0, ctr_L = 0;
  Token const* t = T.sntEnd(T.size()-1);
  char foo = 'L';
  vector<size_t> plen_histogram_L(1000,0);
  vector<size_t> plen_histogram_S(1000,0);
  Token const* Ltic = T.sntEnd(T.size()-1);
  Token const* Stic = Ltic;
  size_t lcnt =0, scnt=0;
  for (id_type c0, c1 = 0; t-- > T.sntStart(0); c1 = c0)
    {
      if ((c0 = t->id()) == c1) continue;
      (c0 > c1 ? lcnt : scnt)++;
      if (c0 > c1)
	{
	  if (foo == 'S')
	    {
	      ++ctr_S;
	      foo = 'L';
	      // size_t tac = t - T.sntStart(0);
	      size_t plen = Stic -t;
	      assert(plen > 1);
	      while (plen >= plen_histogram_S.size())
		plen_histogram_S.push_back(0);
	      plen_histogram_S[plen]++;
	      Stic = t;
	    }
	}
      else if (foo == 'L')
	{
	  ++ctr_L;
	  foo = 'S';
	  // size_t tac = t - T.sntStart(0);
	  size_t plen = tic - t;
	  // cout << plen << endl;
	  assert(plen > 1);
	  while (plen >= plen_histogram_L.size())
	    plen_histogram_L.push_back(0);
	  plen_histogram_L[plen]++;
	  Ltic = t;
	}
    }
  cout << ctr_S << " LMS suffixes out of "
       << T.numTokens() << " tokens."  << endl;
  cout << ctr_L << " LML suffixes out of "
       << T.numTokens() << " tokens."  << endl;
  for (size_t i = 0; i < plen_histogram_L.size(); ++i)
    {
      if (plen_histogram_L[i] || plen_histogram_S[i])
	printf("%3zu %20zu %zu\n", i, plen_histogram_S[i], plen_histogram_L[i]); 
      // cout << i << ":" << plen_histogram_L[i] << endl;
    }
    
}
