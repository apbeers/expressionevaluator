//
//  main.cpp
//  Assignment Two
//
//  Created by Andrew Beers on 2/22/16.
//  Copyright © 2016 Andrew Beers. All rights reserved.
//

#include <iostream>

#include <string>
#include "Token.h"
#include "Expression.h"


using namespace std;

int main(int argc, const char * argv[])
{
    
    string input = "";
    string action = "";

    vector<Expression> expressions;
    Expression expression;
    
    
    // the whole thing is inside of this while loop
    while (action != "q" && action != "Q")
    {
    do {
        cout << "input: ";
        cin >> input;
        } while (input == "");
    
        if (input == "q" || input == "Q")
        {
            break;
        }
        
        if (action == "s" || action == "S")
        {
            expressions.clear();
        }
        
        // this part checks for semicolons and creates the expressions from`1871 the input
        bool foundSemicolon = false;
        string temp = "";
        for (int i = 0; i < input.length();i++)
        {
            
            if (input[input.length()-1] != ';')
            {
                foundSemicolon = false;
                break;
            }
            
            if (input[i] != ';')
            {
                temp += input[i];
            }
            else
            {
                foundSemicolon = true;
                if (temp.size() == 0)
                {
                    foundSemicolon = false;
                    break;
                }
                
                expression.set(temp);
                expressions.push_back(expression);
                temp = "";
            }
        }

        
        action = "";

        // these two cases check that all of the expressions are valid and that the first expression is not an assignment
        for (int i = 0; i < expressions.size(); i++)
        {
            if (!expressions[i].isValid())
            {
                cout << expressions[i].get_original() << " is invalid" << endl;
                action = "s";
            }
        }
        
        if (expressions.size() != 0) {
            if (expressions[0].get_type() == assignment)
            {
                action = "s";
                cout << "the first expression must not be assignment" << endl;
            }
        }
        
        while (action != "q" && action != "c" && action != "s" && action != "Q" && action != "C" && action != "S")
        {
            if (!foundSemicolon)
            {
                cout << "semicolon error" << endl;
                break;
            }
            
            cout << "action: ";
            cin >> action;
 
            
            // loops through the expressions vector and sets the varaible values in the first expression
        for (int i = 0; i < expressions.size(); i++)
        {
            
            for (int i = 0; i < expressions.size(); i++)
            {
                if (expressions[i].get_type() == assignment && expressions[i].isValid())
                {
                    expressions[0].setVariable(expressions[i]);
                    
                }
            }
            
            // performs the specified action
            if (expressions[i].get_type() == arithmetic && expressions[i].isValid())
            {
                
                if (action == "<")
                {
                    cout << "postfix of " << expressions[i].get_original() << " is: " << expressions[i].toPostFix() << endl;
                }
                else if (action == ">")
                {
                    cout << "prefix of " << expressions[i].get_original() << " is: " << expressions[i].toPreFix() << endl;
                }
                else if (action == "=")
                {
                    cout << expressions[i].get_original() << " = " << expressions[i].evaluate() << endl;
                }
                else if (action == "f")
                {
                    cout << "fully parenthesizing " << expressions[i].get_original() << " results: " << expressions[i].toParenthesized() << endl;
                }
                else
                {
                    // check for invalid actions
                    if (action != "q" && action != "c" && action != "s" && action != "Q" && action != "C" && action != "S")
                    {
                        cout << "invalid action" << endl;
                    }
                }
            }
            }
        }
    }
    
    return 0;
}
