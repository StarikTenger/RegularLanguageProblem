#include "Grammar.h"
#include <set>
#include <vector>

using namespace std;

class LinearCFGChecker {
  private:
	// S →∗ α S β
	vector<Word> alpha;
	string alpha1;
	vector<Word> beta;
	string beta1;
	// S →∗ γ
	vector<Word> gamma;

	// Rules
	vector<GeneralLinearProduction> productions;

	// WARNING: hardcode!
	Nonterminal start_symbol = Nonterminal("S");

	int max_recursion_depth = 10;

	// Find alpha, beta et gamma
	/*void find_langs_rec(const GeneralLinearProduction&, Word word_left,
					Word word_right, int depth = 0);*/
	optional<bool> find_unic_words();
	int find_unic_word_gamma(int num);

  public:
	void find_langs(const vector<GeneralLinearProduction>& _productions);
    void print();
};