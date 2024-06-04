#include <bits/stdc++.h>
using namespace std;

class RedBlackTree {
private:
	
	struct Node {
		int data;
		Node* left;
		Node* right;
		char colour;
		Node* parent;

		Node(int data) : data(data), left(nullptr), right(nullptr), colour('R'), parent(nullptr) {}
	};

	Node* root;
	bool ll; 
	bool rr;
	bool lr; 
	bool rl; 

	Node* rotateLeft(Node* node) {
		Node* x = node->right;
		Node* y = x->left;
		x->left = node;
		node->right = y;
		node->parent = x;
		if (y != nullptr)
			y->parent = node;
		return x;
	}

	Node* rotateRight(Node* node) {
		Node* x = node->left;
		Node* y = x->right;
		x->right = node;
		node->left = y;
		node->parent = x;
		if (y != nullptr)
			y->parent = node;
		return x;
	}

	Node* insertHelp(Node* root, int data) {
		bool f = false; 
		if (root == nullptr)
			return new Node(data);
		else if (data < root->data) {
			root->left = insertHelp(root->left, data);
			root->left->parent = root;
			if (root != this->root) {
				if (root->colour == 'R' && root->left->colour == 'R')
					f = true;
			}
		} else {
			root->right = insertHelp(root->right, data);
			root->right->parent = root;
			if (root != this->root) {
				if (root->colour == 'R' && root->right->colour == 'R')
					f = true;
			}
		}

		if (ll) {
			root = rotateLeft(root);
			root->colour = 'B';
			root->left->colour = 'R';
			ll = false;
		} else if (rr) {
			root = rotateRight(root);
			root->colour = 'B';
			root->right->colour = 'R';
			rr = false;
		} else if (rl) {
			root->right = rotateRight(root->right);
			root->right->parent = root;
			root = rotateLeft(root);
			root->colour = 'B';
			root->left->colour = 'R';
			rl = false;
		} else if (lr) {
			root->left = rotateLeft(root->left);
			root->left->parent = root;
			root = rotateRight(root);
			root->colour = 'B';
			root->right->colour = 'R';
			lr = false;
		}

		if (f) {
			if (root->parent->right == root) {
				if (root->parent->left == nullptr || root->parent->left->colour == 'B') {
					if (root->left != nullptr && root->left->colour == 'R')
						rl = true;
					else if (root->right != nullptr && root->right->colour == 'R')
						ll = true;
				} else {
					root->parent->left->colour = 'B';
					root->colour = 'B';
					if (root->parent != this->root)
						root->parent->colour = 'R';
				}
			} else {
				if (root->parent->right == nullptr || root->parent->right->colour == 'B') {
					if (root->left != nullptr && root->left->colour == 'R')
						rr = true;
					else if (root->right != nullptr && root->right->colour == 'R')
						lr = true;
				} else {
					root->parent->right->colour = 'B';
					root->colour = 'B';
					if (root->parent != this->root)
						root->parent->colour = 'R';
				}
			}
			f = false;
		}
		return root;
	}

	void inorderTraversalHelper(Node* node) {
		if (node != nullptr) {
			inorderTraversalHelper(node->left);
			std::cout << node->data << " ";
			inorderTraversalHelper(node->right);
		}
	}



public:
	RedBlackTree() : root(nullptr), ll(false), rr(false), lr(false), rl(false) {}


	void insert(int data) {
		if (root == nullptr) {
			root = new Node(data);
			root->colour = 'B';
		} else
			root = insertHelp(root, data);
	}


	void inorderTraversal() {
		inorderTraversalHelper(root);
	}


};

int main() {
	RedBlackTree t;
	int arr[] = {1, 4, 6, 3, 5, 7, 8, 2, 9};
	for (int i = 0; i < 9; i++) {
		t.insert(arr[i]);
		std::cout << std::endl;
		t.inorderTraversal();
	}
	
	return 0;
}
