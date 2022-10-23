#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "Parcer.h"
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
	cout << parcer.parce_grammar(buffer, grammar);

    auto result = grammar.regular_closure();

    if (result.has_value()) {
		cout << (result.value() ? "regular" : "non-regular");
	} else {
		cout << "unknown";
    }
}