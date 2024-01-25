#pragma once
#include<iostream>
using namespace std;

#include "BinaryNode.h"
#include "AVL_Tree.h"		// AVL Tree functions

class BST
{
private:

	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST();

	// search for a food item (target) in the binary search tree by location
	BinaryNode* searchbyloc(ItemType target);
	BinaryNode* searchbyloc(BinaryNode* root, ItemType target);

	// search for a food item (target) in the binary search tree by category
	BinaryNode* searchbycat(ItemType target);
	BinaryNode* searchbycat(BinaryNode* root, ItemType target);

	// insert an menu item to the binary search tree (food item, location, category)
	void insert(ItemType item, ItemType loc, ItemType cat);
	void insert(BinaryNode*& root, ItemType item, ItemType loc, ItemType cat);

	// traverse the binary search tree in inorder (by cat/location)
	void inorder(ItemType target);
	void inorder(BinaryNode* t, ItemType target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();
};
