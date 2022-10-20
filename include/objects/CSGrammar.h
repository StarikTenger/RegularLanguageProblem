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
	CSGrammar(std::string filename); // конструктор из файла
	std::map<char, aux::letter_class> letters; // Связь: буква -> назначение буквы
	std::map<char, std::vector<std::string>> productions; // Связь: нонтерм -> набор продукций нонтерма
};