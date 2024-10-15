#include "main.h"

void inOrderPrint(nodeptr root) {
    if (root == nullptr) {
        return; // base case: if root is null, return
    }

    // Traverse the left subtree
    inOrderPrint(root->left);

    // Print the current node's value
    std::cout << "Element: " << root->value << std::endl;

    // Traverse the right subtree
    inOrderPrint(root->right);
}

int main () {
    // //Initialize the AVL tree
    // root = nullptr;

    // // Test setHeight
    Node* rootNode = new Node(30);
    Node* leftChild = new Node(20);
    Node* rightChild = new Node(40);
    rootNode->left = leftChild;
    rootNode->right = rightChild;

    inOrderPrint(rootNode);
    cout << endl;

    setHeight(rootNode);
    cout << "Height of root after setHeight: " << rootNode->height << std::endl; //should be 1
    cout << "Height of left child after setHeight: " << leftChild->height << std::endl; //should be 0
    cout << "Height of right child after setHeight: " << rightChild->height << std::endl; //should be 0

    cout << "Calling delete node on 20..." << endl;
    deleteNode(rootNode, 20);
    inOrderPrint(rootNode);

    return 0;

    // // Cleanup
    // delete rightChild;
    // delete leftChild;
    // delete rootNode;

    // // Test search
    // insertNode(root, 30, 2);
    // insertNode(root, 20, 1);
    // insertNode(root, 40, 3);

    // inOrderPrint(root);
    // cout << endl;

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
    // insertNode(root, 30, 2);
    // insertNode(root, 20, 1);
    // insertNode(root, 40, 3);

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


    // //Initialize the AVL tree
    // AVLVector avlTree;

    // // Test search
    // // avlTree.insertAtRank(2, 30);
    // // avlTree.printAll();
    // // avlTree.insertAtRank(1, 20);
    // // avlTree.printAll();
    // // avlTree.insertAtRank(1, 5);
    // // avlTree.printAll();

    // avlTree.insertAtRank(2, 30);
    // avlTree.insertAtRank(1, 20);
    // avlTree.insertAtRank(1, 5);
    // avlTree.insertAtRank(3, 40);
    // // avlTree.insertAtRank(4, 50);
    // // avlTree.insertAtRank(5, 60);

    // avlTree.printAll();
    // cout << endl;

    // cout << "Printing element at rank 1: " << endl;
    // avlTree.elementAtRank(1);
    // cout << "\n";
    // cout << "Printing element at rank 2: " << endl;
    // avlTree.elementAtRank(2);
    // cout << "\n";
    // cout << "Printing element at rank 3: " << endl;
    // avlTree.elementAtRank(3);
    // cout << "\n";
    // cout << "Printing element at rank 4: " << endl;
    // avlTree.elementAtRank(4);
    // cout << "\n";

    // for (int rankToFind = 1; rankToFind <= 3; rankToFind++) {
    //     try {
    //         int result = avlTree.elementAtRank(rankToFind);
    //         std::cout << "Element at rank " << rankToFind << " is: " << result << std::endl; // Check output
    //     } catch (const std::out_of_range& e) {
    //         std::cout << e.what() << std::endl; // Handle any exceptions
    //     }
    // }

    

    // cout << "Printing rank of 30: ";
    // int rank = avlTree.rankOf(30);
    // if (rank != -1) {
    //     cout << rank << endl; // Rank is found and printed
    // } else {
    //     cout << "Element 30 not found in the AVL Tree." << endl;
    // }

    // // // Print the root value
    // // int rootValue = avlTree.getRootValue();
    // // if (rootValue != -1) {
    // //     cout << "Root of the AVL Tree: " << rootValue << endl;
    // // } else {
    // //     cout << "The AVL Tree is empty." << endl;
    // // }
    

    // return 0;

    // AVLVector avlTree;
    // string command = "";
    // cout << "Welcome! To use this AVL-Vector program, type a command along with your rank/element in a single line (exact same format as listed in test data)." << endl;
    // cout << "Please do NOT enter a command and enter without a numerical input in the same line." << endl;
    // cout << "Example input: 'INSERT 1 55'" << endl;
    // cout << "Enter one of the following commands: INSERT, DELETE, REPLACE, ELEMENT-AT, RANK, PRINT, or QUIT followed by the necessary numerical inputs!" << endl;

    // while (true) {
    //     cout << "> ";

    //     getline(cin, command);

    //     size_t start = command.find_first_not_of(" \t");
    //     if (start == string::npos) {
    //         command = "";  // case where the command is all spaces
    //     } else {
    //         size_t end = command.find_last_not_of(" \t");
    //         command = command.substr(start, end - start + 1);
    //     }
        
    //     stringstream input(command);
    //     string operation; 
    //     input >> operation;

    //     if (operation == "INSERT") {
    //         cout << "insert" << endl;
    //         int rank, element;
    //         if (input >> rank >> element) {
    //             avlTree.insertAtRank(rank, element);
    //             avlTree.printAll();
    //             cout << "Just inserted " << element << " (given element) at " << rank << " (given rank)!\n" << endl;
    //         } else {
    //             cout << "Invalid input——the proper format is INSERT <int> <int>!" << endl;
    //         }

    //     } else if (operation == "DELETE") {
    //         int rank;
    //         if (input >> rank) {
    //             int priorRank = 0; //initializing rank tracker
    //             int elementAtRank = avlTree.elementAtRank(rank);
                
    //             if (elementAtRank == -1) {
    //                 cout << "Error: No element found at rank " << rank << endl; 
    //                 cout << "\n";
    //             } else {
    //                 cout << "Deleting element: " << elementAtRank << " at rank " << rank << endl;
    //                 deleteNode(root, elementAtRank); //deleting the node by value
    //                 cout << "\n";
    //             }
    //         } else {
    //             cout << "Invalid input——the proper format is DELETE <int>!" << endl;
    //         }
    //     } else if (operation == "REPLACE") {
    //         int rank, element;
    //         if (input >> rank >> element) {
    //             avlTree.replaceAtRank(rank, element);
    //             cout << "Just replaced the element at rank " << rank << " with " << element << "!" << endl;
    //             avlTree.printAll();
    //         } else {
    //             cout << "Invalid input——the proper format is REPLACE <int> <int>!" << endl;
    //         }

    //     } else if (operation == "ELEMENT-AT") {
    //         int rank;
    //         if (input >> rank) {
    //             avlTree.elementAtRank(rank);
    //         } else {
    //             cout << "Invalid input——the proper format is ELEMENT-AT <int>!" << endl;
    //         }

    //     } else if (operation == "RANK") {
    //         int element;
    //         if (input >> element) {
    //             //come back and modify this logic based on function
    //             int rank = avlTree.rankOf(element);
    //             if (rank != -1) {
    //                 cout << "The rank of the element " << element << " is " << rank << "!" << endl;
    //             } else {
    //                 cout << "Element " << element << " not found in the AVL Tree." << endl;
    //             }
    //         } else {
    //             cout << "Invalid input——the proper format is RANK <int>!" << endl;
    //         }
    //     } else if (operation == "PRINT") {
    //         cout << "Elements in AVL-Vector organized by rank!" << endl;
    //         avlTree.printAll();
    //         int rootValue = avlTree.getRootValue();
    //         if (rootValue != -1) {
    //             cout << "Root of the AVL Tree: " << rootValue << endl;
    //         } else {
    //             cout << "The AVL Tree is empty." << endl;
    //         }
    //     } else if (operation == "QUIT") {
    //         cout << "Bye!" << endl;
    //         cout << "\n";
    //         return 0;
    //     } else {
    //         cout << "Error: Unknown Command:" << command << endl;
    //     }
    // }

    // return 0;
}