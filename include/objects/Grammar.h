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
	Nonterminal m_start_nonterminal;

    friend class LinearCFGChecker;

  public:
	Grammar();
	Grammar(std::set<Terminal>, std::set<Nonterminal>, std::set<Production>,
			Nonterminal);

	void add_terminal(const Terminal&);
	void add_nonterminal(const Nonterminal&);
	void add_production(const Production&);
	void set_start_nonterminal(const Nonterminal&);
	optional<vector<GeneralLinearProduction>> get_linear() const;
};