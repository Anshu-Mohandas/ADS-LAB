#include <iostream>
using namespace std;

class Node {
public:
    int data1;
    int data2;
    Node* left;
    Node* mid;
    Node* right;
    Node* parent;

    Node(int data) {
        data1 = data;
        data2 = -1; // -1 indicates empty
        left = nullptr;
        mid = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class TwoThreeTree {
private:
    Node* root;

    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (node->data2 == -1) {
            if (data < node->data1) {
                node->data2 = node->data1;
                node->data1 = data;
            } else {
                node->data2 = data;
            }
            return node;
        }

        if (data < node->data1) {
            node->left = insert(node->left, data);
        } else if (data > node->data2) {
            node->right = insert(node->right, data);
        } else {
            node->mid = insert(node->mid, data);
        }

        return node;
    }

    Node* remove(Node* node, int data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->data1 == data && node->data2 == -1) {
            delete node;
            return nullptr;
        }

        if (node->data1 == data && node->data2 != -1) {
            node->data1 = node->data2;
            node->data2 = -1;
            return node;
        }

        if (node->data2 == data && node->mid == nullptr) {
            node->data2 = -1;
            return node;
        }

        if (data < node->data1) {
            node->left = remove(node->left, data);
        } else if ((data < node->data2 && data > node->data1) || (node->data1 == data && node->mid != nullptr)) {
            node->mid = remove(node->mid, data);
        } else {
            node->right = remove(node->right, data);
        }

        return node;
    }

    void traverse(Node* node) {
        if (node != nullptr) {
            traverse(node->left);
            cout << node->data1 << " ";
            if (node->data2 != -1) {
                cout << node->data2 << " ";
            }
            traverse(node->mid);
            traverse(node->right);
        }
    }

public:
    TwoThreeTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

    void display() {
        traverse(root);
    }
};

int main() {
    TwoThreeTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(30);
    tree.insert(25);

    cout << "2-3 Tree elements: ";
    tree.display();
    cout << endl;

    cout << "Deleting 15...\n";
    tree.remove(15);
    cout << "2-3 Tree elements after deletion: ";
    tree.display();
    cout << endl;

    return 0;
}
