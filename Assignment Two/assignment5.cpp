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
#include "Stack.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string input = "";
    string action = "";

    vector<Expression> expressions;
    
    
    Expression expression;
    
    
    while (action != "q") {
 
        do {
    cout << "input: ";
        cin >> input;
        } while (input == "");
    
        if (input == "q") {
            break;
        }
        
        if (action == "s") {
            expressions.clear();
        }
        
        bool foundSemicolon = false;
    string temp = "";
        for (int i = 0; i < input.length();i++) {
            if (input[i] != ';') {
                temp += input[i];
            }
            else
            {
                foundSemicolon = true;
                if (temp.size() == 0) {
                    foundSemicolon = false;
                    break;
                }
                
                expression.set(temp);
                expressions.push_back(expression);
                temp = "";
            }
            
            
            if (input[input.length()-1] != ';') {
                
                foundSemicolon = false;
                break;
            }
            
        }
        
        action = "";

        for (int i = 0; i < expressions.size(); i++) {
            if (!expressions[i].isValid()) {
                action = "s";
            }
            if (expressions[0].get_type() == assignment) {
                action = "s";
            }
        }
        
        
        
        while (action != "q" && action != "c" && action != "s") {
            if (!foundSemicolon) {
                cout << "semicolon error" << endl;
                break;
            }
            
            cout << "action: ";
            cin >> action;
 
        for (int i = 0; i < expressions.size(); i++) {
           
          //  cout << "valid: " << expressions[i].isValid() << endl;
            
            
            for (int i = 0; i < expressions.size(); i++) {
                if (expressions[i].get_type() == assignment && expressions[i].isValid())
                {
                    //cout << expressions[i].get_original() << endl;
                    expressions[0].setVariable(expressions[i]);
                    
                }
            }
            
            
            
            
            if (expressions[i].get_type() == arithmetic && expressions[i].isValid()) {
                
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
                    if (action != "q" && action != "c" && action != "s") {
                        
                    
                    cout << "invalid action" << endl;
                    }
                }
            }
         

            
            }
  
        }
        
    
    }
        
        
    
    
    
    
    /*
    Expression test2;
    string test = ")  a23b+12cs-0023*123 hghg ab123((0)";
    string test3 = "    (a + 123 )*(ab - (3 + 4 )), ";
    cout <<" //// TEST 1 ////" << endl;
  
    test2.set(test);
    test2.display();
    */
    

    
    
    
    
    
    
    
    
    return 0;
}
