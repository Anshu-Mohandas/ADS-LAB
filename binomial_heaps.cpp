#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};


Node* createNode(int key) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = nullptr;
    newNode->child = nullptr;
    newNode->sibling = nullptr;
    return newNode;
}

Node* mergeTrees(Node* tree1, Node* tree2) {
    if (tree1->key > tree2->key)
        swap(tree1, tree2);

    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;

    return tree1;
}

Node* mergeHeaps(Node* heap1, Node* heap2) {
    Node* dummy = createNode(INT_MIN);
    Node* tail = dummy;

    while (heap1 && heap2) {
        if (heap1->degree <= heap2->degree) {
            tail->sibling = heap1;
            heap1 = heap1->sibling;
        } else {
            tail->sibling = heap2;
            heap2 = heap2->sibling;
        }
        tail = tail->sibling;
    }

    tail->sibling = (heap1) ? heap1 : heap2;
    return dummy->sibling;
}

Node* unionHeaps(Node* heap1, Node* heap2) {
    Node* mergedHeap = mergeHeaps(heap1, heap2);

    if (!mergedHeap)
        return nullptr;

    Node* prev_x = nullptr;
    Node* x = mergedHeap;
    Node* next_x = x->sibling;

    while (next_x) {
        if (x->degree != next_x->degree || (next_x->sibling && next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->key <= next_x->key) {
                x->sibling = next_x->sibling;
                mergeTrees(x, next_x);
            } else {
                if (!prev_x)
                    mergedHeap = next_x;
                else
                    prev_x->sibling = next_x;

                mergeTrees(next_x, x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }

    return mergedHeap;
}

Node* insert(Node* heap, int key) {
    Node* newNode = createNode(key);
    return unionHeaps(heap, newNode);
}

int getMin(Node* heap) {
    int minKey = INT_MAX;
    Node* curr = heap;
    while (curr) {
        if (curr->key < minKey)
            minKey = curr->key;
        curr = curr->sibling;
    }
    return minKey;
}

Node* extractMin(Node* heap) {
    if (!heap)
        return nullptr;

    int minKey = INT_MAX;
    Node* minNode = nullptr;
    Node* prev = nullptr;
    Node* curr = heap;
    Node* prevMin = nullptr;

    while (curr) {
        if (curr->key < minKey) {
            minKey = curr->key;
            minNode = curr;
            prevMin = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prevMin)
        prevMin->sibling = minNode->sibling;
    else
        heap = minNode->sibling;

    Node* child = minNode->child;
    Node* prevChild = nullptr;
    while (child) {
        child->parent = nullptr;
        Node* nextChild = child->sibling;
        child->sibling = prevChild;
        prevChild = child;
        child = nextChild;
    }

    return unionHeaps(heap, prevChild);
}

void printHeap(Node* heap) {
    cout << "Binomial Heap: ";
    while (heap) {
        cout << heap->key << "(" << heap->degree << ") ";
        heap = heap->sibling;
    }
    cout << endl;
}


int main() {
    Node* heap = nullptr;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 3);

    printHeap(heap);

    cout << "Minimum key: " << getMin(heap) << endl;

    heap = extractMin(heap);
    cout << "After extracting minimum key: ";
    printHeap(heap);

    return 0;
}
