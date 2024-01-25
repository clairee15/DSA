#include "Queue.h"
#include<iomanip>

Queue::Queue()
{
	frontNode = NULL;
	backNode = NULL;
}


Queue::~Queue()
{
	while (!isEmpty())
	{
		dequeue();
	}
}


// enqueue (add) item at the back of queue
bool Queue::addOrder(int num, ItemType id, ItemType item, int quantity, string status)
{
	Node* newNode = new Node;
	newNode->num = num;
	newNode->id = id;
	newNode->item = item;
	newNode->quantity = quantity;
	newNode->status = status;
	newNode->next = NULL;
	if (isEmpty())
	{
		frontNode = newNode;
		backNode = newNode;
	}
	else
	{
		backNode->next = newNode;
		backNode = newNode;
	}
	return true;
}


// dequeue (remove) item from front of queue
bool Queue::dequeue()
{
	if (isEmpty())
	{
		return false;
	}
	Node* temp = frontNode;
	frontNode = frontNode->next;
	delete temp;
	if (frontNode == NULL)
	{
		backNode = NULL;
	}
	return true;
}


// dequeue (remove) and retrieve item from front of queue
bool Queue::removeOrder(int i)
{
	if (isEmpty())
	{
		return false;
	}
	Node* current = frontNode;

	// Find the i-th node
	for (int count = 0; count < i; count++) {
		if (current->num == i)
		{
			cout << current->num;
			frontNode = frontNode->next;
			delete current;
			return true;
		}
		current = current->next;
	}
}

// get no. of items
int Queue::getlength() {
	int count = 0;
	Node* current = frontNode;

	// Traverse the queue and count the number of elements
	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

string Queue::getStatus(int i)
{
	if (isEmpty() || i < 0 || i > getlength()) {
		return 0; // Return a default value in case of invalid index or empty queue
	}
	Node* current = frontNode;

	// Find the i-th node
	for (int count = 0; count < i; count++) {
		current = current->next;
	}
	return current->status;
}

// retrieve (get) item from front of queue
void Queue::getFront(ItemType& item)
{
	if (isEmpty())
	{
		return;
	}
	item = frontNode->item;
}


// check if the queue is empty
bool Queue::isEmpty()
{
	return frontNode == NULL;
}


// display items in queue from front to back
void Queue::displayList()
{
	Node* current = frontNode;
	int i = 1;
	while (current != NULL)
	{
		cout << "[" << i << "]" << current->item << endl;
		current = current->next;
		i++;
	}
	cout << endl;
}

void Queue::displayOrderDetails(ItemType n)
{
	Node* current = frontNode;
	int i = 1;
	while (current != NULL)
	{
		if (current->id == n)
		{
			cout << "[" << i << "]" << setw(15) << current->item << setw(12) << current->quantity << setw(17)<< current->status << endl;
			current = current->next;
			i++;
		}
	}
	cout << endl;
}

void Queue::updateStatus(int i, string newstatus) {
	Node* current = frontNode;

	i = i - 1;
	// Find the i-th node
	for (int count = 0; count < i; count++) {
		current = current->next;
	}

	current->status = newstatus;
}


void Queue::displayItems(int i) {
	if (i < 0 || i >= getlength()) {
		cout << "Invalid index." << endl;
		return;
	}

	Node* current = frontNode;

	for (int count = 0; count < i; count++) {
		current = current->next;
	}

	cout << setw(15) << i+1 << setw(20) << current->id << setw(20) << current->item << setw(15)
		<< current->quantity << setw(20) << current->status << endl;
}


void Queue::displayCompleted()
{
	Node* current = frontNode;
	cout << "OrderID     Dish            Quantity               Status" << endl;
	cout << "------------------------------------------------------------------" << endl;
	int i = 1;
	while (current != NULL && current->status == "Order Completed")
	{
		cout << "[" << i << "]" << setw(15) << current->item << setw(12) << current->quantity << setw(30) << current->status << endl;
		current = current->next;
		i++;
	}
	cout << endl;
}


// get customer id from order i
string Queue::getID(int i)
{
	if (isEmpty() || i < 0 || i >= getlength()) {
		return 0; // Return a default value in case of invalid index or empty queue
	}

	Node* current = frontNode;

	// Find the i-th node
	for (int count = 0; count < i; count++) {
		current = current->next;
	}
	return current->id;
}

//get food name from order i
string Queue::getFood(int i)
{
	if (isEmpty() || i < 0 || i > getlength()) {
		return 0; // Return a default value in case of invalid index or empty queue
	}

	Node* current = frontNode;

	// Find the i-th node
	for (int count = 0; count < i-1; count++) {
		current = current->next;
	}
	return current->item;
}
