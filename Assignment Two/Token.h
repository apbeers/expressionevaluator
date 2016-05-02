#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <cstdlib>

using namespace std;

enum token_type {letter, integer, op, eq, openbrace, closebrace, invalid};
class Token 
{
public:
    Token();
    Token(const string& s);
    void set(const string& s);
    token_type get_type() const;
    string get_token() const;
    int get_priority() const;
private:
    token_type type;
    string token;	
    int priority;
};

#endif

