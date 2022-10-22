#pragma once

class Terminal {

	char m_name;

  public:
	Terminal(char = '\0');
	char name() const;
	void set_name(char);

	friend bool operator<(const Terminal&, const Terminal&);
};
