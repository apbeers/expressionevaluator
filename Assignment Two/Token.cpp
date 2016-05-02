
#include "Token.h"

Token::Token()
{
    type     = invalid;
    token    = "";
    priority = -1;
}

Token::Token(const string& s)
{
    set(s);
}

void Token::set(const string& s)
{
    /*
    token  = s;
    priority = -1;
    
    if (s == "+" || s == "-")
    {
        priority = 6;
        type = op;
    }
    else if (s == "*" || s == "/" || s == "%")
    {
        priority = 5;
        type = op;
    }
    else if (s == "=")
        type = eq;
    else if (s == "(")
    {
        type = openbrace;
        priority = 1;
    }
    else if (s == ")")
    {
        type = closebrace;
        priority = 1;
    }
    
    // error checking from the TAs
    // Single letters are valid. Multiple letters are not.
    else if (s.length() == 1 && isalpha(s[0]))
        type = letter;
        
    // We have an invalid token or a number. Figure out which.
    else
    {
        type = integer;
        for (int i = 0; i < s.length(); ++i)
        {
            if (!isdigit(s[i]))
            {
                type = invalid;
                break;
            }
        }  
    }
     */
    token = s; // these three lines set the default variables
    priority = -1;
    type = invalid;
    
    
    // this if statement is used to set the priority and type of the token
    if (s.length() == 1 && !isdigit(s.at(0)) && !isalpha(s.at(0)))
    {
        if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
        {
            type = op;
            
            if (s == "+" || s == "-") {
                priority = 6;
            }
            else
            {
                priority = 5;
            }
        }
        else if (s == "(")
        {
            type = openbrace;
            priority = 1;
        }
        else if (s == ")")
        {
            type = closebrace;
            priority = 1;
        }
        else if (s == "=")
        {
            type = eq;
        }
    }
    
    else
    {
        bool isInt = true;
        bool isString = true;
        bool startswithzero = false;
        size_t k = s.length();
        
        // this loop goes through the token to see if all of the characters are integers
        for (int i = 0; i < k; i++)
        {
            if (!isdigit(s[i]))
            {
                isInt = false;
            }
            
            // thi set of if statemnets checks if it is an integer that starts with zero
            if (s.at(0) == '0')
            {
                if (s.at(i)!= 0 )
                {
                    startswithzero = true;
                }
            }
        }
        if (isInt && !startswithzero)
        {
            type = integer;
        }
        else
        {
            type = invalid;
        }
        
        // checks if the token is all alphabetic characters
        for (int i = 0; i < k; i++)
        {
            if (!isalpha(s[i]) || s.length() !=1)
            {
                isString = false;
            }
        }
        
        if (isString)
        {
            type = letter;
        }
        
        if (!isString && !isInt)
        {
            type = invalid;
        }
    }
}

token_type Token::get_type() const
{
    return type;
}
 
string Token::get_token() const
{
    return token;
}

int Token::get_priority() const
{
    return priority;
}

