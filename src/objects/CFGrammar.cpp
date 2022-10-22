#include "CFGrammar.h"

CFGrammar::CFGrammar(string filename) { // конструктор из файла
	ifstream file(filename);
	if (!file) {
		cout << "error: cannot find file named " + filename;
		return;
	}
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
}