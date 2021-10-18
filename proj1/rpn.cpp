#include "rpn.h"
#include <iostream>

bool isDouble(string val) {
	bool isDouble;
	double double_num;
	try {
		double_num = stod(val);
		isDouble = true;
	} catch (const invalid_argument& ia) {
		isDouble = false;
	}
	return isDouble;
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
	for (int i = 0; i < 5; i++) {
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

/* Ensures that the strings are only valid operators or operands */
void validateStrings(string *ops, int size) {
	for (int i = 0; i < size; i++) {
		if(!isOperator(ops[i]) && !isDouble(ops[i])) {
			throw invalid_argument("Invalid operator(s)/operand(s) detected");
		}
	}
}

/* Used https://stackoverflow.com/questions/789847/postfix-notation-validation 
 for reference */
void validatePostfixOrder(string *ops, int size) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (isDouble(ops[i])) {
			counter++;
		} else if (!isBinaryOperator(ops[i])) {
			counter--;
		} else {
			counter -= 2;
		}

		if (counter < 0) {
			throw invalid_argument("Invalid postfix sequence");
		}
		if (isOperator(ops[i])) {
			counter++;
		}
	}
}

/* Very similar to rpn, but rather than solving operations, creates string */
void determinePrintingOrder(string *strs, int size, stack<string> &ops_stack) {
	for (int i = 0; i < size; i++) {
		string operand1;
		string op;
		if (isDouble(strs[i])) {
			ops_stack.push(strs[i]);
		} else if (!isBinaryOperator(strs[i])) {
			operand1 = ops_stack.top();
			ops_stack.pop();
			string temp = "(" + strs[i] + " " + operand1 + " " + ")";
			ops_stack.push(temp);
		} else {
			string operand2;
			operand1 = ops_stack.top();
			ops_stack.pop();
			operand2 = ops_stack.top();
			ops_stack.pop();
			string temp = "(" + strs[i] + " " + operand2 + " " + operand1 + " " + ")";
			ops_stack.push(temp);
		}
	}
}

double rpn(string strs[], int size) {
	double result = 0.0;
	stack<double> nums;
	for (int i = 0; i < size; i++) {
		if (isDouble(strs[i])) {
			nums.push(stof(strs[i]));
		} else {
			double first_operand = nums.top();
			nums.pop();
			if (isFloor(strs[i])) {
				nums.push(floor(first_operand));
			} else if (isCeiling(strs[i])) {
				nums.push(ceil(first_operand));
			} else {
				double second_operand = nums.top();
				nums.pop();
				if (isAddition(strs[i])) {
					nums.push(second_operand + first_operand);
				} else if (isSubtraction(strs[i])) {
					nums.push(second_operand - first_operand);
				} else if (isMultiplication(strs[i])) {
					nums.push(second_operand * first_operand);
				} else if (isDivision(strs[i])) {
					if (first_operand == 0) {
						throw domain_error("Division by zero");
					} else {
						nums.push(second_operand / first_operand);
					}
				} else if (isExponent(strs[i])) {
					int test_int = first_operand;
					double test_double = first_operand - test_int;
					if ((second_operand == 0 && first_operand == 0) || 
						(second_operand == 0 && first_operand < 0) ||
						(second_operand < 0 && test_double > 0)) {
						throw domain_error("Exponentiation issue- invalid operand(s)");
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

void printPostfix(string new_order) {
	int tab_count = 0;
	istringstream ss(new_order);
	string temp;
	while (ss >> temp) {
		if (temp[0] == ')') {
			tab_count--;
		}
		for (int i = 0; i < tab_count; i++) {
			cout << "\t";
		}
		cout << temp << endl;
		if (temp[0] == '(') {
			tab_count++;
		}
	}
}

int main(int argc, char *argv[]) {
	string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
	int test_length = sizeof(test)/sizeof(test[0]);
	double result;
	try {
		validateStrings(test, test_length);
		validatePostfixOrder(test, test_length);
		result = rpn(test, test_length);
		cout << "Result: " << result << endl;
		if (argc == 2 && string(argv[1]) == "-l") {
			stack<string> printing_vec;
			determinePrintingOrder(test, test_length, printing_vec);
			printPostfix(printing_vec.top());
		}
	} catch (exception &except) {
		cout << "Exception: " << except.what() << endl;
	}
	return 0;
}