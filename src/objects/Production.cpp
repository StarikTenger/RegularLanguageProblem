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

void Production::set_left(const Nonterminal& nonterminal) {
	m_left = nonterminal;
}

void Production::add_right(const Terminal& terminal) {
	m_right.push_back(terminal);
}

void Production::add_right(const Nonterminal& nonterminal) {
	m_right.push_back(nonterminal);
}
