#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include "Token.h"
#include <vector>
#include <stack>

using namespace std;

enum exp_type {assignment, arithmetic, illegal};
class Expression 
{
public:
    Expression();
    Expression(const string& s);
    void set(const string& s);
    bool isValid();
    string toPostFix();
    string toPreFix();
    string toParenthesized();
    string evaluate();
    string get_original() const;
    exp_type get_type() const;
    void setVariable(Expression exp);
    vector<Token> get_tokenized() const;
    
private:
    string original;
    vector<Token> tokenized;
    vector<Token> postfix;
    bool valid;
    int variables[26];
    int variableSet[26];
    exp_type type;
    stack<int> intStack;
    stack<string> stringStack;
};

#endif