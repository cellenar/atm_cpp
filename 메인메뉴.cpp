#include<iostream>
#include<fstream>
#include<string>
#define CUSTOMER 2
using namespace std;

typedef struct atm {
	char name[20];
	char account[20];
	char bank_name[3];
	int balance;
}atm;

atm a[CUSTOMER] = { 0, };

void main_run();
void main_menu();
void create_account(atm a[]);
void display_bank_code();
void save_account_file(atm a[]);
void display_balance();
void save();
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
		cout << "4. 타행송금 \n";
		cout << "5. 계좌생성 \n";
		cout << "0. 종료 \n";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "계좌조회 선택" << "\n"; display_balance(); break;
		case 2: cout << "입금 선택" << "\n"; save(); break;
		case 3: cout << "출금 선택" << "\n"; break;
		case 4: cout << "타행송금 선택" << "\n"; break;
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

	for (int i = 0; i < CUSTOMER; i++) {
		display_bank_code();
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

	for (int i = 0; i < CUSTOMER; i++) {
		cout << "이름 : " << a[i].name << "\n";
		cout << "은행코드 : " << a[i].bank_name << "\n";
		cout << "계좌번호 : " << a[i].account << "\n";
		cout << "잔액 : " << a[i].balance << "\n";
	} cout << "\n";
	save_account_file(a);
}
void display_bank_code() {
	cout << "은행코드 => " << "신한 : 001  " << "국민 : 002  " << "농협 : 003";
	cout << "\n";
}

void save_account_file(atm a[]) {
	ofstream fileWrite;
	fileWrite.open("atm.bin");
	for (int i = 0; i < sizeof(a); i++) {
		fileWrite << a[i].name << " " << a[i].bank_name << " " << a[i].account << " " << a[i].balance << endl;
	}cout << "\n";
	fileWrite.close();
}

void display_balance() {
	atm a[CUSTOMER] = { 0, };
	ifstream fileRead;
	fileRead.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileRead >> a[i].name >> a[i].bank_name >> a[i].account >> a[i].balance;
	} cout << "\n";
	fileRead.close();

	char check_bankcode[4]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display_bank_code();
	cout << "은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호를 입력하세요 : ";
	cin >> check_account;

	//비교구문을 작성해보자
	/*
	strcmp(string1, string2) 두 문자열이 같다면, 0이라는 값이 나온다.
	*/
	for (int i = 0; i < CUSTOMER; i++) {
		if (strcmp(check_bankcode, a[i].bank_name) == 0 &&
			strcmp(check_account, a[i].account) == 0) {
			string A = a[i].bank_name;
			string B = a[i].account;
			cout << "고객명 : " << a[i].name << "\n";
			cout << "은행코드 :	" << A << "\n";
			cout << "전체 계좌번호 : " << A + B << "\n";
			cout << "잔액 : " << a[i].balance << "\n";
			break;
		}
	}
}

void save() {
	atm a[CUSTOMER] = { 0, };
	ifstream fileRead;
	fileRead.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileRead >> a[i].name >> a[i].bank_name >> a[i].account >> a[i].balance;
	} cout << "\n";
	fileRead.close();
	//파일을 불러와서 구조체 배열에 저장한 상태
	char check_bankcode[4]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display_bank_code();
	cout << "은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호를 입력하세요 : ";
	cin >> check_account;
	for (int i = 0; i < CUSTOMER; i++) {
		if (strcmp(check_bankcode, a[i].bank_name) == 0 &&
			strcmp(check_account, a[i].account) == 0) {
			int save_money = 0;
			cout << "입금 금액 : ";
			cin >> save_money;
			a[i].balance += save_money;
			cout << "입금 완료" << "\n";
			string A = a[i].bank_name;
			string B = a[i].account;
			cout << "고객명 : " << a[i].name << "\n";
			cout << "은행코드 :	" << A << "\n";
			cout << "전체 계좌번호 : " << A + B << "\n";
			cout << "잔액 : " << a[i].balance << "\n";
			break;
		}
	}cout << "\n";

	ofstream fileWrite;
	fileWrite.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileWrite << a[i].name << " " << a[i].bank_name << " " << a[i].account << " " << a[i].balance << endl;
	} cout << "\n";
	fileWrite.close();
}