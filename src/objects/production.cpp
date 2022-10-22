#include "production.h"
#include "grammar.h"
#include "terminal.h"

Production::Production(const Nonterminal &left,
					   const vector<variant<Terminal, Nonterminal>> &right)
	: m_left(left), m_right(right) {}

Nonterminal Production::left() const {
	return m_left;
}

vector<variant<Terminal, Nonterminal>> Production::right() const {
	return m_right;
}

Production::Builder::Builder()
	: m_left(nullopt),
	  m_right(vector<variant<Terminal, Nonterminal>>()) {}

void Production::Builder::set_left(const Nonterminal& nonterminal) {
	m_left = nonterminal;
}

void Production::Builder::add_right_terminal(const Terminal& terminal) {
	m_right.push_back(terminal);
}

void Production::Builder::add_right_nonterminal(const Nonterminal& nonterminal) {
	m_right.push_back(nonterminal);
}

optional<Production> Production::Builder::build() const {
	if (!m_left) return nullopt;

	return Production(m_left.value(), m_right);
}
