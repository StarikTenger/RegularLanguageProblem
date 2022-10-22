#include "Terminal.h"

Terminal::Terminal(char name) : m_name(name) {}

char Terminal::name() const {
	return m_name;
}
