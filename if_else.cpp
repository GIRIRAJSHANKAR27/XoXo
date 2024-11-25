#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int string_to_int(string str){
	int ans = 0;
	for(int i=0;i<str.size();i++){
		ans *= 10;
		ans += str[i] - '0';
	}
	return ans;
}

void check_condition(string str){
	if(str.size() < 2){
		cout << "Invalid input" << endl;
		return;
	}
	string is_if = "";
	is_if += str[0];
	is_if += str[1];
	is_if += str[2];
	if(is_if != "if("){
		cout << "Invalid input" << endl;
		return;
	}
	is_if = "";
	for(int i=3;i<str.size();i++){
		if(str[i] == ')')
			break;
		is_if += str[i];
	}
	int l = 3;
	int condition = -1;
	string input1 = "";
	for(int i = 3;i < str.size()-1;i++){
		if(str[i] == '>'){
			condition = 1;
			l++;
			break;
		}
		else if(str[i] == '<'){
			condition = 2;
			l++;
			break;
		}
		else if(str[i] == '=' && str[i+1] == '='){
			condition = 3;
			l += 2;
			i += 2;
			break;
		}
		else{
			l++;
			input1 += str[i];
		}
	}
	if(condition == -1){ if(input1 != "0"){
		cout << "condition valid" << endl;
		return ;
		}
		else{
			cout << "condition invalid" << endl;
			return;
	}}
	string input2 = "";
	for(int i =l;i<str.size()-1;i++){
		input2 += str[i];
	}
	if(condition == 3){  if (input1 == input2){
		cout << "condition valid" << endl;
		return;
		}
		else{
			cout << "condition invalid" << endl;
			return;
	}}
	if(condition == 1){
		if (string_to_int(input1) > string_to_int(input2)) {
			cout << "condition valid" << endl;
			return;
		}else{
			cout << "condition invalid" << endl;
			return;
		}
	}

	if(condition == 2){
		if (string_to_int(input1) < string_to_int(input2)) {
			cout << "condition valid" << endl;
			return;
		}else{
			cout << "condition invalid" << endl;
			return;
		}
	}
	cout << "condition invalid" << endl;
	return;
}

int main(int argc, char** argv){
	string str;
	if(argc > 1)
		str = argv[1];
	else
		str = "if(5 < 7)";
	cout << "Given expression : " << str << endl;
	check_condition(str);
	return 0;
}
