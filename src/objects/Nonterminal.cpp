#include "nonterminal.h"

using namespace std;

Nonterminal::Nonterminal(const string& name) : m_name(name) {}

string Nonterminal::name() const {
	return m_name;
}

bool operator<(const Nonterminal& lhs, const Nonterminal& rhs) {
	return lhs.m_name < rhs.m_name;
}
