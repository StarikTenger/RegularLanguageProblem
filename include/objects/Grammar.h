#ifndef GRAMMAR_H
#define GRAMMAR_H

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
	Grammar(std::set<Terminal>, std::set<Nonterminal>, std::set<Production>,
			Nonterminal);

	class Builder {

		std::set<Terminal> m_terminals;
		std::set<Nonterminal> m_nonterminals;
		std::set<Production> m_productions;
		std::optional<Nonterminal> m_startNonterminal;

	  public:
		Builder();

		void addTerminal(const Terminal&);
		void addNonterminal(const Nonterminal&);
		void addProduction(const Production&);
		void setStartNonterminal(const Nonterminal&);

		std::optional<Grammar> build() const;
	};
};

#endif // GRAMMAR_H
