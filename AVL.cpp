#include "AVL.h"

/****************************************************************************
 *                                                                          *
 *                 class AVLTree Constructors & Destructor                  *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                   AVLTree Parametrized Constructor                       *
 *****************************************************************************/

AVLTree::AVLTree(const std::vector<int> &initialValues)
{
}

/****************************************************************************
 *                             AVLTree Destructor                           *
 *****************************************************************************/

AVLTree::~AVLTree()
{
}

/****************************************************************************
 *                                                                          *
 *                  class AVLTree Private Helper Functions                  *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                      AVLTree setHeight Helper Function                   *
 ****************************************************************************/

void AVLTree::setHeight(nodeptr temp)
{
    int heightLeft, heightRight;
    if (temp != NULL)
    {
        if (temp->left == NULL)
            heightLeft = 0;
        else
            heightLeft = temp->left->height + 1;
        if (temp->right == NULL)
            heightRight = 0;
        else
            heightRight = temp->right->height + 1;
        temp->height = (heightLeft > heightRight) ? heightLeft : heightRight;
    }
}

/****************************************************************************
 *                       AVLTree search Helper Function                     *
 ****************************************************************************/

int search(nodeptr &some, int val)
{
    if (some == NULL)
        return -1;
    bool done = false;
    while (!done)
    {
        if (some->value == val)
            return 1;
        else if (some->value > val)
            some = some->left;
        else
            some = some->right;
        if (some == NULL)
            return -1;
    }
}

/****************************************************************************
 *                  AVLTree leftLeftRotation Helper Function                *
 *****************************************************************************/

void AVLTree::leftLeftRotation(nodeptr &temp)
{
    nodeptr temp1 = temp->left;
    nodeptr temp2 = temp1->left;
    temp1->parent = temp->parent;
    temp->parent = temp1;
    temp->left = temp1->right;
    temp1->right = temp;
    if (temp1->parent != NULL)
    {
        if (temp1->parent->left == temp)
            temp1->parent->left = temp1;
        else
            temp1->parent->right = temp1;
    }
    setHeight(temp);
    setHeight(temp1);
    temp = temp1;
}

/****************************************************************************
 *                  AVLTree rightRightRotation Helper Function              *
 *****************************************************************************/

void AVLTree::rightRightRotation(nodeptr &temp)
{
    nodeptr temp1 = temp->right;
    nodeptr temp2 = temp1->right;
    temp1->parent = temp->parent;
    temp->parent = temp1;
    temp->right = temp1->left;
    temp1->left = temp;
    if (temp1->parent != NULL)
    {
        if (temp1->parent->right == temp)
            temp1->parent->right = temp1;
        else
            temp1->parent->left = temp1;
    }
    setHeight(temp);
    setHeight(temp1);
    temp = temp1;
}

/****************************************************************************
 *                  AVLTree leftRightRotation Helper Function               *
 *****************************************************************************/

void AVLTree::leftRightRotation(nodeptr &temp)
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
        if (temp2->parent->right == temp)
            temp2->parent->right = temp2;
        else
            temp2->parent->left = temp2;
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;
}

/****************************************************************************
 *                  AVLTree rightLeftRotation Helper Function               *
 *****************************************************************************/

void AVLTree::rightLeftRotation(nodeptr &temp)
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
        if (temp2->parent->right == temp)
            temp2->parent->right = temp2;
        else
            temp2->parent->left = temp2;
    }
    setHeight(temp);
    setHeight(temp1);
    setHeight(temp2);
    temp = temp2;
}

/****************************************************************************
 *                    AVLTree insertNode Helper Function                    *
 *****************************************************************************/

int AVLTree::insertNode(nodeptr &root, int val)
{
    bool done, violation;
    // int myheight;
    nodeptr temp;
    if (root == NULL)
    {
        root = new node;
        root->value = val;
        root->height = 0;
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        return 1;
    }
    else
    {
        temp = root;
        done = false;
        while (!done)
        {
            if (temp->value >= val)
                if (temp->left == NULL)
                {
                    temp->left = new node;
                    temp->left->parent = temp;
                    temp = temp->left;
                    temp->value = val;
                    temp->height = 0;
                    temp->left = NULL;
                    temp->right = NULL;
                    done = true;
                }
                else
                {
                    temp = temp->left;
                }
            else if (temp->right == NULL)
            {
                temp->right = new node;
                temp->right->parent = temp;
                temp = temp->right;
                temp->value = val;
                temp->height = 0;
                temp->left = NULL;
                temp->right = NULL;
                done = true;
            }
            else
                temp = temp->right;
        } // end of while. Now climb back.
        temp = temp->parent;
        temp->height = 1;
        done = (temp->parent == NULL);
        violation = false;
        while (!done)
        {
            temp = temp->parent;
            set - height(temp);
            if ((temp->left == NULL) || (temp->right == NULL))
                violation = true;
            else if ((temp->left->height - temp->right->height > 1) ||
                     (temp->right->height - temp->left->height > 1))
                violation = true;
            if (violation)
            {
                if ((temp->value >= val) && (temp->left->value >= val))
                    leftLeftRotation(temp);
                else if ((temp->value >= val) && (temp->left->value < val))
                    leftRightRotation(temp);
                else if ((temp->value < val) && (temp->right->value >= val))
                    rightLeftRotation(temp);
                else if ((temp->value < val) && (temp->right->value < val))
                    rightRightRotation(temp);
                done = true;
            }
            if (temp == root)
                done = true;
        } // while ! done
        return 1;
    } // end of else
}

/****************************************************************************
 *                    AVLTree deleteNode Helper Function                    *
 *****************************************************************************/

int AVLTree::deleteNode(nodeptr &root, int val)
{
    nodeptr temp = root;
    nodeptr temp1;
    if (temp == NULL)
        return -1;
    if (search(temp, val) == -1)
        return -1;
    // temp now points to the item you want to delete
    nodeptr temp1 = temp;
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
            if (temp1->left == temp)
                temp1->left = temp->right;
            else
                temp1->right = temp->right;
            delete temp;
            set - height(temp1);
            temp = temp1;
        }
    }
    else
    {
        \\ temp->left not NULL
            temp1 = temp->left;
        while (temp1->right != NULL)
            temp1 = temp1->right;
        temp->value = temp1->value;
        temp = temp1->parent;
        if (temp->left == temp1)
            temp->left = temp1->left;
        else
            temp->right = temp1->left;
        set - height(temp);
        delete temp1;
    }
    while (temp != NULL)
    {
        if (temp->height >= 2)
        {
            if (temp->left == NULL)
            {
                if (temp->right->right == NULL)
                    right - left - rotation(temp);
                else
                    right - right - rotation(temp);
            }
            else if (temp->right == NULL)
                if (temp->left->left == NULL)
                    left - right - rotation(temp);
                else
                    left - left - rotation(temp);
            else if (temp->left->height - temp->right->height > 1)
                if (temp->left->left->height >= temp->left->right->height)
                    left - left - rotation(temp);
                else
                    left - right - rotation(temp);
            else if (temp->right->height - temp->left->height > 1)
                if (temp->right->right->height >= temp->right->left->height)
                    right - right - rotation(temp);
                else
                    right - left - rotation(temp);
        } // else of temp->left == NULL
    } // if temp->height >=2
    temp = temp->parent;
    set - height(temp);
}
// for now
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

AVLVector::AVLVector()
{
}

/****************************************************************************
 *                           AVLVector Destructor                           *
 *****************************************************************************/

AVLVector::~AVLVector()
{
}

/****************************************************************************
 *                                                                          *
 *                          class AVLVector Methods                         *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 *                     AVLVector elementAtRank Function                     *
 *****************************************************************************/

int elementAtRank(int r)
{

    // for now
    return 0;
}

/****************************************************************************
 *                     AVLVector replaceAtRank Function                     *
 *****************************************************************************/

void replaceAtRank(int r, int e)
{
}

/****************************************************************************
 *                     AVLVector insertAtRank Function                     *
 *****************************************************************************/

void insertAtRank(int r, int e)
{
}

/****************************************************************************
 *                     AVLVector removeAtRank Function                      *
 *****************************************************************************/

void removeAtRank(int r)
{
}

/****************************************************************************
 *                          AVLVector rankOf Function                       *
 *****************************************************************************/

int rankOf(int e)
{

    // for now
    return 0;
}

/****************************************************************************
 *                        AVLVector printAll Function                       *
 *****************************************************************************/

void printAll()
{
}