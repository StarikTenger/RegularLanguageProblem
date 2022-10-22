#include "Nonterminal.h"

Nonterminal::Nonterminal(string name) : m_name(name) {}

string Nonterminal::name() const {
	return m_name;
}
