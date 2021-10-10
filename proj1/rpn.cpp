#include "rpn.h"
#include <iostream>

int main() {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	// string test[] = {"2.4", "<"}; 
	double result = rpn(test, sizeof(test)/sizeof(test[0]));
	cout << result << endl;
	// printParentheses(test, sizeof(test)/sizeof(test[0]));
}

void printParentheses(string *strs, size_t size) {
	int tab_count = 0;
	int consecutive_nums = 0;
	std::stack<string> ops;
	for (int i = 0; i < size; i++) {
		ops.push(strs[i]);
	}
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < tab_count; j++){
			cout << "\t";
		}
		if (isOperator(ops.top())) {
			cout << "(" << ops.top() << endl;
			tab_count++;
			
		}
		if (isNum(ops.top())) {
			cout << ops.top() << endl;
			consecutive_nums++;
		}
		if (consecutive_nums == 2 || ops.empty()) { // or stack empty
			consecutive_nums = 0;
			if (tab_count > 0) {
				tab_count--;
			}
			for (int j = 0; j < tab_count; j++){
				cout << "\t";
			}
			cout << ")" << endl;
		}
		ops.pop();
	}
}