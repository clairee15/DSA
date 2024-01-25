// BST.cpp
#include<iostream>
#include<iomanip>
using namespace std;
#include "BST.h"

BST::BST()
{
    root = NULL;
}

BinaryNode* BST::searchbyloc(ItemType target) {
    return searchbyloc(root, target);
}

BinaryNode* BST::searchbyloc(BinaryNode* root, ItemType target) {
    if (root == NULL)		// item not found
        return NULL;
    else
    {
        if (root->loc == target)	// item found
            return root;
        else
            if (target < root->loc) {
                return searchbyloc(root->left, target); // search in left subtree
            }
            else {
                return searchbyloc(root->right, target); // search in right subtree
            }  
    }
}


BinaryNode* BST::searchbycat(ItemType target) {
    return searchbycat(root, target);
}

BinaryNode* BST::searchbycat(BinaryNode* root, ItemType target) {
    if (root == NULL)		// item not found
        return NULL;
    else
    {
        if (root->cat == target)	// item found
            return root;
        else
            if (target < root->cat) {
                return searchbycat(root->left, target); // search in left subtree
            }
            else {
                return searchbycat(root->right, target); // search in right subtree
            }  	
    }
}

void BST::insert(ItemType item, ItemType loc, ItemType cat) {
    insert(root, item, loc, cat);
}

void BST::insert(BinaryNode*& root, ItemType item, ItemType loc, ItemType cat) {
    if (root == NULL)
    {
        BinaryNode* newNode = new BinaryNode;
        newNode->item = item;
        newNode->loc = loc;
        newNode->cat = cat;
        newNode->left = NULL;
        newNode->right = NULL;
        root = newNode;
    }
    else if (item < root->item) {
        insert(root->left, item, loc, cat);
    }
    else if (item > root->item) {
        insert(root->right, item, loc, cat);
    }
    root = balance(root);				// balance the tree (AVL Tree function)
}

// traverse the binary search tree in inorder
void BST::inorder(ItemType target)
{
    if (isEmpty())
        cout << "No item found" << endl;
    else
        inorder(root, target);
}

void BST::inorder(BinaryNode* t, ItemType target)
{
    if (t != NULL)
    {
        inorder(t->left, target);

        if (t->cat == target || t->loc == target)
        {
            cout << t->item << endl;
        }

        inorder(t->right, target);
    }
}

// traverse the binary search tree in inorder
void BST::inorder()
{
    if (isEmpty())
        cout << "No item found" << endl;
    else
        inorder(root);
}

void BST::inorder(BinaryNode* t)
{
    if (t != NULL)
    {
        inorder(t->left);
        cout << setw(15) << t->item << setw(15) << t->loc <<
            setw(15) << t->cat << endl;
        inorder(t->right);
    }
}



// traverse the binary search tree in preorder
void BST::preorder()
{
    if (isEmpty())
        cout << "No item found" << endl;
    else
        preorder(root);
}

void BST::preorder(BinaryNode* t)
{
    if (t != NULL)
    {
        cout << setw(15) << t->item << setw(15) << t->loc <<
            setw(15) << t->cat << endl;
        preorder(t->left);
        preorder(t->right);
    }
}

// traverse the binary search tree in postorder
void BST::postorder()
{
    if (isEmpty())
        cout << "No item found" << endl;
    else
        postorder(root);
}

void BST::postorder(BinaryNode* t)
{
    if (t != NULL)
    {
        postorder(t->left);
        postorder(t->right);
        cout << t->item << endl;
    }
}


// check if the binary search tree is empty
bool BST::isEmpty() { return (root == NULL); }
