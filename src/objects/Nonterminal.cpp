#include "Nonterminal.h"

using namespace std;

Nonterminal::Nonterminal() {}

Nonterminal::Nonterminal(const string& name) : m_name(name) {}

string Nonterminal::name() const {
	return m_name;
}

void Nonterminal::set_name(string _name) {
	m_name = _name;
}

bool operator<(const Nonterminal& lhs, const Nonterminal& rhs) {
	return lhs.m_name < rhs.m_name;
}
