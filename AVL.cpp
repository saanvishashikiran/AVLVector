#include "AVL.h"

/****************************************************************************
 *                                                                          *
 *                      AVL Tree Helper Functions                           *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
 * About: Sets height of given node to 1 + maximum of left and righ         *
 * subtree heights. This function is called after insertions, deletions,    *
 * and rotations.                                                           *
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

void AVLVector::setHeight(Node *node)
{
    if (node) //if node isn't null
    {
        if (!node->left && !node->right) //if node is a leaf
            node->height = 0;
        else if (!node->left) //if node has a right child
            node->height = getHeight(node->right) + 1;
        else if (!node->right) //if node has a left child
            node->height = getHeight(node->left) + 1;
        else if (node->left && node->right) //if node has left and right children
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
}



/****************************************************************************
 *                      AVLTree updateSize Helper Function                  *
 * About: Updates size and numLeft for a node. Size is set to the size of   *
 * left subtree + size of right subtree + 1. The variable numLeft (stored   *
 * for each node) is set to the size of the left subtree.                   *  
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

void AVLVector::updateSize(Node *&node)
{
    if (node == NULL) //early exit if node is null
        return;

    //calculating left and right subtree sizes
    int leftSize = (node->left != NULL) ? node->left->size : 0; 
    int rightSize = (node->right != NULL) ? node->right->size : 0;

    node->size = leftSize + rightSize + 1; //updating size of node
    node->numLeft = leftSize; //updating numLeft of node
}



/****************************************************************************
 *                      AVLTree getBalance Helper Function                  *
 * About: Returns the balance factor for a node by subtracting the height   *
 * of the right subtree from the height of the left subtree. The right      *
 * subtree has a "negative pull" in this balance factor while the left      *
 * subtree has a "positive pull."                                           *
 *                                                                          *
 * Runtime: O(1)                                                            *                        
 ****************************************************************************/

int AVLVector::getBalance(Node *node)
{
    int leftSubtreeHeight, rightSubtreeHeight;
    if (!node) //check for null node
    {
        return 0;
    }
    if (!node->left && !node->right) //returning balance of 0 if node is a leaf
        return 0;
    if (!node->left) //node has a right child
    {
        leftSubtreeHeight = -1;
        rightSubtreeHeight = getHeight(node->right);
        return leftSubtreeHeight - rightSubtreeHeight;
    }
    if (!node->right) //node has a left child;
    {
        rightSubtreeHeight = -1;
        leftSubtreeHeight = getHeight(node->left);
        return leftSubtreeHeight - rightSubtreeHeight;
    }

    //node has left and right children
    leftSubtreeHeight = getHeight(node->left);
    rightSubtreeHeight = getHeight(node->right);

    return leftSubtreeHeight - rightSubtreeHeight;
}



/****************************************************************************
 *                    AVLTree insertNode Helper Function                    *
 * About: Inserts nodes according to rank. If the current node (root) is    *
 * null, a new node is created (base case). After calculating current rank, *
 * I insert into the left subtree if rank of the node to be inserted is     *
 * less than or equal to the rank of the current node, which is the root.   *
 * If there is a rank collision, it is handled by incrementing numLeft of   *
 * temp. If the rank of the node to be inserted is greater than the rank    *
 * of the current node, I insert into the right subtree. In both cases      *
 * (left subtree or right subtree) I make recursive calls to insertNode,    *
 * passing in either temp->left or temp->right. Rank calculations for the   *
 * right subtree use the formula rank = number of nodes in left subtree +   *
 * priorRank + 1, and this is accounted for by setting priorRank to         *
 * currentNodeRank before making the recursive call for inserting into the  *
 * right subtree. We then call updateSize, which updates size and numLeft.  *
 * After calling setHeight, I call getBalance to get the balance factor,    *
 * and rebalance the tree based on the balance factor, calling the          *
 * corresponding rotation function if the tree is imbalanced. Finally, I    *
 * set currentNode equal to temp so that we end up with the updated tree.   *
 *                                                                          *
 * Runtime: O(logN). All functions called within insertNode are O(1), and   *
 * the height of an AVL tree is O(logN). The maximum number of recursive    *
 * calls that need to be made before reaching a leaf node to insert the new *  
 * node (worst case) is equal to the height of the tree, O(logN).           *
 ****************************************************************************/

int AVLVector::insertNode(Node *&currentNode, int priorRank, int val, int rank)
{
    //creating a new node if currentNode (root) is null (base case!)
    if (currentNode == NULL)
    {
        currentNode = new Node(val);
        currentNode->size = 1;   
        currentNode->height = 0; 
        currentNode->numLeft = 0;
        currentNode->left = NULL;
        currentNode->right = NULL;
        currentNode->parent = NULL;
        return 1;
    }

    Node *temp = currentNode;
    int currentNodeRank = temp->numLeft + priorRank + 1; //calculating rank of current node (the root)

    //inserting into the left subtree or at the current node's rank
    if (rank <= currentNodeRank)
    { 
        //handling numLeft if inserting at a rank that collides
        if (rank == temp->numLeft + 1)
        {
            temp->numLeft += 1; 
        }

        //inserting into the left subtree
        int result = insertNode(temp->left, priorRank, val, rank); //recursive call for left subtree
        temp->left->parent = temp; //updating parent
        temp->numLeft += 1; //incrementing numLeft since we just inserted into the left subtree
    }
    // inserting into the right subtree
    else
    {
        //adjusting rank for insertion into the right subtree
        priorRank = currentNodeRank; //resetting priorRank to currentNodeRank (needs to include temp->numLeft + 1 in rank calculations for right subtree)
        int result = insertNode(temp->right, priorRank, val, rank); //recursive call for right subtree
        temp->right->parent = temp; //updating parent
    }

    //updating size and height after insertion
    updateSize(temp);
    setHeight(temp);

    //balancing the tree
    int balanceFactor = getBalance(temp);
    if (balanceFactor > 1)
    {
        int leftBalanceFactor = getBalance(temp->left);
        if (leftBalanceFactor >= 0)
        {
            temp = leftLeftRotation(temp); //left-left case
        }
        else
        {
            temp = leftRightRotation(temp); //left-right case
        }
    }
    else if (balanceFactor < -1)
    {
        int rightBalanceFactor = getBalance(temp->right);
        if (rightBalanceFactor <= 0)
        {
            temp = rightRightRotation(temp); //right-right case
        }
        else
        {
            temp = rightLeftRotation(temp); //right-left case
        }
    }

    //setting currentNode to temp to reflect updates
    currentNode = temp;

    //returning 1 for success!
    return 1;
}



/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
 * About: Takes care of rebalancing the tree after a left left imbalance    *
 * case arises. Starts by updating parent pointers to account for rotation, *
 * then reassigns children if temp1 already has a right child, reassigns    *
 * the parent's child pointer to the new root (temp1), and then updates the *
 * numLeft values of temp and temp1. The function returns temp1 after       *
 * calling setHeight and updateSize on temp and temp1.                      *
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

Node *AVLVector::leftLeftRotation(Node *&temp)
{
    Node *temp1 = temp->left;

    //updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    //reassigning child pointers
    temp->left = temp1->right;
    if (temp->left != NULL)
        temp->left->parent = temp; //ensuring temp->left's parent is updated
    temp1->right = temp;

    //reassigning parent's child pointer to the new root (temp1)
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

    //updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    //updating height and size
    updateSize(temp);   //updating size for temp (original root)
    updateSize(temp1);  //updating size for new root temp1
    setHeight(temp);  //updating height for temp
    setHeight(temp1); //updating height for temp1

    return temp1;
}



/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
 * About: Takes care of rebalancing the tree after a right right imbalance  *
 * case arises. Starts by updating parent pointers to account for rotation, *
 * then reassigns children if temp1 already has a left child, reassigns     *
 * the parent's child pointer to the new root (temp1), and then updates the *
 * numLeft values of temp and temp1. The function returns temp1 after       *
 * calling setHeight and updateSize on temp and temp1.                      *
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

Node *AVLVector::rightRightRotation(Node *&temp)
{
    Node *temp1 = temp->right;

    //updating parent pointers
    temp1->parent = temp->parent;
    temp->parent = temp1;

    //reassigning child pointers
    temp->right = temp1->left;
    if (temp->right != NULL)
        temp->right->parent = temp; //ensuring temp->right's parent is updated
    temp1->left = temp;

    //reassigning parent's child pointer to the new root (temp1)
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

    //updating numLeft values after rotation
    temp->numLeft = (temp->left != NULL) ? temp->left->size : 0;
    temp1->numLeft = (temp1->left != NULL) ? temp1->left->size : 0;

    //updating height and size
    updateSize(temp);   //updating size for temp (original root)
    updateSize(temp1);  //updating size for new root temp1
    setHeight(temp);  //updating height for temp
    setHeight(temp1); //updating height for temp1

    return temp1;
}



/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
 * About: Takes care of rebalancing the tree after a left right imbalance   *
 * case arises. Starts by updating parent pointers to account for rotation, *
 * then reassigns children if temp2 already has a right/left child,         *
 * reassigns the parent's child pointer to the new root (temp2), and then   *
 * updates numLeft values of temp and temp1. The function returns temp2     *
 * after calling setHeight and updateSize on temp, temp1, and temp 2.       *
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

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
    updateSize(temp);   // updating size for temp (original root)
    updateSize(temp1);  // updating size for temp1
    updateSize(temp2);  // updating size for new root temp2
    setHeight(temp);  // updating height for temp
    setHeight(temp1); // updating height for temp1
    setHeight(temp2); // updating height for temp2

    // WAS MISSING THIS CHECK IF I NEED IT, would need it if it was void i think.
    //  temp = temp2;

    return temp2;
}



/****************************************************************************
 *                  AVLTree rightLeftRotation Helper Function               *
 * About: Takes care of rebalancing the tree after a right left imbalance   *
 * case arises. Starts by updating parent pointers to account for rotation, *
 * then reassigns children if temp2 already has a right/left child,         *
 * reassigns the parent's child pointer to the new root (temp2), and then   *
 * updates numLeft values of temp and temp1. The function returns temp2     *
 * after calling setHeight and updateSize on temp, temp1, and temp 2.       *
 *                                                                          *
 * Runtime: O(1)                                                            *
 ****************************************************************************/

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
    updateSize(temp);   // updating size for temp (original root)
    updateSize(temp1);  // updating size for temp1
    updateSize(temp2);  // updating size for new root temp2
    setHeight(temp);  // updating height for temp
    setHeight(temp1); // updating height for temp1
    setHeight(temp2); // updating height for temp2

    return temp2;
}




/****************************************************************************
 *                AVLTree decrementNumLeft Helper Function                  *
 * About: Traverses up to the root calling updateSize on each node in order *
 * to ensure size and numLeft values are properly updated after a deletion. *
 *                                                                          *
 * Runtime: O(logN) because the height of a tree is O(logN) so the maximum  *
 * path length from any node to the root is O(logN).                        *
 ****************************************************************************/

void AVLVector::decrementNumLeft(Node* node) {
    while (node != NULL) {
        updateSize(node);
        node = node->parent;
    }
}

/****************************************************************************
 *                    AVLTree searchByRank Helper Function                  *
 * About: Searches the tree to find the node at the given rank. This comes  *
 * in handy for my deleteNode function!                                     *
 *                                                                          *
 * Runtime: O(logN) because each level in an AVL tree has a maximum of      *
 * O(logN) nodes on the path to the target rank.                            *                             
 ****************************************************************************/

Node* AVLVector::searchByRank(Node *some, int rank, int priorRank) {
    if (some == NULL) {
        return NULL; // Rank not found
    }

    while (some != NULL) {
        int currentRank = priorRank + some->numLeft + 1; // using numLeft to calculate current rank

        //debugging statement to observe rank calculation
        cout << "Visiting node with value " << some->value << ", currentRank: " << currentRank << ", priorRank: " << priorRank << endl;

        if (currentRank == rank) {
            return some; //returning the node at the given rank
        } 
        else if (rank < currentRank) {
            //moving to the left subtree, no need to update priorRank here
            some = some->left;
        } 
        else {
            //moving to the right subtree, need to update priorRank
            priorRank = currentRank;
            some = some->right;
        }
    }

    return NULL; //rank not found!!!
}



/****************************************************************************
 *                    AVLTree deleteNode Helper Function                    *
 * About: Deletes nodes by rank. Sets temp to the node at the given rank by *
 * calling searchByRank. If the left subtree is empty, and the node to be   *
 * deleted is the root, the root is reset to the root's right child.        *
 * If the left subtree is empty, and the node to be deleted is not the      *
 * root, the right child of the node to be deleted is set to be a child of  *
 * the parent node. Next, temp is deleted, setHeight is called on temp1,    *
 * and temp is re-set to be temp1. If temp->left was not null, I replace    *
 * the node to be deleted with the rightmost child of the left subtree      *
 * before calling setHeight on temp and deleting temp1. Then, I call        *
 * decrementNumLeft on temp to update sizes and numLefts all the way up the *
 * tree until the root. Finally, I rebalance the tree by calling my         *
 * rotation functions, set temp to the parent of temp, and call setHeight   *
 * on temp.                                                                 *
 *                                                                          *
 * Runtime: O(logN) because the height of a tree is O(logN). All functions  *
 * called within deleteNode are O(1) or O(logN) and called in a manner that *
 * their runtimes are absorbed into O(logN) (outside of loops or traversals)*
 * Thus runtime is O(logN)!                                                 *             
 ****************************************************************************/

int AVLVector::deleteNode(Node* &root, int rank) {
    Node* temp = searchByRank(root, rank); //getting the node at the given rank
    if (temp == NULL) {
        return -1; //node at rank not found
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
            } else
                temp1->right = temp->right;
            if (temp->right != NULL) temp->right->parent = temp1; 
            delete temp;
            setHeight(temp1);
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
        } else
            temp->right = temp1->left;
        if (temp1->left != NULL) temp1->left->parent = temp; 
        setHeight(temp);
        delete temp1;
    }

    decrementNumLeft(temp);

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
        setHeight(temp);
    }

    return 1; //successfully deleted
}



/****************************************************************************
 *                   AVLTree inOrderPrint Helper Function                   *
 * About: Outputs rank and element for each node in the AVL tree in order   *
 * of rank!                                                                 *
 *                                                                          *
 * Runtime: O(N) because there are N nodes in the tree and each node is     *
 * visited and printed.                                                     *
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
        cout << "Rank: " << currentRank << " | Element: " << node->value << endl;

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



/****************************************************************************
 *                 AVLTree findRank Helper Function                         *
 * About: Finds the rank of a given element by traversing the tree. Starts  *
 * by traversing left subtree, incrementing rank if not found in left       *
 * subtree, checking if the current node's value is a match with the given  *
 * element, and if not, continues searching in right subtree.               *
 ****************************************************************************/

int AVLVector::findRank(Node *node, int e, int priorRank)
{
    if (!node) {
        return -1; //element not found
    }

    //traversing the left subtree first
    int leftRank = findRank(node->left, e, priorRank);
    if (leftRank != -1) {
        return leftRank; 
    }

    //incrementing the rank after visiting the left subtree
    priorRank += node->numLeft + 1; // Add numLeft and 1 for the current node

    // Check the current node
    if (node->value == e) {
        return priorRank; // Found the rank of the element
    }

    // Continue searching in the right subtree
    return findRank(node->right, e, priorRank);
}



/****************************************************************************
 *                 AVLTree elementAtRankHelper Helper Function              *
 * About: Returns the element at a specific rank. Returns -1 if the node is *
 * not found. Calculates current rank and returns element if the rank is a  *
 * match! If rank is less than current rank, make a recursive call on the   *
 * left subtree. If not, make a recursive call on the right subtree,        *
 * updating priorRank to be currentRank (rank = number of nodes in left     *
 * subtree + prior rank + 1).                                               *
 *                                                                          *
 * Runtime: O(logN) because the height of an AVL tree is O(logN). Since     *
 * this function recursively traverses the tree, the worst case is visiting *
 * every node along a path from the root to a leaf, which matches height.   *
 ****************************************************************************/

int AVLVector::elementAtRankHelper(Node *node, int r, int &priorRank)
{
    if (node == NULL)
    {
        return -1;
    }

    //calculating the current rank of the node
    int currentRank = priorRank + node->numLeft + 1;

    if (currentRank == r) //found the node with the desired rank
    {
        return node->value;
    }
    else if (r < currentRank)
    {
        //traversing the left subtree
        return elementAtRankHelper(node->left, r, priorRank);
    }
    else
    {
        //traversing the right subtree and updating priorRank
        priorRank = currentRank;
        return elementAtRankHelper(node->right, r, priorRank);
    }
}



/****************************************************************************
 *                 AVLTree getNodeAtRank Helper Function                    *
 * About: Returns node at a given rank. Returns null if the node is not     *
 * found. Calculates current rank and returns node if the rank is a match!  *
 * If rank is less than current rank, make a recursive call on the left     *
 * subtree. If not, make a recursive call on the right subtree, updating    *
 * priorRank to be currentRank (rank = number of nodes in left subtree +    *
 * prior rank + 1).                                                         *
 *                                                                          *
 * Runtime: O(logN) because the height of an AVL tree is O(logN). Since     *
 * this function recursively traverses the tree, the worst case is visiting *
 * every node along a path from the root to a leaf, which matches height.   *
 ****************************************************************************/

Node *AVLVector::getNodeAtRank(Node *node, int rank, int priorRank)
{
    //base case of whether node is not found
    if (!node)
    {
        cout << "Node not found!" << endl;
        return NULL;
    }

    //calculating rank using rank formula from class
    int currentRank = node->numLeft + priorRank + 1; 

    if (rank == currentRank)
    {
        return node; //wooo found the node at the requested rank!
    }
    else if (rank < currentRank)
    {
        //going left, priorRank stays the same
        return getNodeAtRank(node->left, rank, priorRank);
    }
    else
    {
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
 * About: Destructor of AVLVector, calls deleteTree.                        *
 *                                                                          *
 * Runtime: O(N)                                                            *
 ****************************************************************************/

AVLVector::~AVLVector()
{
    deleteTree(root);
}

/****************************************************************************
 *             AVLVector Destructor Tree Deletion Helper Function           *
 * About: Helper function for destructor, deletes tree.                     *
 *                                                                          *
 * Runtime: O(N) because it visits every node.                              *
 ****************************************************************************/

void AVLVector::deleteTree(Node *node)
{
    if (node == nullptr)
        return;

    // recursively deleting left and right children
    deleteTree(node->left);
    deleteTree(node->right);

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
 * About: Checks if tree exists, and if the inputted rank is in range       *
 * before calling elementAtRankHelper to return the element at the inputted *
 * rank.                                                                    *
 *                                                                          *
 * Runtime: O(logN), calls elementAtRankHelper which is O(logN), and all    *
 * other operations run in constant time.                                   *
 ****************************************************************************/

int AVLVector::elementAtRank(int r)
{
    if (root == nullptr) {
        cout << "Tree is empty, cannot access any elements!\n" << endl;
        return -1;
    }

    if (r <= 0 || r > root->size)
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    int priorRank = 0;
    return elementAtRankHelper(root, r, priorRank);
}

/****************************************************************************
 *                     AVLVector replaceAtRank Function                     *
 * About: Replaces the element at the inputted rank with the inputted       *
 * element. First checks if the tree exists, and if the inputted rank is in *
 * range, before calling getNodeAtRank. If the node is found, the node's    *
 * value is reassigned to the inputted replacement value.                   *
 *                                                                          *
 * Runtime: O(logN), calls getNodeAtRank which is O(logN), and all other    *
 * operations run in constant time.                                         *  
 ****************************************************************************/

int AVLVector::replaceAtRank(int r, int e)
{
    if (root == nullptr) {
        cout << "Tree is empty, cannot replace any elements!\n" << endl;
        return -1;
    }

    if (r <= 0 || r > root->size) //added in
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    Node *node = getNodeAtRank(root, r); //calling helper function to find node 

    if (node)
    {
        node->value = e; //replacing the value with e
        return 1;
    }
    else
    {
        cout << "Node at rank not found!" << endl;
        return -1;
    }
}

/****************************************************************************
 *                     AVLVector insertAtRank Function                      *
 * About: Inserts elements by rank. First checks if the rank is in bounds   * 
 * before creating a new node if the root is NULL and calling insertNode    *
 * otherwise.                                                               *
 *                                                                          *
 * Runtime: O(logN), calls insertNodw which is O(logN), and all other       *
 * operations run in constant time.                                         *
 ****************************************************************************/

int AVLVector::insertAtRank(int r, int e)
{
    //bound check
    if ((root == nullptr && r != 1) || r <= 0 || (root != nullptr && r > root->size + 1)) // +1 to account for insertion at the end
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    int result;

    if (root == NULL) //manual insertion if root is null
    {
        Node *newNode = new Node(e);
        newNode->size = 1;   //this node is the only node in its subtree
        newNode->height = 1; //single node has height 1
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        root = newNode;
        cout << "root was NULL" << endl;
    }
    else
    {
        int priorRank = 0;
        result = insertNode(root, priorRank, e, r);
    }

    return result; //returning the result of insertion (1 on success, -1 on failure)
}

/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
 * About: Removed element at inputted rank. First checks if tree is empty   *
 * and if the inputted rank is in bounds, before calling deleteNode.        *
 *                                                                          *
 * Runtime: O(logN), calls deleteNode which is O(logN), and all other       *
 * operations run in constant time.                                         *
 ****************************************************************************/

int AVLVector::removeAtRank(int r) {
    //check for empty tree
    if (root == nullptr) {
        cout << "Tree is empty, cannot remove any elements!\n" << endl;
        return -1;
    }

    //bounds check
    if (r <= 0 || (root != nullptr && r > root->size)) 
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    int result = deleteNode(root, r); //calling deleteNode helper function

    if (root != NULL) {
        root->parent = NULL;  //ensuring the root's parent is always NULL
    }

    return result; //returning the result of deletion (1 on success, -1 on failure)
}



/****************************************************************************
 *                   Extra Credit: AVLVector rankOf Function                *
 * About: Finds the rank of the inputted element by calling findRank.       *
 ****************************************************************************/

int AVLVector::rankOf(int e)
{   
    int priorRank = 0;
    int result = findRank(root, e, priorRank); //calling findRank helper function
    if (result == -1) 
    {
        cout << "Error: Element not found!" << endl;
        return -1;
    }
    return result; 
}



/****************************************************************************
 *                        AVLVector printAll Function                       *
 * About: Prints all elements of AVL tree by rank.                          *
 *                                                                          *
 * Runtime: O(N)                                                            *
 ****************************************************************************/

void AVLVector::printAll()
{
    int priorRank = 0;
    // inOrderPrintByRank(root, priorRank);
    inOrderPrintWithChildren(root, priorRank);
    cout << endl;
}