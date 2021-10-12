#include "rpn.h"
#include <iostream>

bool isNum(string val) {
	if (int(val[0]) >= 48 && int(val[0]) < 58) {
		return true;
	}
	return false;
}

bool isOperator(string op) {
	string valid_ops[] = {"+", "-", "*", "/", "**", "<", ">"};
	for (int i = 0; i < 7; i++) {
		if(valid_ops[i] == op) {
			return true;
		}
	}
	return false;
}

bool isMultiplication(string op) {
	return (int(op[0]) == 42 && (op.length() == 1));
}

bool isExponent(string op) {
	return (int(op[0]) == 42 && int(op[1]) == 42);
}

bool isSubtraction(string op) {
	return (int(op[0]) == 45);
}
bool isDivision(string op) {
	return (int(op[0]) == 47);
}
bool isAddition(string op) {
	return (int(op[0]) == 43);
}
bool isFloor(string op) {
	return (int(op[0]) == 60);
}
bool isCeiling(string op) {
	return (int(op[0]) == 62);
}

void determineOrder(string *strs, int size, vector<string> &ops) {
	for (int i = 0; i < size; i++) {
		ops.push_back(strs[i]);
	}
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (isNum(ops[i])) {
			counter++;
		}
	if (isOperator(ops[i])) {
		if (isFloor(ops[i]) || isCeiling(ops[i])) {
			counter--;
		} else {
			counter = counter - 2;
		}

			if (counter < 0) {
				break;
				//This is invalid sequence
			}
			if (counter == 0) {
				// Move to beginning
				ops.insert(ops.begin(), ops[i]);
				ops.erase(ops.begin() + i + 1);
			}
			if (counter > 0) {
				// Move in front of two operands
				ops.insert(ops.begin() + i - 2, ops[i]);
				// This positioning depends on whether binary or unary
				ops.erase(ops.begin() + i + 1);
			}
			counter++;
		}
	}
}


double rpn(string strs[], int size) {
	double result = 0.0;

	stack<float> nums;
	// error if only 1 input
	for (int i = 0; i < size; i++) {
		if (isNum(strs[i])) {
			nums.push(stof(strs[i]));
		} else {
			float first_operand = nums.top();
			nums.pop();
			if (isFloor(strs[i])) {
				nums.push(floor(first_operand));
			} else if (isCeiling(strs[i])) {
				nums.push(ceil(first_operand));
			} else {
				// error if nothing to pop
				float second_operand = nums.top();
				nums.pop();
				if (isAddition(strs[i])) {
					nums.push(first_operand + second_operand);
				} else if (isSubtraction(strs[i])) {
					nums.push(second_operand - first_operand);
				} else if (isMultiplication(strs[i])) {
					nums.push(first_operand * second_operand);
				} else if (isDivision(strs[i])) {
					nums.push(second_operand / first_operand);
				} else if (isExponent(strs[i])) {
					nums.push(pow(second_operand, first_operand));
				}
				// error if symbol not there
			}
		}
	}
	result += nums.top();
	nums.pop();
	return result;
}

void printParentheses(string *strs, int size) {
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

int main() {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	// string test[] = {"2.4", "<"}; 
	double result = rpn(test, sizeof(test)/sizeof(test[0]));
	cout << result << endl;
	// Need to return vector or pass in
	vector<string> testvec;
	determineOrder(test, sizeof(test)/sizeof(test[0]), testvec);
	printParentheses(test, sizeof(test)/sizeof(test[0]), testvec);
	return 0;
}