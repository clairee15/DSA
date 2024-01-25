#include "ratingList.h"

ratingList::ratingList()
{
    size = 0;
    firstNode = NULL;
}
ratingList::~ratingList()
{
    Node* temp;
    while (firstNode != NULL)
    {
        temp = firstNode;
        firstNode = firstNode->next;
        temp->next = NULL;
        delete temp;
    }
}
bool ratingList::add(string key, string item)
{
    Node* newNode = new Node();
    newNode->key = key;
    newNode->item = item;
    newNode->next = NULL;

    if (size == 0)
    {
        firstNode = newNode;
    }
    else
    {
        Node* temp;
        temp = firstNode;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    size++;
    return true;
}

bool ratingList::add(int index, ItemType item)
{
    if (index < 0 || index > size)
    {
        return false;
    }

    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = NULL;

    if (index == 0)
    {
        newNode->next = firstNode;
        firstNode = newNode;
    }
    else
    {
        Node* temp;
        temp = firstNode;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    size++;
    return true;
}

void ratingList::remove(int index)
{
    if (index < 0 || index >= size)
    {
        return;
    }

    Node* del = NULL;
    if (index == 0)
    {
        del = firstNode;
        firstNode = firstNode->next;
    }
    else {
        Node* temp;
        temp = firstNode;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        del = temp->next;
        temp->next = del->next;
    }

    delete del;
    size--;
}

ItemType ratingList::get(int index)
{
    if (index < 0 || index >= size) //check if out of range
    {
        return "Nothing";
    }

    Node* temp;
    temp = firstNode;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->item;
}

//get size of list
int ratingList::getLength()
{
    return size;  //get size of list
}

void ratingList::print()
{
    Node* temp;
    temp = firstNode;
    cout << "Food selections offered: " << endl;
    int i = 1;
    while (temp != NULL)
    {
        cout << "[" << i << "]" << temp->item << endl;
        temp = temp->next;
        i++;
    }
    cout << endl;
};
