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

	Parcer parcer;
	bool err;
	err = !parcer.parce_terms(buffer, letters);
	if (err) cout << "failed to parce terms";
	err = !parcer.parce_nonterms(buffer, letters);
	if (err) cout << "failed to parce nonterms";
	err = !parcer.parce_productions(buffer, productions, letters);
	if (err) cout << "failed to parce productions";
}