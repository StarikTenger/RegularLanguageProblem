#include "terminal.h"

Terminal::Terminal(char name) : m_name(name) {}

char Terminal::name() const {
	return m_name;
}

bool operator<(const Terminal& lhs, const Terminal& rhs) {
	return lhs.m_name < rhs.m_name;
}
