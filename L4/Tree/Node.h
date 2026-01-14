#pragma once
#include <map>
#include <string>
#include <utility>

#include "../Result/Result.hpp"
#include "../Error/Error.h"
#include "../../L5/SmartPointer/SmartPointer.h"

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
    Node(std::string  value, nodeType type);
    Node(const Node &other);
    Node &operator=(const Node &other);
    ~Node();
    nodeType getNodeType() const { return type; }
    const std::string& getValue() const { return value; }
    void addChild(const SmartPointer<Node>& child) { children.emplace_back(child); }
    const std::vector<SmartPointer<Node> >& getChildren() const { return children; }
    Result<double, Error> evaluate(const std::map<std::string, double> &vars) const;
    void replaceChild(const int index, SmartPointer<Node> newChild) {
        if (index < children.size()) {
            children[index] = std::move(newChild);
        }
    }
    static const std::string NO_VARIABLE_VALUE_ERROR;
    static const std::string WRONG_CHILDREN_NUMBER_ERROR;
    static const std::string UNKNOWN_OPERATOR_ERROR;
    static const std::string DIVIDING_BY_ZERO_ERROR;
private:
    std::string value;
    nodeType type;
    std::vector<SmartPointer<Node> > children;
    void swap(Node &other) noexcept;
    static Result<double, Error> divide(double dividend, double divisor);
};