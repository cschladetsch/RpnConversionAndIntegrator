# An infix to RPN converter and integrator

## Problem Overview

Write a C++20 program that converts mathematical expressions from standard infix notation to Reverse Polish Notation (RPN) and then calculates the definite integral over various ranges. 

This task encompasses parsing input expressions, handling operator precedence, and implementing a user-friendly Read-Eval-Print Loop (REPL) for user interaction.

The program should be versatile, accommodating a variety of mathematical expressions that include supported operations and a single independent variable, `x`. 

The goal is to develop an efficient program for converting natural in-fix expressions to RPN and systematically evaluating them to calculate the integral of the function in a given range.
## Requirements

1. **Implementation in C++**:
    - Develop a C++ program that performs the following core tasks:
    - Accept a mathematical function in standard infix notation as input, encompassing supported operations and an independent variable 'x.'
    - Convert the input function into its equivalent Reverse Polish Notation (RPN) representation.
    - Evaluate the RPN expression repeatedly to calculate the value of the integral over a user-provided range of values for 'x.'
    - Assume all input is valid.
    - Still trap for mathematical errors like division by zero. In this case, report and error and continue processing.
1. **Supported Operations**:
    - The program supports the following mathematical operations:
		* Addition `+`, subtraction `-`, multiplication `*`, division, `\`, and exponentiation `^`.
	 * Add a place-holder `Operation` enumeration value for the independent variable `x`.	
	* There is no requirement to support parenthesis or any other functions or operations.
2. **User Interaction**:
    - Prompt the user to input a mathematical function in standard infix notation (e.g., 'x + x \* 2 - x ^ 4').
	* All tokens are separated by at least one whitespace character.
    - The program assumes that the independent variable is always 'x.'
	* The program terminates without error if no input expression is provided by the user.
    - Continuously prompt the user to enter the range of integration (start and end values, separated by whitespace).
    - The program should enter and continue the REPL loop until the user stops the problem by sending SIGINT (i.e., Ctrl-C).
3. **Number Type**:
    - Ensure that all numbers used in the program are of the double data type, adhering to IEEE 754 double-precision format.
    - All numbers in the input expression are greater than or equal to zero `0` and are also interpreted as `doubles`.
    - Negative numbers are not supported.
4. **Token**  is a `std::variant<double, Operation>`, where the `Operation` is an enumeration of the supported operations as described above. 
5. **Conversion to RPN**:
	* Assume all provided functions are well-formed.
    - Implement the conversion of the input function to RPN using a stack-based algorithm.
    - Handle operator precedence according to standard mathematics. Specifically:
	    - Multiplication and Division are performed from left to right.
	    - Addition and Subtraction are also performed from left to right.
	* The result of the conversion is a `std::vector<Token>`
	* Print the converted RPN expression to `stdout`
6. **Evaluation of RPN Expression**:
    - Evaluate the RPN expression over the defined range of values for `x`.
    - Use a `stack<>` to perform the necessary calculations.
    - Implement error handling for these errors:
	    - Undefined or unhandled mathematical operations.
	    - Division by zero.
7. **Output**:
    - Display only the value of the integration result in IEEE 754 double-precision format.
    - Format the output for clarity and readability.
8. **Continuous Loop (REPL)**:
    - Create a continuous Read-Eval-Print Loop (REPL) that enables users to perform multiple evaluations with different functions and ranges without restarting the program.
	* The REPL terminates when no input is provided by the user for the expression, or sends SIGINT.
## Notes

Use best practice C++20 when generating the code. The code should be well structured, and avoiding long functions and high cyclomatic complexity. Use `std::views` and other C++20 libraries to do this.

This is a non-trivial task. The programmer should also write extensive test cases, which are not  to be included in the generated code for brevity.

Add comments only as needed to clarify what a beginner may find confusing.

Use std::copy and std::transform to reduce loop statements.

To be clear, valid input tokens are:
* `*` `/` `+` `-` `^` `x`
* A `double` value represented as a string.
## Sample Output

Here are two examples of the expected output from the program, using two different input functions

```
Enter a mathematical function: x + 2 / x + 3.14
RPN: x 2 x / + 3.14 +
Enter the range of integration: 1 5
Result: 40.74
Enter the range of integration:
```

```
Enter a mathematical function:  2 * x ^ 2 - 5 * x + 8
RPN: 2 x 2 ^ * 5 x * - 8 +
Enter the range of integration: 0 2
Result: 11.333
Enter the range of integration: 1 3 
Result: 13.3333
Enter the range of integration: 2 4 
Result: 23.373
Enter the range of integration:


