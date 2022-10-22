#pragma once

class Terminal {
  private:
	char m_name;

  public:
	Terminal(char);
	char name() const;
};
