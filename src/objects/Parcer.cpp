#include "Parcer.h"

bool Parcer::get_ch(std::queue<char>* source, char sym) {
	if (source->empty() || source->front() != sym) {
		return false;
	}
	source->pop();
	return true;
}

// ���������� ������� �� ������
bool Parcer::get_ch(std::string* source, char sym) {
	if (source->size() == 0 || source->operator[](0) != sym) {
		return false;
	}
	*source = source->substr(1);
	return true;
}

// ���������� �������� �� ������
bool Parcer::get_str(std::string* source, std::string pref) {
	if (source->size() < pref.size() || source->substr(0, pref.size()) != pref) {
		return false;
	}
	*source = source->substr(pref.size());
	return true;
}

// �������� �� �����
bool Parcer::is_letter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// �������� �� �����
bool Parcer::is_num(char c) {
	return (c >= '0' && c <= '9');
}

// ���������� ����� �� ������
bool Parcer::get_num(std::string* s, int* ans) {
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
	std::string new_s = s->substr(i);
	*s = new_s;
	return i != 0;
}

// ������� �� ������
void Parcer::make_queue(std::queue<char>* q, std::string* s) {
	for (int i = 0; i != s->size(); i++) {
		q->push(s->operator[](i));
	}
}

// ������� �������� �������� �� ������
std::string Parcer::remove_spaces(std::string s) {
	std::string ans;
	for (int i = 0; i < s.size(); i++) {
		s[i] != ' ' ? ans.push_back(s[i]) : void();
	}
	return ans;
}
// ������� ������
bool Parcer::parce_terms(std::stringstream& s, std::map<char, aux::letter_class>& letters) {
	std::string inp;
	getline(s, inp);
	inp = remove_spaces(inp);
	if (!get_str(&inp, "terms="))
		return false;
	while (inp.size()) {
		char letter = inp[0];
		inp = inp.substr(1);
		bool getted = true;
		getted &= (!inp.size() || get_ch(&inp, ','));
		if (!getted)
			return getted;
		letters[letter] = aux::letter_class::term;
	}
	return true;
}
// ������� ������������
bool Parcer::parce_nonterms(std::stringstream& s, std::map<char, aux::letter_class>& letters) {
	std::string inp;
	getline(s, inp);
	inp = remove_spaces(inp);
	if (!get_str(&inp, "nonterms="))
		return false;
	while (inp.size()) {
		char letter = inp[0];
		inp = inp.substr(1);
		bool getted = true;
		getted &= (!inp.size() || get_ch(&inp, ','));
		if (!getted)
			return getted;
		letters[letter] = aux::letter_class::nonterm;
	}
	return true;
}
// ������� ���������
bool Parcer::parce_productions(std::stringstream& s, std::map<char, std::vector<std::string>>& productions, std::map<char, aux::letter_class>& letters) {
	std::string production;
	while (getline(s, production)) {
		production = remove_spaces(production);
		std::queue<char> product;
		make_queue(&product, &production);
		if (product.empty() || letters[product.front()] != aux::letter_class::nonterm)
			return false;
		char nonterm = product.front();
		product.pop();
		if (!get_ch(&product, '='))
			return false;
		std::string pr = "";
		while (!product.empty()) {
			if (get_ch(&product, '|')) {
				productions[nonterm].push_back(pr);
				pr = "";
				continue;
			}
			if (letters[product.front()] == aux::letter_class::undefined)
				return false;
			pr.push_back(product.front());
			product.pop();
		}
		productions[nonterm].push_back(pr);
	}
	return true;
}