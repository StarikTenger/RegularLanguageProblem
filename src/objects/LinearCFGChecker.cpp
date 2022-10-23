#include "LinearCFGChecker.h"

Nonterminal prod_left(const GeneralLinearProduction& prod) {
	if (holds_alternative<TerminalProduction>(prod)) {
		return get<TerminalProduction>(prod).nonterm_left;
	}
	return get<LinearProduction>(prod).nonterm_left;
}

void LinearCFGChecker::find_langs_rec(const GeneralLinearProduction& cur_prod,
									  Word word_left, Word word_right,
									  int depth) {
    cout << depth << " depth\n";
	if (depth > max_recursion_depth) {
		return;
	}

	if (holds_alternative<TerminalProduction>(cur_prod)) {
		gamma.insert(word_left + get<TerminalProduction>(cur_prod).word_right +
					 word_right);
		return;
	}

	const auto& lin_prod = get<LinearProduction>(cur_prod);
	if (lin_prod.nonterm_right == start_symbol) {
		alpha.insert(word_left + lin_prod.words_right.first);
		beta.insert(lin_prod.words_right.first + word_right);
		return;
	}

	for (const auto& prod : productions) {
		if (prod_left(prod) == lin_prod.nonterm_right) {
			find_langs_rec(prod, word_left + lin_prod.words_right.first,
						   lin_prod.words_right.second + word_right, depth + 1);
		}
	}
}

int find_unic_word_gamma(int num) {

}


bool find_unic_words() {
	Word w = gamma[find_unic_word_gamma(0)];
    if 

}

void LinearCFGChecker::print() {
    cout << "alpha:\n";
    for(const auto& w : alpha) {
        println(w);
    }
    cout << "\nbeta:\n";
	for (const auto& w : beta) {
		println(w);
	}
	cout << "\ngamma:\n";
	for (const auto& w : gamma) {
		println(w);
	}
}

void LinearCFGChecker::find_langs(
	const vector<GeneralLinearProduction>& _productions) {
	productions = _productions;
	for (const auto& prod : productions) {
		if (prod_left(prod) == start_symbol) {
			find_langs_rec(prod, {}, {});
		}
	}
}
