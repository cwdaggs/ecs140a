Compilation:
Compile the code using this command in the terminal: g++ -o rpn rpn.cpp
This will have to be recompiled for every test case that is input.

Running the Program:
Then run the program using: ./rpn
This can be run with the -l option as well: ./rpn -l
The rpn result will still be printed when the -l option is used.

Testing:
In the main function in rpn.cpp, change the string array "test" to whatever 
array of strings that you want tested. Refer to above for recompilation.
Examples:
string test[] = {"2", "3", "4", "5", "-", "/", "+"};
string test[] = {"2.4", "<"}; 
string test[] = {"6", "0", "/"};
string test[] = {"6", "dd"};
string test[] = {"6", "2", "+", "+"};

Errors:
There are errors for invalid postfix sequences, strings that are neither
operators nor operands, and calculation errors for rpn. The calculation errors
cover dividing by 0, 0 to the power of 0, 0 to the power of a negative exponent,
or a negative number to the power of a non-integer. 

Design:
The resulting calculation is computed first before printing in the case of -l
such that any mathematical errors are detected before hand and an exception is 
thrown. This will result in -l only printing when there are no errors.