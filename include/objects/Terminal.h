#pragma once

class Terminal {

	char m_name;

  public:
	Terminal(char);

	char name() const;

	friend bool operator<(const Terminal&, const Terminal&);
};
