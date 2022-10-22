#pragma once
#include <optional>
#include <variant>
#include <vector>

#include "Nonterminal.h"
#include "Terminal.h"

using namespace std;

class Production {
	Nonterminal m_left;
	vector<variant<Terminal, Nonterminal>> m_right;

  public:
	Production(const Nonterminal&,
			   const vector<variant<Terminal, Nonterminal>>&);

	void set_left(const Nonterminal&);
	void add_right(const Terminal&);
	void add_right(const Nonterminal&);

	Nonterminal left() const;
	const vector<variant<Terminal, Nonterminal>>& right() const;

	friend bool operator<(const Production&, const Production&);
};

using Word = vector<Terminal>;

// Simpler form of production
struct LinearProduction {
	Nonterminal nonterm_left;
	Nonterminal nonterm_right;
	pair<Word, Word> words_right;
};
