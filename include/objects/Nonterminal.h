#pragma once

#include <string>

using namespace std;

class Nonterminal {

	string m_name = "";

  public:
	Nonterminal();
	Nonterminal(const string&);

	string name() const;
	void set_name(string);

	friend bool operator<(const Nonterminal&, const Nonterminal&);
};
