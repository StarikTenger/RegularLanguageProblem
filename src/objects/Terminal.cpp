#include "Terminal.h"

Terminal::Terminal(char name) : m_name(name) {}

char Terminal::name() const {
	return m_name;
}

void Terminal::set_name(char name) {
	m_name = name;
}

bool operator<(const Terminal& lhs, const Terminal& rhs) {
	return lhs.m_name < rhs.m_name;
}
