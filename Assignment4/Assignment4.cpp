#include <iostream>
#include <stack>
using namespace std;

// Define a structure for a tree node
struct Node {
    char data;
    Node* left;
    Node* right;

    // Constructor to initialize a node
    Node(char value) {
        data = value;
        left = right = nullptr;
    }
};

// Utility function to check if the given character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to construct an expression tree from postfix expression
Node* constructTreeFromPostfix(string postfix) {
    stack<Node*> st;

    for (int i = 0; i < postfix.length(); i++) {
        // If operand, create a node and push it to the stack
        if (!isOperator(postfix[i])) {
            st.push(new Node(postfix[i]));
        }
        // If operator, pop two nodes, make them children and push the result node back
        else {
            Node* node = new Node(postfix[i]);
            node->right = st.top();
            st.pop();
            node->left = st.top();
            st.pop();
            st.push(node);
        }
    }
    // The final node in the stack is the root of the tree
    return st.top();
}

// Function to construct an expression tree from prefix expression
Node* constructTreeFromPrefix(string prefix) {
    stack<Node*> st;

    // Loop through the string in reverse order
    for (int i = prefix.length() - 1; i >= 0; i--) {
        // If operand, create a node and push it to the stack
        if (!isOperator(prefix[i])) {
            st.push(new Node(prefix[i]));
        }
        // If operator, pop two nodes, make them children and push the result node back
        else {
            Node* node = new Node(prefix[i]);
            node->left = st.top();
            st.pop();
            node->right = st.top();
            st.pop();
            st.push(node);
        }
    }
    // The final node in the stack is the root of the tree
    return st.top();
}

// Recursive In-order Traversal
void recursiveInOrder(Node* root) {
    if (root) {
        recursiveInOrder(root->left);
        cout << root->data << " ";
        recursiveInOrder(root->right);
    }
}

// Recursive Pre-order Traversal
void recursivePreOrder(Node* root) {
    if (root) {
        cout << root->data << " ";
        recursivePreOrder(root->left);
        recursivePreOrder(root->right);
    }
}

// Recursive Post-order Traversal
void recursivePostOrder(Node* root) {
    if (root) {
        recursivePostOrder(root->left);
        recursivePostOrder(root->right);
        cout << root->data << " ";
    }
}

// Non-recursive In-order Traversal
void nonRecursiveInOrder(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {
        // Reach the leftmost node
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();
        cout << current->data << " ";

        current = current->right;
    }
}

// Non-recursive Pre-order Traversal
void nonRecursivePreOrder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        cout << current->data << " ";

        if (current->right) {
            st.push(current->right);
        }
        if (current->left) {
            st.push(current->left);
        }
    }
}

// Non-recursive Post-order Traversal
void nonRecursivePostOrder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* current = st1.top();
        st1.pop();
        st2.push(current);

        if (current->left) {
            st1.push(current->left);
        }
        if (current->right) {
            st1.push(current->right);
        }
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Main function
int main() {
    string postfix = "ab+ef*g*-";
    string prefix = "*+ab-efg";

    // Construct the tree from postfix expression
    Node* rootPostfix = constructTreeFromPostfix(postfix);

    cout << "Expression Tree constructed from Postfix:" << endl;
    cout << "Recursive In-order Traversal: ";
    recursiveInOrder(rootPostfix);
    cout << endl;

    cout << "Non-Recursive In-order Traversal: ";
    nonRecursiveInOrder(rootPostfix);
    cout << endl;

    cout << "Recursive Pre-order Traversal: ";
    recursivePreOrder(rootPostfix);
    cout << endl;

    cout << "Non-Recursive Pre-order Traversal: ";
    nonRecursivePreOrder(rootPostfix);
    cout << endl;

    cout << "Recursive Post-order Traversal: ";
    recursivePostOrder(rootPostfix);
    cout << endl;

    cout << "Non-Recursive Post-order Traversal: ";
    nonRecursivePostOrder(rootPostfix);
    cout << endl;

    // Construct the tree from prefix expression
    Node* rootPrefix = constructTreeFromPrefix(prefix);

    cout << "\nExpression Tree constructed from Prefix:" << endl;
    cout << "Recursive In-order Traversal: ";
    recursiveInOrder(rootPrefix);
    cout << endl;

    return 0;
}

