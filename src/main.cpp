#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "Parcer.h"
#include "LinearCFGChecker.h"
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
	parcer.parce_grammar(buffer, grammar);

    LinearCFGChecker checker;
	auto result1 = checker.is_regular(grammar);
    auto result2 = grammar.regular_closure();
	optional<bool> result = result1 && result2;

    if (result.has_value()) {
		cout << (result.value() ? "regular" : "non-regular");
	} else {
		cout << "unknown";
    }
}