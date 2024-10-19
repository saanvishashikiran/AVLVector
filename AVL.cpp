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

void AVLVector::setHeight(Node* temp)
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

        //trying out this code instead of given code, fix given code though
        setHeight(temp->left);
        setHeight(temp->right);

        // int heightLeft = (temp->left != NULL) ? temp->left->height : -1; // -1 for NULL children
        // int heightRight = (temp->right != NULL) ? temp->right->height : -1; // -1 for NULL children
        if (temp->left != NULL) {
            heightLeft = temp->left->height; //getting the height of the left child
        } else {
            heightLeft = -1; // -1 for NULL children
        }

        if (temp->right != NULL) {
            heightRight = temp->right->height; //getting the height of the right child
        } else {
            heightRight = -1; // -1 for NULL children
        }

        temp->height = 1 + max(heightLeft, heightRight);
    }
}



/****************************************************************************
 *                      AVLTree getHeight Helper Function                   *
 ****************************************************************************/

int AVLVector::getHeight(Node* node) {
    if (node == NULL) {
        return -1; // Convention: height of an empty tree is -1
    }
    return node->height; // Return the height stored in the node
}



/****************************************************************************
 *                       AVLTree search Helper Function                     *
 ****************************************************************************/

int AVLVector::search(Node* &some, int val)
{
    if (some == NULL) {
        return -1;
    }

    bool done = false;
    while (!done)
    {
        if (some->value == val) {
            return 1;
        } else if (some->value > val) {
            some = some->left;
        } else {
            some = some->right;
        }

        if (some == NULL) {
            return -1;
        }
    }

    return -1; //for now
}





/****************************************************************************
 *                    AVLTree insertNode Helper Function                    *
 ****************************************************************************/

int AVLVector::insertNode(Node* &currentNode, int priorRank, int val, int rank) {
    if (currentNode == NULL) {
        currentNode = new Node(val);
        currentNode->size = 1;  // this node is the only node in its subtree
        currentNode->height = 1;  // single node has height 0, NOT ONE, THAT WAS WRONG.
        currentNode->numLeft = 0;
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->parent = NULL;
        cout << "currentNode was NULL" << endl;
        return 1;
    }

    Node* temp = currentNode;
    // int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;
    int currentNodeRank = temp->numLeft + priorRank + 1;

    //inserting into the left subtree or at the current node's rank
    if (rank <= currentNodeRank) { //modifying to be <
        cout << "inserting " << val << " into left subtree or at current node rank" << endl;
        // If inserting at a rank that collides, shift ranks of all subsequent nodes
        if (rank == temp->numLeft + 1) {
            shiftRanks(temp->right);  //shifting nodes in the right subtree
        }
        // Insert into the left subtree
        int result = insertNode(temp->left, priorRank, val, rank);
        temp->left->parent = temp;
        temp->numLeft += 1;
    } 
    //inserting into the right subtree
    else {
        cout << "inserting " << val << " into right subtree" << endl;
        // Adjust rank for insertion into the right subtree
        priorRank = currentNodeRank;
        int result = insertNode(temp->right, priorRank, val, rank);
        temp->right->parent = temp;
    }

    //updating size and height after insertion
    updateSize3(temp);
    setHeight2(temp);

    //balancing the tree
    int balanceFactor = getBalanceFactor2(temp);
    if (balanceFactor > 1) {
        int leftBalanceFactor = getBalanceFactor2(temp->left);
        if (leftBalanceFactor >= 0) {
            cout << "left left case while inserting " << val <<  endl;
            temp = leftLeftRotation(temp);  //left-left case
        } else {
            cout << "left right case while inserting " << val << endl;
            temp = leftRightRotation(temp);  //left-right case
        }
    } else if (balanceFactor < -1) {
        int rightBalanceFactor = getBalanceFactor2(temp->right);
        if (rightBalanceFactor <= 0) {
            cout << "right right case while inserting " << val << endl;
            temp = rightRightRotation(temp);  //right-right case
        } else {
            cout << "right left case while inserting " << val << endl;
            temp = rightLeftRotation(temp);  //right-left case
        }
    }

    //adding in
    currentNode = temp;

    return 1;
}


//helper function to update the size of a node
void AVLVector::updateSize3(Node* &node) {
    if (node == NULL) return;
    int leftSize = (node->left != NULL) ? node->left->size : 0;
    int rightSize = (node->right != NULL) ? node->right->size : 0;
    node->size = leftSize + rightSize + 1;
    node->numLeft = leftSize; // adding in
}

// //function for calculating balance factor of a node
int AVLVector::getBalanceFactor2(Node* &node) {
    if (node == NULL) return 0;
    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

//function for updating height of a node
void AVLVector::setHeight2(Node* &node) {
    if (node == NULL) return;
    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + 1;
}

//helper function for shifting ranks of nodes in the right subtree
void AVLVector::shiftRanks(Node* &node) {
    if (node == NULL) return;

    Node* temp = node;
    // Perform rank shift on the current node
    while (temp != NULL) {
        updateSize(temp);  // Update the size of the current node
        temp = temp->right;  // Shift to the next node in the right subtree
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


Node* AVLVector::leftLeftRotation(Node* &temp)
{   
    Node* temp1 = temp->left;

    //updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    //reassigning child pointers
    temp->left = temp1->right;
    if (temp->left != NULL) temp->left->parent = temp;  //ensuring temp->left's parent is updated
    temp1->right = temp;

    //updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    //reassigning parent's child pointer to the new root (temp1)
    if (temp1->parent != NULL)
    {
        if (temp1->parent->left == temp) {
            temp1->parent->left = temp1;
        } else {
            temp1->parent->right = temp1;
        }
    }

    //updating height and size
    updateSize3(temp);  //updating size for temp (original root)
    updateSize3(temp1);  //updating size for new root temp1
    setHeight2(temp);    //updating height for temp
    setHeight2(temp1);   //updating height for temp1

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


Node* AVLVector::rightRightRotation(Node* &temp)
{
    Node* temp1 = temp->right;

    //updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    //reassigning child pointers
    temp->right = temp1->left;
    if (temp->right != NULL) temp->right->parent = temp;  //ensuring temp->right's parent is updated
    temp1->left = temp;

    //updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    //reassigning parent's child pointer to the new root (temp1)
    if (temp1->parent != NULL)
    {
        if (temp1->parent->right == temp) {
            temp1->parent->right = temp1;
        } else {
            temp1->parent->left = temp1;
        }
    }

    //updating height and size
    updateSize3(temp);  //updating size for temp (original root)
    updateSize3(temp1);  //updating size for new root temp1
    setHeight2(temp);    //updating height for temp
    setHeight2(temp1);   //updating height for temp1

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

Node* AVLVector::leftRightRotation(Node* &temp)
{
    Node* temp1 = temp->left;
    Node* temp2 = temp1->right;

    //updating parent pointers
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;

    //reassigning child pointers
    temp1->right = temp2->left;
    if (temp1->right != NULL) temp1->right->parent = temp1;
    temp->left = temp2->right;
    if (temp->left != NULL) temp->left->parent = temp;

    temp2->left = temp1;
    temp2->right = temp;

    //reassigning parent's child pointer to the new root (temp2)
    if (temp2->parent != NULL)
    {
        if (temp2->parent->left == temp) {
            temp2->parent->left = temp2;
        } else {
            temp2->parent->right = temp2;
        }
    }

    //updating numLeft after rotation
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;

    //updating height and size
    updateSize3(temp);   //updating size for temp (original root)
    updateSize3(temp1);  //updating size for temp1
    updateSize3(temp2);  //updating size for new root temp2
    setHeight2(temp);    //updating height for temp
    setHeight2(temp1);   //updating height for temp1
    setHeight2(temp2);   //updating height for temp2

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

Node* AVLVector::rightLeftRotation(Node* &temp)
{
    Node* temp1 = temp->right;
    Node* temp2 = temp1->left;

    //updating parent pointers
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;

    //reassigning child pointers
    temp1->left = temp2->right;
    if (temp1->left != NULL) temp1->left->parent = temp1;
    temp->right = temp2->left;
    if (temp->right != NULL) temp->right->parent = temp;

    temp2->right = temp1;
    temp2->left = temp;

    //reassigning parent's child pointer to the new root (temp2)
    if (temp2->parent != NULL)
    {
        if (temp2->parent->right == temp) {
            temp2->parent->right = temp2;
        } else {
            temp2->parent->left = temp2;
        }
    }

    //updating numLeft after rotation
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;

    //updating height and size
    updateSize3(temp);   //updating size for temp (original root)
    updateSize3(temp1);  //updating size for temp1
    updateSize3(temp2);  //updating size for new root temp2
    setHeight2(temp);    //updating height for temp
    setHeight2(temp1);   //updating height for temp1
    setHeight2(temp2);   //updating height for temp2

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



//given code
int AVLVector::deleteNode(Node* &root, int val)
{
    Node* temp = root;
    Node* temp1;
    if (temp == NULL) {
        return -1;
    }
    if (search(temp, val) == -1) {
        return -1;
    }
    // temp now points to the item you want to delete
    temp1 = temp;
    if (temp->left == NULL)
    {
        if (temp == root)
        {
            root = root->right;
            root->parent = NULL;
        }
        else
        {
            temp1 = temp->parent;
            if (temp1->left == temp) {
                temp1->left = temp->right;
            } else {
                temp1->right = temp->right;
            }
            delete temp;
            setHeight(temp1);
            temp = temp1;
        }
    }
    else
    { //temp->left not NULL
        temp1 = temp->left;
        while (temp1->right != NULL)
            temp1 = temp1->right;
        temp->value = temp1->value;
        temp = temp1->parent;
        if (temp->left == temp1) {
            temp->left = temp1->left;
        } else {
            temp->right = temp1->left;
        }
        setHeight(temp);
        delete temp1;
    }

    while (temp != NULL)
    {
        //adding this in to debug
        setHeight(temp);

        if (temp->height >= 2)
        {
            if (temp->left == NULL)
            {
                if (temp->right->right == NULL) {
                    rightLeftRotation(temp);
                } else {
                    rightRightRotation(temp);
                }
            } else if (temp->right == NULL) {
                if (temp->left->left == NULL) {
                    leftRightRotation(temp);
                }
                else {
                    leftLeftRotation(temp);
                }
            } else if (temp->left->height - temp->right->height > 1) {
                if (temp->left->left->height >= temp->left->right->height) {
                    leftLeftRotation(temp);
                } else {
                    leftRightRotation(temp);
                }
            } else if (temp->right->height - temp->left->height > 1) {
                if (temp->right->right->height >= temp->right->left->height) {
                    rightRightRotation(temp);
                }
                else {
                    rightLeftRotation(temp);
                }
            }
        } // else of temp->left == NULL
        temp = temp->parent;
    } // if temp->height >=2
    //setHeight(temp); //COMMENTING OUT TO TEST

    return 1; //for now
}



/****************************************************************************
 *                 AVLTree getBalanceFactor Helper Function                 *
 ****************************************************************************/

int AVLVector::getBalanceFactor (Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}



/****************************************************************************
 *                       AVLTree Balance Helper Function                    *
 ****************************************************************************/

void AVLVector::restoreBalance (Node* &node) {
    if (node == nullptr) return;

    int balanceFactor = getBalanceFactor(node);

    //left heavy tree
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
            node = rightRightRotation(node);
        } else {
            node = leftRightRotation(node);
        }
    } else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            node = leftLeftRotation(node);
        } else {
            node = rightLeftRotation(node);
        }
    }

}

int AVLVector::sizeOfSubtree(Node* node) {
    if (node == nullptr) {
        return 0;
    } 

    return sizeOfSubtree(node->left) + sizeOfSubtree(node->right) + 1;
}



/****************************************************************************
 *                   AVLTree inOrderPrint Helper Function                   *
 ****************************************************************************/
 
void AVLVector::inOrderPrintByRank(Node* node, int& priorRank) {
    if (node != nullptr) {
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



//simple inorder for testing
void AVLVector::inorder(Node* root)
{
    if(!root) return;

    inorder(root->left);
    cout << root->value << " " << root->numLeft << " " << root->height << endl;
    inorder(root->right);
}



//simple preorder for testing
void AVLVector::preorder(Node* root)
{
    if(!root) return;
    cout << root->value << " " << root->numLeft << " " << root->height << endl;
    preorder(root->left);
    preorder(root->right);
}



void AVLVector::inOrderPrintWithChildren(Node* node, int& priorRank) {
    if (node != nullptr) {
        inOrderPrintWithChildren(node->left, priorRank);

        // Print current node
        int currentRank = priorRank + 1;
        cout << "Element: " << node->value << " | Rank: " << currentRank;

        // Left child
        if (node->left != nullptr) {
            cout << " | Left Child: " << node->left->value;
        } else {
            cout << " | Left Child: None";
        }

        // Right child
        if (node->right != nullptr) {
            cout << " | Right Child: " << node->right->value;
        } else {
            cout << " | Right Child: None";
        }

        cout << endl;

        priorRank = currentRank;

        inOrderPrintWithChildren(node->right, priorRank);
    }
}

void AVLVector::preOrderPrintWithChildren(Node* node, int priorRank) {
    if (node != nullptr) {
        // Calculate the rank of the current node
        int currentRank = priorRank + size(node->left) + 1;
        
        // Print current node details
        cout << "Element: " << node->value << " | Rank: " << currentRank;

        // Left child
        if (node->left != nullptr) {
            cout << " | Left Child: " << node->left->value;
        } else {
            cout << " | Left Child: None";
        }

        // Right child
        if (node->right != nullptr) {
            cout << " | Right Child: " << node->right->value;
        } else {
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

int AVLVector::findValueByRank(Node* root, int rank, int& currentRank) {
    if (root == NULL) return -1; // Base case: If the root is NULL, the rank is out of bounds.

    // Traverse the left subtree first
    int leftResult = findValueByRank(root->left, rank, currentRank);
    if (leftResult != -1) {
        return leftResult; // Found the rank in the left subtree
    }

    // Increment the current rank (this node's rank in the in-order traversal)
    currentRank++;

    // If the current rank matches the requested rank, return the value of this node
    if (currentRank == rank) {
        return root->value;
    }

    // Otherwise, continue the traversal in the right subtree
    return findValueByRank(root->right, rank, currentRank);
}














//helper function to count nodes in a subtree
int AVLVector::countNodes(Node* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}



int AVLVector::findRank(Node* node, int e, int rankOffset) {
    if (!node) return -1; // Element not found

    //if the current node matches the element
    if (node->value == e) {
        //returning the rank 
        return countNodes(node->left); //only counting nodes in the left subtree
    }

    //searching in the left subtree if the element is smaller
    if (e < node->value) {
        return findRank(node->left, e);
    } else {
        //searching in the right subtree if the element is larger
        int leftCount = countNodes(node->left); //counting nodes in left subtree
        int rightRank = findRank(node->right, e); //recursively finding rank in right subtree
        void setHeight(Node* temp);
        if (rightRank == -1) return -1; //element not found in right subtree
        return leftCount + 1 + rightRank; //include left count and current node
    }
}



void AVLVector::updateSize(Node* node) {
    if (node != nullptr) {
        node->size = 1 + size(node->left) + size(node->right);
    }
}



int AVLVector::size(Node* node) {
    if (!node) return 0; // Base case: no nodes
    return 1 + size(node->left) + size(node->right); // Count the current node plus left and right subtrees
}



int AVLVector::elementAtRankHelper(Node* node, int r, int& priorRank) {
    if (node == nullptr) {
        return -1;  //returning -1 if rank is out of bounds
    }

    //traversing the left subtree first
    int leftResult = elementAtRankHelper(node->left, r, priorRank);
    if (leftResult != -1) {
        return leftResult;  // If the left subtree returns a valid result, propagate it upwards
    }

    //increment the rank and check if it matches after left traversal
    priorRank++;
    cout << "Visiting Node: " << node->value << " | Calculated Rank: " << priorRank << endl;
    
    if (priorRank == r) {
        cout << "\nElement at rank " << priorRank << " is " << node->value << "!\n" << endl;
        return node->value;  // Found the node with the desired rank
    }

    //traversing the right subtree if element is not found yet
    return elementAtRankHelper(node->right, r, priorRank);
}



Node* AVLVector::getNodeAtRank(Node* node, int rank, int priorRank) {
    //base case of whether node is not found
    if (!node) {
        return nullptr; 
    }

    int leftSize = size(node->left);  //getting size of left subtree
    int currentRank = leftSize + priorRank + 1;  //calculating rank using rank formula from class

    if (rank == currentRank) {
        return node;  //YAY found the node at the requested rank!
    } 
    else if (rank < currentRank) {
        //going left, priorRank stays the same
        return getNodeAtRank(node->left, rank, priorRank);
    } 
    else {
        //go right, updating priorRank to currentRank 
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

void AVLVector::deleteSubtree(Node* node) {
    if (node == nullptr) return;

    //recursively deleting left and right children
    deleteSubtree(node->left);
    deleteSubtree(node->right);

    //deleting the current node
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
    if (r <= 0 || r > size(root)) {
        throw out_of_range("Rank is out of bounds");
    }

    Node* node = getNodeAtRank(root, r);
    if (node) {
        node->value = e;  // Replace the value
    } else {
        throw runtime_error("Node at rank not found");
    }
}



/****************************************************************************
 *                     AVLVector insertAtRank Function                      *
 **************************************************************************x*/

void AVLVector::insertAtRank(int r, int e)
{
    if (root == NULL) {
        //manual insert
        Node* newNode = new Node(e);
        newNode->size = 1;  // this node is the only node in its subtree
        newNode->height = 1;  // single node has height 1
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        root = newNode;
        cout << "root was NULL" << endl;
    } else {
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
int AVLVector::searchByRank(Node* &node, int rank)
{
    if (node == nullptr) {
        return -1; // Not found
    }

    int leftSize = size(node->left); // Get the size of the left subtree

    if (rank == leftSize + 1) {
        // The current node is the one we're looking for (rank matches)
        // return node->value; // Return the value at this rank
        return 1;
    } else if (rank <= leftSize) {
        // Search in the left subtree
        return search(node->left, rank);
    } else {
        // Search in the right subtree, adjusting rank accordingly
        return search(node->right, rank - leftSize - 1);
    }
}

Node* AVLVector::findNodeByValue(Node* node, int value) {
    if (node == nullptr) {
        return nullptr; // Not found
    }

    if (node->value == value) {
        return node; // Found the node
    } else if (value < node->value) {
        return findNodeByValue(node->left, value); // Search left subtree
    } else {
        return findNodeByValue(node->right, value); // Search right subtree
    }
}


Node* AVLVector::deleteNodeByRank(Node* &node, int rank)
{
    if (node == NULL) return NULL;

    int leftSize = size(node->left);
    int currentNodeRank = leftSize + 1;

    //traversing to the correct rank
    if (rank < currentNodeRank) {
        node->left = deleteNodeByRank(node->left, rank);
    } else if (rank > currentNodeRank) {
        node->right = deleteNodeByRank(node->right, rank - currentNodeRank);
    } else {
        //node to be deleted is found
        if (node->left == NULL && node->right == NULL) {
            //node w/ no children
            delete node;
            return NULL;
        } else if (node->left == NULL) {
            //node w/ only right child
            Node* rightChild = node->right;
            rightChild->parent = node->parent; //ensuring correct re-linking
            delete node;
            return rightChild;
        } else if (node->right == NULL) {
            //node w/ only left child
            Node* leftChild = node->left;
            leftChild->parent = node->parent; //ensuring correct re-linking
            delete node;
            return leftChild;
        } else {
            //node with two children, find in-order predecessor
            Node* predecessor = findMax(node->left);
            node->value = predecessor->value;  //swapping values
            node->left = deleteNodeByRank(node->left, leftSize); //deleting predecessor
        }
    }

    //rebalancing and update size/height
    updateSize3(node);
    setHeight2(node);

    int balanceFactor = getBalanceFactor2(node);

    //tree is LEFT heavy
    if (balanceFactor > 1) {
        if (getBalanceFactor2(node->left) >= 0) {
            return leftLeftRotation(node);
        } else {
            return leftRightRotation(node);
        }
    }
    //tree is RIGHT heavy
    if (balanceFactor < -1) {
        if (getBalanceFactor2(node->right) <= 0) {
            return rightRightRotation(node);
        } else {
            return rightLeftRotation(node);
        }
    }

    return node;
}


int AVLVector::removeAtRank(int r)
{
    if (r < 1 || r > size(root)) return -1; // Invalid rank

    root = deleteNodeByRank(root, r); // Call the updated delete function

    if (root != NULL) {
        root->parent = NULL;  // Ensure the root's parent is always NULL
    }

    return 1;
}


// Find the maximum node in the left subtree (in-order predecessor)
Node* AVLVector::findMax(Node* node) {
    while (node->right != NULL) {
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

//not used rn.
int AVLVector::getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return size(node->left) - size(node->right);
}

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

int AVLVector::rankOf(int e)
{
    int result = findRank(root, e);
    if (result == -1) {
        cout << "Error: Element not found\n";
        return -1;
    }
    int rank = result + 1;
    return rank;
}

/****************************************************************************
 *                        AVLVector printAll Function                       *
 ****************************************************************************/

void AVLVector::printAll()
{
    int priorRank = 0;
    //inOrderPrintByRank(root, priorRank);
    inOrderPrintWithChildren(root, priorRank);
    cout << endl;
}