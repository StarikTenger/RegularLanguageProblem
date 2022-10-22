#pragma once
#include <string>

class Nonterminal {
  private:
	std::string m_name;

  public:
	Nonterminal(std::string);
	std::string name() const;
};
