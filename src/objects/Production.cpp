#include "Production.h"

using namespace std;

Production::Production(const Nonterminal& left,
					   const vector<variant<Terminal, Nonterminal>>& right)
	: m_left(left), m_right(right) {}

Nonterminal Production::left() const {
	return m_left;
}

const vector<variant<Terminal, Nonterminal>>& Production::right() const {
	return m_right;
}

set<Nonterminal> Production::right_nonterminals() const {
	set<Nonterminal> rns;

	for (auto symbol : right()) {
		if (holds_alternative<Nonterminal>(symbol))
			rns.insert(get<Nonterminal>(symbol));
	}

	return rns;
}

void Production::set_left(const Nonterminal& nonterminal) {
	m_left = nonterminal;
}

void Production::add_right(const Terminal& terminal) {
	m_right.push_back(terminal);
}

void Production::add_right(const Nonterminal& nonterminal) {
	m_right.push_back(nonterminal);
}

string Production::to_str() const{
	string ans;
	ans += m_left.name();
	for (int i = 0; i < m_right.size(); i++) {
		(holds_alternative<Terminal>(m_right[i])
			 ? ans += get<Terminal>(m_right[i]).name()
			 : ans += get<Nonterminal>(m_right[i]).name());
	}
	return ans;
}

bool operator<(const Production& lhs, const Production& rhs) {
	return lhs.to_str() < rhs.to_str();
	// if (lhs.m_left < rhs.m_left) {
	//	return true;
	//   }
	// if (lhs.m_right.size() < rhs.m_right.size()) {
	//	return true;
	//}
	// if (lhs.m_right.size() > rhs.m_right.size()) {
	//	return false;
	//}
	//   // Equal sized right-parts
	// for (int i = 0; i < lhs.m_right.size(); i++) {
	//	bool lhs_term = holds_alternative<Terminal>(lhs.m_right[i]);
	//	bool rhs_term = holds_alternative<Terminal>(rhs.m_right[i]);

	//	if (lhs_term == rhs_term && lhs.m_right[i] < rhs.m_right[i]) {
	//		return true;
	//	}

	//       if (lhs_term == true && rhs_term == false) {
	//		return true;
	//       }
	//   }
	// return false;
}
