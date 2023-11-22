#include "Grammar.h"
#include "Parcer.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	Grammar grammar;
	Parcer parcer;
	string filename = "test.CFG";
	ifstream file(filename);
	if (!file) {
		cout << "error: cannot find file named " + filename;
		return 0;
	}
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	if (!parcer.parce_grammar(buffer, grammar)) {
		cout << "Syntax error";
		return 0;
	}
	auto result = grammar.regular_closure();
	ofstream outfile("result");
	if (result.has_value()) {
		outfile << (result.value() ? "regular" : "non-regular");
	} else {
		outfile << "unknown";
	}
}