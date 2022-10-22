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

  public:
	// Парсинг термов
	bool parce_terms(stringstream& s,
					 map<char, aux::letter_class>& letters);
	// Парсинг нетерминалов
	bool parce_nonterms(stringstream& s,
						map<char, aux::letter_class>& letters);
	// Парсинг продукций
	bool parce_productions(
		stringstream& s,
		map<char, vector<string>>& productions,
		map<char, aux::letter_class>& letters);
};