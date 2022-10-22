#pragma once

#include <string>

using namespace std;

class Nonterminal {

	string m_name;

  public:
	Nonterminal(const string&);

	string name() const;

	friend bool operator<(const Nonterminal&, const Nonterminal&);
};
