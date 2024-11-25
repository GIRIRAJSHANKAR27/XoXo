#include <iostream>
#include <regex>
#include <string>
using namespace std;

int determineType(const string& value) {
    regex integerPattern("^[+-]?[0-9]+$");
    regex floatPattern("^[+-]?[0-9]*\\.[0-9]+$");
    regex characterPattern("^'[^']'$");
    regex stringPattern("^\"[^\"]*\"$");
    
    if (regex_match(value, integerPattern)) {
        return 1;
    } else if (regex_match(value, floatPattern)) {
        return 2;
    } else if (regex_match(value, characterPattern)) {
        return 3;
    } else if (regex_match(value, stringPattern)) {
        return 4;
    }
    return 0;
}

void getInput(string& varName, string& varValue, int& userType) {
    cout << "Variable Name: ";
    cin >> varName;
    cout << "Enter Value: ";
    cin >> varValue;
    cout << "Type Choice\n1: Integer\n2: Float\n3: Char\n4: String\n0: None\n";
    cin >> userType;
}

void displayResult(bool isValid) {
    if (isValid)
        cout << "Data-type is valid.\n";
    else
        cout << "Data-type is invalid.\n";
}

int main() {
    string varName, varValue;
    int userType;
    
    getInput(varName, varValue, userType);
    
    bool isValidType = (determineType(varValue) == userType);
    
    displayResult(isValidType);
    
    return 0;
}
