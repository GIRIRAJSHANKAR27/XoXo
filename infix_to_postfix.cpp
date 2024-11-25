#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char ch) {
    switch (ch) {
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

string converter(string infix){
	string postfix;
	stack<char> symbols;
	for(int i=0;i<infix.size();i++){
		if(!(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')' || infix[i] == ' '))
			postfix += infix[i];
		else if(infix[i] == '(')
			symbols.push(infix[i]);
		else if(infix[i] == ')'){
			while(symbols.top() != '('){
				postfix += symbols.top();
				symbols.pop();
			}
			symbols.pop();
		}
		else if(infix[i] == ' ')
			continue;
		else if(!symbols.empty() && precedence(infix[i]) <= precedence(symbols.top())){
			while(!symbols.empty() && precedence(infix[i]) <= precedence(symbols.top())){
				postfix += symbols.top();
				symbols.pop();
			}
			symbols.push(infix[i]);
		}
		else 
			symbols.push(infix[i]);
	}
	while(!symbols.empty()){
		postfix += symbols.top();
		symbols.pop();
	}
	return postfix;
}

int main(){
	string infix;
	cout << "enter infix expression" << endl;
	getline(cin, infix);
	string postfix = converter(infix);
	cout << "corresponding postfix expression is :\n" << postfix << endl;
	return 0;
}
