#include "AVL.h"

//setting root to nullptr
nodeptr root = nullptr;

/****************************************************************************
 *                                                                          *
 *                      AVL Tree Helper Functions                           *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
 ****************************************************************************/

void setHeight(nodeptr temp)
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

int getHeight(nodeptr node) {
    if (node == NULL) {
        return -1; // Convention: height of an empty tree is -1
    }
    return node->height; // Return the height stored in the node
}



/****************************************************************************
 *                       AVLTree search Helper Function                     *
 ****************************************************************************/

int search(nodeptr &some, int val)
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

// //given code
// int insertNode(nodeptr &root, int val)
// {
//     bool done, violation;
//     // int myheight;
//     nodeptr temp;
//     if (root == NULL)
//     {
//         // root = new Node(val);
//         root = new Node(val);
//         root->value = val;
//         root->height = 0;
//         root->left = NULL;
//         root->right = NULL;
//         root->parent = NULL;
//         return 1;
//     }
//     else
//     {
//         temp = root;
//         done = false;
//         while (!done)
//         {
//             if (temp->value >= val)
//                 if (temp->left == NULL)
//                 {
//                     temp->left = new Node(val);
//                     temp->left->parent = temp;
//                     temp = temp->left;
//                     temp->value = val;
//                     temp->height = 0;
//                     temp->left = NULL;
//                     temp->right = NULL;
//                     done = true;
//                 }
//                 else
//                 {
//                     temp = temp->left;
//                 }
//             else if (temp->right == NULL)
//             {
//                 temp->right = new Node(val);
//                 temp->right->parent = temp;
//                 temp = temp->right;
//                 temp->value = val;
//                 temp->height = 0;
//                 temp->left = NULL;
//                 temp->right = NULL;
//                 done = true;
//             }
//             else
//                 temp = temp->right;
//         } // end of while. Now climb back.
//         temp = temp->parent;
//         temp->height = 1;
//         done = (temp->parent == NULL);
//         violation = false;
//         while (!done)
//         {
//             temp = temp->parent;
//             setHeight(temp);

//             if ((temp->left == NULL) || (temp->right == NULL)) {
//                 violation = true;
//             } else if ((temp->left->height - temp->right->height > 1) || (temp->right->height - temp->left->height > 1)) {
//                 violation = true;
//             }

//             if (violation)
//             {
//                 if ((temp->value >= val) && (temp->left->value >= val)) {
//                     leftLeftRotation(temp);
//                 } else if ((temp->value >= val) && (temp->left->value < val)) {
//                     leftRightRotation(temp);
//                 } else if ((temp->value < val) && (temp->right->value >= val)) {
//                     rightLeftRotation(temp);
//                 } else if ((temp->value < val) && (temp->right->value < val)) {
//                     rightRightRotation(temp);
//                 }

//                 done = true;
//             }

//             if (temp == root)
//                 done = true;
//         } // while ! done
//         return 1;
//     } // end of else
// }


// nodeptr insertNode(nodeptr &root, int val, int rank) {
//     bool done, violation;
//     nodeptr temp;

//     if (root == NULL) {
//         root = new Node(val);
//         root->value = val;
//         root->height = 0;
//         root->size = 1; // New node has size 1
//         root->left = NULL;
//         root->right = NULL;
//         root->parent = NULL;
//         return root;
//     } else {
//         temp = root;
//         done = false;
        
//         int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;

//         while (!done) {
//             // Insert into the left subtree if rank <= leftSubtreeSize + 1
//             if (rank <= leftSubtreeSize + 1) {
//                 if (temp->left == NULL) {
//                     temp->left = new Node(val);
//                     temp->left->parent = temp;
//                     temp = temp->left;
//                     temp->value = val;
//                     temp->height = 0;
//                     temp->size = 1;
//                     temp->left = NULL;
//                     temp->right = NULL;
//                     done = true;
//                 } else {
//                     temp = temp->left;
//                 }
//             } 
//             // Insert into the right subtree, adjust the rank accordingly
//             else {
//                 if (temp->right == NULL) {
//                     temp->right = new Node(val);
//                     temp->right->parent = temp;
//                     temp = temp->right;
//                     temp->value = val;
//                     temp->height = 0;
//                     temp->size = 1;
//                     temp->left = NULL;
//                     temp->right = NULL;
//                     done = true;
//                 } else {
//                     rank = rank - (leftSubtreeSize + 1);  // Adjust rank for the right subtree
//                     temp = temp->right;
//                 }
//             }

//             // Update leftSubtreeSize based on the new position of the temp node
//             leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;
//         }

//         // Climb back up and update the size and height of each node
//         temp = temp->parent;
//         while (temp != NULL) {
//             // Update the size of each node: size = size of left subtree + size of right subtree + 1 (for itself)
//             temp->size = 1 + ((temp->left != NULL) ? temp->left->size : 0) + ((temp->right != NULL) ? temp->right->size : 0);
            
//             // Update height
//             setHeight(temp);

//             // Check balance factor and rebalance if necessary
//             int balanceFactor = getBalanceFactor2(temp);
//             if (balanceFactor > 1) { // Left heavy
//                 if (rank <= leftSubtreeSize + 1) {
//                     temp = leftLeftRotation(temp);  // Left-Left case
//                 } else {
//                     temp = leftRightRotation(temp); // Left-Right case
//                 }
//             } 
//             else if (balanceFactor < -1) { // Right heavy
//                 if (rank > leftSubtreeSize + 1) {
//                     temp = rightRightRotation(temp); // Right-Right case
//                 } else {
//                     temp = rightLeftRotation(temp);  // Right-Left case
//                 }
//             }

//             // Move up to parent
//             temp = temp->parent;
//         }

//         return root;
//     }
// }


/****************************************************************************
 *    Modified AVLTree insertNode Helper Function For Rank. Need to debug.  *
 ****************************************************************************/
//sort of working rn 9:13pm
// nodeptr insertNode(nodeptr &root, int val, int rank) {
//     if (root == NULL) {
//         root = new Node(val);
//         root->size = 1;  // this node is the only node in its subtree
//         root->height = 1;  // single node has height 1
//         root->left = NULL;
//         root->right = NULL;
//         root->parent = NULL;
//         return root;
//     }

//     nodeptr temp = root;
//     int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;

//     //inserting into the left subtree or at the current node's rank
//     if (rank <= leftSubtreeSize + 1) {
//         // If inserting at a rank that collides, shift ranks of all subsequent nodes
//         if (rank == leftSubtreeSize + 1) {
//             shiftRanks(temp->right);  //shifting nodes in the right subtree
//         }
//         // Insert into the left subtree
//         temp->left = insertNode(temp->left, val, rank);
//         temp->left->parent = temp;
//     } 
//     //inserting into the right subtree
//     else {
//         // Adjust rank for insertion into the right subtree
//         temp->right = insertNode(temp->right, val, rank - (leftSubtreeSize + 1));
//         temp->right->parent = temp;
//     }

//     //updating size and height after insertion
//     updateSize3(temp);
//     setHeight2(temp);

//     //balancing the tree
//     int balanceFactor = getBalanceFactor2(temp);
//     if (balanceFactor > 1) {
//         if (rank <= leftSubtreeSize + 1) {
//             temp = leftLeftRotation(temp);  //left-left case
//         } else {
//             temp = leftRightRotation(temp);  //left-right case
//         }
//     } else if (balanceFactor < -1) {
//         if (rank > leftSubtreeSize + 1) {
//             temp = rightRightRotation(temp);  //right-right case
//         } else {
//             temp = rightLeftRotation(temp);  //right-left case
//         }
//     }

//     return temp;
// }

//fixing after david's OH
int AVLVector::insertNode(nodeptr &currentNode, int val, int rank) {
    if (currentNode == NULL) {
        currentNode = new Node(val);
        currentNode->size = 1;  // this node is the only node in its subtree
        currentNode->height = 1;  // single node has height 1
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->parent = NULL;
        cout << "currentNode was NULL" << endl;
        return 1;
    }

    nodeptr temp = currentNode;
    int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;

    //inserting into the left subtree or at the current node's rank
    if (rank <= leftSubtreeSize + 1) {
        cout << "rank <= leftSize + 1" << endl;
        // If inserting at a rank that collides, shift ranks of all subsequent nodes
        if (rank == leftSubtreeSize + 1) {
            shiftRanks(temp->right);  //shifting nodes in the right subtree
        }
        // Insert into the left subtree
        int result = insertNode(temp->left, val, rank);
        temp->left->parent = temp;
    } 
    //inserting into the right subtree
    else {
        cout << "inserting " << val << " into right subtree" << endl;
        // Adjust rank for insertion into the right subtree
        int result = insertNode(temp->right, val, rank - (leftSubtreeSize + 1));
        temp->right->parent = temp;
    }

    //updating size and height after insertion
    updateSize3(temp);
    setHeight2(temp);

    //balancing the tree
    int balanceFactor = getBalanceFactor2(temp);
    if (balanceFactor > 1) {
        if (rank <= leftSubtreeSize + 1) {
            cout << "left left case while inserting " << val <<  endl;
            temp = leftLeftRotation(temp);  //left-left case
        } else {
            cout << "left right case while inserting " << val << endl;
            temp = leftRightRotation(temp);  //left-right case
        }
    } else if (balanceFactor < -1) {
        if (rank > leftSubtreeSize + 1) {
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
void updateSize3(nodeptr &node) {
    if (node == NULL) return;
    int leftSize = (node->left != NULL) ? node->left->size : 0;
    int rightSize = (node->right != NULL) ? node->right->size : 0;
    node->size = leftSize + rightSize + 1;
}

// //function for calculating balance factor of a node
int getBalanceFactor2(nodeptr &node) {
    if (node == NULL) return 0;
    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;
    return leftHeight - rightHeight;
}

//function for updating height of a node
void setHeight2(nodeptr &node) {
    if (node == NULL) return;
    int leftHeight = (node->left != NULL) ? node->left->height : 0;
    int rightHeight = (node->right != NULL) ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + 1;
}

//helper function for shifting ranks of nodes in the right subtree
void shiftRanks(nodeptr &node) {
    if (node == NULL) return;

    nodeptr temp = node;
    // Perform rank shift on the current node
    while (temp != NULL) {
        updateSize(temp);  // Update the size of the current node
        temp = temp->right;  // Shift to the next node in the right subtree
    }
}

// nodeptr insertNode(nodeptr &root, int val, int rank) {
//     if (root == NULL) {
//         root = new Node(val); // Create a new node with the value
//         root->size = 1;       // Single node has size 1
//         root->height = 1;     // Single node has height 1
//         root->left = NULL;
//         root->right = NULL;
//         root->parent = NULL;
        
//         // Debug output
//         cout << "Inserted node with value: " << val << " at rank: " << rank << endl;
//         return root;
//     }

//     nodeptr temp = root;
//     int leftSubtreeSize = (temp->left != NULL) ? temp->left->size : 0;

//     // Debug output
//     cout << "Visiting node with value: " << temp->value << " | Current rank: " << rank << endl;

//     // Insert in the left subtree if rank <= leftSubtreeSize + 1
//     if (rank <= leftSubtreeSize + 1) {
//         temp->left = insertNode(temp->left, val, rank);
//         temp->left->parent = temp;
//     }
//     // Insert in the right subtree if rank > leftSubtreeSize + 1
//     else {
//         temp->right = insertNode(temp->right, val, rank - (leftSubtreeSize + 1));
//         temp->right->parent = temp;
//     }

//     // Update the size and height after the insertion
//     updateSize3(temp);
//     setHeight2(temp);

//     // Debug output
//     cout << "Node value: " << temp->value << " | Left size: " << leftSubtreeSize << endl;

//     // Rebalance the tree if it's unbalanced
//     int balanceFactor = getBalanceFactor2(temp);
//     if (balanceFactor > 1) {
//         if (rank <= leftSubtreeSize + 1) {
//             cout << "Performing left-left rotation." << endl;
//             temp = leftLeftRotation(temp); // Left-Left case
//         } else {
//             cout << "Performing left-right rotation." << endl;
//             temp = leftRightRotation(temp); // Left-Right case
//         }
//     }
//     else if (balanceFactor < -1) {
//         if (rank > leftSubtreeSize + 1) {
//             cout << "Performing right-right rotation." << endl;
//             temp = rightRightRotation(temp); // Right-Right case
//         } else {
//             cout << "Performing right-left rotation." << endl;
//             temp = rightLeftRotation(temp); // Right-Left case
//         }
//     }

//     return temp;
// }







/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
 *****************************************************************************/

nodeptr leftLeftRotation(nodeptr &temp)
{   
    //identifying nodes in rotation
    nodeptr temp1 = temp->left;
    nodeptr temp2 = temp1->left;

    //reassinging parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;


    temp->left = temp1->right;
    temp1->right = temp;
    if (temp1->parent != NULL)
    {
        if (temp1->parent->left == temp) {
            temp1->parent->left = temp1;
        } else {
            temp1->parent->right = temp1;
        }
    }
    setHeight(temp);
    setHeight(temp1);
    temp = temp1; 

    return temp;
}

/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
 *****************************************************************************/

nodeptr rightRightRotation(nodeptr &temp)
{
    nodeptr temp1 = temp->right;
    nodeptr temp2 = temp1->right;
    temp1->parent = temp->parent;
    temp->parent = temp1;
    temp->right = temp1->left;
    temp1->left = temp;
    if (temp1->parent != NULL)
    {
        if (temp1->parent->right == temp) {
            temp1->parent->right = temp1;
        } else {
            temp1->parent->left = temp1;
        }
    }
    setHeight(temp);
    setHeight(temp1);
    temp = temp1;

    return temp;
}

/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
 *****************************************************************************/

nodeptr leftRightRotation(nodeptr &temp)
{
    nodeptr temp1 = temp->left;
    nodeptr temp2 = temp1->right;
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;
    temp->left = temp2->right;
    temp1->right = temp2->left;
    if (temp2->parent != NULL)
    {
        if (temp2->parent->right == temp) {
            temp2->parent->right = temp2;
        } else {
            temp2->parent->left = temp2;
        }
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;

    return temp;
}

/****************************************************************************
 *                  AVLTree rightLeftRotation Helper Function               *
 *****************************************************************************/

nodeptr rightLeftRotation(nodeptr &temp)
{
    nodeptr temp1 = temp->right;
    nodeptr temp2 = temp1->left;
    temp2->parent = temp->parent;
    temp1->parent = temp2;
    temp->parent = temp2;
    temp->right = temp2->left;
    temp1->left = temp2->right;
    if (temp2->parent != NULL)
    {
        if (temp2->parent->right == temp) {
            temp2->parent->right = temp2;
        } else {
            temp2->parent->left = temp2;
        }
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;

    return temp;
}



/****************************************************************************
 *                    AVLTree deleteNode Helper Function                    *
 *****************************************************************************/
// int getBalance(nodeptr node) {
//     if (node == nullptr)
//         return 0;  // If the node is null, the balance is 0 (tree is empty)
    
//     int leftHeight = (node->left != nullptr) ? node->left->height : -1;
//     int rightHeight = (node->right != nullptr) ? node->right->height : -1;

//     return leftHeight - rightHeight;  // Balance factor = height of left subtree - height of right subtree
// }


// int deleteNode(nodeptr &root, int val)
// {
//     if (root == nullptr) return -1;  // Tree is empty

//     nodeptr temp = root;
//     nodeptr parent = nullptr;

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
//         nodeptr child = (temp->left != nullptr) ? temp->left : temp->right;
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
//         nodeptr successor = temp->left;  // Find the in-order predecessor (max node in left subtree)
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
int deleteNode(nodeptr &root, int val)
{
    nodeptr temp = root;
    nodeptr temp1;
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

int getBalanceFactor (nodeptr node) {
    if (node == nullptr) return 0;
    int leftHeight = (node->left != nullptr) ? node->left->height : 0;
    int rightHeight = (node->right != nullptr) ? node->right->height : 0;
    return leftHeight - rightHeight;
}



/****************************************************************************
 *                       AVLTree Balance Helper Function                    *
 ****************************************************************************/

void restoreBalance (nodeptr &node) {
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

int sizeOfSubtree(nodeptr node) {
    if (node == nullptr) {
        return 0;
    } 

    return sizeOfSubtree(node->left) + sizeOfSubtree(node->right) + 1;
}



/****************************************************************************
 *                   AVLTree inOrderPrint Helper Function                   *
 ****************************************************************************/
 
void inOrderPrintByRank(nodeptr node, int& priorRank) {
    if (node != nullptr) {
        // Traverse the left subtree first
        inOrderPrintByRank(node->left, priorRank);

        // The rank of the current node is based on the prior rank + 1
        int currentRank = priorRank + 1;

        // Print the current node's value and its calculated rank
        cout << "Element: " << node->value << " | Rank: " << currentRank << endl;

        // Update priorRank to the current rank
        priorRank = currentRank;

        // Traverse the right subtree
        inOrderPrintByRank(node->right, priorRank);
    }
}

void inOrderPrintWithChildren(nodeptr node, int& priorRank) {
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


/****************************************************************************
 *                 AVLTree findValueByRank Helper Function                  *
 ****************************************************************************/

int findValueByRank(nodeptr root, int rank, int& currentRank) {
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
int countNodes(nodeptr node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}



int findRank(nodeptr node, int e, int rankOffset) {
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
        
        if (rightRank == -1) return -1; //element not found in right subtree
        return leftCount + 1 + rightRank; //include left count and current node
    }
}



void updateSize(nodeptr node) {
    if (node != nullptr) {
        node->size = 1 + size(node->left) + size(node->right);
    }
}



int size(nodeptr node) {
    return node ? node->size : 0; //returning size if node exists
}



int elementAtRankHelper(nodeptr node, int r, int& priorRank) {
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


nodeptr getNodeAtRank(nodeptr node, int rank) {
    if (!node) return nullptr;
    int leftSize = size(node->left);
    if (rank == leftSize) return node;
    if (rank < leftSize) return getNodeAtRank(node->left, rank);
    return getNodeAtRank(node->right, rank - leftSize - 1);
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

void deleteSubtree(nodeptr node) {
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
    nodeptr node = getNodeAtRank(root, r);
    if (!node) {
        cout << "Error: Rank out of bounds\n";
        return;
    }
    node->value = e;
}

/****************************************************************************
 *                     AVLVector insertAtRank Function                      *
 **************************************************************************x*/

void AVLVector::insertAtRank(int r, int e)
{
    nodeptr pointer = this->getRoot();
    insertNode(pointer, e, r);
    root = pointer;
    // int result = insertNode(pointer, e, r);
    // if (result != 1) {
    //     cout << "Error, insert unsuccessful..." << endl;
    // }
}

/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
 ****************************************************************************/

void AVLVector::removeAtRank(int r)
{
    //root = deleteNode(root, r);
}

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