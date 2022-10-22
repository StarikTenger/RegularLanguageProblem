#include "grammar.h"
#include "nonterminal.h"
#include "production.h"
#include "terminal.h"

using namespace std;

Grammar::Grammar() {}

Grammar::Grammar(set<Terminal> terminals, set<Nonterminal> nonterminals,
				 set<Production> productions, Nonterminal startNonterminal)
	: m_terminals(terminals), m_nonterminals(nonterminals),
	  m_productions(productions), m_startNonterminal(startNonterminal) {}

void Grammar::add_terminal(const Terminal& terminal) {
	m_terminals.insert(terminal);
}

void Grammar::add_nonterminal(const Nonterminal& nonterminal) {
	m_nonterminals.insert(nonterminal);
}

void Grammar::add_production(const Production& production) {
	m_productions.insert(production);
}

void Grammar::set_start_nonterminal(const Nonterminal& nonterminal) {
	m_startNonterminal = nonterminal;
}

void Grammar::get_epsilon_generative(set<Nonterminal>& epss) {
	for (auto it = m_productions.begin(); it != m_productions.end(); it++) {
		if (it->right().size() == 1 &&
			holds_alternative<Terminal>(it->right().at(0)) &&
			get<Terminal>(it->right().at(0)).name() == '_')
			epss.insert(it->left());
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (auto it = m_productions.begin(); it != m_productions.end(); it++) {
			if (epss.count(it->left())) continue;
			bool all_eps = true;
			for (int i = 0; i < it->right().size(); i++) {
				if (holds_alternative<Terminal>(it->right().at(i)) ||
					!epss.count(get<Nonterminal>(it->right().at(i)))) {
					all_eps = false;
					break;
				}
				all_eps = false;
			}
			changed |= all_eps;
			if (all_eps) epss.insert(it->left());
		}
	}
}

Nonterminal Grammar::generate_new_nonterminal() {
	for (int i = 0;; i++) {
		string name = "S" + to_string(i);
		if (!m_nonterminals.count(name)) {
			m_nonterminals.insert(Nonterminal(name));
			return Nonterminal(name);
		}
    }
}

void Grammar::remove_epsilon_rules(set<Production>& result) {
	result = m_productions;
	set<Nonterminal> epss;
	get_epsilon_generative(epss);
	for (auto it = m_productions.begin(); it != m_productions.end(); it++) {
		vector<int> nums;
		for (int i = 0; i < it->right().size(); i++) {
			if (holds_alternative<Nonterminal>(it->right().at(i)) &&
				epss.count(get<Nonterminal>(it->right().at(i)))) {
				nums.push_back(i);
			}
		}
		for (int i = 0; i < (1 << nums.size()); i++) {
			int cur_num = 0;
			auto product = Production(it->left(),
								  vector<variant<Terminal, Nonterminal>>());
			for (int j = 0; j < it->right().size(); j++) {
				while (cur_num != nums.size() - 1 && nums[cur_num] < j) {
					cur_num++;
				}
				if (nums[cur_num] != j || i >> cur_num) {
					product.add_right(it->right().at(j));
				}
			}
			result.insert(product);
		}
	}
	for (auto it = result.begin(); it != result.end(); it++) {
		if (it->right().size() == 1 &&
			holds_alternative<Terminal>(it->right().at(0)) &&
			get<Terminal>(it->right().at(0)).name() == '_')
			result.erase(it);
	}
	if (epss.count(m_startNonterminal)) {
		Nonterminal new_s = generate_new_nonterminal();
		auto old_s =
			Production(new_s, vector<variant<Terminal, Nonterminal>>());
		old_s.add_right(m_startNonterminal);
		auto eps = Production(new_s, vector<variant<Terminal, Nonterminal>>());
		eps.add_right(Terminal('_'));
		add_production(old_s);
		add_production(eps);
		m_startNonterminal = new_s;
	}
}
