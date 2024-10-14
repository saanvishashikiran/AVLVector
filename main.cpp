#include "main.h"

int main () {
    // // Initialize the AVL tree
    // root = nullptr;

    // // Test setHeight
    // Node* rootNode = new Node(30);
    // Node* leftChild = new Node(20);
    // Node* rightChild = new Node(40);
    // rootNode->left = leftChild;
    // rootNode->right = rightChild;

    // setHeight(rootNode);
    // cout << "Height of root after setHeight: " << rootNode->height << std::endl; //should be 1
    // cout << "Height of left child after setHeight: " << leftChild->height << std::endl; //should be 0
    // cout << "Height of right child after setHeight: " << rightChild->height << std::endl; //should be 0

    // // Cleanup
    // delete rootNode;
    // delete leftChild;
    // delete rightChild;

    // // Test search
    // insertNode(root, 30);
    // insertNode(root, 20);
    // insertNode(root, 40);

    // int found = search(root, 20);
    // cout << "Search for 20: " << (found != -1 ? "Found" : "Not Found") << endl;

    // found = search(root, 50);
    // cout << "Search for 50: " << (found != -1 ? "Found" : "Not Found") << endl;

    // // Test rotations
    // Node* rotationRoot = new Node(30);
    // Node* rotationLeftChild = new Node(20);
    // Node* rotationLeftLeftChild = new Node(10);
    // rotationRoot->left = rotationLeftChild;
    // rotationLeftChild->left = rotationLeftLeftChild;

    // cout << "Before left-left rotation: ";
    // inOrderPrint(rotationRoot);
    // cout << std::endl;

    // leftLeftRotation(rotationRoot);

    // cout << "After left-left rotation: ";
    // inOrderPrint(rotationRoot);
    // cout << std::endl;

    // // Test insert and delete
    // insertNode(root, 30);
    // insertNode(root, 20);
    // insertNode(root, 40);

    // cout << "Tree after insertions (in-order): ";
    // inOrderPrint(root);
    // cout << std::endl;

    // deleteNode(root, 20);
    // cout << "Tree after deleting 20 (in-order): ";
    // inOrderPrint(root);
    // cout << std::endl;

    // deleteNode(root, 30);
    // cout << "Tree after deleting 30 (in-order): ";
    // inOrderPrint(root);
    // cout << std::endl;

    // deleteNode(root, 40); // Ensure to clean up the remaining node

    // return 0;


    string command = "";
    cout << "Welcome! To use this AVL-Vector program, type a command along with your rank/element in a single line (exact same format as listed in test data)." << endl;
    cout << "Please do NOT enter a command and enter without a numerical input in the same line." << endl;
    cout << "Example input: 'INSERT 1 55'" << endl;
    cout << "Enter one of the following commands: INSERT, DELETE, REPLACE, ELEMENT-AT, RANK, PRINT, or QUIT followed by the necessary numerical inputs!" << endl;

    while (true) {
        cout << ">";

        getline(cin, command);

        size_t start = command.find_first_not_of(" \t");
        if (start == string::npos) {
            command = "";  // case where the command is all spaces
        } else {
            size_t end = command.find_last_not_of(" \t");
            command = command.substr(start, end - start + 1);
        }
        
        if (command.substr(0,6) == "INSERT") {
            cout << "insert" << endl;
        } else if (command.substr(0,6) == "DELETE") {
            cout << "delete" << endl;
        } else if (command.substr(0,7) == "REPLACE") {
            cout << "replace" << endl;
        } else if (command.substr(0,10) == "ELEMENT-AT") {
            cout << "element-at" << endl;
        } else if (command.substr(0,4) == "RANK") {
            cout << "rank" << endl;
        } else if (command.substr(0,5) == "PRINT") {
            cout << "print" << endl;
        } else if (command.substr(0,4) == "QUIT") {
            cout << "quit" << endl;
            return 0;
        } else {
            cout << "Error: Unknown Command:" << command << endl;
        }
    }

    return 0;
}