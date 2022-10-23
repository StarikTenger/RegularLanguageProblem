#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <variant>
#include "Production.h"
#include "Grammar.h"

using namespace std;

class Parcer {
  private:
	// Считывание символа из очереди
	bool get_ch(queue<char>* source, char sym);

	// Считывание символа из строки
	bool get_ch(string* source, char sym);

	// Считывание префикса из строки
	bool get_str(string* source, string pref);

	// Проверка на букву
	bool is_letter(char c);

	// Проверка на цифру
	bool is_num(char c);

	// Считывание числа из строки
	bool get_num(string* s, int* ans);

	// Очередь из строки
	void make_queue(queue<char>* q, string* s);

	// Функция удаления пробелов из строки
	string remove_spaces(string s);

    // Возврат значений в очередь
	void restore(queue<char>& stream, std::string save);

	// Парсинг термов
	bool get_term(queue<char>& input, Terminal& nonterm);

	// Парсинг нетерминалов
	bool get_nonterm(queue<char>& input, Nonterminal& nonterm);

    public:

    // Парсинг грамматики
	bool parce_grammar(stringstream& s, Grammar& productions);
};
