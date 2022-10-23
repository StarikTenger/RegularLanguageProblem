#include "grammar.h"
#include "nonterminal.h"
#include "production.h"
#include "terminal.h"
#include "variant"

using namespace std;

Grammar::Grammar() {}

Grammar::Grammar(set<Terminal> terminals, set<Nonterminal> nonterminals,
				 set<Production> productions, Nonterminal startNonterminal)
	: m_terminals(terminals), m_nonterminals(nonterminals),
	  m_productions(productions), m_startNonterminal(startNonterminal) {}

void Grammar::add_terminal(const Terminal& terminal) {
	m_terminals.insert(terminal);
}

set<Nonterminal> Grammar::non_generating_nonterminals() const {
	map<Nonterminal, bool> is_generating;

	for (const auto& nonterminal : m_nonterminals) {
		is_generating[nonterminal] = false;
	}

	map<Production, int> counter;

	for (const auto& production : m_productions) {
		counter[production] = production.right_nonterminals().size();
	}

	map<Nonterminal, set<Production>> concerned_productions;

	for (const auto& nonterminal : m_nonterminals) {
		concerned_productions[nonterminal] = set<Production>();

		for (const auto& production : m_productions) {
			if (production.right_nonterminals().count(nonterminal))
				concerned_productions[nonterminal].insert(production);
		}
	}

	queue<Nonterminal> q;

	for (const auto& [production, count] : counter) {
		if (!count) q.push(production.left());
	}

	while (!q.empty()) {
		auto nonterminal = q.front();

		q.pop();

		for (const auto& production : concerned_productions[nonterminal]) {
			if (--counter[production] == 0) {
				auto left = production.left();

				is_generating[left] = true;
				q.push(left);
			}
		}
	}

	set<Nonterminal> result;

	for (const auto& [nonterminal, generating] : is_generating) {
		if (generating) result.insert(nonterminal);
	}

	return result;
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
bool Grammar::is_linear() {
	int nonterminal_number = 0;
	for (auto i : m_productions) {
        for (auto j : i.right()) {
			if (holds_alternative<Nonterminal>(j)) {
				nonterminal_number++;
            }
        }
    }
	return nonterminal_number <= 1;
}