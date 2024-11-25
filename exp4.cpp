// 1) begin the program
// 2) the expression is read from the file using file writer
// 3) each string is read and the total no of string in the file is counted
// 4) the string is then checked for the given condition(an operator)
// 5) if the condition is satisfied the previous and next string are concatinated and in are stored in first temp value and the 3 address code exp is printed.
// 6) suppose if another operand c then the first temp value is contatinated to the next string using the operator and the expression is printed.
// 7) the final temp value is replaced with the left operant value.
// 8) the program ends
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (ch == ' ')
            continue;

        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(')
                s.pop();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!s.empty() && s.top() != '(' && getPrecedence(ch) <= getPrecedence(s.top())) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        } else {
            postfix += ch;
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}


vector<string> generate3AddressCode(string postfix, string target) {
    vector<string> threeAddressCode;
    stack<string> s;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            string op2 = s.top();
            s.pop();
            string op1 = s.top();
            s.pop();
            string temp = "t" + to_string(threeAddressCode.size());
            threeAddressCode.push_back(temp + " = " + op1 + " " + ch + " " + op2);
            s.push(temp);
        } else {
            s.push(string(1, ch));
        }
    }

    
    threeAddressCode.push_back(target + " = " + s.top());

    return threeAddressCode;
}

int main() {
    string infix;
    ifstream inputFile("file.txt"); 

    if (!inputFile) {
        cerr << "Unable to open input file";
        return 1; 
    }

    getline(inputFile, infix); 

    inputFile.close(); 

    size_t equalsPos = infix.find('=');
    string target = infix.substr(0, equalsPos);
    string expression = infix.substr(equalsPos + 1);

    string postfix = infixToPostfix(expression);
    cout << "Postfix expression: " << postfix << endl;

    vector<string> threeAddressCode = generate3AddressCode(postfix, target);

    cout << "3-Address Code:" << endl;
    for (int i = 0; i < threeAddressCode.size(); i++) {
        cout << threeAddressCode[i] << endl;
    }

    return 0;
}