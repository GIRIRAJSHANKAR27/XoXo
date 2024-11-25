#include <bits/stdc++.h>
using namespace std;
bool isInteger(const string &val)
{
    regex reg(R"([-+]?\d+)");
    return regex_match(val, reg);
}
bool isFloat(const string &val)
{
    regex reg(R"([-+]?\d*\.?\d+f?)");
    return regex_match(val, reg);
}
bool isDouble(const string &val)
{
    regex reg(R"([-+]?\d*\.?\d+([eE][-+]?\d+)?)");
    return regex_match(val, reg);
}
bool isChar(const string &val)
{
    regex reg(R"('([^'\\]|\\.)')");
    return regex_match(val, reg);
}
bool isString(const string &val)
{
    regex reg(R"("([^"\\]|\\.)*")");
    return regex_match(val, reg);
}
bool isBool(const string &val)
{
    return val == "true" || val == "false";
}
int main()
{
    int n;
    cout << "Enter the number of variables: ";
    cin >> n;
    while (n--)
    {
        string var, type, val;
        cout << "\nEnter the variable name: ";
        cin >> var;
        cout << "Enter the type of variable: ";
        cin >> type;
        cout << "Enter the value of variable: ";
        cin >> val;
        if (type == "int")
        {
            if (isInteger(val))
                cout << var << " is an integer";
            else
                cout << var << " is not an integer";
        }
        else if (type == "float")
        {
            if (isFloat(val))
                cout << var << " is a floating-point number";
            else
                cout << var << " is not a floating-point number";
        }
        else if (type == "double")
        {
            if (isDouble(val))
                cout << var << " is a double";
            else
                cout << var << " is not a double";
        }
        else if (type == "char")
        {
            if (isChar(val))
                cout << var << " is a character";
            else
                cout << var << " is not a character";
        }
        else if (type == "string")
        {
            if (isString(val))
                cout << var << " is a string";
            else
                cout << var << " is not a string";
        }
        else if (type == "bool")
        {
            if (isBool(val))
                cout << var << " is a boolean";
            else
                cout << var << " is not a boolean";
        }
        else
        {
            cout << "Undefined datatype";
        }
        cout << endl;
    }
    return 0;
}