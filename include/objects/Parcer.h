#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include "AuxLib.h"

class Parcer {
private:
	// ���������� ������� �� �������
	bool get_ch(std::queue<char>* source, char sym);

	// ���������� ������� �� ������
	bool get_ch(std::string* source, char sym);

	// ���������� �������� �� ������
	bool get_str(std::string* source, std::string pref);

	// �������� �� �����
	bool is_letter(char c);

	// �������� �� �����
	bool is_num(char c);

	// ���������� ����� �� ������
	bool get_num(std::string* s, int* ans);

	// ������� �� ������
	void make_queue(std::queue<char>* q, std::string* s);

	// ������� �������� �������� �� ������
	std::string remove_spaces(std::string s);

public:
	// ������� ������
	bool parce_terms(std::stringstream& s, std::map<char, aux::letter_class>& letters);
	// ������� ������������
	bool parce_nonterms(std::stringstream& s, std::map<char, aux::letter_class>& letters);
	// ������� ���������
	bool parce_productions(std::stringstream& s, std::map<char, std::vector<std::string>>& productions, std::map<char, aux::letter_class>& letters);
};