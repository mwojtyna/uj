#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using operator_t = char;
using num_t = int64_t;

class Calculator {
public:
    std::vector<std::string> infixToONP(std::vector<std::string>& infix) {
        std::vector<std::string> onp;
        std::vector<operator_t> operatorStack;

        for (const std::string& token : infix) {
            // 1. Handling Operators
            if (isOperator(token)) {
                operator_t currentOp = token[0];

                while (!operatorStack.empty()) {
                    operator_t topOp = operatorStack.back();

                    if (topOp == '(') {
                        break;
                    }

                    int currentPriority = operatorPriority[currentOp];
                    int topPriority = operatorPriority[topOp];

                    // '^' and '~' are right-associative, others are left-associative.
                    bool isRightAssociative = (currentOp == '^' || currentOp == '~');

                    if ((isRightAssociative && topPriority > currentPriority) ||
                        (!isRightAssociative && topPriority >= currentPriority)) {
                        onp.emplace_back(std::string{topOp});
                        operatorStack.pop_back();
                    } else {
                        break;
                    }
                }
                operatorStack.push_back(currentOp);
            }
            // 2. Handling Left Parenthesis
            else if (token == "(") {
                operatorStack.push_back('(');
            }
            // 3. Handling Right Parenthesis
            else if (token == ")") {
                while (!operatorStack.empty() && operatorStack.back() != '(') {
                    onp.emplace_back(std::string{operatorStack.back()});
                    operatorStack.pop_back();
                }
                // Pop the remaining '('
                if (!operatorStack.empty()) {
                    operatorStack.pop_back();
                }
            }
            // 4. Handling operands
            else {
                onp.emplace_back(token);
            }
        }

        // 5. Pop remaining operators from stack
        while (!operatorStack.empty()) {
            onp.emplace_back(std::string{operatorStack.back()});
            operatorStack.pop_back();
        }

        return onp;
    }

    num_t calculateONP(std::vector<std::string> onp) {
        std::vector<num_t> stack;

        for (std::string& token : onp) {
            if (isOperator(token)) {
                if (token == "~") {
                    // Unary operator: 1 operand
                    num_t val = stack.back();
                    stack.pop_back();
                    stack.push_back(-val);
                } else {
                    // Binary operators: 2 operands
                    num_t b = stack.back(); // Right operand
                    stack.pop_back();
                    num_t a = stack.back(); // Left operand
                    stack.pop_back();

                    stack.push_back(applyOperator(a, b, token[0]));
                }
            } else {
                // It's a number
                stack.push_back(std::stoll(token));
            }
        }

        return stack.empty() ? 0 : stack.back();
    }

private:
    bool isOperator(std::string_view token) {
        if (token.size() == 1) {
            if (operatorPriority.find(token[0]) != operatorPriority.end()) {
                return true;
            }
        }

        return false;
    }

    num_t applyOperator(num_t a, num_t b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            case '^':
                return std::pow(a, b);
            default:
                throw std::runtime_error("Operator '" + std::string{op} + "' not recognized");
        }
    }

    std::unordered_map<operator_t, int> operatorPriority = {
        {'^', 4}, {'~', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1},
    };
};

std::vector<std::string> readInfix() {
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<std::string> infix;
    std::string token;
    while (std::getline(ss, token, ' ')) {
        infix.emplace_back(token);
    }

    return infix;
}

int main() {
    std::cout << "Podaj wyrażenie w notacji tradycyjnej: ";
    std::vector<std::string> infix = readInfix();

    Calculator calc;
    std::vector<std::string> onp = calc.infixToONP(infix);
    num_t result = calc.calculateONP(onp);

    std::cout << "ONP:";
    for (std::string& token : onp) {
        std::cout << " " << token;
    }
    std::cout << std::endl;

    std::cout << "Wynik: " << result << std::endl;

    return 0;
}
