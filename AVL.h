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

//     typedef Node* nodeptr;
//     nodeptr root = nullptr;

//     //need to figure out which private member functions for AVL properities are needed
//     //these are inspired by class notes
//     void setHeight(nodeptr temp);
//     int search(nodeptr &some, int val);

//     void leftLeftRotation(nodeptr &temp);
//     void rightRightRotation(nodeptr &temp);
//     void leftRightRotation(nodeptr &temp);
//     void rightLeftRotation(nodeptr &temp);

//     int insertNode(nodeptr &root, int val);
//     int deleteNode(nodeptr &root, int val);


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
    Node* left;
    Node* right;
    Node* parent;

    //node constructor
    Node(int val) : value(val), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

    typedef Node* nodeptr;
    extern nodeptr root;



/****************************************************************************
 *                                                                          *
 *                    AVL Tree Helper Function Declarations                 *
 *                                                                          *
 ****************************************************************************/

void setHeight(nodeptr temp);
int getHeight(nodeptr node);
int search(nodeptr &some, int val);
nodeptr leftLeftRotation(nodeptr &temp);
nodeptr rightRightRotation(nodeptr &temp);
nodeptr leftRightRotation(nodeptr &temp);
nodeptr rightLeftRotation(nodeptr &temp);
// nodeptr insertNode(nodeptr &root, int val, int rank);
// int insertNode(nodeptr &root, int val);
// nodeptr insertNode(nodeptr &root, int val, int rank);
int deleteNode(nodeptr &root, int val);
int getBalanceFactor (nodeptr node);
void restoreBalance (nodeptr &node);
void inOrderPrintByRank(nodeptr node);
int findValueByRank(nodeptr root, int rank, int& currentRank); //testing this out to use with deleteNode function

//helper function to count nodes in a subtree
int countNodes(nodeptr node);

//currently disorganized helper functions added in for different function ideas
int findRank(nodeptr node, int e, int rankOffset = 0);
void updateSize(nodeptr node);
int size(nodeptr node);
int elementAtRankHelper(nodeptr node, int r, int& priorRank);
int sizeOfSubtree(nodeptr node);
void inOrderPrintByRank(nodeptr node, int& priorRank);
nodeptr getNodeAtRank(nodeptr node, int rank);
void updateSize3(nodeptr &node);
int getBalanceFactor2(nodeptr &node);
void setHeight2(nodeptr &node);
void shiftRanks(nodeptr &node);
int getBalance(nodeptr node);
void deleteSubtree(nodeptr node);
void inOrderPrintWithChildren(nodeptr node, int& priorRank);


/****************************************************************************
 *                                                                          *
 *                       class AVLVector declaration                        *
 *                                                                          *
 ****************************************************************************/

class AVLVector {
    private:
    // AVLTree tree;
    nodeptr root;

    public:
    AVLVector() : root(nullptr) {}
    ~AVLVector();

    int elementAtRank(int r);
    void replaceAtRank(int r, int e);
    void insertAtRank(int r, int e);
    void removeAtRank(int r);
    int rankOf(int e);
    void printAll();

    int insertNode(nodeptr &root, int val, int rank);


    nodeptr getRoot() {
        return root;
    }

    //testing!
    int getRootValue() const {
        if (root != nullptr) {
            return root->value;  // Assuming the Node structure has a value attribute
        }
        return -1; // Or some indication that the tree is empty
    }


};



#endif