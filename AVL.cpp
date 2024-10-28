#include "AVL.h"

/****************************************************************************
 *                                                                          *
 *                      AVL Tree Helper Functions                           *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
 ****************************************************************************/

void AVLVector::setHeight(Node *node)
{
    // Purpose: Set the height of a given node to 1 + the max of the heights of its left and right
    //          subtrees. Primarily used after rotations were completed to update heights.
    // Runtime: O(1)

    if (node)
    {
        if (!node->left && !node->right)
            node->height = 0;
        else if (!node->left)
            node->height = getHeight(node->right) + 1;
        else if (!node->right)
            node->height = getHeight(node->left) + 1;
        else if (node->left && node->right)
        {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
}



/****************************************************************************
 *                      AVLTree updateSize Helper Function                  *
 ****************************************************************************/

void AVLVector::updateSize(Node *&node)
{
    if (node == NULL)
        return;
    int leftSize = (node->left != NULL) ? node->left->size : 0;
    int rightSize = (node->right != NULL) ? node->right->size : 0;
    node->size = leftSize + rightSize + 1;
    node->numLeft = leftSize; 
    cout << "inside of updateSize, numLeft of " << node->value << " is: " << node->numLeft << endl;
}



/****************************************************************************
 *                      AVLTree getBalance Helper Function                  *
 ****************************************************************************/

int AVLVector::getBalance(Node *node)
{
    // Purpose: return the net balance between the right and left subtrees of a node, where the right
    //          subtree has a "negative" pull, and the left subtree has a "positive" pull.
    // Runtime: O(1)

    int leftHeight, rightHeight;
    if (!node)
    {
        return 0;
    }
    if (!node->left && !node->right)
        return 0;
    if (!node->left)
    {
        leftHeight = -1;
        rightHeight = getHeight(node->right);
        return leftHeight - rightHeight;
    }
    if (!node->right)
    {
        rightHeight = -1;
        leftHeight = getHeight(node->left);
        return leftHeight - rightHeight;
    }

    leftHeight = getHeight(node->left);
    rightHeight = getHeight(node->right);

    return leftHeight - rightHeight;
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
            // shiftRanks(temp->right); // shifting nodes in the right subtree
            temp->numLeft += 1; //replacing shiftRanks with this to fix runtime...
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
    updateSize(temp);
    setHeight(temp);

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



/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
 *****************************************************************************/

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
    updateSize(temp);   // updating size for temp (original root)
    updateSize(temp1);  // updating size for new root temp1
    setHeight(temp);  // updating height for temp
    setHeight(temp1); // updating height for temp1

    // temp=temp1;

    return temp1;
}



/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
 *****************************************************************************/

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
    updateSize(temp);   // updating size for temp (original root)
    updateSize(temp1);  // updating size for new root temp1
    setHeight(temp);  // updating height for temp
    setHeight(temp1); // updating height for temp1

    // temp = temp1;

    return temp1;
}



/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
 *****************************************************************************/

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
 *****************************************************************************/

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
 ****************************************************************************/

void AVLVector::decrementNumLeft(Node* node) {
    // Traverse up to the root, decrementing numLeft for each node that has the current node in its left subtree (using updateSize function)
    while (node != NULL) {
        updateSize(node);
        node = node->parent;
    }
}

/****************************************************************************
 *                    AVLTree searchByRank Helper Function                  *
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



/****************************************************************************
 *                 AVLTree findRank Helper Function                  *
 ****************************************************************************/


int AVLVector::findRank(Node *node, int e, int priorRank)
{
    if (!node) {
        return -1; // Element not found
    }

    // Traverse the left subtree first
    int leftRank = findRank(node->left, e, priorRank);
    if (leftRank != -1) {
        return leftRank; // If found in left subtree, propagate the rank upwards
    }

    // Increment the rank after visiting the left subtree
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
 ****************************************************************************/

int AVLVector::elementAtRankHelper(Node *node, int r, int &priorRank)
{
    if (node == NULL)
    {
        return -1;
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



/****************************************************************************
 *                 AVLTree getNodeAtRank Helper Function              *
 ****************************************************************************/

Node *AVLVector::getNodeAtRank(Node *node, int rank, int priorRank)
{
    // base case of whether node is not found
    if (!node)
    {
        cout << "Node not found!" << endl;
        return NULL;
    }

    // int leftSize = size(node->left);            // getting size of left subtree
    int currentRank = node->numLeft + priorRank + 1; // calculating rank using rank formula from class

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
    deleteTree(root);
}

/****************************************************************************
 *             AVLVector Destructor Tree Deletion Helper Function           *
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

    Node *node = getNodeAtRank(root, r);
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
 **************************************************************************x*/

int AVLVector::insertAtRank(int r, int e)
{
    if ((root == nullptr && r != 1) || r <= 0 || (root != nullptr && r > root->size + 1)) // +1 to account for insertion at the end
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    int result;

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
        result = insertNode(root, priorRank, e, r);
    }

    return result; //returning the result of insertion (1 on success, -1 on failure)
}

/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
 ****************************************************************************/

int AVLVector::removeAtRank(int r) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot remove any elements!\n" << endl;
        return -1;
    }

    if (r <= 0 || (root != nullptr && r > root->size)) 
    {
        cout << "Rank is out of bounds!\n" << endl;
        return -1;
    }

    int result = deleteNode(root, r); 

    if (root != NULL) {
        root->parent = NULL;  //ensuring the root's parent is always NULL
    }

    return result; //returning the result of deletion (1 on success, -1 on failure)
}



/****************************************************************************
 *                   Extra Credit: AVLVector rankOf Function                *
 ****************************************************************************/

int AVLVector::rankOf(int e)
{   
    int priorRank = 0;
    int result = findRank(root, e, priorRank); // Start with rankOffset of 0
    if (result == -1)
    {
        cout << "Error: Element not found!" << endl;
        return -1;
    }
    return result; 
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