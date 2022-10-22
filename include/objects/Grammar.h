#pragma once

#include <optional>
#include <set>

#include "nonterminal.h"
#include "production.h"
#include "terminal.h"

class Grammar {
	std::set<Terminal> m_terminals;
	std::set<Nonterminal> m_nonterminals;
	std::set<Production> m_productions;
	Nonterminal m_startNonterminal;

  public:
	Grammar();
	Grammar(std::set<Terminal>, std::set<Nonterminal>, std::set<Production>,
			Nonterminal);

<<<<<<< HEAD
	class Builder {

		std::set<Terminal> m_terminals;
		std::set<Nonterminal> m_nonterminals;
		std::set<Production> m_productions;
		std::optional<Nonterminal> m_startNonterminal;

	  public:
		Builder();

		void add_terminal(const Terminal&);
		void add_nonterminal(const Nonterminal&);
		void add_production(const Production&);
		void set_start_nonterminal(const Nonterminal&);
		bool is_linear();
		std::optional<Grammar> build() const;
	};
=======
	void add_terminal(const Terminal&);
	void add_nonterminal(const Nonterminal&);
	void add_production(const Production&);
	void set_start_nonterminal(const Nonterminal&);
>>>>>>> master
};