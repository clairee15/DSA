#pragma once
#include<iostream>
#include <string>
using namespace std;

typedef string ItemType;

struct BinaryNode 
{
    ItemType item;
    ItemType loc;
    ItemType cat;

    BinaryNode* left;
    BinaryNode* right;
};
