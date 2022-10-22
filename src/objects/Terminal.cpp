#include "Terminal.h"
#include "..\..\include\objects\Terminal.h"

Terminal::Terminal(char name) : m_name(name) {}

char Terminal::name() const {
	return m_name;
}

void Terminal::set_name(char name) {
	m_name = name;
}
