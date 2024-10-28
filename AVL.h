#ifndef AVL_H
#define AVL_H

#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>

using namespace std;


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

    int getRank(int priorRank) {return (priorRank + numLeft + 1);}
};



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
    
    Node* getRoot() {return root;}

    //AVLVector required functions
    int elementAtRank(int r);
    void replaceAtRank(int r, int e);
    void insertAtRank(int r, int e);
    int removeAtRank(int r);
    int rankOf(int e);
    void printAll();

    //helper functions for testing
    void preorder(Node* root);
    void inorder(Node* root);


    int insertNode(Node* &currentNode, int priorRank, int val, int rank);
    int deleteNode(Node* &root, int val);


    int getRootValue() const {
        if (root != nullptr) {
            return root->value; 
        }
        return -1; 
    }

    void setHeight(Node* temp);
    int getHeight(Node* node) {return node->height;}
    Node* leftLeftRotation(Node* &temp);
    Node* rightRightRotation(Node* &temp);
    Node* leftRightRotation(Node* &temp);
    Node* rightLeftRotation(Node* &temp);
    void inOrderPrintByRank(Node* node);
    int countNodes(Node* node);

    int findRank(Node* node, int e, int priorRank = 0);
    int size(Node* node);
    int elementAtRankHelper(Node* node, int r, int& priorRank);
    void inOrderPrintByRank(Node* node, int& priorRank);
    Node* getNodeAtRank(Node* node, int rank, int priorRank = 0);
    void updateSize3(Node* &node);
    void deleteSubtree(Node* node);
    void inOrderPrintWithChildren(Node* node, int& priorRank);

    void updateHeight(Node* node);
    int getBalance(Node* node);

    Node* searchByRankAgain(Node *some, int rank, int priorRank = 0);
    void decrementNumLeft(Node* node);
};



#endif