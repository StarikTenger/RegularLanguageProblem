#pragma once

#include <optional>
#include <set>
#include <queue>
#include <map>

#include "nonterminal.h"
#include "production.h"
#include "terminal.h"

class Grammar {
	std::set<Terminal> m_terminals;
	std::set<Nonterminal> m_nonterminals;
	std::set<Production> m_productions;
	Nonterminal m_startNonterminal;
	std::set<Nonterminal> non_generating_nonterminals() const;

    friend class LinearCFGChecker;

    void get_epsilon_generative(set<Nonterminal>& epss);

    Nonterminal generate_new_nonterminal();

	bool is_reachable_from(Nonterminal a, Nonterminal b) const;
	bool are_mutual_recursive(Nonterminal a, Nonterminal b) const;

  public:
	Grammar();
	Grammar(std::set<Terminal>, std::set<Nonterminal>, std::set<Production>,
			Nonterminal);

	void add_terminal(const Terminal&);
	void add_nonterminal(const Nonterminal&);
	void add_production(const Production&);
	void set_start_nonterminal(const Nonterminal&);

    void remove_epsilon_rules(set<Production>& result);

	bool is_right(set<Nonterminal> nonterminals) const;
	bool is_left(set<Nonterminal> nonterminals) const;
	set<set<Nonterminal>> Grammar::nonterminal_partition() const;
};