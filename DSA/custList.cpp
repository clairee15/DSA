#include "custList.h"

custList::custList()
{
    size = 0;
    firstNode = NULL;
}
custList::~custList()
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
bool custList::add(ItemType item, string password, string firstName, string lastName, string hpNum, string Add)
{
    Node* newNode = new Node();
    newNode->item = item;
    newNode->password = password;
    newNode->firstName = firstName;
    newNode->lastName = lastName;
    newNode->hpNum = hpNum;
    newNode->address = Add;
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

bool custList::add(int index, ItemType item)
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

void custList::remove(int index)
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

ItemType custList::get(int index)
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
int custList::getLength()
{
    return size;  //get size of list
}

void custList::print()
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

void custList:: displayCustDetails(ItemType id) {
    Node* current = firstNode;

    while (current != nullptr) {
        if (current->item == id) {
            cout << "Customer ID: " << current->item << endl;
            cout << "First Name: " << current->firstName << endl;
            cout << "Last Name: " << current->lastName << endl;
            cout << "Phone Number: " << current->hpNum << endl;
            cout << "Address: " << current->address << endl;
            return; // Exit the function after displaying details
        }
        current = current->next;
    }

    // If customer with the specified ID is not found
    cout << "Customer with username " << id << " not found." << endl;
}

string custList::getPassword(ItemType item)
{
    Node* current = firstNode;
    while (current != nullptr)
    {
        if (current->item == item)
            return current->password;
        else
            current = current->next;
    }
}