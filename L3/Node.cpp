#include "Node.h"

#include <iostream>
#include <map>
#include <ostream>
#include <cmath>

void Node::swap(Node& other) {
    std::swap(value, other.value);
    std::swap(type, other.type);
    children.swap(other.children);
}

Node::Node() : type(NODE_UNKNOWN) {}

Node::Node(const std::string& value, const nodeType type)
    : value(value), type(type) {}

Node::Node(const Node &other) : value(other.value), type(other.type) {
    for (size_t i = 0; i < other.children.size(); ++i) {
        Node* childCopy = new Node(*other.children[i]);
        children.push_back(childCopy);
    }
}

Node& Node::operator=(const Node &other) {
    if (this != &other) {
        Node temp(other);
        this->swap(temp);
    }
    return *this;
}

Node::~Node() {
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
    children.clear();
}

double Node::evaluate(const std::map<std::string, double> &vars) const {
    switch (type) {
        case NODE_CONSTANT: return std::atof(value.c_str());

        case NODE_VARIABLE: {
            std::map<std::string, double>::const_iterator it = vars.find(value);
            if (it != vars.end()) return it->second;
            std::cout << "Blad: Brak wartosci dla '" << value << "'. 0." << std::endl;
            return 0.0;
        }

        case NODE_OPERATOR_BINARY: {
            if (children.size() < 2) return 0.0;
            const double value1 = children[0]->evaluate(vars);
            const double value2 = children[1]->evaluate(vars);

            if (value == "+") return value1 + value2;
            if (value == "-") return value1 - value2;
            if (value == "*") return value1 * value2;
            if (value == "/") return (value2 == 0 ? 0 : value1 / value2);
            return 0.0;
        }

        case NODE_OPERATOR_UNARY: {
            if (children.empty()) return 0.0;
            const double value1 = children[0]->evaluate(vars);
            if (value == "sin") return std::sin(value1);
            if (value == "cos") return std::cos(value1);
            return 0.0;
        }

        default: return 0.0;
    }
}