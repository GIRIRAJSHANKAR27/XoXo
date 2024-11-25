#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool check_string(unordered_map<char, vector<string>>& grammar, int pos, string str, char LHS){
    for(auto i:grammar[LHS]){
        for(int j = 0; j < i.size(); j++){
            if(i[j] >= 'A' && i[j] <= 'Z'){
                if(check_string(grammar, pos, str, i[j])) pos++;
                else break;
            }
            else if(i[j] == str[pos]){
                pos++;
            }
            else break;

            if(j == i.size() - 1) return true;
        }

        if(pos == str.size()) return true;
        pos = 0;
    } 

    return false;
} 

int main(){
    unordered_map<char, vector<string>> grammar;
    int num;
    char beg_LHS;

    cout << "enter number of grammars\n";
    cin >> num;

    for(int i = 0; i < num; i++){
        char LHS;int n;
        cout << "enter LHS for grammar " << (i+1) << endl;
        cin >> LHS;
        if(i == 0) beg_LHS = LHS;
        cout << "enter number of productions for " << LHS << endl;
        cin >> n;

        for(int j = 0; j < n; j++){
            string str;
            cin >> str;
            grammar[LHS].push_back(str);
        }
    }

    string str;
    cout << "enter string to check\n";
    cin >> str;

    bool ans = check_string(grammar, 0, str, beg_LHS);
    str = (ans)? "valid String":"Invalid String";
    cout << str << endl;
    return 0;
}
