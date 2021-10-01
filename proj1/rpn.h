#include <string>
#include <vector>
#include <stack>
#include <math.h>
using namespace std;

double rpn(string strs[]) {
	double result = 0.0;

	std::stack<float> nums;
	for (unsigned int i = 0; i < sizeof(strs)/sizeof(strs[0]); i++) {
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
				float second_operand = nums.top();
				nums.pop();
				if (isAddition(strs[i])) {
					nums.push(first_operand + second_operand);
				} else if (isSubtraction(strs[i])) {
					nums.push(first_operand - second_operand);
				} else if (isMultiplication(strs[i])) {
					nums.push(first_operand * second_operand);
				} else if (isDivision(strs[i])) {
					nums.push(first_operand / second_operand);
				} else if (isExponent(strs[i])) {
					nums.push(pow(first_operand, second_operand));
				}
			}
		}
	}
	result += nums.top();
	return result;
}

bool isNum(string val) {
	if (int(val[0]) >= 48 && int(val[0]) < 58) {
		return true;
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