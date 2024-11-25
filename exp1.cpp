#include <iostream>
#include <stack>
#include <string>
using namespace std;
int getPrecedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
string infixToPostfix(const string &infix)
{
    stack<char> stk;
    string postfix = "";
    for (char ch : infix)
    {
        if (isalnum(ch))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            // Push '(' to stack
            stk.push(ch);
        }
        else if (ch == ')')
        {
            while (!stk.empty() && stk.top() != '(')
            {
                postfix += stk.top();
                stk.pop();
            }
            if (!stk.empty())
                stk.pop();
        }
        else
        {
            while (!stk.empty() && getPrecedence(stk.top()) >= getPrecedence(ch))
            {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(ch);
        }
    }
    while (!stk.empty())
    {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}
int main()
{
    string infixExpr;
    cout << "Enter an infix expression: ";
    cin >> infixExpr;
    string postfixExpr = infixToPostfix(infixExpr);
    cout << "Postfix: " << postfixExpr << endl;
    return 0;
}
