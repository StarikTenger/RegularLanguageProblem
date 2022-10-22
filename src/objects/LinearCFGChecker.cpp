#include "LinearCFGChecker.h"

Nonterminal prod_left(const GeneralLinearProduction& prod) {
	if (holds_alternative<TerminalProduction>(prod)) {
		return get<TerminalProduction>(prod).nonterm_left;
	}
	return get<LinearProduction>(prod).nonterm_left;
}

void LinearCFGChecker::find_langs(const GeneralLinearProduction& cur_prod,
								  Word word_left, Word word_right, int depth) {
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

	// TODO: find lin_prod.nonterm_right in left parts and continue recursion
	for (const auto& prod : productions) {
		if (prod_left(prod) == lin_prod.nonterm_right) {
			find_langs(prod, lin_prod.words_right.first,
					   lin_prod.words_right.second, depth + 1);
		}
	}
}