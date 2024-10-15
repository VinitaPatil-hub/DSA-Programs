#include <iostream>
#include <queue>
using namespace std;

// Node structure for the tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Insert a node in the BST
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Find the minimum value node
Node* findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

// Delete a node in the BST
Node* deleteNode(Node* root, int data) {
    if (root == nullptr) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Search for a node in the BST
bool search(Node* root, int data) {
    if (root == nullptr) return false;
    if (root->data == data) return true;
    else if (data < root->data) return search(root->left, data);
    else return search(root->right, data);
}

// Inorder traversal
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Display leaf nodes
void displayLeafNodes(Node* root) {
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr) {
            cout << root->data << " ";
        }
        displayLeafNodes(root->left);
        displayLeafNodes(root->right);
    }
}

// Display tree level-wise
void displayLevelWise(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Display Leaf Nodes\n";
        cout << "8. Display Level-wise\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Found\n";
                else
                    cout << "Not Found\n";
                break;
            case 4:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << "\n";
                break;
            case 5:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << "\n";
                break;
            case 6:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << "\n";
                break;
            case 7:
                cout << "Leaf Nodes: ";
                displayLeafNodes(root);
                cout << "\n";
                break;
            case 8:
                cout << "Level-wise Traversal: ";
                displayLevelWise(root);
                cout << "\n";
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

