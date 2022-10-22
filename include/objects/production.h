#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <optional>
#include <variant>
#include <vector>

#include "nonterminal.h"
#include "terminal.h"

class Production {
	Nonterminal m_left;
	std::vector<std::variant<Terminal, Nonterminal>> m_right;

  public:
	Production(const Nonterminal&,
			   const std::vector<std::variant<Terminal, Nonterminal>>&);

	Nonterminal left() const;
	std::vector<std::variant<Terminal, Nonterminal>> right() const;

	class Builder {

		std::optional<Nonterminal> m_left;
		std::vector<std::variant<Terminal, Nonterminal>> m_right;

	  public:
		Builder();

		void setLeft(const Nonterminal&);
		void addRightTerminal(const Terminal&);
		void addRightNonterminal(const Nonterminal&);

		std::optional<Production> build() const;
	};
};

#endif // PRODUCTION_H
