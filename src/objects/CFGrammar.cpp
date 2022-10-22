#include "CFGrammar.h"

CFGrammar::CFGrammar(std::string filename) { // конструктор из файла
	std::ifstream file(filename);
	if (!file) {
		std::cout << "error: cannot find file named " + filename;
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
}