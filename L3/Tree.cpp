#include "Tree.h"

#include <iostream>
#include <ostream>
#include <sstream>

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

std::string Tree::enter(const std::string &formula) {
    std::stringstream ss(formula);
    std::string token;
    std::queue<std::string> queue;
    while (ss >> token) {
        queue.push(token);
    }
    if (queue.empty()) {
        return "Wprowadzono pusta formule.";
    }
    delete root;
    root = buildTree(&queue);
    if (!queue.empty()) {
        return "Zignorowano nadmiarowe argumenty";
    }
    return "Poprawnie zbudowano drzewo";
}

Node* Tree::buildTree(std::queue<std::string> *queue) {
    if (queue->empty()) {
        std::cout << "Wykryto brakujacy argument. Wstawiam domyslna wartosc '1'" << std::endl;
        return new Node("1", NODE_CONSTANT);
    }
    const std::string current_value = queue->front();
    queue->pop();
    if (BINARY_OPERATORS.count(current_value) > 0) {
        Node* node = new Node(current_value, NODE_OPERATOR_BINARY);
        node->addChild(buildTree(queue));
        node->addChild(buildTree(queue));
        return node;
    }
    if (UNARY_OPERATORS.count(current_value) > 0) {
        Node* node = new Node(current_value, NODE_OPERATOR_UNARY);
        node->addChild(buildTree(queue));
        return node;
    }
    if (isNumber(current_value)) {
        return new Node(current_value, NODE_CONSTANT);
    }
    const std::string variable = validateVariable(current_value);
    if (!variable.empty()) {
        return new Node(variable, NODE_VARIABLE);
    }

    std::cout << "Nieznany token '" << current_value << "'. Traktuje jako domyslna zmienna 'x'" << std::endl;
    return new Node("x", NODE_VARIABLE);
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

double Tree::comp(const std::string& formula) {
    if (root == nullptr) {
        std::cout << "Drzewo jest puste";
        return 0.0;
    }
    updateVariables();
    std::stringstream ss(formula);
    double value;
    std::map<std::string, double>::iterator var_it = variables.begin();
    bool running = true;
    while (running && ss >> value) {
        if (var_it != variables.end()) {
            var_it->second = value;
            ++var_it;
        } else {
            std::cout << "Nadmiarowe argumenty zignorowano. Wymagana liczba argumentów dla obecnego drzewa: " << variables.size() << ". ";
            running = false;
        }
    }

    if (var_it != variables.end()) {
        std::cout << "Podano za malo argumentów. Wymagana liczba argumentów dla obecnego drzewa: " << variables.size() << ". Zwracam: ";
        return 0;
    }
    else {
        std::cout << "Wynik: ";
        return root->evaluate(variables);
    }
}

std::string Tree::join(const std::string &formula) {
    Tree tree;
    std::string result = tree.enter(formula);
    join(tree);
    return result;
}

void Tree::join(const Tree& other) {
    if (root == nullptr) {
        if (other.root != nullptr)
            root = new Node(*other.root);
    }
    else {
        Node *join_node = root;
        Node *parent = nullptr;
        while (join_node != nullptr && join_node->getNodeType() != NODE_VARIABLE && join_node->getNodeType() != NODE_CONSTANT) {
            parent = join_node;
            join_node = join_node->getChildren()[0];
        }
        if (parent) {
            parent->replaceChild(0, new Node(*other.root));
        }
        else {
            delete root;
            if (other.root != nullptr)
                root = new Node(*other.root);
            else
                root = nullptr;
        }
        updateVariables();
    }
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
