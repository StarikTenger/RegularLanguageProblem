#pragma once
#include <optional>
#include <variant>
#include <vector>

#include "nonterminal.h"
#include "terminal.h"

using namespace std;

class Production {
  private:
	Nonterminal m_left;
	vector<variant<Terminal, Nonterminal>> m_right;

  public:
	Production(const Nonterminal&,
			   const vector<variant<Terminal, Nonterminal>>&);

	Nonterminal left() const;
	vector<variant<Terminal, Nonterminal>> right() const;

	class Builder {
	  private:
		optional<Nonterminal> m_left;
		vector<variant<Terminal, Nonterminal>> m_right;

	  public:
		Builder();

		void set_left(const Nonterminal&);
		void add_right_terminal(const Terminal&);
		void add_right_nonterminal(const Nonterminal&);

		optional<Production> build() const;
	};
};
