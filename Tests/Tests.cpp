#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Calculator.hpp"

using Calc = Calculator<double>;

TEST_CASE("Conversion to RPN handles edge cases correctly") {
    Calc calculator;

    SECTION("Empty expression") {
        std::string expression = "";
        Calc::Tokens rpn = calculator.convertToRPN(expression);
        REQUIRE(rpn.empty());
    }

    SECTION("Expression with only one token") {
        std::string expression = "x";
        Calc::Tokens rpn = calculator.convertToRPN(expression);
        REQUIRE(rpn.size() == 1);
        REQUIRE(std::get<Calc::Operation>(rpn[0]) == Calc::Operation::VariableX);
    }
}

TEST_CASE("Evaluation of RPN expressions handles edge cases correctly") {
    Calc calculator;

    SECTION("Empty RPN expression") {
        Calc::Tokens rpn = {};
        double result = calculator.evaluateRPN(rpn, 0);
        REQUIRE(result == 0.0);
    }
}

TEST_CASE("Integration calculation handles edge cases correctly") {
    Calc calculator;
    Calc::Tokens rpn = { 1.0, 2.0, Calc::Operation::Multiplication };

    SECTION("Integration over a single point") {
        double result = calculator.calculateIntegral(rpn, 0, 0, 1000);
        REQUIRE(result == Approx(0.0));
    }

    SECTION("Integration over a zero interval") {
        double result = calculator.calculateIntegral(rpn, 0, 0, 1000);
        REQUIRE(result == Approx(0.0));
    }

    SECTION("Integration over a negative interval") {
        double result = calculator.calculateIntegral(rpn, -1, 1, 1000);
        REQUIRE(result == Approx(4.0));
    }
}

TEST_CASE("Conversion to RPN works correctly") {
    Calc calculator;

    SECTION("Basic arithmetic expression") {
        std::string expression = "2 + 3 * x";
        Calc::Tokens rpn = calculator.convertToRPN(expression);
        REQUIRE(rpn.size() == 5);
        REQUIRE(calculator.evaluateRPN(rpn, 4) == 14.0);
    }

    SECTION("Expression with exponentiation") {
        std::string expression = "x ^ 2 + 3 * x";
        Calc::Tokens rpn = calculator.convertToRPN(expression);
        REQUIRE(rpn.size() == 7);
        REQUIRE(std::get<Calc::Operation>(rpn[2]) == Calc::Operation::Exponentiation);
    }
}

TEST_CASE("Evaluation of RPN expressions works correctly") {
    Calc calculator;
    Calc::Tokens rpn = { 2.0, 3.0, Calc::Operation::Multiplication };

    SECTION("Basic arithmetic operation") {
        double result = calculator.evaluateRPN(rpn, 0);
        REQUIRE(result == 6.0);
    }
}

TEST_CASE("Integration calculation works correctly") {
    Calc calculator;
    Calc::Tokens rpn = { 1.0, 2.0, Calc::Operation::Multiplication };

    SECTION("Integration over a small range") {
        double result = calculator.calculateIntegral(rpn, 0, 1, 1000);
        REQUIRE(result == Approx(2.0));
    }

    SECTION("Integration over a large range") {
        double result = calculator.calculateIntegral(rpn, 0, 10, 1000);
        REQUIRE(result == Approx(20.02));
    }
}

TEST_CASE("Evaluation of RPN expressions handles additional cases correctly") {
    Calc calculator;
    Calc::Tokens rpn = { 2.0, 3.0, Calc::Operation::Division };

    SECTION("Expression with division") {
        double result = calculator.evaluateRPN(rpn, 0);
        REQUIRE(result == Approx(0.66667).epsilon(0.001)); // Approximate due to floating point precision
    }
}

TEST_CASE("Integration calculation handles additional cases correctly") {
    Calc calculator;
    Calc::Tokens rpn = { 1.0, 2.0, Calc::Operation::Multiplication };

    SECTION("Integration over a larger step size") {
        double result = calculator.calculateIntegral(rpn, 0, 1, 10);
        REQUIRE(result == Approx(1.5));
    }

    SECTION("Integration over a negative range") {
        double result = calculator.calculateIntegral(rpn, -1, 0, 1000);
        REQUIRE(result == Approx(-0.5));
    }
}
