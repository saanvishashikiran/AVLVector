#include "main.h"


int main () {
    // // //Initialize the AVL tree
    // // root = nullptr;

    // // // Test setHeight
    // Node* rootNode = new Node(30);
    // Node* leftChild = new Node(20);
    // Node* rightChild = new Node(40);
    // rootNode->left = leftChild;
    // rootNode->right = rightChild;

    // inOrderPrint(rootNode);
    // cout << endl;

    // setHeight(rootNode);
    // cout << "Height of root after setHeight: " << rootNode->height << std::endl; //should be 1
    // cout << "Height of left child after setHeight: " << leftChild->height << std::endl; //should be 0
    // cout << "Height of right child after setHeight: " << rightChild->height << std::endl; //should be 0

    // cout << "Calling delete node on 20..." << endl;
    // deleteNode(rootNode, 20);
    // inOrderPrint(rootNode);

    // return 0;

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

    // cout << "Tree after insertions (in-order): " << endl;
    // inOrderPrint(root);
    // cout << std::endl;

    // deleteNode(root, 20);
    // cout << "Tree after deleting 20 (in-order): " << endl;
    // inOrderPrint(root);
    // cout << std::endl;

    // deleteNode(root, 30);
    // cout << "Tree after deleting 30 (in-order): " << endl;
    // inOrderPrint(root);
    // cout << std::endl;

    // Test insert and delete

    // AVLVector avlTree;
    // avlTree.insertAtRank(1, 20);
    // avlTree.insertAtRank(2, 30);
    // avlTree.insertAtRank(3, 40);
    // avlTree.insertAtRank(4, 66);
    // // avlTree.insertAtRank(5, 88);


    // int priorRank = 0; // Initialize the rank tracker
    // cout << "Elements in AVL-Vector organized by rank with children:" << endl;
    // inOrderPrintWithChildren(avlTree.getRoot(), priorRank); // Call to the print function

    // cout << "Tree after insertions (in-order): " << endl;
    // avlTree.printAll();
    // cout << std::endl;

    // deleteNode(root, 20);
    // cout << "Tree after deleting 20 (in-order): " << endl;
    // avlTree.printAll();
    // cout << std::endl;

    // deleteNode(root, 30);
    // cout << "Tree after deleting 30 (in-order): " << endl;
    // avlTree.printAll();
    // cout << std::endl;

    // deleteNode(root, 40); // Ensure to clean up the remaining node

    // return 0;

    // Node* root = nullptr;
    // insertNode(root, 30);
    // insertNode(root, 20);
    // insertNode(root, 40);
    // insertNode(root, 10);
    // insertNode(root, 25);
    // insertNode(root, 35);
    // insertNode(root, 50);
    // Insert elements based on rank





    AVLVector vect;

    // vect.insertAtRank(1, 101);
    // vect.insertAtRank(1, 102);
    // vect.insertAtRank(3, 103);
    // vect.insertAtRank(2, 104);
    // vect.insertAtRank(1, 105);
    // vect.insertAtRank(1, 106);
    // vect.insertAtRank(5, 107);
    // vect.insertAtRank(6, 108);
    // vect.insertAtRank(9, 109);
    // vect.insertAtRank(4, 110);
    // vect.insertAtRank(6, 111);
    // vect.insertAtRank(12, 112);
    // vect.insertAtRank(5, 113);
    // vect.insertAtRank(4, 114);
    // vect.insertAtRank(3, 115);
    // vect.insertAtRank(1, 116);
    // vect.insertAtRank(11, 117);
    // vect.insertAtRank(6, 118);
    // vect.insertAtRank(15, 119);
    // vect.insertAtRank(4, 120);

    vect.insertAtRank(1, 23);
    vect.insertAtRank(2, 12);
    vect.insertAtRank(1, 45);
    vect.insertAtRank(4, 10);
    vect.insertAtRank(5, 55);
    vect.insertAtRank(3, 16);
    vect.insertAtRank(4, 77);
    vect.insertAtRank(6, 108);
    
    vect.insertAtRank(4, 123);
    vect.insertAtRank(8, 128);
    vect.insertAtRank(5, 451);
    vect.insertAtRank(7, 109);
    vect.insertAtRank(10, 525);
    vect.insertAtRank(13, 136);
    vect.insertAtRank(2, 727);
    vect.insertAtRank(5, 128);
    vect.replaceAtRank(4, 102);

    vect.removeAtRank(6),             
    vect.removeAtRank(12);      
    vect.insertAtRank(2, 431); 
    vect.insertAtRank(6, 139); //CORRECT UP UNTIL THIS POINT.
    vect.insertAtRank(10, 325);
    vect.insertAtRank(4, 236);
    vect.removeAtRank(14);
    vect.removeAtRank(7);

    vect.insertAtRank(1, 31); //first wrong tree, inconsistencies carry through

    cout << endl;
    vect.printAll();


    vect.inorder(vect.getRoot());
    cout << endl;
    vect.preorder(vect.getRoot());

    // vect.insertAtRank(14, 79); 

    // vect.replaceAtRank(1, 1);
    // vect.replaceAtRank(2, 2);
    // vect.replaceAtRank(3, 3);
    // vect.replaceAtRank(4, 4);
    // vect.replaceAtRank(5, 5);
    // vect.replaceAtRank(6, 6);
    // vect.replaceAtRank(7, 7);
    // vect.replaceAtRank(8, 8);
    // vect.replaceAtRank(9, 9);
    // vect.replaceAtRank(10, 10);
    // vect.replaceAtRank(11, 11);
    // vect.replaceAtRank(12, 12);
    // vect.replaceAtRank(13, 13);
    // vect.replaceAtRank(14, 14);
    // vect.replaceAtRank(15, 15);
    // vect.replaceAtRank(16, 16);
    // vect.replaceAtRank(17, 17);
    // vect.replaceAtRank(18, 18);

    // vect.removeAtRank(13); //correct
    // vect.removeAtRank(6); //imbalanced tree
    // vect.removeAtRank(4); 

    // vect.removeAtRank(10);
    // vect.removeAtRank(4);
    // vect.removeAtRank(6);

    // vect.removeAtRank(7);
    // vect.removeAtRank(7);
    // vect.removeAtRank(7);
    // //somewhere in these removals the root changes to be wrong.

    // cout << endl;
    // vect.inorder(vect.getRoot());
    // cout << endl;
    // vect.preorder(vect.getRoot());

























    // AVLVector avlTree;
    // Node* root = avlTree.getRoot();

    // // avlTree.insertNode(root, 30, 1);  // Insert 30 at rank 1 (first position)
    // // avlTree.insertNode(root, 20, 1);  // Insert 20 at rank 1 (now 20 will be at rank 1, 30 will shift to rank 2)
    // // avlTree.insertNode(root, 40, 3);  // Insert 40 at rank 3 (after 30)
    // // // insertNode(root, 10, 1);  // Insert 10 at rank 1 (shifts others down, 10 is now at rank 1)
    // // // insertNode(root, 25, 3);  // Insert 25 at rank 3 (between 20 and 30)
    // // // insertNode(root, 35, 5);  // Insert 35 at rank 5 (between 30 and 40)
    // // // insertNode(root, 50, 7);  // Insert 50 at rank 7 (last position)
    // // avlTree.insertNode(root, 66, 4);  // Insert 30 at rank 1 (first position)
    // // avlTree.insertNode(root, 88, 5);  // Insert 20 at rank 1 (now 20 will be at rank 1, 30 will shift to rank 2)
    // // int priorRank = 0;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // int priorRank = 0;
    // avlTree.insertNode(root, priorRank, 20, 1);
    // avlTree.insertNode(root, priorRank, 30, 2);
    // avlTree.insertNode(root, priorRank, 40, 3);
    // avlTree.insertNode(root, priorRank, 66, 4);
    // avlTree.insertNode(root, 88, 5);

    //16 node tree, insert worked correctly.
    // avlTree.insertNode(root, priorRank, 30, 1);
    // avlTree.insertNode(root, priorRank, 20, 2);
    // avlTree.insertNode(root, priorRank, 40, 3);
    // avlTree.insertNode(root, priorRank, 10, 4);
    // avlTree.insertNode(root, priorRank, 25, 5);
    // avlTree.insertNode(root, priorRank, 35, 6);
    // avlTree.insertNode(root, priorRank, 50, 7);
    // avlTree.insertNode(root, priorRank, 5, 8);
    // avlTree.insertNode(root, priorRank, 15, 9);
    // avlTree.insertNode(root, priorRank, 37, 10);
    // avlTree.insertNode(root, priorRank, 60, 11);
    // avlTree.insertNode(root, priorRank, 2, 12);
    // avlTree.insertNode(root, priorRank, 8, 13);
    // avlTree.insertNode(root, priorRank, 38, 14);
    // avlTree.insertNode(root, priorRank, 55, 15);
    // avlTree.insertNode(root, priorRank, 53, 16);


    // // Right Rotation Test
    // avlTree.insertNode(root, priorRank, 100, 1);  // Insert node with value 100 at rank 1
    // avlTree.insertNode(root, priorRank, 200, 2);  // Insert node with value 200 at rank 2
    // avlTree.insertNode(root, priorRank, 300, 3);  // Insert node with value 300 at rank 3 (causes right rotation)

    // // Left Rotation Test
    // // cout << "inserting 400 at rank 4" << endl;
    // avlTree.insertNode(root, priorRank, 400, 4);  // Insert node with value 400 at rank 4
    // // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;
    
    // // cout << "inserting 500 at rank 2" << endl;
    // avlTree.insertNode(root, priorRank, 500, 2);  // Insert node with value 500 at rank 2 (causes left rotation)
    // // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;

    // // Left-Right Rotation Test
    // avlTree.insertNode(root, priorRank, 600, 6);  // Insert node with value 600 at rank 6
    // avlTree.insertNode(root, priorRank, 700, 5);  // Insert node with value 700 at rank 5 (causes left-right rotation)
    // // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;

    // // Right-Left Rotation Test
    // avlTree.insertNode(root, priorRank, 800, 8);  // Insert node with value 800 at rank 8
    // avlTree.insertNode(root, priorRank, 900, 9);  // Insert node with value 900 at rank 9
    // avlTree.insertNode(root, priorRank, 1000, 7); // Insert node with value 1000 at rank 7 (causes right-left rotation)
    // // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;

    // // Rank Collision Test
    // avlTree.insertNode(root, priorRank, 300, 3);  // Insert node with value 300 at rank 3 again (collides)
    // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;

    // // Inserting at the Rank of the Root
    // avlTree.insertNode(root, priorRank, 101, 1);  // Insert at the rank of the root (rank 1)
    // priorRank = 0;
    // // cout << "current root is " << root->value << endl;
    // // avlTree.inOrderPrintWithChildren(root, priorRank);
    // // cout << "\n" << endl;

    // avlTree.insertAtRank(1, 100);
    // avlTree.insertAtRank(2, 200);
    // avlTree.insertAtRank(3, 300);
    // avlTree.insertAtRank(4, 400);
    // avlTree.insertAtRank(2, 500);
    // avlTree.insertAtRank(5, 700);
    // avlTree.insertAtRank(8, 800);
    // avlTree.insertAtRank(9, 900);
    // avlTree.insertAtRank(7, 1000);
    // avlTree.insertAtRank(3, 300);
    // avlTree.insertAtRank(1, 101);

    // priorRank = 0;
    // Node* currentRoot = avlTree.getRoot();
    // cout << "current root is " << currentRoot->value << endl;
    // avlTree.printAll();

    
    // avlTree.inOrderPrintWithChildren(root, priorRank);


    // cout << "now trying to replace 30 with 90" << endl;
    // avlTree.replaceAtRank(1, 90);
    // avlTree.insertAtRank(1, 20);
    // avlTree.printAll();
    // avlTree.insertAtRank(2, 30);
    // avlTree.printAll();
    // avlTree.insertAtRank(3, 40);
    // avlTree.printAll();
    // avlTree.insertAtRank(4, 66);
    // avlTree.printAll();
    // // avlTree.insertAtRank(5, 88);

    // cout << "calling printAll" << endl;
    // avlTree.printAll();


    // cout << "removing node at rank 3 " << endl;
    // avlTree.removeAtRank(3);


    // priorRank = 0;
    // avlTree.inOrderPrintWithChildren(root, priorRank);
    //avlTree.printAll();

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


    return 0;

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
    //         int rank, element;
    //         if (input >> rank >> element) {
    //             avlTree.insertAtRank(rank, element);
    //             //Node* ptr = avlTree.getRoot();
    //             //avlTree.insertNode(ptr, element, rank);
    //             avlTree.printAll();
    //             int rootValue = avlTree.getRootValue();
    //             if (rootValue != -1) {
    //                 cout << "Root of the AVL Tree: " << rootValue << endl;
    //             } else {
    //                 cout << "The AVL Tree is empty." << endl;
    //             }
    //             cout << "Just inserted " << element << " (given element) at " << rank << " (given rank)!\n" << endl;
    //         } else {
    //             cout << "Invalid input——the proper format is INSERT <int> <int>!" << endl;
    //         }

    //         // cout << "outputting root" << endl;
    //         // cout << avlTree.getRoot() -> value << endl;
    //         // cout << avlTree.getRoot() -> left << endl;
    //         // cout << avlTree.getRoot() -> right << endl;

    //     } else if (operation == "DELETE") {
    //         int rank;
    //         if (input >> rank) {
    //             int priorRank = 0; //initializing rank tracker
    //             cout << "Deleting element at rank " << rank << endl;
    //             avlTree.removeAtRank(rank);

    //             cout << "TESTING, PRINTING UPDATED TREE" << endl;
    //             avlTree.printAll();

    //             // int elementAtRank = avlTree.elementAtRank(rank);
                
    //             // if (elementAtRank == -1) {
    //             //     cout << "Error: No element found at rank " << rank << endl; 
    //             //     cout << "\n";
    //             // } else {
    //             //     cout << "Deleting element: " << elementAtRank << " at rank " << rank << endl;
    //             //     avlTree.deleteNode(root, elementAtRank); //deleting the node by value
    //             //     cout << "\n";
    //             // }
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
    //                 cout << "The rank of the element " << element << " is " << rank << "!\n" << endl;
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