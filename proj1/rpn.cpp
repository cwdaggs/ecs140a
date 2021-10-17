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

int countOperators(string *ops, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if(isOperator(ops[i])) {
			count++;
		}
	}
	return count;
}

int countOperands(string *ops, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if(isNum(ops[i])) {
			count++;
		}
	}
	return count;
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

void validateStrings(string *ops, int size) {
	for (int i = 0; i < size; i++) {
		if(!isOperator(ops[i]) && !isNum(ops[i])) {
			throw "Invalid operator(s)/operand(s) detected";
		}
	}
}

void determineOrder(string *strs, int size, stack<string> &ops_stack, int num_operands) {
	for (int i = 0; i < size; i++) {
		if (isNum(strs[i])) {
			ops_stack.push(strs[i]);
		} else if (isBinaryOperator(strs[i])) {
			string operand1;
			string operand2;
			string op;
			operand1 = ops_stack.top();
			ops_stack.pop();
			operand2 = ops_stack.top();
			ops_stack.pop();
			string temp = "(" + strs[i] + " " + operand2 + " " + operand1 + " " + ")";
			// op.emplace_back(strs[i]);
			// vector<string> all_ops;
			// all_ops.reserve(operand1.size() + operand2.size() + op.size());
			// all_ops.insert(all_ops.end(), op.begin(), op.end());
			// all_ops.insert(all_ops.end(), operand2.begin(), operand2.end());
			// all_ops.insert(all_ops.end(), operand1.begin(), operand1.end());
			ops_stack.push(temp);
		} else {
			string operand1;
			string op;
			operand1 = ops_stack.top();
			ops_stack.pop();
			string temp = strs[i] + " " + operand1;
			// op.emplace_back(strs[i]);
			// vector<string> all_ops;
			// all_ops.reserve(operand1.size() + op.size());
			// all_ops.insert(all_ops.end(), op.begin(), op.end());
			// all_ops.insert(all_ops.end(), operand1.begin(), operand1.end());
			ops_stack.push(temp);
		}
	}
	// for (int i = 0; i < size; i++) {
	// 	ops.push_back(strs[i]);
	// }
	// int counter = 0;
	// vector<int> indexes;
	// for (int i = 0; i < size; i++) {
	// 	if (isNum(ops[i])) {
	// 		counter++;
	// 	}
	// 	if (isOperator(ops[i])) {
	// 		if (isFloor(ops[i]) || isCeiling(ops[i])) {
	// 			counter--;
	// 		} else {
	// 			counter = counter - 2;
	// 		}

	// 		if (counter < 0) {
	// 			throw "Invalid sequence- this is not a valid sequence in postfix notation";
	// 		}
	// 		if (counter == 0) {
	// 			// Move to beginning
	// 			ops.insert(ops.begin(), ops[i]);
	// 			ops.erase(ops.begin() + i + 1);
	// 		}
	// 		if (counter > 0) {
	// 			// Move in front of two operands
	// 			int next = 0;
	// 			if (indexes.size() + 1 == num_operands) {
	// 				ops.insert(ops.begin() + 1, ops[i]);
	// 			} else {
	// 				while ((i - 3 - next) >= 0) {
	// 					if(isOperator(ops[i - 3 - next]) || count(indexes.begin(), indexes.end(), (i - 3 - next))) {
	// 						next++;
	// 					} else {
	// 						if (next == 0) {
	// 							indexes.push_back(i - 1);
	// 							indexes.push_back(i - 2);
	// 							ops.insert(ops.begin() + i - 2 - next, ops[i]);
	// 						} else {
	// 							indexes.push_back(i - 3 - next);
	// 							ops.insert(ops.begin() + i - 3 - next, ops[i]);
	// 						}
	// 						break;
	// 					}
	// 				}
	// 				for (int j = 0; j < indexes.size(); j++) {
	// 					if (indexes[j] > (i - 3)) {
	// 						indexes[j]++;
	// 					}
	// 				}
	// 			}
				
	// 			// This positioning depends on whether binary or unary
	// 			ops.erase(ops.begin() + i + 1);
	// 		}
	// 		counter++;
	// 	}
	// }

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
					if (first_operand == 0) {
						throw "Division by zero";
					} else {
						nums.push(second_operand / first_operand);
					}
				} else if (isExponent(strs[i])) {
					if ((second_operand == 0 && first_operand == 0) || (second_operand == 0 && first_operand < 0)) {
						throw "Exponentiation issue- invalid operand(s)";
					} else {
						nums.push(pow(second_operand, first_operand));
					}			
				}
			}
		}
	}
	result += nums.top();
	nums.pop();
	return result;
}

// void printParentheses(string *strs, int size, vector<string> &ops, int num_ops) {
// 	int tab_count = 0;
// 	int consecutive_nums = 0;
// 	int close_parentheses = 0;
// 	int nums_left = 0;
// 	string previous_op;
// 	while (close_parentheses != num_ops) {
// 		for (int j = 0; j < tab_count && !ops.empty(); j++){
// 			cout << "\t";
// 		}
// 		if (isOperator(ops.front()) && !ops.empty()) {
// 			cout << "(" << ops.front() << endl;
// 			tab_count++;
// 			consecutive_nums = 0;
// 			previous_op = ops.front();
// 		}
// 		if (isNum(ops.front()) && !ops.empty()) {
// 			cout << ops.front() << endl;
// 			consecutive_nums++;
// 		}
// 		if ((consecutive_nums == 2 && isBinaryOperator(previous_op)) || (consecutive_nums == 1 && !isBinaryOperator(previous_op)) || ops.empty()) { 
// 			consecutive_nums = 0;
// 			if (tab_count > 0) {
// 				tab_count--;
// 			}
// 			for (int j = 0; j < tab_count; j++){
// 				cout << "\t";
// 			}
// 			cout << ")" << endl;
// 			close_parentheses++;
// 			if (tab_count > 0) {
// 				tab_count--;
// 				for (int j = 0; j < tab_count; j++){
// 					cout << "\t";
// 				}
// 				cout << ")" << endl;
// 				close_parentheses++;
// 			}
// 		}
// 		if (!ops.empty()) {
// 			ops.erase(ops.begin());
// 		}
// 	}
// }

int main() {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"}; 
	// string test[] = {"2", "3", "4", "5", "-", "/", "+"};
	// string test[] = {"1", "2", "3", "4", "+", "-", "5", "6", "7", "+", "-", "+", "-"};
	// string test[] = {"2.4", "<"}; 
	// string test[] = {"6", "0", "/"};
	// string test[] = {"6", "dd"};
	// string test[] = {"1", "2", "3", "+", "4", "5", "6", "*", "/", "7", ">", "+", "8", "9", "1", "<", "-", "-", "+", "/", "*"};

	try {
		validateStrings(test, sizeof(test)/sizeof(test[0]));
	} catch (const char *except) {
		cout << "Exception: " << except << endl;
	}
	double result;
	try {
		result = rpn(test, sizeof(test)/sizeof(test[0]));
		cout << result << endl;
	} catch (const char *except) {
		cout << "Exception: " << except << endl;
	}
	
	stack<string> testvec;
	int num_operands = countOperands(test, sizeof(test)/sizeof(test[0]));
	determineOrder(test, sizeof(test)/sizeof(test[0]), testvec, num_operands);
	istringstream ss(testvec.top());
	int num_ops = countOperators(test, sizeof(test)/sizeof(test[0]));
	// printParentheses(test, sizeof(test)/sizeof(test[0]), testvec, num_ops);
	return 0;
}