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
<<<<<<< HEAD

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

optional<Grammar> Grammar::Builder::build() const {
	if (m_terminals.empty()) return nullopt;

	if (m_nonterminals.empty()) return nullopt;

	if (m_productions.empty()) return nullopt;

	if (!m_startNonterminal) return nullopt;

	return optional{Grammar(m_terminals, m_nonterminals, m_productions,
							m_startNonterminal.value())};
}
=======
>>>>>>> f5e772db678778c226c92e14c9113c3c27e0cfc6
