#include<iostream>
using namespace std;

void main_run();

int main() {

	main_run();
	return 0;
}

void main_run() {
	cout << "신한은행에 오신 것을 환영합니다 \n";
	int main_menu = 10;
	do {
		cout << "1. 계좌조회 \n";
		cout << "2. 입금 \n";
		cout << "3. 출금 \n";
		cout << "4. 송금 \n";
		cout << "0. 종료 \n";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "계좌조회 선택" << "\n"; break;
		case 2: cout << "입금 선택" << "\n"; break;
		case 3: cout << "출금 선택" << "\n"; break;
		case 4: cout << "송금 선택" << "\n"; break;
		case 0: cout << "종료 선택" << "\n"; break;
		default:
			cout << "메뉴를 다시 선택하세요 \n";
			break;
		}
	} while (main_menu != 0);
	cout << "시스템종료" << "\n";
}