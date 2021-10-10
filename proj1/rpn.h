#include <string>
#include <vector>
#include <stack>
#include <math.h>
#include <array>
#include <iostream>
using namespace std;

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

double rpn(string strs[], size_t size) {
	double result = 0.0;

	std::stack<float> nums;
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

void printParentheses(string *strs, size_t size);