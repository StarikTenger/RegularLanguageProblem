#include <iostream>
#include "Grammar.h"
#include "Parcer.h"
using namespace std;

int main() {
	Grammar grammar;
	Parcer parcer;
	string filename = "input.txt";
    ifstream file(filename);
	if (!file) {
		cout << "error: cannot find file named " + filename;
		return 0;
	}
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	parcer.parce_grammar(buffer, grammar);
	cout << "Regular Language Problem";
}