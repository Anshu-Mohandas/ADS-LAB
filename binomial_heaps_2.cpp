Node* deleteNode(Node* heap, int keyToDelete) {
    decreaseKey(heap, keyToDelete, INT_MIN);
    return extractMin(heap);
}

void decreaseKey(Node* heap, int oldKey, int newKey) {
    Node* targetNode = nullptr;
    targetNode = findNode(heap, oldKey);
    if (!targetNode)
        return;

    targetNode->key = newKey;

    while (targetNode->parent && targetNode->key < targetNode->parent->key) {
        swap(targetNode->key, targetNode->parent->key);
        targetNode = targetNode->parent;
    }
}
