#pragma once
#include <iostream>
#include <optional>
#include <variant>
#include <vector>
#include <set>

#include "Nonterminal.h"
#include "Terminal.h"

using namespace std;

class Production {
  private:
	Nonterminal m_left;
	vector<variant<Terminal, Nonterminal>> m_right;
	string to_str() const;

  public:
	Production(const Nonterminal&,
			   const vector<variant<Terminal, Nonterminal>>&);

	void set_left(const Nonterminal&);
	void add_right(const Terminal&);
	void add_right(const Nonterminal&);
	void add_right(const variant<Terminal, Nonterminal>&);

    set<Nonterminal> right_nonterminals() const;

	Nonterminal left() const;
	const vector<variant<Terminal, Nonterminal>>& right() const;

	friend bool operator<(const Production&, const Production&);
};

using Word = vector<Terminal>;

Word operator+(const Word&, const Word&);
void println(const Word&);

// Terminal form of production
struct TerminalProduction {
	Nonterminal nonterm_left;
	Word word_right;
	TerminalProduction(){};
	TerminalProduction(Nonterminal nonterm_left, Word word_right)
		: nonterm_left(nonterm_left), word_right(word_right) {}
};

// Linear form of production
struct LinearProduction {
	Nonterminal nonterm_left;
	Nonterminal nonterm_right;
	pair<Word, Word> words_right;
	LinearProduction(){};
	LinearProduction(Nonterminal nonterm_left, Nonterminal nonterm_right,
					 pair<Word, Word> words_right)
		: nonterm_left(nonterm_left), nonterm_right(nonterm_right),
		  words_right(words_right){};
};

using GeneralLinearProduction = variant<TerminalProduction, LinearProduction>;