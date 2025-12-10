#pragma once
#include <map>
#include <string>

#include "../Result/Result.hpp"
#include "../Error/Error.h"

enum nodeType {
    NODE_UNKNOWN,
    NODE_OPERATOR_BINARY,
    NODE_OPERATOR_UNARY,
    NODE_VARIABLE,
    NODE_CONSTANT
};

class Node {
public:
    Node();
    Node(const std::string& value, nodeType type);
    Node(const Node &other);
    Node &operator=(const Node &other);
    ~Node();
    nodeType getNodeType() const { return type; }
    const std::string& getValue() const { return value; }
    void addChild(Node* child) { children.push_back(child); }
    const std::vector<Node*>& getChildren() const { return children; }
    Result<double, Error> evaluate(const std::map<std::string, double> &vars) const;
    void replaceChild(const int index, Node* newChild) {
        if (index < children.size()) {
            delete children[index];
            children[index] = newChild;
        }
    }
    std::string print() const;
    static const std::string NO_VARIABLE_VALUE_ERROR;
    static const std::string WRONG_CHILDREN_NUMBER_ERROR;
    static const std::string UNKNOWN_OPERATOR_ERROR;
    static const std::string DIVIDING_BY_ZERO_ERROR;
private:
    std::string value;
    nodeType type;
    std::vector<Node*> children;
    void swap(Node &other);
    static Result<double, Error> divide(double dividend, double divisor);
    static std::string printPrefixRecursive(const Node* node);
};