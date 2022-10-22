#include "grammar.h"
#include "nonterminal.h"
#include "production.h"
#include "terminal.h"

using namespace std;

Grammar::Grammar(set<Terminal> terminals, set<Nonterminal> nonterminals,
				 set<Production> productions, Nonterminal startNonterminal)
	: m_terminals(terminals), m_nonterminals(nonterminals),
	  m_productions(productions), m_startNonterminal(startNonterminal) {}

Grammar::Builder::Builder()
	: m_terminals(set<Terminal>()), m_nonterminals(set<Nonterminal>()),
	  m_productions(set<Production>()), m_startNonterminal(nullopt) {}

void Grammar::Builder::add_terminal(const Terminal& terminal) {
	m_terminals.insert(terminal);
}

void Grammar::Builder::add_nonterminal(const Nonterminal& nonterminal) {
	m_nonterminals.insert(nonterminal);
}

void Grammar::Builder::add_production(const Production& production) {
	m_productions.insert(production);
}

void Grammar::Builder::set_start_nonterminal(const Nonterminal& nonterminal) {
	m_startNonterminal = nonterminal;
}

optional<Grammar> Grammar::Builder::build() const {
	if (m_terminals.empty()) return nullopt;

	if (m_nonterminals.empty()) return nullopt;

	if (m_productions.empty()) return nullopt;

	if (!m_startNonterminal) return nullopt;

	return optional{Grammar(m_terminals, m_nonterminals, m_productions,
							m_startNonterminal.value())};
}
