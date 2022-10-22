#include "production.h"
#include "grammar.h"
#include "terminal.h"

Production::Production(const Nonterminal &left,
					   const std::vector<std::variant<Terminal, Nonterminal>> &right)
	: m_left(left), m_right(right) {}

Nonterminal Production::left() const {
	return m_left;
}

std::vector<std::variant<Terminal, Nonterminal>> Production::right() const {
	return m_right;
}

Production::Builder::Builder()
	: m_left(std::nullopt),
	  m_right(std::vector<std::variant<Terminal, Nonterminal>>()) {}

void Production::Builder::setLeft(const Nonterminal& nonterminal) {
	m_left = nonterminal;
}

void Production::Builder::addRightTerminal(const Terminal& terminal) {
	m_right.push_back(terminal);
}

void Production::Builder::addRightNonterminal(const Nonterminal& nonterminal) {
	m_right.push_back(nonterminal);
}

std::optional<Production> Production::Builder::build() const {
	if (!m_left) return std::nullopt;

	return Production(m_left.value(), m_right);
}
