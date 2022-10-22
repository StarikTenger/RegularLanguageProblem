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

class CFGrammar {
  public:
	CFGrammar(string filename); // конструктор из файла
	map<char, aux::letter_class>
		letters; // Связь: буква -> назначение буквы
	map<char, vector<string>>
		productions; // Связь: нонтерм -> набор продукций нонтерма
};