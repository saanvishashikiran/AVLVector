#include "AVL.h"

// //setting root to nullptr
// Node* root = nullptr;

/****************************************************************************
 *                                                                          *
 *                      AVL Tree Helper Functions                           *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
 ****************************************************************************/

void AVLVector::setHeight(Node *temp)
{
    int heightLeft, heightRight;
    if (temp != NULL)
    {
        // if (temp->left == NULL) {
        //     heightLeft = 0;
        // } else {
        //     heightLeft = temp->left->height + 1;
        // }

        // if (temp->right == NULL) {
        //     heightRight = 0;
        // } else {
        //     heightRight = temp->right->height + 1;
        // }

        // temp->height = (heightLeft > heightRight) ? heightLeft : heightRight;

        // trying out this code instead of given code, fix given code though
        setHeight(temp->left);
        setHeight(temp->right);

        // int heightLeft = (temp->left != NULL) ? temp->left->height : -1; // -1 for NULL children
        // int heightRight = (temp->right != NULL) ? temp->right->height : -1; // -1 for NULL children
        if (temp->left != NULL)
        {
            heightLeft = temp->left->height; // getting the height of the left child
        }
        else
        {
            heightLeft = -1; // -1 for NULL children
        }

        if (temp->right != NULL)
        {
            heightRight = temp->right->height; // getting the height of the right child
        }
        else
        {
            heightRight = -1; // -1 for NULL children
        }

        temp->height = 1 + max(heightLeft, heightRight);
    }
}

/****************************************************************************
 *                      AVLTree getHeight Helper Function                   *
 ****************************************************************************/

int AVLVector::getHeight(Node *node)
{
    // if (node == NULL) {
    //     return -1; // Convention: height of an empty tree is -1
    // }
    return node->height; // Return the height stored in the node
}

/****************************************************************************
 *                       AVLTree search Helper Function                     *
 ****************************************************************************/

int AVLVector::search(Node *&some, int val)
{
    if (some == NULL)
    {
        return -1;
    }

    bool done = false;
    while (!done)
    {
        if (some->value == val)
        {
            return 1;
        }
        else if (some->value > val)
        {
            some = some->left;
        }
        else
        {
            some = some->right;
        }

        if (some == NULL)
        {
            return -1;
        }
    }

    return -1; // for now
}

/****************************************************************************
 *                    AVLTree insertNode Helper Function                    *
 ****************************************************************************/

int AVLVector::insertNode(Node *&currentNode, int priorRank, int val, int rank)
{
    if (currentNode == NULL)
    {
        currentNode = new Node(val);
        currentNode->size = 1;   // this node is the only node in its subtree
        currentNode->height = 0; // single node has height 0, NOT ONE, THAT WAS WRONG.
        currentNode->numLeft = 0;
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->parent = NULL;
        cout << "currentNode was NULL" << endl;
        return 1;
    }

    Node *temp = currentNode;
    // int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;
    int currentNodeRank = temp->numLeft + priorRank + 1;

    // inserting into the left subtree or at the current node's rank
    if (rank <= currentNodeRank)
    { // modifying to be <
        cout << "inserting " << val << " into left subtree or at current node rank" << endl;
        // If inserting at a rank that collides, shift ranks of all subsequent nodes
        if (rank == temp->numLeft + 1)
        {
            shiftRanks(temp->right); // shifting nodes in the right subtree
        }
        // Insert into the left subtree
        int result = insertNode(temp->left, priorRank, val, rank);
        temp->left->parent = temp;
        temp->numLeft += 1;
        cout << "new numLeft is of " << temp->value << " is: " << temp->numLeft << endl;
    }
    // inserting into the right subtree
    else
    {
        cout << "inserting " << val << " into right subtree" << endl;
        // Adjust rank for insertion into the right subtree
        priorRank = currentNodeRank;
        int result = insertNode(temp->right, priorRank, val, rank);
        temp->right->parent = temp;
    }

    // updating size and height after insertion
    updateSize3(temp);
    updateHeight(temp);

    // balancing the tree
    int balanceFactor = getBalance(temp);
    if (balanceFactor > 1)
    {
        int leftBalanceFactor = getBalance(temp->left);
        if (leftBalanceFactor >= 0)
        {
            cout << "left left case while inserting " << val << endl;
            temp = leftLeftRotation(temp); // left-left case
        }
        else
        {
            cout << "left right case while inserting " << val << endl;
            temp = leftRightRotation(temp); // left-right case
        }
    }
    else if (balanceFactor < -1)
    {
        int rightBalanceFactor = getBalance(temp->right);
        if (rightBalanceFactor <= 0)
        {
            cout << "right right case while inserting " << val << endl;
            temp = rightRightRotation(temp); // right-right case
        }
        else
        {
            cout << "right left case while inserting " << val << endl;
            temp = rightLeftRotation(temp); // right-left case
            cout << "after RL rotation, numLeft of " << temp->value << " is: " << temp->numLeft << endl;
        }
    }

    // adding in
    currentNode = temp;

    return 1;
}

// helper function to update the size of a node
void AVLVector::updateSize3(Node *&node)
{
    if (node == NULL)
        return;
    int leftSize = (node->left != NULL) ? node->left->size : 0;
    int rightSize = (node->right != NULL) ? node->right->size : 0;
    node->size = leftSize + rightSize + 1;
    node->numLeft = leftSize; // adding in
    cout << "inside of updateSize3, numLeft of " << node->value << " is: " << node->numLeft << endl;
}





// function for calculating balance factor of a node
int AVLVector::getBalanceFactor2(Node *&node)
{
    if (node == NULL)
        return 0;
    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

// function for updating height of a node
void AVLVector::setHeight2(Node *&node)
{
    if (node == NULL)
        return;

    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;

    node->height = max(leftHeight, rightHeight) + 1;
}

int AVLVector::getBalance(Node *nd)
{
    // Purpose: return the net balance between the right and left subtrees of a node, where the right
    //          subtree has a "negative" pull, and the left subtree has a "positive" pull.
    // Runtime: O(1)

    int leftHeight, rightHeight;
    if (!nd)
    {
        return 0;
    }
    if (!nd->left && !nd->right)
        return 0;
    if (!nd->left)
    {
        leftHeight = -1;
        rightHeight = getHeight(nd->right);
        return leftHeight - rightHeight;
    }
    if (!nd->right)
    {
        rightHeight = -1;
        leftHeight = getHeight(nd->left);
        return leftHeight - rightHeight;
    }

    leftHeight = getHeight(nd->left);
    rightHeight = getHeight(nd->right);

    return leftHeight - rightHeight;
}

/***************************************************************************************************
 *************************************** updateHeight method ***************************************
 ***************************************************************************************************/

void AVLVector::updateHeight(Node *nd)
{
    // Purpose: Set the height of a given node to 1 + the max of the heights of its left and right
    //          subtrees. Primarily used after rotations were completed to update heights.
    // Runtime: O(1)

    if (nd)
    {
        if (!nd->left && !nd->right)
            nd->height = 0;
        else if (!nd->left)
            nd->height = getHeight(nd->right) + 1;
        else if (!nd->right)
            nd->height = getHeight(nd->left) + 1;
        else if (nd->left && nd->right)
        {
            nd->height = 1 + max(getHeight(nd->left), getHeight(nd->right));
        }
    }
}

// helper function for shifting ranks of nodes in the right subtree
void AVLVector::shiftRanks(Node *&node)
{
    if (node == NULL)
        return;

    Node *temp = node;
    // Perform rank shift on the current node
    while (temp != NULL)
    {
        updateSize(temp);   // Update the size of the current node
        temp = temp->right; // Shift to the next node in the right subtree
    }
}

/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
 *****************************************************************************/

// Node* AVLVector::leftLeftRotation(Node* &temp)
// {
//     //identifying nodes in rotation
//     Node* temp1 = temp->left;
//     Node* temp2 = temp1->left;

//     //reassinging parent pointers
//     temp1->parent = temp->parent;
//     temp->parent = temp1;

//     temp->left = temp1->right;
//     temp1->right = temp;
//     if (temp1->parent != NULL)
//     {
//         if (temp1->parent->left == temp) {
//             temp1->parent->left = temp1;
//         } else {
//             temp1->parent->right = temp1;
//         }
//     }
//     setHeight(temp);
//     setHeight(temp1);
//     temp = temp1;

//     return temp;
// }

// maybe this should be void.
Node *AVLVector::leftLeftRotation(Node *&temp)
{
    Node *temp1 = temp->left;

    // updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    // reassigning child pointers
    temp->left = temp1->right;
    if (temp->left != NULL)
        temp->left->parent = temp; // ensuring temp->left's parent is updated
    temp1->right = temp;

    // updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    // reassigning parent's child pointer to the new root (temp1)
    if (temp1->parent != NULL)
    {
        if (temp1->parent->left == temp)
        {
            temp1->parent->left = temp1;
        }
        else
        {
            temp1->parent->right = temp1;
        }
    }

    // updating height and size
    updateSize3(temp);   // updating size for temp (original root)
    updateSize3(temp1);  // updating size for new root temp1
    updateHeight(temp);  // updating height for temp
    updateHeight(temp1); // updating height for temp1

    // temp=temp1;

    return temp1;
}

/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
 *****************************************************************************/

// Node* AVLVector::rightRightRotation(Node* &temp)
// {
//     Node* temp1 = temp->right;
//     Node* temp2 = temp1->right;
//     temp1->parent = temp->parent;
//     temp->parent = temp1;
//     temp->right = temp1->left;
//     temp1->left = temp;
//     if (temp1->parent != NULL)
//     {
//         if (temp1->parent->right == temp) {
//             temp1->parent->right = temp1;
//         } else {
//             temp1->parent->left = temp1;
//         }
//     }
//     setHeight(temp);
//     setHeight(temp1);
//     temp = temp1;

//     return temp;
// }

Node *AVLVector::rightRightRotation(Node *&temp)
{
    Node *temp1 = temp->right;

    // updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    // reassigning child pointers
    temp->right = temp1->left;
    if (temp->right != NULL)
        temp->right->parent = temp; // ensuring temp->right's parent is updated
    temp1->left = temp;

    // updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    // reassigning parent's child pointer to the new root (temp1)
    if (temp1->parent != NULL)
    {
        if (temp1->parent->right == temp)
        {
            temp1->parent->right = temp1;
        }
        else
        {
            temp1->parent->left = temp1;
        }
    }

    // updating height and size
    updateSize3(temp);   // updating size for temp (original root)
    updateSize3(temp1);  // updating size for new root temp1
    updateHeight(temp);  // updating height for temp
    updateHeight(temp1); // updating height for temp1

    // temp = temp1;

    return temp1;
}

/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
 *****************************************************************************/

// Node* AVLVector::leftRightRotation(Node* &temp)
// {
//     Node* temp1 = temp->left;
//     Node* temp2 = temp1->right;
//     temp2->parent = temp->parent;
//     temp1->parent = temp2;
//     temp->parent = temp2;
//     temp->left = temp2->right;
//     temp1->right = temp2->left;
//     if (temp2->parent != NULL)
//     {
//         if (temp2->parent->right == temp) {
//             temp2->parent->right = temp2;
//         } else {
//             temp2->parent->left = temp2;
//         }
//     }
//     setHeight(temp);
//     setHeight(temp1);
//     setHeight(temp2);
//     temp = temp2;

//     return temp;
// }

Node *AVLVector::leftRightRotation(Node *&temp)
{
    Node *temp1 = temp->left;
    Node *temp2 = temp1->right;

    // updating parent pointers
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;

    // reassigning child pointers
    temp1->right = temp2->left;
    if (temp1->right != NULL)
        temp1->right->parent = temp1;
    temp->left = temp2->right;
    if (temp->left != NULL)
        temp->left->parent = temp;

    temp2->left = temp1;
    temp2->right = temp;

    // reassigning parent's child pointer to the new root (temp2)
    if (temp2->parent != NULL)
    {
        if (temp2->parent->left == temp)
        {
            temp2->parent->left = temp2;
        }
        else
        {
            temp2->parent->right = temp2;
        }
    }

    // updating numLeft after rotation
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;

    // updating height and size
    updateSize3(temp);   // updating size for temp (original root)
    updateSize3(temp1);  // updating size for temp1
    updateSize3(temp2);  // updating size for new root temp2
    updateHeight(temp);  // updating height for temp
    updateHeight(temp1); // updating height for temp1
    updateHeight(temp2); // updating height for temp2

    // WAS MISSING THIS CHECK IF I NEED IT, would need it if it was void i think.
    //  temp = temp2;

    return temp2;
}

/****************************************************************************
 *                  AVLTree rightLeftRotation Helper Function               *
 *****************************************************************************/

// Node* AVLVector::rightLeftRotation(Node* &temp)
// {
//     Node* temp1 = temp->right;
//     Node* temp2 = temp1->left;
//     temp2->parent = temp->parent;
//     temp1->parent = temp2;
//     temp->parent = temp2;
//     temp->right = temp2->left;
//     temp1->left = temp2->right;
//     if (temp2->parent != NULL)
//     {
//         if (temp2->parent->right == temp) {
//             temp2->parent->right = temp2;
//         } else {
//             temp2->parent->left = temp2;
//         }
//     }
//     setHeight(temp);
//     setHeight(temp1);
//     setHeight(temp2);
//     temp = temp2;

//     return temp;
// }

Node *AVLVector::rightLeftRotation(Node *&temp)
{
    Node *temp1 = temp->right;
    Node *temp2 = temp1->left;

    // updating parent pointers
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;

    // reassigning child pointers
    temp1->left = temp2->right;
    if (temp1->left != NULL)
        temp1->left->parent = temp1;
    temp->right = temp2->left;
    if (temp->right != NULL)
        temp->right->parent = temp;

    temp2->right = temp1;
    temp2->left = temp;

    // reassigning parent's child pointer to the new root (temp2)
    if (temp2->parent != NULL)
    {
        if (temp2->parent->right == temp)
        {
            temp2->parent->right = temp2;
        }
        else
        {
            temp2->parent->left = temp2;
        }
    }

    // updating numLeft after rotation
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;

    // updating height and size
    updateSize3(temp);   // updating size for temp (original root)
    updateSize3(temp1);  // updating size for temp1
    updateSize3(temp2);  // updating size for new root temp2
    updateHeight(temp);  // updating height for temp
    updateHeight(temp1); // updating height for temp1
    updateHeight(temp2); // updating height for temp2

    return temp2;
}

/****************************************************************************
 *                    AVLTree deleteNode Helper Function                    *
 *****************************************************************************/
// int getBalance(Node* node) {
//     if (node == nullptr)
//         return 0;  // If the node is null, the balance is 0 (tree is empty)

//     int leftHeight = (node->left != nullptr) ? node->left->height : -1;
//     int rightHeight = (node->right != nullptr) ? node->right->height : -1;

//     return leftHeight - rightHeight;  // Balance factor = height of left subtree - height of right subtree
// }

// int deleteNode(Node* &root, int val)
// {
//     if (root == nullptr) return -1;  // Tree is empty

//     Node* temp = root;
//     Node* parent = nullptr;

//     //searching for the node to delete
//     while (temp != nullptr && temp->value != val) {
//         parent = temp;
//         if (val < temp->value) {
//             temp = temp->left;
//         } else {
//             temp = temp->right;
//         }
//     }

//     //node not found
//     if (temp == nullptr) {
//         return -1;
//     }

//     //case 1: node has no children and is thus a leaf node
//     if (temp->left == nullptr && temp->right == nullptr) {
//         if (temp == root) {
//             root = nullptr;  // If the node to delete is the root and it's a leaf
//         } else if (parent->left == temp) {
//             parent->left = nullptr;
//         } else {
//             parent->right = nullptr;
//         }
//         delete temp;
//     }
//     //case 2: node has only one child (left or right)
//     else if (temp->left == nullptr || temp->right == nullptr) {
//         Node* child = (temp->left != nullptr) ? temp->left : temp->right;
//         if (temp == root) {
//             root = child;  // If the node to delete is the root
//         } else if (parent->left == temp) {
//             parent->left = child;
//         } else {
//             parent->right = child;
//         }
//         delete temp;
//     }
//     //case 3: node has two children
//     else {
//         Node* successor = temp->left;  // Find the in-order predecessor (max node in left subtree)
//         parent = temp;

//         while (successor->right != nullptr) {
//             parent = successor;
//             successor = successor->right;
//         }

//         // Replace the value of temp with the successor's value
//         temp->value = successor->value;

//         // Now delete the successor node
//         if (parent->left == successor) {
//             parent->left = successor->left;  // The successor has no right child
//         } else {
//             parent->right = successor->left;  // The successor has no right child
//         }

//         delete successor;
//     }

//     //rebalancing the tree and updating heights after deletion
//     while (root != nullptr) {
//         setHeight(root);

//         int balance = getBalance(root);  // Get the balance factor

//         if (balance > 1) {
//             if (getBalance(root->left) >= 0) {
//                 // Perform right rotation
//                 root = rightRightRotation(root);
//             } else {
//                 // Perform left-right rotation
//                 root = leftRightRotation(root);
//             }
//         }
//         else if (balance < -1) {
//             if (getBalance(root->right) <= 0) {
//                 // Perform left rotation
//                 root = leftLeftRotation(root);
//             } else {
//                 // Perform right-left rotation
//                 root = rightLeftRotation(root);
//             }
//         }

//         root = root->parent;  //moving up the tree
//     }

//     return 1;  //node successfully deleted
// }

// given code modified
//  int AVLVector::deleteNode(Node* &root, int rank)
//  {
//      Node* temp = root;
//      Node* temp1;
//      if (temp == NULL) {
//          return -1;
//      }
//      if (searchByRank(temp, rank) == -1) {
//          return -1;
//      }
//      // temp now points to the item you want to delete
//      temp1 = temp;
//      if (temp->left == NULL)
//      {
//          if (temp == root)
//          {
//              root = root->right;
//              root->parent = NULL;
//          }
//          else
//          {
//              temp1 = temp->parent;
//              if (temp1->left == temp) {
//                  temp1->left = temp->right;
//              } else {
//                  temp1->right = temp->right;
//              }
//              delete temp;
//              setHeight(temp1);
//              temp = temp1;
//          }
//      }
//      else
//      { //temp->left not NULL
//          temp1 = temp->left;
//          while (temp1->right != NULL)
//              temp1 = temp1->right;
//          temp->value = temp1->value;
//          temp = temp1->parent;
//          if (temp->left == temp1) {
//              temp->left = temp1->left;
//          } else {
//              temp->right = temp1->left;
//          }
//          setHeight(temp);
//          delete temp1;
//      }

//     while (temp != NULL)
//     {
//         //adding this in to debug
//         setHeight(temp);

//         if (temp->height >= 2)
//         {
//             if (temp->left == NULL)
//             {
//                 if (temp->right->right == NULL) {
//                     rightLeftRotation(temp);
//                 } else {
//                     rightRightRotation(temp);
//                 }
//             } else if (temp->right == NULL) {
//                 if (temp->left->left == NULL) {
//                     leftRightRotation(temp);
//                 }
//                 else {
//                     leftLeftRotation(temp);
//                 }
//             } else if (temp->left->height - temp->right->height > 1) {
//                 if (temp->left->left->height >= temp->left->right->height) {
//                     leftLeftRotation(temp);
//                 } else {
//                     leftRightRotation(temp);
//                 }
//             } else if (temp->right->height - temp->left->height > 1) {
//                 if (temp->right->right->height >= temp->right->left->height) {
//                     rightRightRotation(temp);
//                 }
//                 else {
//                     rightLeftRotation(temp);
//                 }
//             }
//         } // else of temp->left == NULL
//         temp = temp->parent;
//     } // if temp->height >=2
//     setHeight(temp); //COMMENTING OUT TO TEST

//     return 1; //for now
// }

int AVLVector::deleteNode2(Node *&node, int priorRank, int rank)
{
    if (node == NULL)
        return -1; // Base case: not found

    // Calculate the current node's rank
    int currentRank = priorRank + node->numLeft + 1;

    // Traversing to the correct rank
    if (rank < currentRank)
    {
        return deleteNode2(node->left, priorRank, rank);
    }
    else if (rank > currentRank)
    {
        return deleteNode2(node->right, currentRank, rank);
    }
    else
    {
        // Node to be deleted is found
        if (node->left == NULL && node->right == NULL)
        {
            // Node has no children
            delete node;
            node = NULL;
            return 1; // Success
        }
        else if (node->left == NULL)
        {
            // Node has only a right child
            Node *rightChild = node->right;
            rightChild->parent = node->parent; // Re-linking
            delete node;
            node = rightChild; // Update the current node
            return 1;          // Success
        }
        else if (node->right == NULL)
        {
            // Node has only a left child
            Node *leftChild = node->left;
            leftChild->parent = node->parent; // Re-linking
            delete node;
            node = leftChild; // Update the current node
            return 1;         // Success
        }
        else
        {
            // Node has two children, find in-order predecessor
            Node *predecessor = findMax(node->left);
            node->value = predecessor->value; // Swap values
            // Now delete the predecessor
            return deleteNode2(node->left, priorRank, predecessor->numLeft + 1);
        }
    }

    // Rebalancing the tree after deletion
    updateSize3(node);
    setHeight2(node);

    int balanceFactor = getBalanceFactor2(node);

    // Left-heavy case
    if (balanceFactor > 1)
    {
        if (getBalanceFactor2(node->left) >= 0)
        {
            node = leftLeftRotation(node);
        }
        else
        {
            node = leftRightRotation(node);
        }
    }
    // Right-heavy case
    if (balanceFactor < -1)
    {
        if (getBalanceFactor2(node->right) <= 0)
        {
            node = rightRightRotation(node);
        }
        else
        {
            node = rightLeftRotation(node);
        }
    }

    return 1; // Deletion successful
}

/****************************************************************************
 *                 AVLTree getBalanceFactor Helper Function                 *
 ****************************************************************************/

int AVLVector::getBalanceFactor(Node *node)
{
    if (node == nullptr)
        return 0;
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

/****************************************************************************
 *                       AVLTree Balance Helper Function                    *
 ****************************************************************************/

void AVLVector::restoreBalance(Node *&node)
{
    if (node == nullptr)
        return;

    int balanceFactor = getBalanceFactor(node);

    // left heavy tree
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(node->left) >= 0)
        {
            node = rightRightRotation(node);
        }
        else
        {
            node = leftRightRotation(node);
        }
    }
    else if (balanceFactor < -1)
    {
        if (getBalanceFactor(node->right) <= 0)
        {
            node = leftLeftRotation(node);
        }
        else
        {
            node = rightLeftRotation(node);
        }
    }
}

int AVLVector::sizeOfSubtree(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return sizeOfSubtree(node->left) + sizeOfSubtree(node->right) + 1;
}

/****************************************************************************
 *                   AVLTree inOrderPrint Helper Function                   *
 ****************************************************************************/

void AVLVector::inOrderPrintByRank(Node *node, int &priorRank)
{
    if (node != nullptr)
    {
        // Traverse the left subtree first
        inOrderPrintByRank(node->left, priorRank);

        // The rank of the current node is based on the prior rank + 1
        int currentRank = priorRank + node->numLeft + 1;

        // Print the current node's value and its calculated rank
        cout << "Element: " << node->value << " | Rank: " << currentRank << endl;

        // Update priorRank to the current rank
        priorRank = currentRank;

        // Traverse the right subtree
        inOrderPrintByRank(node->right, priorRank);
    }
}

// simple inorder for testing
void AVLVector::inorder(Node *root)
{
    if (!root)
        return;

    inorder(root->left);
    cout << root->value << " " << root->numLeft << " " << root->height << endl;
    inorder(root->right);
}

// simple preorder for testing
void AVLVector::preorder(Node *root)
{
    if (!root)
        return;
    cout << root->value << " " << root->numLeft << " " << root->height << endl;
    preorder(root->left);
    preorder(root->right);
}

void AVLVector::inOrderPrintWithChildren(Node *node, int &priorRank)
{
    if (node != nullptr)
    {
        inOrderPrintWithChildren(node->left, priorRank);

        // Print current node
        int currentRank = priorRank + 1;
        cout << "Element: " << node->value << " | Rank: " << currentRank;

        // Left child
        if (node->left != nullptr)
        {
            cout << " | Left Child: " << node->left->value;
        }
        else
        {
            cout << " | Left Child: None";
        }

        // Right child
        if (node->right != nullptr)
        {
            cout << " | Right Child: " << node->right->value;
        }
        else
        {
            cout << " | Right Child: None";
        }

        cout << endl;

        priorRank = currentRank;

        inOrderPrintWithChildren(node->right, priorRank);
    }
}

void AVLVector::preOrderPrintWithChildren(Node *node, int priorRank)
{
    if (node != nullptr)
    {
        // Calculate the rank of the current node
        int currentRank = priorRank + size(node->left) + 1;

        // Print current node details
        cout << "Element: " << node->value << " | Rank: " << currentRank;

        // Left child
        if (node->left != nullptr)
        {
            cout << " | Left Child: " << node->left->value;
        }
        else
        {
            cout << " | Left Child: None";
        }

        // Right child
        if (node->right != nullptr)
        {
            cout << " | Right Child: " << node->right->value;
        }
        else
        {
            cout << " | Right Child: None";
        }

        cout << endl;

        // Recurse on the left subtree with the same priorRank
        preOrderPrintWithChildren(node->left, priorRank);

        // Recurse on the right subtree with the updated priorRank after processing left subtree
        preOrderPrintWithChildren(node->right, currentRank);
    }
}

/****************************************************************************
 *                 AVLTree findValueByRank Helper Function                  *
 ****************************************************************************/

int AVLVector::findValueByRank(Node *root, int rank, int &currentRank)
{
    if (root == NULL)
        return -1; // Base case: If the root is NULL, the rank is out of bounds.

    // Traverse the left subtree first
    int leftResult = findValueByRank(root->left, rank, currentRank);
    if (leftResult != -1)
    {
        return leftResult; // Found the rank in the left subtree
    }

    // Increment the current rank (this node's rank in the in-order traversal)
    currentRank++;

    // If the current rank matches the requested rank, return the value of this node
    if (currentRank == rank)
    {
        return root->value;
    }

    // Otherwise, continue the traversal in the right subtree
    return findValueByRank(root->right, rank, currentRank);
}

// helper function to count nodes in a subtree
int AVLVector::countNodes(Node *node)
{
    if (!node)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

// int AVLVector::findRank(Node* node, int e, int rankOffset) {
//     if (!node) return -1; // Element not found

//     //if the current node matches the element
//     if (node->value == e) {
//         //returning the rank
//         return countNodes(node->left); //only counting nodes in the left subtree
//     }

//     //searching in the left subtree if the element is smaller
//     if (e < node->value) {
//         return findRank(node->left, e);
//     } else {
//         //searching in the right subtree if the element is larger
//         int leftCount = countNodes(node->left); //counting nodes in left subtree
//         int rightRank = findRank(node->right, e); //recursively finding rank in right subtree
//         void setHeight(Node* temp);
//         if (rightRank == -1) return -1; //element not found in right subtree
//         return leftCount + 1 + rightRank; //include left count and current node
//     }
// }

int AVLVector::findRank(Node *node, int e, int rankOffset)
{
    if (!node)
        return -1; // Element not found

    // If the current node matches the element
    if (node->value == e)
    {
        // Returning the rank, which is the count of nodes in the left subtree plus the rankOffset
        return rankOffset + countNodes(node->left);
    }

    // Searching in the left subtree if the element is smaller
    if (e < node->value)
    {
        return findRank(node->left, e, rankOffset); // Pass rankOffset unchanged
    }
    else
    {
        // Searching in the right subtree if the element is larger
        int leftCount = countNodes(node->left); // Count of nodes in the left subtree
        // Include the leftCount and the current node's rank in rankOffset
        int rightRank = findRank(node->right, e, rankOffset + leftCount + 1);
        return rightRank; // Returning the rank found in the right subtree
    }
}

void AVLVector::updateSize(Node *node)
{
    if (node != nullptr)
    {
        node->size = 1 + size(node->left) + size(node->right);
    }
}

int AVLVector::size(Node *node)
{
    if (!node)
        return 0;                                    // Base case: no nodes
    return 1 + size(node->left) + size(node->right); // Count the current node plus left and right subtrees
}

int AVLVector::elementAtRankHelper(Node *node, int r, int &priorRank)
{
    if (node == nullptr)
    {
        return -1; // returning -1 if rank is out of bounds
    }

    // traversing the left subtree first
    int leftResult = elementAtRankHelper(node->left, r, priorRank);
    if (leftResult != -1)
    {
        return leftResult; // If the left subtree returns a valid result, propagate it upwards
    }

    // increment the rank and check if it matches after left traversal
    priorRank++;
    cout << "Visiting Node: " << node->value << " | Calculated Rank: " << priorRank << endl;

    if (priorRank == r)
    {
        cout << "\nElement at rank " << priorRank << " is " << node->value << "!\n"
             << endl;
        return node->value; // Found the node with the desired rank
    }

    // traversing the right subtree if element is not found yet
    return elementAtRankHelper(node->right, r, priorRank);
}

Node *AVLVector::getNodeAtRank(Node *node, int rank, int priorRank)
{
    // base case of whether node is not found
    if (!node)
    {
        return nullptr;
    }

    int leftSize = size(node->left);            // getting size of left subtree
    int currentRank = leftSize + priorRank + 1; // calculating rank using rank formula from class

    if (rank == currentRank)
    {
        return node; // YAY found the node at the requested rank!
    }
    else if (rank < currentRank)
    {
        // going left, priorRank stays the same
        return getNodeAtRank(node->left, rank, priorRank);
    }
    else
    {
        // go right, updating priorRank to currentRank
        priorRank = currentRank;
        return getNodeAtRank(node->right, rank, priorRank);
    }
}

/****************************************************************************
 *                                                                          *
 *                 class AVLVector Constructors & Destructor                *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                           AVLVector Destructor                           *
 ****************************************************************************/

AVLVector::~AVLVector()
{
    deleteSubtree(root);
}

/****************************************************************************
 *             AVLVector Destructor Tree Deletion Helper Function           *
 ****************************************************************************/

void AVLVector::deleteSubtree(Node *node)
{
    if (node == nullptr)
        return;

    // recursively deleting left and right children
    deleteSubtree(node->left);
    deleteSubtree(node->right);

    // deleting the current node
    delete node;
}

/****************************************************************************
 *                                                                          *
 *                          class AVLVector Methods                         *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                     AVLVector elementAtRank Function                     *
 ****************************************************************************/

int AVLVector::elementAtRank(int r)
{
    int priorRank = 0;
    return elementAtRankHelper(root, r, priorRank);
}

/****************************************************************************
 *                     AVLVector replaceAtRank Function                     *
 ****************************************************************************/

void AVLVector::replaceAtRank(int r, int e)
{
    if (r <= 0 || r > size(root))
    {
        throw out_of_range("Rank is out of bounds");
    }

    Node *node = getNodeAtRank(root, r);
    if (node)
    {
        node->value = e; // Replace the value
    }
    else
    {
        throw runtime_error("Node at rank not found");
    }
}

/****************************************************************************
 *                     AVLVector insertAtRank Function                      *
 **************************************************************************x*/

void AVLVector::insertAtRank(int r, int e)
{
    if (root == NULL)
    {
        // manual insert
        Node *newNode = new Node(e);
        newNode->size = 1;   // this node is the only node in its subtree
        newNode->height = 1; // single node has height 1
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        root = newNode;
        cout << "root was NULL" << endl;
    }
    else
    {
        int priorRank = 0;
        insertNode(root, priorRank, e, r);
    }

    // int result = insertNode(pointer, e, r);
    // if (result != 1) {
    //     cout << "Error, insert unsuccessful..." << endl;
    // }
}

/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
 ****************************************************************************/

int AVLVector::removeAtRank(int r) {
    if (r < 1 || r > size(root)) return -1; // Invalid rank

    // Call the deletion function to remove the node at rank r
    int result = deletion(root, r); // deletion returns 1 on success, -1 on failure

    if (root != NULL) {
        root->parent = NULL;  // Ensure the root's parent is always NULL
    }

    return result; // Return the result of deletion (1 on success, -1 on failure)
}


int AVLVector::searchByRank(Node *&node, int rank)
{
    if (node == nullptr)
    {
        return -1; // Not found
    }

    if (rank == node->numLeft + 1)
    {
        // The current node is the one we're looking for (rank matches)
        // return node->value; // Return the value at this rank
        return 1;
    }
    else if (rank <= node->numLeft)
    {
        // Search in the left subtree
        return search(node->left, rank);
    }
    else
    {
        // Search in the right subtree, adjusting rank accordingly
        return search(node->right, rank - node->numLeft - 1);
    }
}

Node *AVLVector::findNodeByValue(Node *node, int value)
{
    if (node == nullptr)
    {
        return nullptr; // Not found
    }

    if (node->value == value)
    {
        return node; // Found the node
    }
    else if (value < node->value)
    {
        return findNodeByValue(node->left, value); // Search left subtree
    }
    else
    {
        return findNodeByValue(node->right, value); // Search right subtree
    }
}

// current delete function

// //function from last night collab
// bool AVLVector::deleteNodee(int rank)
// {
//     bool isDeleted = false;

//     if(1 != 1)
//     {
//         //CODE FOR IF THERE IS ONLY ONE NODE THE TREE
//     }
//     else
//     {
//         int priorRank = 0;
//         Node* current = root;
//         Node* bottom;

//         while(current != NULL && !isDeleted)
//         {
//             int currRank = current->getRank(priorRank);

//             if(rank < currRank)
//             {
//                 current->numLeft--;
//                 current = current->left;
//             }
//             else if(rank == currRank)
//             {
//                 if(!current->left && !current->right)
//                 {
//                     //optional: decrement size of tree
//                     Node* par = current->parent;
//                     if(par->left == current)
//                     {
//                         par->left = NULL;
//                     }
//                     else if(par->right == current)
//                     {
//                         par->right = NULL;
//                     }
//                     delete current;
//                     current = NULL;

//                     bottom = par;
//                     isDeleted = true;

//                 }
//                 else if(!current->right)
//                 {
//                     Node* par = current->parent;
//                     Node* leftChild = current->left;
//                     if(par->left == current)
//                     {
//                         par->left = leftChild;
//                     }
//                     else if(par->right == current)
//                     {
//                         par->right = leftChild;
//                     }
//                     leftChild->parent = par;
//                     delete current;
//                     current = NULL;
//                     bottom = leftChild;
//                     isDeleted = true;
//                 }
//                 else if(!current->left)
//                 {
//                     Node* par = current->parent;
//                     Node* rightChild = current->right;
//                     if(par->left == current)
//                     {
//                         par->left = rightChild;
//                     }
//                     else if(par->right == current)
//                     {
//                         par->right = rightChild;
//                     }
//                     rightChild->parent = par;
//                     delete current;
//                     current = NULL;
//                     bottom = rightChild;
//                     isDeleted = true;
//                 }
//                 else
//                 {
//                     current->numLeft--;
//                     Node* original = current;
//                     current = current->left;
//                     while(current->right)
//                     {
//                         current = current->right;
//                     }
//                     //At this point, current is equal to the node you wanna swap original with.
//                     original->value = current->value;
//                     if(current->left) //this implies that current has a left child.
//                     {
//                         Node* par = current->parent;
//                         Node* leftChild = current->left;
//                         par->right = leftChild;
//                         leftChild->parent = par;
//                         delete current;
//                         current = NULL;
//                         bottom = leftChild;
//                         isDeleted = true;
//                     }
//                     else //this implies that current is a leaf
//                     {
//                         Node* par = current->parent;
//                         par->right = NULL;
//                         delete current;
//                         current = NULL;
//                         bottom = par;
//                         isDeleted = true;
//                     }
//                 }

//             }
//             else //case where rank > currRank
//             {
//                 priorRank = currRank;
//                 current = current->right;
//             }
//         } //end WHILE LOOP

//         balanceTreeAfterInsertion(bottom);
//     }
//     return true;
// }

// GIVES CORRECT TREE AFTER INSERTION OF 31 AT RANK 1, but deletes rank 11 when i say to delete 13...
bool AVLVector::deleteNodee(int rank)
{
    bool isDeleted = false;
    Node *current = root;
    Node *bottom = NULL;
    int priorRank = 0;

    while (current != NULL && !isDeleted)
    {
        int currRank = current->getRank(priorRank); // Calculate current node's rank

        if (rank < currRank)
        {
            current->numLeft--; // Decrease left subtree size since we're moving left
            current = current->left;
        }
        else if (rank == currRank)
        {
            // Found the node to delete
            if (!current->left && !current->right)
            {
                // Leaf node deletion
                Node *par = current->parent;
                if (par != NULL)
                {
                    if (par->left == current)
                        par->left = NULL;
                    else
                        par->right = NULL;
                }
                else
                {
                    root = NULL; // Tree only had one node
                }
                delete current;
                current = NULL;
                bottom = par;
                isDeleted = true;
            }
            else if (!current->right)
            {
                // Node has only left child
                Node *par = current->parent;
                Node *leftChild = current->left;
                if (par != NULL)
                {
                    if (par->left == current)
                        par->left = leftChild;
                    else
                        par->right = leftChild;
                }
                else
                {
                    root = leftChild;
                }
                leftChild->parent = par;
                delete current;
                current = NULL;
                bottom = leftChild;
                isDeleted = true;
            }
            else if (!current->left)
            {
                // Node has only right child
                Node *par = current->parent;
                Node *rightChild = current->right;
                if (par != NULL)
                {
                    if (par->left == current)
                        par->left = rightChild;
                    else
                        par->right = rightChild;
                }
                else
                {
                    root = rightChild;
                }
                rightChild->parent = par;
                delete current;
                current = NULL;
                bottom = rightChild;
                isDeleted = true;
            }
            else
            {
                // Node has two children, find the in-order predecessor (rightmost of left subtree)
                current->numLeft--; // Adjust numLeft as we're going to swap with a node in the left subtree
                Node *original = current;
                priorRank = current->getRank(priorRank); // Get the current node's rank

                current = current->left; // Go to left subtree
                while (current->right)
                {
                    current = current->right; // Find the rightmost node
                }

                // Swap the values between the current node and the rightmost node of the left subtree
                original->value = current->value;

                // Now delete the rightmost node
                if (current->left)
                {
                    Node *par = current->parent;
                    Node *leftChild = current->left;
                    if (par->right == current)
                        par->right = leftChild;
                    else
                        par->left = leftChild;

                    leftChild->parent = par;
                    delete current;
                    current = NULL;
                    bottom = leftChild;
                }
                else
                {
                    Node *par = current->parent;
                    if (par->right == current)
                        par->right = NULL;
                    else
                        par->left = NULL;

                    delete current;
                    current = NULL;
                    bottom = par;
                }
                isDeleted = true;
            }
        }
        else // rank > currRank, move to the right subtree
        {
            priorRank = currRank + 1; // Update priorRank when moving right
            current = current->right;
        }
    }

    // Balance the tree after deletion
    if (bottom != NULL)
    {
        balanceTreeAfterInsertion(bottom);
    }

    return isDeleted;
}

/***************************************************************************************************
 ********************************** balanceTreeAfterInsertion method *******************************
 ***************************************************************************************************/

void AVLVector::balanceTreeAfterInsertion(Node *insertedNode)
{
    // Purpose: This function starts at a newly inserted leaf and traverses up the tree, checking if
    //          each subtree is an AVL tree. If it is not, then it performs the appropriate rotation.
    //          If it is an AVL tree, it simply continues traversing up the tree. Called by insert
    //          function.
    // Runtime: O(log(n)), the base of the logarithm is 2, and n is the number of nodes in the tree.

    Node *current = insertedNode->parent;
    while (current != NULL)
    {
        // Update height
        updateHeight(current);

        // Get balance factor
        int balance = getBalance(current);

        if (balance > 1) // this means the left subtree had a height greater than the right by more
        {                // than 1
            if (getBalance(current->left) >= 0)
            {
                leftLeftRotation(current);
            }
            else
            {
                // Left Right Case
                leftRightRotation(current);
            }
        }
        else if (balance < -1) // this means that the right subtree had a height greater than the
        {                      // left by more than 1
            if (getBalance(current->right) <= 0)
            {
                // Right Right Case
                rightRightRotation(current);
            }
            else
            {
                // Right Left Case
                rightLeftRotation(current);
            }
        }
        current = current->parent;
    }
}

Node *AVLVector::deleteNodeByRank(Node *&node, int rank)
{
    if (node == NULL)
        return NULL;

    // int leftSize = size(node->left);
    int currentNodeRank = node->numLeft + 1;

    // traversing to the correct rank
    if (rank < currentNodeRank)
    {
        node->left = deleteNodeByRank(node->left, rank);
    }
    else if (rank > currentNodeRank)
    {
        node->right = deleteNodeByRank(node->right, rank - currentNodeRank);
    }
    else
    {
        // node to be deleted is found
        if (node->left == NULL && node->right == NULL)
        {
            // node w/ no children
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            // node w/ only right child
            Node *rightChild = node->right;
            rightChild->parent = node->parent; // ensuring correct re-linking
            delete node;
            return rightChild;
        }
        else if (node->right == NULL)
        {
            // node w/ only left child
            Node *leftChild = node->left;
            leftChild->parent = node->parent; // ensuring correct re-linking
            delete node;
            return leftChild;
        }
        else
        {
            // node with two children, find in-order predecessor
            Node *predecessor = findMax(node->left);
            node->value = predecessor->value;                         // swapping values
            node->left = deleteNodeByRank(node->left, node->numLeft); // deleting predecessor
        }
    }

    // rebalancing and update size/height
    updateSize3(node);
    updateHeight(node);

    int balanceFactor = getBalance(node);

    // tree is LEFT heavy
    if (balanceFactor > 1)
    {
        if (getBalance(node->left) >= 0)
        {
            return leftLeftRotation(node);
        }
        else
        {
            return leftRightRotation(node);
        }
    }
    // tree is RIGHT heavy
    if (balanceFactor < -1)
    {
        if (getBalance(node->right) <= 0)
        {
            return rightRightRotation(node);
        }
        else
        {
            return rightLeftRotation(node);
        }
    }

    return node;
}

Node *AVLVector::deleteNodeByRank2(Node *&node, int priorRank, int rank)
{
    if (node == NULL)
        return NULL;

    // int leftSize = size(node->left);
    int currentNodeRank = node->numLeft + priorRank + 1;

    // traversing to the correct rank
    if (rank < currentNodeRank)
    {
        node->left = deleteNodeByRank2(node->left, priorRank, rank);
    }
    else if (rank > currentNodeRank)
    {
        node->right = deleteNodeByRank2(node->right, currentNodeRank, rank - currentNodeRank);
    }
    else
    {
        // node to be deleted is found
        if (node->left == NULL && node->right == NULL)
        {
            // node w/ no children
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            // node w/ only right child
            Node *rightChild = node->right;
            rightChild->parent = node->parent; // ensuring correct re-linking
            delete node;
            return rightChild;
        }
        else if (node->right == NULL)
        {
            // node w/ only left child
            Node *leftChild = node->left;
            leftChild->parent = node->parent; // ensuring correct re-linking
            delete node;
            return leftChild;
        }
        else
        {
            // node with two children, find in-order predecessor
            Node *predecessor = findMax(node->left);
            node->value = predecessor->value;                                        // swapping values
            node->left = deleteNodeByRank2(node->left, 0, predecessor->numLeft + 1); // deleting predecessor
        }
    }

    // rebalancing and update size/height
    updateSize3(node);
    updateHeight(node);

    int balanceFactor = getBalance(node);

    // tree is LEFT heavy
    if (balanceFactor > 1)
    {
        if (getBalance(node->left) >= 0)
        {
            return leftLeftRotation(node);
        }
        else
        {
            return leftRightRotation(node);
        }
    }
    // tree is RIGHT heavy
    if (balanceFactor < -1)
    {
        if (getBalanceFactor2(node->right) <= 0)
        {
            return rightRightRotation(node);
        }
        else
        {
            return rightLeftRotation(node);
        }
    }

    return node;
}






// void AVLVector::decrementNumLeft(Node* node) {
//     // Traverse up to the root, decrementing numLeft for each node that has the current node in its left subtree
//     while (node != NULL) {
//         if (node->left != NULL) {
//             node->numLeft--;  // Decrement numLeft if this node's left child is involved in deletion
//         }
//         node = node->parent;
//     }
// }



void AVLVector::decrementNumLeft(Node* node) {
    // Traverse up to the root, decrementing numLeft for each node that has the current node in its left subtree
    while (node != NULL) {
        updateSize3(node);
        node = node->parent;
    }
}




// void AVLVector::decrementNumLeft(Node* node, Node* deletedNode) {
//     // Traverse up to the root, decrementing numLeft for each node that has the deleted node in its left subtree
//     while (node != NULL) {
//         // Check if the deletedNode was part of this node's left subtree
//         if (node->left == deletedNode || isDescendant(node->left, deletedNode)) {
//             node->numLeft--; // Decrement numLeft if the deleted node or one of its descendants is in the left subtree
//         }
//         node = node->parent; // Continue traversal upwards
//     }
// }

// // Helper function to check if a node is a descendant of another
// bool AVLVector::isDescendant(Node* ancestor, Node* node) {
//     while (ancestor != NULL) {
//         if (ancestor == node) return true;
//         ancestor = ancestor->left; // Check only left descendants
//     }
//     return false;
// }



Node* AVLVector::searchByRankAgain(Node *some, int rank, int priorRank) {
    if (some == NULL) {
        return NULL; // Rank not found
    }

    while (some != NULL) {
        int currentRank = priorRank + some->numLeft + 1; // Use numLeft to calculate current rank
        // Debugging print statement to observe rank calculation
        cout << "Visiting node with value " << some->value << ", currentRank: " << currentRank << ", priorRank: " << priorRank << endl;

        if (currentRank == rank) {
            return some; // Return the node at the given rank
        } 
        else if (rank < currentRank) {
            // Move to the left subtree, no need to update priorRank here
            some = some->left;
        } 
        else {
            // Move to the right subtree, but we must carefully update priorRank
            priorRank = currentRank; // priorRank should now include the current node's rank
            some = some->right;
        }
    }

    return NULL; // Rank not found
}


int AVLVector::deletion(Node* &root, int rank) {
    Node* temp = searchByRankAgain(root, rank); // Get the node at the given rank
    if (temp == NULL) {
        return -1; // Node at rank not found
    }

    //debugging statement
    cout << "temp (node to be deleted) is currently: " << temp->value << endl;

    Node* temp1;
    if (temp->left == NULL) { //empty left subtree!
        if (temp == root) {
            root = root->right;
            if (root != NULL) root->parent = NULL;
        } else {
            temp1 = temp->parent;
            //debugging statement
            cout << "temp1 (parent of node to be deleted) is currently: " << temp1->value << endl;
            if (temp1->left == temp) {
                temp1->left = temp->right;
                // temp1->numLeft--; //adding in
                // decrementNumLeft(temp1);
            } else
                temp1->right = temp->right;
            if (temp->right != NULL) temp->right->parent = temp1; //not in his code but needed to make temp parent of whatever was in temp1's subtree that got shifted
            delete temp;
            updateHeight(temp1);
            temp = temp1;
        }
    } else { //temp->left not NULL
        temp1 = temp->left;
        while (temp1->right != NULL)
            temp1 = temp1->right;
        //debugging statement
        cout << "temp1 (rightmost node in node to be deleted's left subtree—replacement value) is currently: " << temp1->value << endl;
        temp->value = temp1->value; // Copy value from predecessor
        temp = temp1->parent; 
        if (temp->left == temp1) {
            temp->left = temp1->left;
            // temp->numLeft--;
            // decrementNumLeft(temp);  // Call helper function to update numLeft up the tree
        } else
            temp->right = temp1->left;
        if (temp1->left != NULL) temp1->left->parent = temp; //not in his code but needed to make temp parent of whatever was in temp1's subtree that got shifted
        updateHeight(temp);
        delete temp1;
    }

    Node* parentNode = temp->parent;
    // if (parentNode != NULL && parentNode->left == temp) {
    //     parentNode->numLeft--;  // Decrement numLeft for the parent if the deleted node was a left child
    //     decrementNumLeft(parentNode);  // Propagate numLeft decrement up the tree
    // }

    decrementNumLeft(temp);

    // if (parentNode != NULL) {
    //     if (parentNode->left == temp) {
    //         parentNode->numLeft--;  // Decrement numLeft for the parent if the deleted node was a left child
    //         updateSize3(parentNode);
    //     }

    //     parentNode = parentNode->parent;
    //     Node* previousNode = temp->parent;
    //     decrementNumLeft(parentNode, previousNode);  // Propagate numLeft decrement up the tree
    // }

    // Rebalance the tree and adjust heights
    while (temp != NULL) {
        if (temp->height >= 2) {
            if (temp->left == NULL) {
                if (temp->right->right == NULL)
                    rightLeftRotation(temp);
                else
                    rightRightRotation(temp);
            }
            else if (temp->right == NULL) {
                if (temp->left->left == NULL)
                    leftRightRotation(temp);
                else
                    leftLeftRotation(temp);
            }
            else if (temp->left->height - temp->right->height > 1) {
                if (temp->left->left->height >= temp->left->right->height)
                    leftLeftRotation(temp);
                else
                    leftRightRotation(temp);
            }
            else if (temp->right->height - temp->left->height > 1) {
                if (temp->right->right->height >= temp->right->left->height)
                    rightRightRotation(temp);
                else
                    rightLeftRotation(temp);
            }
        }
        temp = temp->parent;
        updateHeight(temp);
    }

    return 1; // Successfully deleted
}


// Find the maximum node in the left subtree (in-order predecessor)
Node *AVLVector::findMax(Node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

// int AVLVector::removeAtRank(int r)
// {
//     // int result = deleteNode(root, r);
//     Node* temp = root;
//     Node* temp1;
//     if (temp == NULL) return -1;
//     if (searchByRank(temp, r) == -1) return -1;

//     // temp now points to the item you want to delete
//     temp1 = temp;
//     if (temp->left == NULL)
//     {
//         if (temp == root)
//         {
//             root = root->right;
//             root->parent = NULL;
//         }
//         else
//         {
//             temp1 = temp->parent;
//             if (temp1->left == temp) {
//                 temp1->left = temp->right;
//             } else {
//                 temp1->right = temp->right;
//             }
//             delete temp;
//             setHeight(temp1);
//             temp = temp1;
//         }
//     }
//     else
//     { //temp->left not NULL
//         temp1 = temp->left;
//         while (temp1->right != NULL)
//             temp1 = temp1->right;
//         temp->value = temp1->value;
//         temp = temp1->parent;
//         if (temp->left == temp1) {
//             temp->left = temp1->left;
//         } else {
//             temp->right = temp1->left;
//         }
//         setHeight(temp);
//         delete temp1;
//     }

//     while (temp != NULL)
//     {
//         //adding this in to debug
//         setHeight(temp);

//         if (temp->height >= 2)
//         {
//             if (temp->left == NULL)
//             {
//                 if (temp->right->right == NULL) {
//                     rightLeftRotation(temp);
//                 } else {
//                     rightRightRotation(temp);
//                 }
//             } else if (temp->right == NULL) {
//                 if (temp->left->left == NULL) {
//                     leftRightRotation(temp);
//                 }
//                 else {
//                     leftLeftRotation(temp);
//                 }
//             } else if (temp->left->height - temp->right->height > 1) {
//                 if (temp->left->left->height >= temp->left->right->height) {
//                     leftLeftRotation(temp);
//                 } else {
//                     leftRightRotation(temp);
//                 }
//             } else if (temp->right->height - temp->left->height > 1) {
//                 if (temp->right->right->height >= temp->right->left->height) {
//                     rightRightRotation(temp);
//                 }
//                 else {
//                     rightLeftRotation(temp);
//                 }
//             }
//         } // else of temp->left == NULL
//         temp = temp->parent;
//     } // if temp->height >=2
//     //setHeight(temp); //COMMENTING OUT TO TEST

//     return 1; //for now
// }

// not used rn.
//  int AVLVector::getBalance(Node* node) {
//      if (node == nullptr) {
//          return 0;
//      }
//      return size(node->left) - size(node->right);
//  }

// int AVLVector::removeAtRank(int r) {
//     int valueToDelete = searchByRank(root, r);
//     if (valueToDelete == -1) {
//         return -1; // Rank not found
//     }

//     // Find the node corresponding to the value to delete
//     Node* target = findNodeByValue(root, valueToDelete);
//     if (target == nullptr) {
//         return -1; // Node not found (shouldn't happen)
//     }

//     // Handle deletion logic
//     Node* temp = target;

//     if (temp->left == nullptr) {
//         // Node has no left child
//         if (temp == root) {
//             root = temp->right; // If it's the root
//         } else {
//             // Update parent's child pointer
//             if (temp->parent->left == temp) {
//                 temp->parent->left = temp->right;
//             } else {
//                 temp->parent->right = temp->right;
//             }
//         }
//         if (temp->right != nullptr) {
//             temp->right->parent = temp->parent; // Update child's parent
//         }
//         delete temp;
//     } else {
//         // Node has a left child
//         Node* successor = temp->left;
//         while (successor->right != nullptr) {
//             successor = successor->right; // Find max in left subtree
//         }
//         temp->value = successor->value; // Copy value from successor

//         // Remove the successor
//         if (successor->left != nullptr) {
//             // If successor has a left child
//             if (successor->parent->left == successor) {
//                 successor->parent->left = successor->left;
//             } else {
//                 successor->parent->right = successor->left;
//             }
//             successor->left->parent = successor->parent; // Update child's parent
//         } else {
//             // If successor has no left child
//             if (successor->parent->left == successor) {
//                 successor->parent->left = nullptr;
//             } else {
//                 successor->parent->right = nullptr;
//             }
//         }
//         delete successor;
//     }

//     // Rebalance the tree starting from the parent of the deleted node
//     Node* current = temp->parent; // Start from the parent of the deleted node
//     while (current != nullptr) {
//         setHeight(current); // Update height

//         // Check balance and perform rotations if necessary
//         if (getBalance(current) > 1) {
//             // Left heavy
//             if (getBalance(current->left) < 0) {
//                 // Left-Right case
//                 leftRightRotation(current);
//             } else {
//                 // Left-Left case
//                 rightRightRotation(current);
//             }
//         } else if (getBalance(current) < -1) {
//             // Right heavy
//             if (getBalance(current->right) > 0) {
//                 // Right-Left case
//                 rightLeftRotation(current);
//             } else {
//                 // Right-Right case
//                 leftLeftRotation(current);
//             }
//         }

//         current = current->parent; // Move up the tree
//     }

//     return 1; // Successful deletion
// }

/****************************************************************************
 *                   Extra Credit: AVLVector rankOf Function                *
 ****************************************************************************/

// int AVLVector::rankOf(int e)
// {
//     int result = findRank(root, e);
//     if (result == -1) {
//         cout << "Error: Element not found\n";
//         return -1;
//     }
//     int rank = result + 1;
//     return rank;
// }
int AVLVector::rankOf(int e)
{
    int result = findRank(root, e, 0); // Start with rankOffset of 0
    if (result == -1)
    {
        cout << "Error: Element not found\n";
        return -1;
    }
    return result + 1; // Adjust for 1-based rank
}

/****************************************************************************
 *                        AVLVector printAll Function                       *
 ****************************************************************************/

void AVLVector::printAll()
{
    int priorRank = 0;
    // inOrderPrintByRank(root, priorRank);
    inOrderPrintWithChildren(root, priorRank);
    cout << endl;
}