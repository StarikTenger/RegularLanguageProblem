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
	int max_recursion_depth = 15;

	// Find alpha, beta et gamma
	void find_langs_rec(Nonterminal start_symbol,
						const GeneralLinearProduction& prod, Word word_left,
						Word word_right, int depth = 0);
	optional<bool> find_unic_words(bool empty);
	int find_unic_word_gamma(int num);

  public:
	void find_langs(Nonterminal start_symbol,
					int _max_recursion_depth = 10);
    // Entery point
	optional<bool> is_regular(const Grammar& grammar);
	void print();
};