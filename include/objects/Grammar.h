#pragma once

#include <optional>
#include <set>
#include <queue>
#include <map>
#include <deque>

#include "Nonterminal.h"
#include "Production.h"
#include "Terminal.h"

class Grammar {
	std::set<Terminal> m_terminals;
	std::set<Nonterminal> m_nonterminals;
	std::set<Production> m_productions;
	Nonterminal m_start_nonterminal = Nonterminal("S");
	std::set<Nonterminal> non_generating_nonterminals() const;
	void remove_epsilon_rules(set<Production>& result);

    friend class LinearCFGChecker;

    void get_epsilon_generative(set<Nonterminal>& epss,
								set<Nonterminal>& useless);

    Nonterminal generate_new_nonterminal();

	bool is_reachable_from(Nonterminal a, Nonterminal b,
					  set<Nonterminal>& c) const;
	bool are_mutual_recursive(Nonterminal a, Nonterminal b) const;

  public:
	Grammar();
	Grammar(std::set<Terminal>, std::set<Nonterminal>, std::set<Production>,
			Nonterminal);

	void add_terminal(const Terminal&);
	void add_nonterminal(const Nonterminal&);
	void add_production(const Production&);
	void set_start_nonterminal(const Nonterminal&);

    void clear_up();

	bool is_right(set<Nonterminal> nonterminals) const;
	bool is_left(set<Nonterminal> nonterminals) const;
	vector<set<Nonterminal>> nonterminal_partition() const;

    std::optional<bool> regular_closure();
	optional<vector<GeneralLinearProduction>> get_linear() const;
};