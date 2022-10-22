#include "Nonterminal.h"

Nonterminal::Nonterminal(string name) : m_name(name) {}

string Nonterminal::name() const {
	return m_name;
}

void Nonterminal::set_name(string _name) {
	m_name = _name;
}
