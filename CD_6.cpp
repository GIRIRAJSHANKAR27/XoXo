/*
Write a C/C++ code to check weather a string belongs to a given grammar or not.
Grammar:
S-> aS
s-> Sb
s->ab

Input stirng :aab 
Output: Accepted or not
*/

#include <bits/stdc++.h>
using namespace std;

bool checkGrammar(string str, int index) {
    if (index == str.length()) {
        return true;
    }
    if (str[index] == 'a') {
        return checkGrammar(str, index + 1);
    }
    if (str[index] == 'b') {
        for (int i = index; i < str.length(); ++i) {
            if (str[i] != 'b') {
                return false;
            }
        }
        return true;
    }
    return false; 
}

int main() {
    string str, str2;
    cout<< "The String aab is ";
    str2 = "aab";

    if (str2.length() >= 2 && str2[0] == 'a' && str2[str2.length() - 1] == 'b' && checkGrammar(str2, 0)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }

    cout << "Enter your string: ";
    getline(cin, str);

    if (str.length() >= 2 && str[0] == 'a' && str[str.length() - 1] == 'b' && checkGrammar(str, 0)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Not Accepted" << endl;
    }

    return 0;
}
