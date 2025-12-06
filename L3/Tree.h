#ifndef L3_TREE_H
#define L3_TREE_H
#include <set>
#include <map>
#include <queue>

#include "Node.h"

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
private:
    Node* root;
    std::map<std::string, double> variables;
    void updateVariables();
    void updateVariablesRecursive(const Node* node);
    static Node* buildTree(std::queue<std::string> *queue);
    void join(const Tree& other);
    static std::string printPrefixRecursive(const Node *node);
public:
    Tree();
    Tree(const Tree &other);
    ~Tree();
    Tree& operator=(const Tree &other);
    Tree operator+(const Tree &other) const;
    std::string enter(const std::string &formula);
    std::string vars();
    double comp(const std::string &formula);
    std::string join(const std::string &formula);
    std::string print() const;
};


#endif //L3_TREE_H