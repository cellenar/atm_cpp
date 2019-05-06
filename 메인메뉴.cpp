#include<iostream>
#include<string>
using namespace std;

typedef struct atm {
	char name[20];
	char account[20];
	char bank_name[3];
	int balance;
}atm;

atm a[2] = { 0, };

void main_run();
void main_menu();
void create_account(atm a[]);
void show_bank_code();

int main() {

	main_run();
	return 0;
}

void main_run() {
	cout << "신한은행에 오신 것을 환영합니다 \n";
	main_menu();
}
void main_menu() {
	int main_menu = 10;
	do {
		cout << "1. 계좌조회 \n";
		cout << "2. 입금 \n";
		cout << "3. 출금 \n";
		cout << "4. 송금 \n";
		cout << "5. 계좌생성 \n";
		cout << "0. 종료 \n";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "계좌조회 선택" << "\n"; break;
		case 2: cout << "입금 선택" << "\n"; break;
		case 3: cout << "출금 선택" << "\n"; break;
		case 4: cout << "송금 선택" << "\n"; break;
		case 5: cout << "계좌생성 선택" << "\n"; create_account(a); break;
		case 0: cout << "종료 선택" << "\n"; break;
		default:
			cout << "메뉴를 다시 선택하세요 \n";
			break;
		}
	} while (main_menu != 0);
	cout << "시스템종료" << "\n";
}
void create_account(atm a[]) {

	for (int i = 0; i < 2; i++) {
		show_bank_code();
		cout << "이름 : ";
		cin >> a[i].name;
		cout << "은행코드 : ";
		cin >> a[i].bank_name;
		cout << "나머지 계좌번호를 입력하세요 : ";
		cin >> a[i].account;
		cout << "잔액 : ";
		cin >> a[i].balance;
		cout << "\n";
	} cout << "\n";

	for (int i = 0; i < 2; i++) {
		cout << "이름 : " << a[i].name << "\n";
		cout << "은행코드 : " << a[i].bank_name << "\n";
		cout << "계좌번호 : " << a[i].account << "\n";
		cout << "잔액 : " << a[i].balance << "\n";
	}
}
void show_bank_code() {
	cout << "은행코드 => " << "신한 : 001  " << "국민 : 002  " << "농협 : 003";
	cout << "\n";
}