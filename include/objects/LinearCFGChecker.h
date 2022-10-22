#include "Grammar.h"
#include <set>
#include <vector>

using namespace std;

class LinearCFGChecker {
  private:
	// S →∗ α S β
	set<Word> alpha;
	set<Word> beta;
	// S →∗ γ
	set<Word> gamma;

	// Rules
	vector<GeneralLinearProduction> productions;

	// WARNING: hardcode!
	Nonterminal start_symbol = Nonterminal("S");

	int max_recursion_depth = 10;

	// Find alpha, beta et gamma
	void find_langs(const GeneralLinearProduction&, Word word_left,
					Word word_right, int depth = 0);

  public:
};