#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int menuNum;
	do {
		cout << "\t Menu Select" << endl;
		cout << "\t 1. 입금" << endl;
		cout << "\t 2. 출금" << endl;
		cout << "\t 3. 계좌이체" << endl;
		cout << "\t 0. 종료" << endl;
		cout << "\t 메뉴입력 : ";
		cin >> menuNum;
		switch (menuNum)
		{
		case (1):
			cout << "입금에 진입" << endl; break;
		case (2):
			cout << "출금에 진입" << endl; break;
		case (3):
			cout << "계좌이체에 진입" << endl; break;
		case (0):
			cout << "종료를 선택. 시스템을 종료합니다" << endl; break;
		default:
			cout << "잘못된 선택입니다. 다시 선택하세요" << endl; break;
			break;
		}
	} while (menuNum != 0);
	return 0;
}