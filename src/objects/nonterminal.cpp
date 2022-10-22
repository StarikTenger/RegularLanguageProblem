#include "nonterminal.h"

Nonterminal::Nonterminal(std::string name) : m_name(name) {}

std::string Nonterminal::name() const { return m_name; }
