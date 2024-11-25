#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string expr;
    cout << "Enter the expression: ";
    cin >> expr;
    vector<int> nums;
    string operatorSign = "";
    string tempNum = "";
    for (char ch : expr)
    {
        if (isdigit(ch))
        {
            tempNum += ch;
        }
        else
        {
            if (!tempNum.empty())
            {
                nums.push_back(stoi(tempNum));
                tempNum = "";
            }
            if (ch == '>' || ch == '<' || ch == '=' || ch == '!')
            {
                operatorSign += ch;
            }
        }
    }
    if (!tempNum.empty())
    {
        nums.push_back(stoi(tempNum));
    }
    if (operatorSign == ">" && nums[0] > nums[1])
    {
        cout << "Condition is True" << endl;
    }
    else if (operatorSign == "<" && nums[0] < nums[1])
    {
        cout << "Condition is True" << endl;
    }
    else if (operatorSign == "==" && nums[0] == nums[1])
    {
        cout << "Condition is True" << endl;
    }
    else if (operatorSign == "!=" && nums[0] != nums[1])
    {
        cout << "Condition is True" << endl;
    }
    else
    {
        cout << "Condition is False or Error in Expression" << endl;
    }
    return 0;
}