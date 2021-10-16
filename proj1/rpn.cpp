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

bool isBinaryOperator(string op) {
	string valid_ops[] = {"+", "-", "*", "/", "**"};
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
				int next = 0;
				while ((i - 3 - next) >= 0) {
					if(isOperator(ops[i - 3 - next])) {
						next++;
					} else {
						if (next == 0) {
							ops.insert(ops.begin() + i - 2 - next, ops[i]);
						} else {
							ops.insert(ops.begin() + i - 3 - next, ops[i]);
						}
						break;
					}
				}
				
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

void printParentheses(string *strs, int size, vector<string> &ops, int num_ops) {
	int tab_count = 0;
	int consecutive_nums = 0;
	int close_parentheses = 0;
	int nums_left = 0;
	string previous_op;
	// pass in number of ops, make while loop that counts up when putting closing parentheses
	// need some counter to keep track of closing parentheses like in determining order ex: consec = 0 and counter at 1 (meaning 1 number still unaccounted for)
	while (close_parentheses != num_ops) {
		for (int j = 0; j < tab_count; j++){
			cout << "\t";
		}
		if (isOperator(ops.front()) && !ops.empty()) {
			cout << "(" << ops.front() << endl;
			tab_count++;
			consecutive_nums = 0;
			previous_op = ops.front();
		}
		if (isNum(ops.front()) && !ops.empty()) {
			cout << ops.front() << endl;
			consecutive_nums++;
		}
		if ((consecutive_nums == 2 && isBinaryOperator(previous_op)) || (consecutive_nums == 1 && !isBinaryOperator(previous_op)) || ops.empty()) { 
			consecutive_nums = 0;
			if (tab_count > 0) {
				tab_count--;
			}
			for (int j = 0; j < tab_count; j++){
				cout << "\t";
			}
			cout << ")" << endl;
			close_parentheses++;
			if (tab_count > 0) {
				tab_count--;
				for (int j = 0; j < tab_count; j++){
					cout << "\t";
				}
				cout << ")" << endl;
				close_parentheses++;
			}
		}
		if (!ops.empty()) {
			ops.erase(ops.begin());
		}
	}
}

int main() {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	// string test[] = {"2", "3", "4", "5", "-", "/", "+"};
	// string test[] = {"1", "2", "3", "4", "+", "-", "5", "6", "7", "+", "-", "+", "-"};
	// string test[] = {"2.4", "<"}; 
	double result = rpn(test, sizeof(test)/sizeof(test[0]));
	cout << result << endl;
	vector<string> testvec;
	determineOrder(test, sizeof(test)/sizeof(test[0]), testvec);
	int num_ops = 6;
	printParentheses(test, sizeof(test)/sizeof(test[0]), testvec, num_ops);
	return 0;
}