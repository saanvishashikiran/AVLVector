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
    Node(int val) : value(val), height(0), size(1), numLeft(0), left(nullptr), right(nullptr), parent(nullptr) {}
};



/****************************************************************************
 *                                                                          *
 *                       class AVLVector declaration                        *
 *                                                                          *
 ****************************************************************************/

class AVLVector {
    private:
    Node* root;

    //core helper functions
    void setHeight(Node* node); //sets node height
    int getBalance(Node* node); //gets balance factor
    void updateSize(Node* &node); //updates node size and numLeft
    int insertNode(Node* &currentNode, int priorRank, int val, int rank); //inserts nodes by rank, called in insertAtRank
    Node* searchByRank(Node *some, int rank, int priorRank = 0); //finds the node to be deleted by inputted rank, called in deleteNode
    void decrementNumLeft(Node* node); //calls updateSize to update size and numLeft, called in deleteNode
    int deleteNode(Node* &root, int val); //deletes nodes by rank, called in removeAtRank
    int findRank(Node* node, int e, int priorRank = 0); //finds rank of inputted element, called in rankOf
    int elementAtRankHelper(Node* node, int r, int& priorRank); //finds element at inputted rank, called in elementAtRank
    Node* getNodeAtRank(Node* node, int rank, int priorRank = 0); //gets the node at inputted rank, called in replaceAtRank
    void inOrderPrint(Node* node, int& priorRank); //prints tree (rank and elements in order of rank)
    void deleteTree(Node* node); //destructor helper function for deleting entire tree

    //rotations
    Node* leftLeftRotation(Node* &temp);
    Node* rightRightRotation(Node* &temp);
    Node* leftRightRotation(Node* &temp);
    Node* rightLeftRotation(Node* &temp);

    public:
    AVLVector() : root(nullptr) {} //constructor
    ~AVLVector(); //destructor
    
    //AVLVector required functions
    int elementAtRank(int r);
    int replaceAtRank(int r, int e);
    int insertAtRank(int r, int e);
    int removeAtRank(int r);
    int rankOf(int e);
    void printAll();

    //inline getter functions
    Node* getRoot() {return root;}
    int getHeight(Node* node) {return node->height;}
    int getRootValue() const {
        if (root != nullptr) {
            return root->value; 
        }
        return -1; 
    }
};



#endif