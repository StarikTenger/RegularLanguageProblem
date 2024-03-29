#include "LinearCFGChecker.h"

Nonterminal prod_left(const GeneralLinearProduction& prod) {
	if (holds_alternative<TerminalProduction>(prod)) {
		return get<TerminalProduction>(prod).nonterm_left;
	}
	return get<LinearProduction>(prod).nonterm_left;
}

void LinearCFGChecker::find_langs_rec(Nonterminal start_symbol,
									  const GeneralLinearProduction& cur_prod,
									  Word word_left, Word word_right,
									  int depth) {

	if (depth > max_recursion_depth) {
		return;
	}

	if (holds_alternative<TerminalProduction>(cur_prod)) {
		gamma.push_back(word_left +
						get<TerminalProduction>(cur_prod).word_right +
					 word_right);
		return;
	}

	const auto& lin_prod = get<LinearProduction>(cur_prod);
	if (lin_prod.nonterm_right == start_symbol) {
		alpha.push_back(word_left + lin_prod.words_right.first);
		beta.push_back(lin_prod.words_right.second + word_right);
		return;
	}

	for (const auto& prod : productions) {
		if (prod_left(prod) == lin_prod.nonterm_right) {
			find_langs_rec(start_symbol, prod,
						   word_left + lin_prod.words_right.first,
						   lin_prod.words_right.second + word_right, depth + 1);
		}
	}
}

string word_to_string(Word w) {
	string s = "";
	for (int i = 0; i < w.size(); i++) {
		s.push_back(w[i].name());
	}
	return s;
}

int LinearCFGChecker::find_unic_word_gamma(int num) {
	for (int i = num; i < gamma.size(); i++) {
		Word w = gamma[i];
		string str = word_to_string(w);
		bool flag = true;
		for (int j = 0; j < gamma.size(); j++) {
			if (i != j) {
				string str1 = word_to_string(gamma[j]);
				if (str == str1) {
					flag = false;
					break;
}
			}
		}
		if (flag) {
			return i;
		}
	}
	return -1;
}

optional<Word> find_unic_word(vector<Word> al, string al1) {
	for (int i = 0; i < al.size(); i++) {
		string str = word_to_string(al[i]);
		if (al1.find(str) == al1.rfind(str)) {
			return al[i];
		}
	}
	return nullopt;
}

optional<bool> LinearCFGChecker::find_unic_words(bool empty) {
	int i = find_unic_word_gamma(0);
	if (i == -1) return nullopt;
	int j = i;
	while (i < gamma.size()) {
		Word w = gamma[i];
		string str = word_to_string(w);
		//добавить проверку на пустые переходы
		if (alpha1.find(str) == -1 && beta1.find(str) == -1 && !empty) {
			return false;
		} else {
			i = find_unic_word_gamma(i+1);
		}
	}
	Word wgamma = gamma[j];
	optional<Word> walpha = find_unic_word(alpha, alpha1);
	if (walpha == nullopt) {
		return nullopt;
	}
	optional<Word> wbeta = find_unic_word(beta, beta1);
	if (wbeta == nullopt) {
		return nullopt;
	}
	return false;
}

void LinearCFGChecker::print() {
    cout << "alpha:\n";
	for (const auto& w : alpha) {
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
	Nonterminal start_symbol,
	int _max_recursion_depth) {

    alpha = {};
    beta = {};
    gamma = {};
	max_recursion_depth = _max_recursion_depth;
	for (const auto& prod : productions) {
		if (prod_left(prod) == start_symbol) {
			find_langs_rec(start_symbol, prod, {}, {});
		}
	}
}

optional<bool> LinearCFGChecker::is_regular(const Grammar& grammar) {
	auto lin_form = grammar.get_linear();
    if (lin_form == nullopt) {
        return nullopt;
    }

	productions = *lin_form;
	for (const auto& prod : productions) {
		find_langs(prod_left(prod));
        bool empty_words = false;
		for (auto word : alpha) {
			if (word.size() == 0) {
				empty_words = true;
            }
			alpha1 += word_to_string(word);
        }
		for (auto word : beta) {
			if (word.size() == 0) {
				empty_words = true;
			}
			beta1 += word_to_string(word);
		}
		if (auto res = find_unic_words(empty_words); res != nullopt) {
            return res;
		}
	}
	return nullopt;
}
