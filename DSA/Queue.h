// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class Queue
{
private:
	struct Node
	{
		ItemType item;	// item
		int quantity;
		string status;
		ItemType id;
		int num;
		Node* next;	// pointer pointing to next item
	};

	Node* frontNode;	// point to the first item
	Node* backNode;	// point to the first item

public:
	// constructor
	Queue();

	~Queue();

	// enqueue (add) item at the back of queue
	bool addOrder(int num, ItemType id, ItemType item, int quantity, string status);

	// dequeue (remove) item from front of queue
	bool dequeue();

	// dequeue (remove) and retrieve item from front of queue
	bool removeOrder(int i);

	// get length of queue
	int getlength();

	// gets the status of an order at the specified position (i)
	// returns the current status as a string
	string getStatus(int i);

	// retrieve (get) item from front of queue
	void getFront(ItemType& item);

	// check if the queue is empty
	bool isEmpty();

	// display items in queue from front to back
	void displayList();

	// display food items of specified order
	void displayItems(int i);

	void displayOrderDetails(ItemType n);

	// update order status of order i with newstatus
	void updateStatus(int i, string newstatus);

	void displayCompleted();

	// get id from an order (order i)
	// returns the id/username as a string
	string getID(int i);

	string getFood(int i);
};



