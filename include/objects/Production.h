#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "nonterminal.h"
#include "terminal.h"

using namespace std;

class Production {
	Nonterminal m_left;
	vector<variant<Terminal, Nonterminal>> m_right;

  public:
	Production(const Nonterminal&,
			   const vector<variant<Terminal, Nonterminal>>&);

	Nonterminal left() const;
	vector<variant<Terminal, Nonterminal>> right() const;

	friend bool operator<(const Production&, const Production&);

	class Builder {

		optional<Nonterminal> m_left;
		vector<variant<Terminal, Nonterminal>> m_right;

	  public:
		Builder();

		void setLeft(const Nonterminal&);
		void addRightTerminal(const Terminal&);
		void addRightNonterminal(const Nonterminal&);

		optional<Production> build() const;
	};
};
