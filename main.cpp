#include "main.h"


int main () {

    AVLVector vect;

    // // our test
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

    // cout << "outputting ranks of 120";
    // vect.rankOf(120);


    // bala's test
    vect.insertAtRank(1, 23);
    vect.insertAtRank(2, 12);
    vect.insertAtRank(1, 45);
    vect.insertAtRank(4, 10);
    vect.insertAtRank(5, 55);
    vect.insertAtRank(3, 16);
    vect.insertAtRank(4, 77);
    vect.insertAtRank(6, 108);

    vect.printAll();
    
    vect.insertAtRank(4, 123);
    vect.insertAtRank(8, 128);
    vect.insertAtRank(5, 451);
    vect.insertAtRank(7, 109);
    vect.insertAtRank(10, 525);
    vect.insertAtRank(13, 136);
    vect.insertAtRank(2, 727);
    vect.insertAtRank(5, 128);
    vect.replaceAtRank(4, 102);

    vect.removeAtRank(6);  
    vect.removeAtRank(12);    
    vect.insertAtRank(2, 431); 
    vect.insertAtRank(6, 139); 
    vect.insertAtRank(10, 325);
    vect.insertAtRank(4, 236);
    vect.removeAtRank(14);
    vect.removeAtRank(7);

    vect.insertAtRank(1, 31); 
    vect.insertAtRank(14, 79); 

    vect.printAll();
    
    cout << "elements at ranks 1-9: " << endl;
    vect.elementAtRank(1),
    vect.elementAtRank(2),
    vect.elementAtRank(3),
    vect.elementAtRank(4),
    vect.elementAtRank(5),
    vect.elementAtRank(6),
    vect.elementAtRank(7),
    vect.elementAtRank(8),
    vect.elementAtRank(9),

    vect.printAll();

    vect.replaceAtRank(1, 1);
    vect.replaceAtRank(2, 2);
    vect.replaceAtRank(3, 3);
    vect.replaceAtRank(4, 4);
    vect.replaceAtRank(5, 5);
    vect.replaceAtRank(6, 6);
    vect.replaceAtRank(7, 7);
    vect.replaceAtRank(8, 8);
    vect.replaceAtRank(9, 9);
    vect.replaceAtRank(10, 10);
    vect.replaceAtRank(11, 11);
    vect.replaceAtRank(12, 12);
    vect.replaceAtRank(13, 13);
    vect.replaceAtRank(14, 14);
    vect.replaceAtRank(15, 15);
    vect.replaceAtRank(16, 16);
    vect.replaceAtRank(17, 17);
    vect.replaceAtRank(18, 18);

    vect.printAll();

    vect.removeAtRank(13); 
    vect.removeAtRank(6); 
    vect.removeAtRank(4); 

    vect.printAll();

    vect.removeAtRank(10);
    vect.removeAtRank(4);
    vect.removeAtRank(6);

    vect.printAll();

    vect.removeAtRank(7);
    vect.removeAtRank(7);
    vect.removeAtRank(7);

    cout << endl;
    cout << "current root is " << vect.getRoot()->value << endl;
    vect.printAll();


    vect.inorder(vect.getRoot());
    cout << endl;
    vect.preorder(vect.getRoot());


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
    //             cout << endl;
    //             avlTree.inorder(avlTree.getRoot());
    //             cout << endl;
    //             avlTree.preorder(avlTree.getRoot());
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
    //             cout << endl;
    //             avlTree.inorder(avlTree.getRoot());
    //             cout << endl;
    //             avlTree.preorder(avlTree.getRoot());

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
    //         cout << endl;
    //         avlTree.inorder(avlTree.getRoot());
    //         cout << endl;
    //         avlTree.preorder(avlTree.getRoot());
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