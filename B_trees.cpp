#include <iostream>
#include <vector>
using namespace std;

const int MAX_KEYS = 3; // B-tree order

class Node {
public:
    vector<int> keys;
    vector<Node*> children;
    bool leaf;
    Node* parent;

    Node(bool isLeaf) {
        leaf = isLeaf;
        parent = nullptr;
    }
};

class BTree {
private:
    Node* root;

    void splitChild(Node* x, int i) {
        Node* z = new Node(true);
        Node* y = x->children[i];
        z->leaf = y->leaf;

        // Move keys to the new node
        for (int j = 0; j < MAX_KEYS - 1; j++) {
            z->keys.push_back(y->keys[j + MAX_KEYS]);
            y->keys.pop_back();
        }

        // If not leaf, move children too
        if (!y->leaf) {
            for (int j = 0; j < MAX_KEYS; j++) {
                z->children.push_back(y->children[j + MAX_KEYS]);
                y->children.pop_back();
            }
        }

        x->keys.insert(x->keys.begin() + i, y->keys[MAX_KEYS - 1]);
        x->children.insert(x->children.begin() + i + 1, z);
        y->keys.pop_back();
    }

    void insertNonFull(Node* x, int key) {
        int i = x->keys.size() - 1;

        if (x->leaf) {
            x->keys.push_back(0);
            while (i >= 0 && key < x->keys[i]) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }
            x->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < x->keys[i]) {
                i--;
            }
            i++;

            if (x->children[i]->keys.size() == MAX_KEYS * 2 - 1) {
                splitChild(x, i);
                if (key > x->keys[i]) {
                    i++;
                }
            }
            insertNonFull(x->children[i], key);
        }
    }

public:
    BTree() {
        root = nullptr;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == MAX_KEYS * 2 - 1) {
                Node* s = new Node(false);
                s->children.push_back(root);
                splitChild(s, 0);
                root = s;
            }
            insertNonFull(root, key);
        }
    }

    void display(Node* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); i++) {
                cout << node->keys[i] << " ";
            }
            cout << endl;

            if (!node->leaf) {
                for (int i = 0; i < node->children.size(); i++) {
                    display(node->children[i]);
                }
            }
        }
    }

    void display() {
        display(root);
    }
};

int main() {
    BTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(30);
    tree.insert(25);

    cout << "B-tree elements: " << endl;
    tree.display();

    return 0;
}
