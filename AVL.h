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
int search(nodeptr &some, int val);
void leftLeftRotation(nodeptr &temp);
void rightRightRotation(nodeptr &temp);
void leftRightRotation(nodeptr &temp);
void rightLeftRotation(nodeptr &temp);
int insertNode(nodeptr &root, int val);
int deleteNode(nodeptr &root, int val);
void inOrder(nodeptr node, vector<int>& vector);
int getBalanceFactor (nodeptr node);
void restoreBalance (nodeptr &node);



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
};



#endif