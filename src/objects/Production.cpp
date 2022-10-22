#include "production.h"
#include "grammar.h"
#include "terminal.h"

Production::Production(const Nonterminal &left,
					   const vector<variant<Terminal, Nonterminal>> &right)
	: m_left(left), m_right(right) {}

Nonterminal Production::left() const {
	return m_left;
}

const vector<variant<Terminal, Nonterminal>>& Production::right() const {
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

bool operator<(const Production& lhs, const Production& rhs) {
	if (lhs.m_left < rhs.m_left) {
		return true;
    }
	if (lhs.m_right.size() < rhs.m_right.size()) {
		return true;
	}
	if (lhs.m_right.size() > rhs.m_right.size()) {
		return false;
	}
    // Equal sized right-parts
	for (int i = 0; i < lhs.m_right.size(); i++) {
		if (lhs.m_right[i] < rhs.m_right[i]) {
			return true;
		}
    }
	return false;
}
