#include "Dictionary.h"
#include <iomanip>
#include "ratingList.h"

// constructor
Dictionary::Dictionary()
{
	size = 0;
	for (int i = 0;i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
}

// destructor
Dictionary::~Dictionary()
{
	for (int i = 0;i < MAX_SIZE; i++)
	{
		Node* current = items[i];
		while (current != NULL)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

int Dictionary::hash(KeyType key)
{
	int hashValue = 0;
	for (int i = 0; i < key.length(); i++)
	{
		char c = key[i];
		int charVal = charvalue(c);
		hashValue += charVal;
	}
	return hashValue % MAX_SIZE;
}

// add a new item with the specified key to the Dictionary
bool Dictionary::giveRating(KeyType newKey, ItemType newItem)
{
	int index = hash(newKey);
	ratingList ratingList;
	if (items[index] == NULL)
	{
		items[index] = new Node;
		items[index]->key = newKey;
		items[index]->item = newItem;
		items[index]->next = items[index];
	}
	else
	{
		Node* currentNode = items[index];
		if (currentNode->key == newKey)
		{
			return true;
		}
		while (currentNode->next != NULL)
		{
			currentNode = currentNode->next;
			if (currentNode->key == newKey)
			{
				ratingList.add(newKey, newItem);
			}
		}
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		newNode->next = NULL;
		currentNode->next = newNode;
	}
	size++;
	return true;
}

// remove an item with the specified key in the Dictionary
void Dictionary::remove(KeyType key)
{
	int index = hash(key);
	if (items[index] != NULL)
	{
		Node* currentNode = items[index];
		Node* temp = NULL;
		while (currentNode != NULL)
		{
			if (currentNode->key == key)
			{
				if (temp == NULL)
				{
					items[index] = currentNode->next;
				}
				else
				{
					temp->next = currentNode->next;
				}
				delete currentNode;
				size--;
				cout << "Removed successfully." << endl;
				return;
			}
			temp = currentNode;
			currentNode = currentNode->next;
		}
	}
	cout << "Order not found" << endl;
}

void Dictionary::cancel(KeyType key)
{
	int index = hash(key);
	if (items[index] != NULL)
	{
		Node* currentNode = items[index];
		Node* temp = NULL;
		while (currentNode != NULL)
		{
			if (currentNode->key == key || currentNode->next != NULL)
			{
				if (temp == NULL)
				{
					items[index] = currentNode->next->next;
				}
				else
				{
					temp->next->next = currentNode->next->next;
				}
				delete currentNode;
				size--;
				cout << "Removed successfully." << endl;
				return;
			}
			temp = currentNode;
			currentNode = currentNode->next->next;
		}
	}
	cout << "Order not found" << endl;
}


// get an item with the specified key in the Dictionary (retrieve)
// pre : key must exist in the dictionary
// post: none
// return the item with the specified key from the Dictionary
ItemType Dictionary::get(KeyType key)
{
	int index = hash(key);
	Node* currentNode = items[index];
	while (currentNode != NULL)
	{
		if (currentNode->key == key)
		{
			return currentNode->item;
		}
		currentNode = currentNode->next;
	}
	return currentNode->item;
}

// check if the Dictionary is empty
// pre : none
// post: none
// return true if the Dictionary is empty; otherwise returns false
bool Dictionary::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
}

// check the size of the Dictionary
// pre : none
// post: none
// return the number of items in the Dictionary
int Dictionary::getLength()
{
	return size;
}

//------------------- Other useful functions -----------------

// display the items in the Dictionary
void Dictionary::print()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node* currentNode = items[i];
		while (currentNode != NULL)
		{
			cout << currentNode->key << setw(16) << currentNode->item << endl;
			currentNode = currentNode->next;
		}
	}
}


string Dictionary::printByItem(string item)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node* currentNode = items[i];
		if (currentNode && item == items[i]->item)
		{
			return currentNode->key;
		}

	}
}

// bool contains(KeyType key);

int Dictionary::charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
			return (int)c - (int)'A';
		else
			return (int)c - (int)'a' + 26;
	}
	else
		return -1;
}
