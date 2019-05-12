#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void account_search();
int main() {
	
	account_search();
	return 0;
}

void account_search() {
	string ask;
	cout << "계좌번호를 입력하세요 : ";
	cin >> ask;
	string in_line;
	ifstream in("account.txt");
	while (getline(in, in_line)) {
		if (ask == in_line) {
			cout << in_line << endl;
		}
	} 
	cout << "계좌번호가 없습니다. 올바른 번호를 입력하세요" << "\n";
	in.close();
}