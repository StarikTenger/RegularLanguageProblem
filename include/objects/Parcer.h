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
	// Считывание символа из очереди
	bool get_ch(std::queue<char>* source, char sym);

	// Считывание символа из строки
	bool get_ch(std::string* source, char sym);

	// Считывание префикса из строки
	bool get_str(std::string* source, std::string pref);

	// Проверка на букву
	bool is_letter(char c);

	// Проверка на цифру
	bool is_num(char c);

	// Считывание числа из строки
	bool get_num(std::string* s, int* ans);

	// Очередь из строки
	void make_queue(std::queue<char>* q, std::string* s);

	// Функция удаления пробелов из строки
	std::string remove_spaces(std::string s);

public:
	// Парсинг термов
	bool parce_terms(std::stringstream& s, std::map<char, aux::letter_class>& letters);
	// Парсинг нетерминалов
	bool parce_nonterms(std::stringstream& s, std::map<char, aux::letter_class>& letters);
	// Парсинг продукций
	bool parce_productions(std::stringstream& s, std::map<char, std::vector<std::string>>& productions, std::map<char, aux::letter_class>& letters);
};