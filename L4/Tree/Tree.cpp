#include "Tree.h"

#include <iostream>
#include <ostream>
#include <sstream>

// constans
const std::string Tree::TREE_BUILD_ERROR = "[Błąd podczas budowy drzewa]";
const std::string Tree::ENTER_ERROR = "[Błąd podczas tokenizacji formuły]";
const std::string Tree::EMPTY_TREE_ERROR = "[Drzewo jest puste]";
const std::string Tree::INVALID_NUM_OF_ARGS_ERROR = "[Błąd liczby argumentów]";
const std::string Tree::UNKNOWN_ARGUMENT_ERROR = "[Podano błędny argument]";


// utils
static bool isNumber(const std::string &s) {
    if (s.empty()) return false;
    for (int i = 0; i < s.length(); ++i) {
        if (!std::isdigit(s[i])) return false;
    }
    return true;
}

static std::string validateVariable(const std::string &s) {
    std::string validName;
    bool hasLetter = false;
    for (int i = 0; i < s.length(); ++i) {
        if (std::isalnum(s[i])) {
            validName += s[i];
            if (std::isalpha(s[i])) {
                hasLetter = true;
            }
        } else {
            std::cout << "Zignorowano niedozwolony znak '" << s[i]
                      << "' w zmiennej '" << s << "'." << std::endl;
        }
    }
    if (hasLetter) {
        return validName;
    }
    return "";
}
// =========

Tree::Tree():root(nullptr) {}

Tree::~Tree() {
    delete root;
}

Tree::Tree(const Tree &other) {
    if (other.root != nullptr)
        root = new Node(*other.root);
    else
        root = nullptr;
}

Tree& Tree::operator=(const Tree &other) {
    if (this != &other) {
        delete root;
        if (other.root != nullptr)
            root = new Node(*other.root);
        else
            root = nullptr;
        updateVariables();
    }
    return *this;
}

Tree Tree::operator+(const Tree &other) const {
    Tree result(*this);
    if (root && other.root) {
        result.join(other);
    }
    return result;
}

Result<void, Error> Tree::enter(const std::string &formula) {
    std::stringstream ss(formula);
    std::string token;
    std::queue<std::string> queue;
    while (ss >> token) {
        queue.push(token);
    }
    if (queue.empty()) {
        return Result<void, Error>::fail(new Error(ENTER_ERROR + ": podano pustą formułę"));
    }
    Result<Node *, Error> node = buildTree(&queue);
    if (!node.isSuccess()) return Result<void, Error>::fail(node.getErrors());

    delete root;
    root = node.getValue();

    if (!queue.empty()) {
        delete root;
        root = nullptr;
        return Result<void, Error>::fail(new Error(ENTER_ERROR + ": podano za dużo argumentów"));
    }

    return Result<void, Error>::success();
}

Result<Node*, Error> Tree::buildTree(std::queue<std::string> *queue) {
    if (queue->empty()) {
        return Result<Node*, Error>::fail(new Error("Brak argumentów"));
    }

    const std::string current_value = queue->front();
    queue->pop();

    if (BINARY_OPERATORS.count(current_value) > 0) {
        Node* node = new Node(current_value, NODE_OPERATOR_BINARY);
        Result<Node*, Error> first = buildTree(queue);
        if (!first.isSuccess()) {
            delete node;
            return Result<Node*, Error>::fail(first.getErrors());
        }
        node->addChild(first.getValue());

        Result<Node*, Error> second = buildTree(queue);
        if (!second.isSuccess()) {
            delete node;
            return Result<Node*, Error>::fail(second.getErrors());
        }
        node->addChild(second.getValue());

        return Result<Node*, Error>::success(node);
    }

    if (UNARY_OPERATORS.count(current_value) > 0) {
        Node* node = new Node(current_value, NODE_OPERATOR_UNARY);

        Result<Node*, Error> first = buildTree(queue);
        if (!first.isSuccess()) {
            delete node;
            return Result<Node*, Error>::fail(first.getErrors());
        }
        node->addChild(first.getValue());

        return Result<Node*, Error>::success(node);
    }

    if (isNumber(current_value)) {
        return Result<Node*, Error>::success(new Node(current_value, NODE_CONSTANT));
    }

    const std::string variable = validateVariable(current_value);
    if (!variable.empty()) {
        return Result<Node*, Error>::success(new Node(variable, NODE_VARIABLE));
    }

    return Result<Node*, Error>::fail(new Error(UNKNOWN_ARGUMENT_ERROR + ": " + current_value));
}

void Tree::updateVariables() {
    variables.clear();
    updateVariablesRecursive(root);
}

void Tree::updateVariablesRecursive(const Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->getNodeType() == NODE_VARIABLE) {
        variables[node->getValue()] = 0.0;
    }
    for (int i = 0; i < node->getChildren().size(); ++i) {
        updateVariablesRecursive(node->getChildren()[i]);
    }
}

std::string Tree::vars() {
    updateVariables();
    if (variables.empty()) {
        return "Brak zmiennych w drzewie";
    }
    std::string result = "Zmienne: ";
    for (std::map<std::string, double>::const_iterator it = variables.begin(); it != variables.end(); ++it)
        result += it->first + " ";
    return result;
}

Result<double, Error> Tree::comp(const std::string& formula) {
    if (root == nullptr) {
        return Result<double, Error>::fail(new Error(EMPTY_TREE_ERROR));
    }
    updateVariables();
    std::stringstream ss(formula);
    double value;
    std::map<std::string, double>::iterator var_it = variables.begin();
    while (ss >> value) {
        if (var_it != variables.end()) {
            var_it->second = value;
            ++var_it;
        } else {
            std::stringstream errSS;
            errSS << INVALID_NUM_OF_ARGS_ERROR << ": Wymagana liczba argumentów: " << variables.size();
            return Result<double, Error>::fail(new Error(errSS.str()));
        }
    }

    if (var_it != variables.end()) {
        std::stringstream errSS;
        errSS << INVALID_NUM_OF_ARGS_ERROR << ": Wymagana liczba argumentów: " << variables.size();
        return Result<double, Error>::fail(new Error(errSS.str()));
    }
    Result<double, Error> result = root->evaluate(variables);
    if (!result.isSuccess()) return Result<double, Error>::fail(result.getErrors());
    return result;
}

Result<void, Error> Tree::join(const std::string &formula) {
    Tree tree;
    Result<void, Error> res = tree.enter(formula);
    if (!res.isSuccess()) {
        return res;
    }
    return join(tree);
}

Result<void, Error> Tree::join(const Tree& other) {
    if (other.root == nullptr) {
        return Result<void, Error>::success();
    }

    if (root == nullptr) {
        root = new Node(*other.root);
        updateVariables();
        return Result<void, Error>::success();
    }

    Node *join_node = root;
    Node *parent = nullptr;
    int childIndex = 0;
    while (join_node != nullptr && join_node->getNodeType() != NODE_VARIABLE && join_node->getNodeType() != NODE_CONSTANT) {
        parent = join_node;
        if (!join_node->getChildren().empty()) {
            join_node = join_node->getChildren()[0];
            childIndex = 0;
        }
        else break;
    }
    Node* newSubTree = new Node(*other.root);
    if (parent != nullptr) {
        parent->replaceChild(childIndex, newSubTree);
    } else {
        delete root;
        root = newSubTree;
    }
    updateVariables();
    return Result<void, Error>::success();
}

std::string Tree::print() const {
    return printPrefixRecursive(root);
}

std::string Tree::printPrefixRecursive(const Node* node) {
    if (node == nullptr) return "";

    std::stringstream ss;
    ss << node->getValue() << " ";

    const std::vector<Node*>& children = node->getChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        ss << printPrefixRecursive(children[i]);
    }
    return ss.str();
}

Result<Node*, Error> Tree::getTreeAsResult() const {
    if (root == nullptr) {
        return Result<Node*, Error>::fail(new Error(EMPTY_TREE_ERROR));
    }
    return Result<Node*, Error>::success(root);
}