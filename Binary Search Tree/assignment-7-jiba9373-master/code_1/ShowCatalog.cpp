#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}

ShowItem* minValueNode(ShowItem* node)
{
    ShowItem* current = node;
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}

ShowItem* removeShowHelper(ShowItem* currNode, string title)
{
    if (currNode)
    {
        if (title.compare(currNode->title) < 0)
        {
            currNode->left = removeShowHelper(currNode->left, title);
        }
        else if (title.compare(currNode->title) > 0)
        {
            currNode->right = removeShowHelper(currNode->right, title);
        }
        else if (title == currNode->title)
        {
            if(!currNode->right && !currNode->left)
            {
                delete currNode;
                currNode = nullptr;
                return NULL;
            }
            else
            {
                if (currNode->left && !currNode->right)
                {
                    ShowItem* temp = currNode->left;
                    delete currNode;
                    return temp;
                }
                else if (currNode->right && !currNode->left)
                {
                    ShowItem* temp = currNode->right;
                    delete currNode;
                    return temp;
                }
                else
                {
                    ShowItem* next = minValueNode(currNode->right);
                    currNode->title = next->title;
                    currNode->showRating = next->showRating;
                    currNode->userRating = next->userRating;
                    currNode->year = next->year;
                    currNode->right = removeShowHelper(currNode->right, currNode->title);
                }
            }
        }
        return currNode;
    }
    return NULL;
}

/* TODO */
void ShowCatalog::removeShow(std::string title)
{
    // TODO
    root = removeShowHelper(root, title);
}

/* TODO */


ShowItem* getParentHelper(ShowItem *currNode, ShowItem* find)
{
    if (currNode == NULL)
    {
        return NULL;
    }
    if (currNode->left == find || currNode->right == find)
    {
        return currNode;
    }
    if (currNode->title.compare(find->title) > 0)
    {
        return getParentHelper(currNode->left, find);

    }
    return getParentHelper(currNode->right, find);
}


void ShowCatalog::rightRotate(std::string title)
{   
    ShowItem* x = getShowHelper(root, title);
    ShowItem* xparent = getParentHelper(root, x);
    ShowItem* xLeft = x->left;
    x->left = xLeft->right;
    xLeft->right = x;
    if(xparent != NULL)
    {
        if (x == root)
        {
            root = xLeft;
        }
        else if (xLeft->title < xparent->title)
        {
            xparent->left = xLeft;
        }
        else if (xLeft->title > xparent->title)
        {
            xparent->right = xLeft;
        }
    }
    else
    {
        root = xLeft;
    }
}

/* TODO */
void ShowCatalog::leftRotate(std::string title)
{
    // TODO
    ShowItem* x = getShowHelper(root, title);
    ShowItem* xparent = getParentHelper(root, x);
    ShowItem* xRight = x->right;
    x->right = xRight->left;
    xRight->left = x;
    if(xparent != NULL)
    {
        if (x == root)
        {
            root = xRight;
        }
        else if (xRight->title < xparent->title)
        {
            xparent->left = xRight;
        }
        else if (xRight->title > xparent->title)
        {
            xparent->right = xRight;
        }
    }
    else
    {
        root = xRight;
    }
}
