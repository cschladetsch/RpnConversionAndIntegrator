#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <variant>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <limits>
#include <unordered_map>
#include <type_traits>
#include <functional>

template <typename Number>
concept FloatingPoint = std::is_floating_point_v<Number>;

template <FloatingPoint Number>
class Calculator {
public:
    enum class Operation { Addition, Subtraction, Multiplication, Division, Exponentiation, VariableX };
    using Token = std::variant<Number, Operation>;
    using Tokens = std::vector<Token>;
    using OperationFunction = std::function<Number(Number, Number)>;

    Calculator() = default;

    int getPrecedence(Operation op) {
        if (op == Operation::Addition || op == Operation::Subtraction)
            return 1;
        if (op == Operation::Multiplication || op == Operation::Division)
            return 2;
        if (op == Operation::Exponentiation)
            return 3;
        return 0;
    }

    Tokens convertToRPN(const std::string& expression) {
        std::istringstream input(expression);
        std::stack<Operation> operatorStack;
        Tokens outputQueue;

        std::string token;
        while (input >> token) {
            if (token == "x") {
                outputQueue.push_back(Operation::VariableX);
            }
            else if (operatorMap.count(token)) {
                Operation currentOp = operatorMap.at(token);

                while (!operatorStack.empty() &&
                    getPrecedence(operatorStack.top()) >= getPrecedence(currentOp)) {
                    outputQueue.push_back(operatorStack.top());
                    operatorStack.pop();
                }

                operatorStack.push(currentOp);
            }
            else {
                double number = std::stod(token);
                outputQueue.push_back(number);
            }
        }

        while (!operatorStack.empty()) {
            outputQueue.push_back(operatorStack.top());
            operatorStack.pop();
        }

        return outputQueue;
    }


    Number evaluateRPN(const Tokens& rpn, Number x) {
        std::stack<Number> operandStack;

        for (const Token& token : rpn) {
            if (std::holds_alternative<Number>(token)) {
                operandStack.push(std::get<Number>(token));
            }
            else {
                Operation op = std::get<Operation>(token);
                if (op == Operation::VariableX) {
                    operandStack.push(x);
                }
                else {
                    Number operand2 = operandStack.top();
                    operandStack.pop();
                    Number operand1 = operandStack.top();
                    operandStack.pop();
                    Number result = operationFunctions[op](operand1, operand2);
                    operandStack.push(result);
                }
            }
        }

        if (operandStack.size() != 1) {
            std::cerr << "Error: Invalid expression" << std::endl;
            return Number(0);
        }

        return operandStack.top();
    }

    Number calculateIntegral(const Tokens& rpn, Number a, Number b, int numSteps) {
        Number step = (b - a) / Number(numSteps);
        Number result = Number(0);

        for (Number x = a; x < b; x += step) {
            Number f0 = evaluateRPN(rpn, x);
            Number f1 = evaluateRPN(rpn, x + step);
            result += (f0 + f1) * step / Number(2);
        }

        return result;
    }

    void printRPN(const Tokens& rpn) {
        std::cout << "RPN Expression: ";
        for (const Token& token : rpn) {
            if (std::holds_alternative<Number>(token)) {
                std::cout << std::get<Number>(token) << " ";
            }
            else {
                Operation op = std::get<Operation>(token);
                std::cout << operatorToString[op] << " ";
            }
        }
        std::cout << std::endl;
    }

private:
    std::unordered_map<Operation, std::string> operatorToString = {
        {Operation::Addition, "+"},
        {Operation::Subtraction, "-"},
        {Operation::Multiplication, "*"},
        {Operation::Division, "/"},
        {Operation::Exponentiation, "^"},
        {Operation::VariableX, "x"}
    };
    std::unordered_map<std::string, Operation> operatorMap = {
        {"+", Operation::Addition},
        {"-", Operation::Subtraction},
        {"*", Operation::Multiplication},
        {"/", Operation::Division},
        {"^", Operation::Exponentiation},
        {"x", Operation::VariableX}
    };
    std::unordered_map<Operation, OperationFunction> operationFunctions = {
        {Operation::Addition, [](Number a, Number b) { return a + b; }},
        {Operation::Subtraction, [](Number a, Number b) { return a - b; }},
        {Operation::Multiplication, [](Number a, Number b) { return a * b; }},
        {Operation::Division, [](Number a, Number b) {
            if (b == Number(0)) {
                std::cerr << "Error: Division by zero" << std::endl;
                return Number(0);
            }
            return a / b;
        }},
        {Operation::Exponentiation, [](Number a, Number b) { return std::pow(a, b); }}
    };
};

int main() {
    Calculator<double> calculator;
    std::cout << std::setprecision(5);

    std::string expression;
    std::cout << "Enter a function: ";
    std::getline(std::cin, expression);
    Calculator<double>::Tokens rpn = calculator.convertToRPN(expression);
    calculator.printRPN(rpn);

    while (true) {
        double start, end;
        std::cout << "Enter the range of integration: ";
        std::cin >> start >> end;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        const int NumSteps = 1000;
        double result = calculator.calculateIntegral(rpn, start, end, NumSteps);
        std::cout << "The integral is: " << result << std::endl;
    }

    return 0;
}
