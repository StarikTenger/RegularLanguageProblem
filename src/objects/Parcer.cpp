#include "Parcer.h"

using namespace std;

bool Parcer::get_ch(queue<char>* source, char sym) {
	if (source->empty() || source->front() != sym) {
		return false;
	}
	source->pop();
	return true;
}

// Считывание символа из строки
bool Parcer::get_ch(string* source, char sym) {
	if (source->size() == 0 || source->operator[](0) != sym) {
		return false;
	}
	*source = source->substr(1);
	return true;
}

// Считывание префикса из строки
bool Parcer::get_str(string* source, string pref) {
	if (source->size() < pref.size() ||
		source->substr(0, pref.size()) != pref) {
		return false;
	}
	*source = source->substr(pref.size());
	return true;
}

// Проверка на букву
bool Parcer::is_letter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Проверка на цифру
bool Parcer::is_num(char c) {
	return (c >= '0' && c <= '9');
}

// Считывание числа из строки
bool Parcer::get_num(string* s, int* ans) {
	int i = 0;
	int cur_ans = 0;
	for (; i < s->size(); i++) {
		char cur = s->operator[](i);
		if (!is_num(cur)) {
			break;
		}
		cur_ans = cur_ans * 10;
		cur_ans = cur_ans + cur - '0';
	}
	*ans = cur_ans;
	string new_s = s->substr(i);
	*s = new_s;
	return i != 0;
}

// Очередь из строки
void Parcer::make_queue(queue<char>* q, string* s) {
	for (int i = 0; i != s->size(); i++) {
		q->push(s->operator[](i));
	}
}

// Функция удаления пробелов из строки
string Parcer::remove_spaces(string s) {
	string ans;
	for (int i = 0; i < s.size(); i++) {
		s[i] != ' ' && s[i] != 9 ? ans.push_back(s[i]) : void();
	}
	return ans;
}

// Возврат значений в очередь
void Parcer::restore(std::queue<char>& stream, std::string save) {
	std::queue<char> back;
	while (!stream.empty()) {
		back.push(stream.front());
		stream.pop();
	}
	for (int i = 0; i < save.size(); i++) {
		stream.push(save[i]);
	}
	while (!back.empty()) {
		stream.push(back.front());
		back.pop();
	}
}

// Парсинг термов
bool Parcer::get_term(std::queue<char>& input, Terminal& nonterm) {
	if (input.front() == '_' ||
		(input.front() >= 'a' && input.front() <= 'z')) {
		nonterm = input.front();
		input.pop();
		return true;
	}
	return false;
}

// Парсинг нетерминалов
bool Parcer::get_nonterm(std::queue<char>& input, Nonterminal& result) {
	string nonterm;
	if (!get_ch(&input, '[')) return false;
	bool lnow = true;
	while (!input.empty() && input.front() != ']') {
		if (is_letter(input.front())) {
			if (!lnow) {
				restore(input, "[" + nonterm);
				return false;
			}
			nonterm.push_back(input.front());
			input.pop();
			continue;
		}
		if (is_num(input.front())) {
			if (nonterm.empty()) {
				restore(input, "[" + nonterm);
				return false;
			}
			lnow = false;
			nonterm.push_back(input.front());
			input.pop();
			continue;
		}
		restore(input, "[" + nonterm);
		return false;
	}

	if (!get_ch(&input, ']')) {
		restore(input, "[" + nonterm);
		return false;
	}
	result = Nonterminal(nonterm);
	return true;
}

// Парсинг продукций
bool Parcer::parce_grammar(std::stringstream& s, Grammar& grammar) {
	string inp;
	set<char> terms;
	set<string> nonterms;
	bool added = false;
	while (getline(s, inp)) {
		inp = remove_spaces(inp);
        queue<char> product;
		make_queue(&product, &inp);
		if (product.empty()) continue;
		Nonterminal variable("");
		bool success = get_nonterm(product, variable);
		if (!success || !get_ch(&product, '-') || !get_ch(&product, '>'))
			return false;
		Production production =
			Production(variable, vector<variant<Terminal, Nonterminal>>());
		grammar.add_nonterminal(variable);
		while (!product.empty()) {
			Terminal term('_');
			Nonterminal nonterm("");
			if (get_term(product, term)) {
				production.add_right(term);
				grammar.add_terminal(term);
				continue;
			}
			if (get_nonterm(product, nonterm)) {
				production.add_right(nonterm);
				grammar.add_nonterminal(nonterm);
				continue;
			}
			return false;
		}
		if (production.right().empty()) return false;
		grammar.add_production(production);
		added = true;
	}
	return added;
}