#pragma once
#include "AuxLib.h"
#include "Parcer.h"
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class CSGrammar {
  public:
	CSGrammar(std::string filename); // конструктор из файла
	std::map<char, aux::letter_class>
		letters; // Связь: буква -> назначение буквы
	std::map<char, std::vector<std::string>>
		productions; // Связь: нонтерм -> набор продукций нонтерма
};