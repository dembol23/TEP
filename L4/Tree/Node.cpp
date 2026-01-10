#include "Node.h"

#include <map>
#include <ostream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <utility>

#include "Tree.h"
#include "../Result/Result.hpp"

const std::string Node::NO_VARIABLE_VALUE_ERROR = "[Błąd wartości zmiennej]";
const std::string Node::WRONG_CHILDREN_NUMBER_ERROR = "[Błąd liczby dzieci operatora]";
const std::string Node::UNKNOWN_OPERATOR_ERROR = "[Nieznany operator]";
const std::string Node::DIVIDING_BY_ZERO_ERROR = "[Dzielenie przez 0]";

void Node::swap(Node& other) {
    std::swap(value, other.value);
    std::swap(type, other.type);
    children.swap(other.children);
}

Node::Node() : type(NODE_UNKNOWN) {}

Node::Node(std::string  value, const nodeType type)
    : value(std::move(value)), type(type) {}

Node::Node(const Node &other) : value(other.value), type(other.type) {
    std::cout << "--- COPY Node: " << value << std::endl;
    for (const auto & i : other.children) {
        children.push_back(SmartPointer<Node>(new Node(*i)));
    }
}

Node& Node::operator=(const Node &other) {
    if (this != &other) {
        Node temp(other);
        this->swap(temp);
    }
    return *this;
}

Node::~Node() = default;

Result<double, Error> Node::evaluate(const std::map<std::string, double> &vars) const {
    switch (type) {
        case NODE_CONSTANT: return Result<double, Error>::success(std::atof(value.c_str()));

        case NODE_VARIABLE: {
            const auto it = vars.find(value);
            if (it != vars.end()) return Result<double, Error>::success(it->second);
            std::stringstream errSS;
            errSS << NO_VARIABLE_VALUE_ERROR << ": Brak wartości dla zmiennej: " << value;
            return Result<double, Error>::fail(new Error(errSS.str()));
        }

        case NODE_OPERATOR_BINARY: {
            if (children.size() < 2) return Result<double, Error>::fail(new Error(WRONG_CHILDREN_NUMBER_ERROR));
            Result<double, Error> result1 = children[0]->evaluate(vars);
            if (!result1.isSuccess()) return Result<double, Error>::fail(result1.getErrors());
            Result<double, Error> result2 = children[1]->evaluate(vars);
            if (!result2.isSuccess()) return Result<double, Error>::fail(result2.getErrors());

            if (value == "+") return Result<double, Error>::success(result1.getValue() + result2.getValue());
            if (value == "-") return Result<double, Error>::success(result1.getValue() - result2.getValue());
            if (value == "*") return Result<double, Error>::success(result1.getValue() * result2.getValue());
            if (value == "/") return divide(result1.getValue(), result2.getValue());
            return Result<double, Error>::fail(new Error(UNKNOWN_OPERATOR_ERROR + ": " + value));
        }

        case NODE_OPERATOR_UNARY: {
            if (children.empty()) return Result<double,Error>::fail(new Error(WRONG_CHILDREN_NUMBER_ERROR));
            Result<double, Error> result1 = children[0]->evaluate(vars);
            if (!result1.isSuccess()) return Result<double, Error>::fail(result1.getErrors());
            if (value == "sin") return Result<double, Error>::success(std::sin(result1.getValue()));
            if (value == "cos") return Result<double, Error>::success(std::cos(result1.getValue()));
            return Result<double, Error>::fail(new Error(UNKNOWN_OPERATOR_ERROR + ": " + value));
        }

        default: return Result<double, Error>::fail(new Error(UNKNOWN_OPERATOR_ERROR + ": " + value));
    }
}

Result<double, Error> Node::divide(double dividend, double divisor) {
    if (divisor == 0) {
        return Result<double, Error>::fail(new Error(DIVIDING_BY_ZERO_ERROR));
    }
    return Result<double, Error>(dividend/divisor);
}

std::string Node::print() const {
    return printPrefixRecursive(this);
}

std::string Node::printPrefixRecursive(const Node* node) {
    if (node == nullptr) return "";

    std::stringstream ss;
    ss << node->getValue() << " ";

    const std::vector<SmartPointer<Node> >& children = node->getChildren();
    for (const auto & i : children) {
        ss << printPrefixRecursive(&(*i));
    }
    return ss.str();
}