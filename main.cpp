#include "main.h"

//TEST PRINTING FUCNCTION!! 
//function to print the tree in-order for verification
void inOrderPrint(nodeptr node) {
    if (node != nullptr) {
        inOrderPrint(node->left);
        cout << node->value << " ";
        inOrderPrint(node->right);
    }
}


int main () {
    // Initialize the AVL tree
    root = nullptr;

    // Test setHeight
    Node* rootNode = new Node(30);
    Node* leftChild = new Node(20);
    Node* rightChild = new Node(40);
    rootNode->left = leftChild;
    rootNode->right = rightChild;

    setHeight(rootNode);
    cout << "Height of root after setHeight: " << rootNode->height << std::endl; //should be 1
    cout << "Height of left child after setHeight: " << leftChild->height << std::endl; //should be 0
    cout << "Height of right child after setHeight: " << rightChild->height << std::endl; //should be 0

    // Cleanup
    delete rootNode;
    delete leftChild;
    delete rightChild;

    // Test search
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);

    int found = search(root, 20);
    cout << "Search for 20: " << (found != -1 ? "Found" : "Not Found") << endl;

    found = search(root, 50);
    cout << "Search for 50: " << (found != -1 ? "Found" : "Not Found") << endl;

    // Test rotations
    Node* rotationRoot = new Node(30);
    Node* rotationLeftChild = new Node(20);
    Node* rotationLeftLeftChild = new Node(10);
    rotationRoot->left = rotationLeftChild;
    rotationLeftChild->left = rotationLeftLeftChild;

    cout << "Before left-left rotation: ";
    inOrderPrint(rotationRoot);
    cout << std::endl;

    leftLeftRotation(rotationRoot);

    cout << "After left-left rotation: ";
    inOrderPrint(rotationRoot);
    cout << std::endl;

    // Cleanup
    delete rotationLeftLeftChild;
    delete rotationLeftChild;
    delete rotationRoot;

    // Test insert and delete
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);

    cout << "Tree after insertions (in-order): ";
    inOrderPrint(root);
    cout << std::endl;

    deleteNode(root, 20);
    cout << "Tree after deleting 20 (in-order): ";
    inOrderPrint(root);
    cout << std::endl;

    deleteNode(root, 30);
    cout << "Tree after deleting 30 (in-order): ";
    inOrderPrint(root);
    cout << std::endl;

    deleteNode(root, 40); // Ensure to clean up the remaining node

    return 0;
}