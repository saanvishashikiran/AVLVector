#include "AVL.h"

/****************************************************************************
 *                                                                          *
 *                 class AVLTree Constructors & Destructor                  *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                   AVLTree Parametrized Constructor                       *
*****************************************************************************/

AVLTree::AVLTree(const std::vector<int>& initialValues) {

}



/****************************************************************************
 *                             AVLTree Destructor                           *
*****************************************************************************/

AVLTree::~AVLTree() {

}



/****************************************************************************
 *                                                                          *
 *                  class AVLTree Private Helper Functions                  *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
*****************************************************************************/

void AVLTree::setHeight(nodeptr temp) {
    int heightLeft, heightRight;
    if (temp!=NULL) {
        if (temp->left == NULL) heightLeft = 0;
        else heightLeft = temp->left->height +1;
        if (temp->right == NULL) heightRight = 0;
        else heightRight= temp->right->height +1;
        temp->height = (heightLeft > heightRight) ? heightLeft: heightRight;
    }
}



/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
*****************************************************************************/

void AVLTree::leftLeftRotation(nodeptr &temp) {
    nodeptr temp1 = temp->left;
    nodeptr temp2 = temp1->left;
    temp1->parent = temp->parent;
    temp->parent = temp1;
    temp->left = temp1->right;
    temp1->right= temp;
    if (temp1->parent != NULL) {
        if (temp1->parent->left == temp) temp1->parent->left = temp1;
        else temp1->parent->right = temp1;
    }
    setHeight(temp);
    setHeight(temp1);
    temp=temp1;
}



/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
*****************************************************************************/

void AVLTree::rightRightRotation(nodeptr &temp) {
    nodeptr temp1 = temp->right;
    nodeptr temp2 = temp1->right;
    temp1->parent = temp->parent;
    temp->parent = temp1;
    temp->right = temp1->left;
    temp1->left= temp;
    if (temp1->parent != NULL) {
        if (temp1->parent->right == temp) temp1->parent->right = temp1;
        else temp1->parent->left = temp1;
    }
    setHeight(temp);
    setHeight(temp1);
    temp = temp1;
}



/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
*****************************************************************************/

void AVLTree::leftRightRotation(nodeptr &temp) {
    nodeptr temp1 = temp->left;
    nodeptr temp2 = temp1->right;
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;
    temp->left = temp2->right;
    temp1->right = temp2->left;
    if (temp2->parent != NULL) {
        if (temp2->parent->right == temp) temp2->parent->right = temp2;
        else temp2->parent->left = temp2;
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;
}



/****************************************************************************
 *                  AVLTree rightLeftRotation Helper Function               *
*****************************************************************************/

void AVLTree::rightLeftRotation(nodeptr &temp) {
    nodeptr temp1 = temp->right;
    nodeptr temp2 = temp1->left;
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;
    temp->right= temp2->left;
    temp1->left = temp2->right;
    if (temp2->parent != NULL) {
        if (temp2->parent->right == temp) temp2->parent->right = temp2;
        else temp2->parent->left = temp2;
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;
}



/****************************************************************************
 *                    AVLTree insertNode Helper Function                    *
*****************************************************************************/

int AVLTree::insertNode(nodeptr &root, int val) {
    

    //for now
    return 0;
}


/****************************************************************************
 *                    AVLTree deleteNode Helper Function                    *
*****************************************************************************/

int AVLTree::deleteNode(nodeptr &root, int val) {

    //for now
    return 0;
}



/****************************************************************************
 *                                                                          *
 *                          class AVLTree Methods                           *
 *                                                                          *
 ****************************************************************************/






/****************************************************************************
 *                                                                          *
 *                 class AVLVector Constructors & Destructor                *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                          AVLVector Constructor                           *
*****************************************************************************/

AVLVector::AVLVector() {
    
}



/****************************************************************************
 *                           AVLVector Destructor                           *
*****************************************************************************/

AVLVector::~AVLVector() {

}



/****************************************************************************
 *                                                                          *
 *                          class AVLVector Methods                         *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                     AVLVector elementAtRank Function                     *
*****************************************************************************/

int elementAtRank(int r) {
    
    
    //for now
    return 0;
}



/****************************************************************************
 *                     AVLVector replaceAtRank Function                     *
*****************************************************************************/

void replaceAtRank(int r, int e) {


}



/****************************************************************************
 *                     AVLVector insertAtRank Function                     *
*****************************************************************************/

void insertAtRank(int r, int e) {


}


/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
*****************************************************************************/

void removeAtRank(int r) {



}


/****************************************************************************
 *                          AVLVector rankOf Function                       *
*****************************************************************************/

int rankOf(int e) {


    //for now
    return 0;
}
    

  
/****************************************************************************
 *                        AVLVector printAll Function                       *
*****************************************************************************/
  
void printAll() {

}