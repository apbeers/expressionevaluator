#include "Expression.h"
#include <iostream>


// sets all of the initial class variables
Expression::Expression()
{
    valid    = false;
    original = "";
    type     = illegal;
}

//just calls set to tokenize the function
Expression::Expression(const string& s)
{
    set(s);
}

bool delimCheck(char s, string delims) // this method is used as part of the tokenizing operation. it checks if the character is a delimiter and returns true if it is, otherwise false
{
    size_t k = delims.length();
    for (int i = 0; i < k; i++)
    {
        
        if (s == delims.at(i))
        {
            return true;
        }
    }
    return false;
}

void Expression::set(const string& s)
{
    tokenized.clear();
    original = s; // sets the original variable in the class for this expression
    string delims = "()+-=/* %"; // string of delimiters
    string temp = ""; // this string is used to store characters that come between tokens
    size_t k = s.length(); // set k = the size of the string for efficiency. this way it only runs once
    for (int i = 0; i < k; i++) {
        
        if (delimCheck(s.at(i),delims))
        {
            if (temp != "")
            {
                tokenized.push_back(temp);
            }
            if (s.at(i) != ' ')
            {
               string b(1,s.at(i));
                tokenized.push_back(b);
            }
            temp = "";
        }
        else
        {
            temp+=s.at(i); // if the character was not a delimiter, it gets added to the temp string to be tokenized when the next delimiter is found
        }
    }
    if (temp != "")
    {
        tokenized.push_back(temp);
    }
    
    // this nest part checks if the function is valied and sets it's type
    enum States {operand, func, done};
    // this sets it the expression conatins an equal sign
    bool eqtrue = false;
    States state = operand; // an enum value used in the error checking
    int pcount = 0; // use to make sure there is the correct amount of open and close braces
    valid = true;
    
    // loops through the expression and looks for errors
    for (int i = 0; i < tokenized.size() && state != done; i++)
    {
        switch (state) {
                // checks if the token is an operand or open brace. if it is a close brace the expression is invalid
            case operand:
                if (tokenized[i].get_type() == openbrace)
                {
                    pcount++;
                }
                else if (tokenized[i].get_type() == integer || tokenized[i].get_type() == letter)
                {
                    state = func;
                }
                else
                {
                    valid = false;
                    state = done;
                }
                break;
                // this tests the function and checks if it is valid
            case func:
                if (tokenized[i].get_type() == closebrace)
                {
                    pcount--;
                    
                    if (pcount < 0) {
                        valid = false;
                        state = done;
                    }
                    
                }

                else if (tokenized[i].get_type() == eq)
                {
                    eqtrue = true;
                    state = operand;
                }
                else if (tokenized[i].get_type() == op)
                {
                    state = operand;
                }
                else
                {
                    valid = false;
                    state = done;
                }
                
            default:
               // cout << "break" << endl;
                break;
        }
    }

    // if the parenthesis aren't balanced it is invalid
    if (pcount != 0)
    {
        valid = false;
    }
    // it the check ends on operand it is invalid
    if (state == operand)
    {
        valid = false;
    }
    // it it is valid and is an assignment, it sets it as such
    if (valid) {
        if (eqtrue && tokenized[0].get_type() == letter && tokenized[2].get_type() == integer && tokenized.size() == 3)
        {
            type = assignment;
            
        }
        else
        {
            //valid = false;
            type = arithmetic;
        }
    }
    else
    {
        type = arithmetic;
    }
    
    if (!valid)
    {
        cout << original << " is invalid" << endl;
    }
    
    
    
    
}

string Expression::get_original() const
{
    return original;
}

vector<Token> Expression::get_tokenized() const
{
    return tokenized;
}

exp_type Expression::get_type() const
{
    return type;
}

// hashes the value of the variables into a slot in the array based on the letter
void Expression::setVariable(Expression exp)
{
      variables[tolower(exp.original[0]) - 'a'] = stoi(exp.tokenized[2].get_token());
}

// this function will check for invalid tokens in the expression
bool Expression::isValid()
{
    return valid;
}

// this is used to check the proirty of operands on the stack
int getPriority(string s)
{
    int temp = 0;
    if (s == "+" || s == "-")
    {
        temp = 6;
    }
    else if (s == "*" || s == "/" || s == "5")
    {
        temp = 5;
    }
    else if (s == "(" || s == ")")
    {
        temp = 1;
    }
    return temp;
}

// converts the expression to postix and loads the result into the postix vector.
string Expression::toPostFix()
{
    // the string that holds the output.
    string output = "";
    
    for (int i = 0; i < tokenized.size(); i++)
    {
        
        // if the token is a letter or number, it is put to the ootput and loaded into the postfix vectore
        if (tokenized[i].get_type() != op && tokenized[i].get_type() != openbrace && tokenized[i].get_type() != closebrace)
        {
            output += tokenized[i].get_token() + " ";
            postfix.push_back(tokenized[i].get_token());
        }
        
        // if the token is an oerpator it is pushed on the stack.
        else if (tokenized[i].get_type() == op)
        {
            // pops ttokens off of the stack and to the output until it gets to an operator with ahigher priort, the bottom of the stack, or an open brace
            while (!stringStack.empty() && stringStack.top() != "(" &&  getPriority(stringStack.top()) <= getPriority(tokenized[i].get_token()))
            {
                output+= stringStack.top() + " ";
                postfix.push_back(stringStack.top());
                
                stringStack.pop();
            }
            // pushed the lasts item to the stack
            stringStack.push(tokenized[i].get_token());
        }
        
        // open braces are pushed to the stack
        else if (tokenized[i].get_token() == "(")
        {
            stringStack.push(tokenized[i].get_token());
        }
       
        // prints of everything until it reaches an open brace
        else if (tokenized[i].get_token() == ")")
        {
            
            while (!stringStack.empty())
            {
                if (stringStack.top() == "(")
                {
                    
                    stringStack.pop();
                    break;
                }
                output += stringStack.top()+" ";
                postfix.push_back(stringStack.top());
                
                stringStack.pop();
            }
        }
    }
    
    // pops everyhting else off of the stack and to the output
    while (!stringStack.empty())
    {
        output += stringStack.top() + " ";
        postfix.push_back(stringStack.top());
        stringStack.pop();
    }
    
    return output;
}

// this function converts the postfix expression to a prefix version
string Expression::toPreFix()
{
    stack<string> Stack;
    
    toPostFix();
    
    
    string temp1 = "";
    string temp2 = "";
    string output = "";
    
    
    // loops throught the postfix vector, when it finds an operator it pops two items from the stack and puts the operator on the front. then it stores this entire string back to the stack
    for (int i = 0; i < postfix.size(); i++)
    {
   
        
        if (postfix[i].get_type() == integer || postfix[i].get_type() == letter)
        {
            Stack.push(postfix[i].get_token());
        }
        else if (postfix[i].get_type() == op)
        {
            temp2 = Stack.top();
            Stack.pop();
            temp1 = Stack.top();
            Stack.pop();
            output += postfix[i].get_token() +" "+temp1+" "+temp2;
            Stack.push(output);
            output = "";
        }
    }
    
    // at the end, the last item on the stack is the answer we want
    string result = Stack.top();
    Stack.pop();
    
    return result;
}

// uses the same logic as the evaluate function. It also uses the postfix version of the expression. It will loop through, when it finds an operator it pops two times from the stack, appends an open brace to the beginning, puts the items and operator inside after reversing the operands, then puts a close brace on and pushed the entire string back to the stack. at the end of the function the top of the stack contains the answer we want
string Expression::toParenthesized()
{
    stack<string> Stack;
    string num1 = "";
    string num2 = "";
    string temp = "";
    
    toPostFix();
    
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i].get_type() == integer || postfix[i].get_type() == letter)
        {
            Stack.push(postfix[i].get_token());
        }
        
        else if (postfix[i].get_type() == op)
        {
            // num2 is popped first becuase it will haave to go second in the parenthesize notation
            num2 = Stack.top();
            Stack.pop();
            num1 = Stack.top();
            Stack.pop();
            
            // create the parenthesize peice and pushed it back onto the stack
            temp += "("+num1+postfix[i].get_token()+num2+")";
            Stack.push(temp);
            temp = "";
        }
    }
    return Stack.top();
}

// this also uses the postix expression. It will loop through until it finds an operator. when it does, it pops two items from the stack, performs the operation, and pushes the result back onto the stack. at the end, the stack only contains the result
int Expression::evaluate()
{
    stack<string> Stack;
    int num1 = 0;
    int num2 = 0;
    double result = 0.0;
    
    toPostFix();
    
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i].get_type() == integer)
        {
            Stack.push(postfix[i].get_token());
            
        }
        // if it is a letter, it replaced it with the value from the variable array
        else if (postfix[i].get_type() == letter)
        {
            string a = postfix[i].get_token();
            Stack.push(to_string(variables[a[0]-'a']));
        }
        
        if (postfix[i].get_type() == op)
        {
            num2 = stoi(Stack.top());
            Stack.pop();
            num1 = stoi(Stack.top());
            Stack.pop();
        
            if (postfix[i].get_token() == "+")
            {
                result = num1 + num2;
            }
            else if (postfix[i].get_token() == "-")
            {
                result = num1 - num2;
            }
            else if (postfix[i].get_token() == "*")
            {
                result = num1 * num2;
            }
            else if (postfix[i].get_token() == "/")
            {
                result = num1 / num2;
            }
            else
            {
                result = num1 % num2;
            }
            Stack.push(to_string(result));
        }
    }
    // at the end, the top of the stack is the string i want
    return stoi(Stack.top());
}


