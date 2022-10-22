#pragma once
#include "AuxLib.h"
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <variant>

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

    // Возврат значений в очередь
	void restore(std::queue<char>& stream, std::string save);

	// Парсинг термов
	bool get_term(std::queue<char>& input, char& nonterm);

	// Парсинг нетерминалов
	bool get_nonterm(std::queue<char>& input, std::string& nonterm);

	// Парсинг продукций
	bool parce_productions(std::stringstream& s);

    public:

	bool parce_from_file();
};