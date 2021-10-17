#include <string>
#include <stack>
#include <math.h>
#include <string.h>
#include <sstream>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <exception>
using namespace std;

bool isNum(string val);
bool isOperator(string op);
int countOperators(string *ops, int size);
int countOperands(string *ops, int size);
bool isBinaryOperator(string op);
bool isMultiplication(string op);
bool isExponent(string op);
bool isSubtraction(string op);
bool isDivision(string op);
bool isAddition(string op);
bool isFloor(string op);
bool isCeiling(string op);
void validateStrings(string *ops, int size);

void determineOrder(string *strs, int size, stack<string> &ops, int num_operands);
double rpn(string strs[], int size);
// void printParentheses(string *strs, int size, stack<vector<string>> &ops, int num_ops);