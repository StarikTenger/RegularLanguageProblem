#pragma once

class Terminal {
  private:
	char m_name;

  public:
	Terminal(char = '\0');
	char name() const;
	void set_name(char);
};
