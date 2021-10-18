#include <string>
#include <stack>
#include <math.h>
#include <string.h>
#include <sstream>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <exception>
using namespace std;

bool isDouble(string val);
bool isOperator(string op);
bool isBinaryOperator(string op);
bool isMultiplication(string op);
bool isExponent(string op);
bool isSubtraction(string op);
bool isDivision(string op);
bool isAddition(string op);
bool isFloor(string op);
bool isCeiling(string op);
void validateStrings(string *ops, int size);
void validatePostfixOrder(string *ops, int size);
void determinePrintingOrder(string *strs, int size, stack<string> &ops_stack);
double rpn(string strs[], int size);
void printPostfix(string new_order);