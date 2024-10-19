#ifndef AVL_H
#define AVL_H

#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;

// /****************************************************************************
//  *                                                                          *
//  *                       class AVLTree Declaration                          *
//  *                                                                          *
//  ****************************************************************************/

// class AVLTree {
//     private:
//     struct Node {
//         int value;
//         int height;
//         Node* left;
//         Node* right;
//         Node* parent;

//         //node constructor
//         Node(int val) : value(val), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
//     };

//     typedef Node* Node*;
//     Node* root = nullptr;

//     //need to figure out which private member functions for AVL properities are needed
//     //these are inspired by class notes
//     void setHeight(Node* temp);
//     int search(Node* &some, int val);

//     void leftLeftRotation(Node* &temp);
//     void rightRightRotation(Node* &temp);
//     void leftRightRotation(Node* &temp);
//     void rightLeftRotation(Node* &temp);

//     int insertNode(Node* &root, int val);
//     int deleteNode(Node* &root, int val);


//     public:
//     AVLTree() : root(nullptr) {} //default constructor
//     AVLTree(const std::vector<int>& initialValues); //parametrized constructor
//     ~AVLTree(); //destructor

//     //idk figure out which other functions are needed for this
// };


/****************************************************************************
 *                                                                          *
 *                         struct Node Declaration                          *
 *                                                                          *
 ****************************************************************************/
struct Node {
    int value;
    int height;
    int size;
    int numLeft;
    Node* left;
    Node* right;
    Node* parent;

    //node constructor
    Node(int val) : value(val), height(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

    // typedef Node* Node*;
    // extern Node* root;



/****************************************************************************
 *                                                                          *
 *                    AVL Tree Helper Function Declarations                 *
 *                                                                          *
 ****************************************************************************/

// void setHeight(Node* temp);
// int getHeight(Node* node);
// int search(Node* &some, int val);
// Node* leftLeftRotation(Node* &temp);
// Node* rightRightRotation(Node* &temp);
// Node* leftRightRotation(Node* &temp);
// Node* rightLeftRotation(Node* &temp);
// // Node* insertNode(Node* &root, int val, int rank);
// // int insertNode(Node* &root, int val);
// // Node* insertNode(Node* &root, int val, int rank);
// int deleteNode(Node* &root, int val);
// int getBalanceFactor (Node* node);
// void restoreBalance (Node* &node);
// void inOrderPrintByRank(Node* node);
// int findValueByRank(Node* root, int rank, int& currentRank); //testing this out to use with deleteNode function

// //helper function to count nodes in a subtree
// int countNodes(Node* node);

// //currently disorganized helper functions added in for different function ideas
// int findRank(Node* node, int e, int rankOffset = 0);
// void updateSize(Node* node);
// int size(Node* node);
// int elementAtRankHelper(Node* node, int r, int& priorRank);
// int sizeOfSubtree(Node* node);
// void inOrderPrintByRank(Node* node, int& priorRank);
// Node* getNodeAtRank(Node* node, int rank);
// void updateSize3(Node* &node);
// int getBalanceFactor2(Node* &node);
// void setHeight2(Node* &node);
// void shiftRanks(Node* &node);
// int getBalance(Node* node);
// void deleteSubtree(Node* node);
// void inOrderPrintWithChildren(Node* node, int& priorRank);


/****************************************************************************
 *                                                                          *
 *                       class AVLVector declaration                        *
 *                                                                          *
 ****************************************************************************/

class AVLVector {
    private:
    // AVLTree tree;
    Node* root;

    public:
    AVLVector() : root(nullptr) {}
    ~AVLVector();
        Node* getRoot() {
        return root;
    }

    int elementAtRank(int r);
    void replaceAtRank(int r, int e);
    void insertAtRank(int r, int e);
    int removeAtRank(int r);
    int rankOf(int e);
    void printAll();

    void preorder(Node* root);
    void inorder(Node* root);

    // int insertNode(Node* &root, int val, int rank);
    int insertNode(Node* &currentNode, int priorRank, int val, int rank) ;




    //testing!
    int getRootValue() const {
        if (root != nullptr) {
            return root->value;  // Assuming the Node structure has a value attribute
        }
        return -1; // Or some indication that the tree is empty
    }


    void setHeight(Node* temp);
    int getHeight(Node* node);
    int search(Node* &some, int val);
    Node* leftLeftRotation(Node* &temp);
    Node* rightRightRotation(Node* &temp);
    Node* leftRightRotation(Node* &temp);
    Node* rightLeftRotation(Node* &temp);
    // Node* insertNode(Node* &root, int val, int rank);
    // int insertNode(Node* &root, int val);
    // Node* insertNode(Node* &root, int val, int rank);
    int deleteNode(Node* &root, int val);
    int getBalanceFactor (Node* node);
    void restoreBalance (Node* &node);
    void inOrderPrintByRank(Node* node);
    int findValueByRank(Node* root, int rank, int& currentRank); //testing this out to use with deleteNode function

    //helper function to count nodes in a subtree
    int countNodes(Node* node);

    //currently disorganized helper functions added in for different function ideas
    int findRank(Node* node, int e, int rankOffset = 0);
    void updateSize(Node* node);
    int size(Node* node);
    int elementAtRankHelper(Node* node, int r, int& priorRank);
    int sizeOfSubtree(Node* node);
    void inOrderPrintByRank(Node* node, int& priorRank);
    // Node* getNodeAtRank(Node* node, int rank);
    Node* getNodeAtRank(Node* node, int rank, int priorRank = 0);
    void updateSize3(Node* &node);
    int getBalanceFactor2(Node* &node);
    void setHeight2(Node* &node);
    void shiftRanks(Node* &node);
    int getBalance(Node* node);
    void deleteSubtree(Node* node);
    void inOrderPrintWithChildren(Node* node, int& priorRank);
    void preOrderPrintWithChildren(Node* node, int priorRank);

    int searchByRank(Node* &node, int val);
    Node* findNodeByValue(Node* node, int value);

    Node* deleteNodeByRank(Node* &node, int rank);
    Node* findMax(Node* node);


};



#endif