#include "CSGrammar.h"

CSGrammar::CSGrammar(std::string filename) { // конструктор из файла
	std::ifstream file(filename);
	if (!file) {
		std::cout << "error: cannot find file named " + filename;
		return;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	Parcer parcer;
	bool err;
	err = !parcer.parce_terms(buffer, letters);
	if (err) std::cout << "failed to parce terms";
	err = !parcer.parce_nonterms(buffer, letters);
	if (err) std::cout << "failed to parce nonterms";
	err = !parcer.parce_productions(buffer, productions, letters);
	if (err) std::cout << "failed to parce productions";
}