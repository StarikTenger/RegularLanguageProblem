#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <string>

class Nonterminal {

  std::string m_name;

public:
  Nonterminal(std::string);
  std::string name() const;
};

#endif // NONTERMINAL_H
