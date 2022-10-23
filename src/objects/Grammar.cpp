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

void Grammar::add_nonterminal(const Nonterminal& nonterminal) {
	m_nonterminals.insert(nonterminal);
}

void Grammar::add_production(const Production& production) {
	m_productions.insert(production);
}

void Grammar::set_start_nonterminal(const Nonterminal& nonterminal) {
	m_startNonterminal = nonterminal;
}

bool Grammar::is_reachable_from(Nonterminal a, Nonterminal b) const {
	if (a == b) {
		return true;
	}

	for (auto production : m_productions) {
		if (production.left() == a) {
			for (auto nonterminal : production.right_nonterminals()) {
				if (is_reachable_from(nonterminal, b)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool Grammar::are_mutual_recursive(Nonterminal a, Nonterminal b) const {
	return is_reachable_from(a, b) && is_reachable_from(b, a);
}

set<set<Nonterminal>> Grammar::nonterminal_partition() const {
	set<set<Nonterminal>> result;

	for (auto a : m_nonterminals) {
		bool done = false;

		for (auto p : result) {
			for (auto b : m_nonterminals) {
				if (are_mutual_recursive(a, b)) {
					p.insert(a);
					done = true;
				}
			}
		}

		if (!done) {
			set<Nonterminal> p = {a};
			result.insert(p);
		}
	}

	return result;
}

bool Grammar::is_left(set<Nonterminal> nonterminals) const {
	for (auto production : m_productions) {
		Nonterminal a = production.left();

		if (nonterminals.count(a) > 0) {
			vector<variant<Terminal, Nonterminal>> l, r = production.right();
			optional<Nonterminal> b;

			while (!b.has_value() || r.empty()) {
				l.push_back(r.back());

				if (holds_alternative<Nonterminal>(r.back())) {
					if (nonterminals.count(get<Nonterminal>(r.back())) > 0) {
						b = get<Nonterminal>(r.back());
					}
				}

				r.pop_back();
			}

			if (b.has_value() && !l.empty()) {
				return true;
			}
		}
	}

	return false;
}

bool Grammar::is_right(set<Nonterminal> nonterminals) const {
	for (auto production : m_productions) {
		Nonterminal a = production.left();

		if (nonterminals.count(a) > 0) {
			vector<variant<Terminal, Nonterminal>> l, r = production.right();
			optional<Nonterminal> b;

			while (!b.has_value() || r.empty()) {
				l.push_back(r.back());

				if (holds_alternative<Nonterminal>(r.back())) {
					if (nonterminals.count(get<Nonterminal>(r.back())) > 0) {
						b = get<Nonterminal>(r.back());
					}
				}

				r.pop_back();
			}

			if (b.has_value() && !r.empty()) {
				return true;
			}
		}
	}

	return false;
}
