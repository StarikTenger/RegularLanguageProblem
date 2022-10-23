#include "Grammar.h"
#include "LinearCFGChecker.h"
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
		cout << "SYNTAX";
		return 0;
    }

	LinearCFGChecker checker;
	auto result1 = checker.is_regular(grammar);
	auto result2 = grammar.regular_closure();
	optional<bool> result = nullopt;
	if (result1.has_value()) {
		result = result1;
	} else {
		if (result2.has_value()) {
			result = result2;
		}
	}

    ofstream outfile("result");
	if (result.has_value()) {
		outfile << (result.value() ? "regular" : "non-regular");
	} else {
		outfile << "unknown";
	}
}