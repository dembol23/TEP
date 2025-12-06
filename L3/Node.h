#ifndef L3_NODE_H
#define L3_NODE_H
#include <map>
#include <string>

enum nodeType {
    NODE_UNKNOWN,
    NODE_OPERATOR_BINARY,
    NODE_OPERATOR_UNARY,
    NODE_VARIABLE,
    NODE_CONSTANT
};

class Node {
private:
    std::string value;
    nodeType type;
    std::vector<Node*> children;
    void swap(Node &other);

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
    double evaluate(const std::map<std::string, double> &vars) const;
    void replaceChild(const int index, Node* newChild) {
        if (index < children.size()) {
            delete children[index];
            children[index] = newChild;
        }
    }
};

#endif //L3_NODE_H