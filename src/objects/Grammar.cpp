#include "grammar.h"
#include "nonterminal.h"
#include "production.h"
#include "terminal.h"
#include "variant"

using namespace std;

Grammar::Grammar() {}

Grammar::Grammar(set<Terminal> terminals, set<Nonterminal> nonterminals,
				 set<Production> productions, Nonterminal startNonterminal)
	: m_terminals(terminals), m_nonterminals(nonterminals),
	  m_productions(productions), m_start_nonterminal(startNonterminal) {}

void Grammar::add_terminal(const Terminal& terminal) {
	m_terminals.insert(terminal);
}

void Grammar::add_nonterminal(const Nonterminal& nonterminal) {
	m_nonterminals.insert(nonterminal);
}

void Grammar::add_production(const Production& production) {
	m_productions.insert(production);
}

void Grammar::set_start_nonterminal(const Nonterminal& nonterminal) {
	m_start_nonterminal = nonterminal;
}

optional<vector<GeneralLinearProduction>> Grammar::get_linear() const {
	int nonterminal_number = 0;
	vector<GeneralLinearProduction> linprod = {};
	for (auto production : m_productions) {
		for (auto symbol : production.right()) {
			if (holds_alternative<Nonterminal>(symbol)) {
				nonterminal_number++;
			}
		}
		if (nonterminal_number <= 1) {
			if (nonterminal_number == 0) {
				TerminalProduction prod;
				prod.nonterm_left = production.left();
				for (auto j : production.right()) {
					prod.word_right.push_back(get<Terminal>(j));
				}
				linprod.push_back(prod);
            } else {
				LinearProduction prod;
				prod.nonterm_left = production.left();
				int sygn = 0;
				for (auto j : production.right()) {
					if (holds_alternative<Terminal>(j) && sygn == 0) {
						prod.words_right.first.push_back(get<Terminal>(j));
					} else if (holds_alternative<Nonterminal>(j)) {
						prod.nonterm_right = get<Nonterminal>(j);
						sygn++;
					} else {
						prod.words_right.second.push_back(get<Terminal>(j));
                    }
				}
				linprod.push_back(prod);
            }
        } else {
			return nullopt;
        }
		nonterminal_number = 0;
	}
	return linprod;
}