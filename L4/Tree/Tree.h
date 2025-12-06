#pragma once
#include <set>
#include <map>
#include <queue>

#include "Node.h"
#include "../Error/Error.h"
#include "../Result/Result.hpp"

inline std::set<std::string> binaryOperatorsInit() {
    std::set<std::string> op;
    op.insert("+");
    op.insert("-");
    op.insert("*");
    op.insert("/");
    return op;
}
static const std::set<std::string> BINARY_OPERATORS = binaryOperatorsInit();

inline std::set<std::string> unaryOperatorsInit() {
    std::set<std::string> op;
    op.insert("sin");
    op.insert("cos");
    return op;
}
static const std::set<std::string> UNARY_OPERATORS = unaryOperatorsInit();

class Tree {
public:
    Tree();
    Tree(const Tree &other);
    ~Tree();
    Tree& operator=(const Tree &other);
    Tree operator+(const Tree &other) const;
    Result<void, Error> enter(const std::string &formula);
    std::string vars();
    Result<double, Error> comp(const std::string &formula);
    Result<void, Error> join(const std::string &formula);
    std::string print() const;
    Result<Node*, Error> getTreeAsResult() const;

    static const std::string TREE_BUILD_ERROR;
    static const std::string UNKNOWN_ARGUMENT_ERROR;
    static const std::string ENTER_ERROR;
    static const std::string EMPTY_TREE_ERROR;
    static const std::string INVALID_NUM_OF_ARGS_ERROR;
private:
    Node* root;
    std::map<std::string, double> variables;
    void updateVariables();
    void updateVariablesRecursive(const Node* node);
    static Result<Node*, Error> buildTree(std::queue<std::string> *queue);
    Result<void, Error> join(const Tree& other);
    static std::string printPrefixRecursive(const Node *node);
};