#include <string>
#include <stack>
#include <math.h>
#include <array>
#include <vector>
#include <iostream>
using namespace std;

bool isNum(string val);
bool isOperator(string op);
bool isBinaryOperator(string op);
bool isMultiplication(string op);
bool isExponent(string op);
bool isSubtraction(string op);
bool isDivision(string op);
bool isAddition(string op);
bool isFloor(string op);
bool isCeiling(string op);

void determineOrder(string *strs, int size, vector<string> &ops);
double rpn(string strs[], int size);
void printParentheses(string *strs, int size, vector<string> &ops, int num_ops);