#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class custList
{
private:
	struct Node
	{
		ItemType item;	// item
		string password;
		string firstName;
		string lastName;
		string hpNum;
		string address;
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	custList();

	// destructor
	~custList();

	// add an item to the back of the list (append)
	bool add(ItemType item, string password, string firstName, string lastName, string hpNum, string Add);

	// add an item at a specified position in the list (insert)
	bool add(int index, ItemType item);

	// remove an item at a specified position in the list
	void remove(int index);

	//get an item at a specified position in the list (retrieve)
	ItemType get(int index);

	//check the size of the list
	int getLength();

	// display all the items in the list
	void print();

	// display everyth in a specified position in the list
	void displayCustDetails(ItemType id);

	string getPassword(ItemType item);
};
