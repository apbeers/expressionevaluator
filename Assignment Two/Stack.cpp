//
//  Stack.cpp
//  Assignment Five
//
//  Created by Andrew Beers on 4/25/16.
//  Copyright © 2016 Andrew Beers. All rights reserved.
//

#include "Stack.h"

Stack::Stack() {
    topIndex = -1;
    numElements = 0;
    buffer = new int[100];
}


Stack::~Stack() {
    topIndex = -1;
    numElements = 0;
}

// checks if the stack is empty
bool Stack::empty() const
{
    if (numElements == 0)
    {
        return true;
    }
    else
        return false;
    
}

// returns the size
unsigned int Stack::size() const
{
    return numElements;
}

// the nest two functions return the top of the stack
int& Stack::top()
{
    return buffer[topIndex];
}

const int& Stack::top() const
{
    return buffer[topIndex];
}

// puts a new item on top of the stack
void Stack::push(const int& x)
{
    numElements++;
    topIndex++;
    buffer[topIndex] = x;
}

// delets the item on the top and incremets the size
void Stack::pop()
{
    numElements--;
    topIndex--;
}
