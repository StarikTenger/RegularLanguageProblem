#pragma once
#include <string>

class Nonterminal {
  private:
	string m_name;

  public:
	Nonterminal(string = "");
	string name() const;
	void set_name(string);
};
