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
#include "Parcer.h"

class CSGrammar {
public:
	CSGrammar(std::string filename); // ����������� �� �����
	std::map<char, aux::letter_class> letters; // �����: ����� -> ���������� �����
	std::map<char, std::vector<std::string>> productions; // �����: ������� -> ����� ��������� ��������
};