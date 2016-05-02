

#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

class Stack
{
public:
    // Constructors
    Stack();
    ~Stack();
    
    // Capacity
    bool empty() const;
    unsigned int size() const;
    
    // Element access
    int& top();
    const int& top() const;
    
    // Modification
    void push(const int& x);
    void pop();
    void print();
    
private:
    int* buffer;              // The dynamically-allocated array that holds the stack
    unsigned int numElements; // The number of elements currently on the stack
    unsigned int topIndex;    // The index of the top of the stack (0 initially)
};

#endif /* STACK_H */
