#include<iostream>
#include<fstream>
#include<string>
#define CUSTOMER 4
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
void withdraw(); //계좌 출금
void remittance(); // 송금 & 타행송금
void get_file_to_struct(atm a[]); //파일을 불러와서 구조체 배열에 저장
void save_struct_to_file(atm a[]); //구조체의 변동 내역을 파일에 저장
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
		cout << "메뉴입력 : ";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "계좌조회 선택" << "\n"; display_balance(); break;
		case 2: cout << "입금 선택" << "\n"; save(); break;
		case 3: cout << "출금 선택" << "\n"; withdraw(); break;
		case 4: cout << "송금 선택" << "\n"; remittance();  break;
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
	// 입력 결과 확인용
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
	get_file_to_struct(a);
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
	get_file_to_struct(a);
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
			cout << "입금 결과" << "\n";
			string A = a[i].bank_name;
			string B = a[i].account;
			cout << "고객명 : " << a[i].name << "\n";
			cout << "은행코드 :	" << A << "\n";
			cout << "전체 계좌번호 : " << A + B << "\n";
			cout << "잔액 : " << a[i].balance << "\n";
			break;
		}
	}cout << "\n";
	save_struct_to_file(a);
}
void withdraw() {
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
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
			int withdraw = 0;
			cout << "출금 금액 : ";
			cin >> withdraw;
			if (a[i].balance - withdraw < 0) {
				cout << "잔액보다 출금금액이 많아서 출금할 수 없습니다. " << "\n";
				return;
			}
			else {
				a[i].balance -= withdraw;
				cout << "출금 완료" << "\n";
				cout << "출금 결과" << "\n";
				string A = a[i].bank_name;
				string B = a[i].account;
				cout << "고객명 : " << a[i].name << "\n";
				cout << "은행코드 :	" << A << "\n";
				cout << "전체 계좌번호 : " << A + B << "\n";
				cout << "잔액 : " << a[i].balance << "\n";
				break;
			}
		}
	}cout << "\n";
	//출금 내역을 저장한다. 
	save_struct_to_file(a);
}

void remittance() { //송금 & 타행송금
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[4]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display_bank_code();
	cout << "본인의 은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호를 입력하세요 : ";
	cin >> check_account;
	for (int i = 0; i < CUSTOMER; i++) {
		if (strcmp(check_bankcode, a[i].bank_name) == 0 &&
			strcmp(check_account, a[i].account) == 0) {
			int withdraw = 0;
			cout << "송금 금액 : ";
			cin >> withdraw;
			if (a[i].balance - withdraw < 0) {
				cout << "잔액보다 송금금액이 많아서 송금할 수 없습니다. " << "\n";
				return;
			}
			else {
				//잔액이 송금금액 이상일 때만 실행
				//타인의 뱅크코드와 계좌번호를 입력받는다.
				char check_bankcode_other[4]; //3자리의 은행코드 + null = 문자열
				char check_account_other[20];
				display_bank_code();
				cout << "송금을 원하는 계좌의 은행 코드 세자리를 입력하세요 : ";
				cin >> check_bankcode_other;
				cout << "나머지 계좌번호를 입력하세요 : ";
				cin >> check_account_other;
				for (int j = 0; j < CUSTOMER; j++) {
					if (strcmp(check_bankcode_other, a[j].bank_name) == 0 &&
						strcmp(check_account_other, a[j].account) == 0) {
						if (strcmp(check_bankcode, check_bankcode_other) != 0) {
							cout << "타행송금에 따른 수수료 500원이 부과됩니다." << "\n";
							int send_money = withdraw + 500;
							cout << "수수료가 적용된 송금금액 : " << send_money << "\n";
							a[i].balance -= send_money;
							a[j].balance += withdraw;
							break;
						}
						else { //타행송금이 아닐때, 수수료가 부과안됨
							cout << "동일한 은행에 송금을 진행하므로 수수료가 없습니다." << "\n";
							a[i].balance -= withdraw;
							a[j].balance += withdraw;
							break;
						}
					}
				}
				//a[i].balance -= withdraw;
				//결과 출력 구문
				cout << "송금 완료" << "\n";
				cout << "송금 결과" << "\n";
				string A = a[i].bank_name;
				string B = a[i].account;
				cout << "고객명 : " << a[i].name << "\n";
				cout << "은행코드 :	" << A << "\n";
				cout << "전체 계좌번호 : " << A + B << "\n";
				cout << "잔액 : " << a[i].balance << "\n";
				break;
			}
		}
	}cout << "\n";
	save_struct_to_file(a);
}

void get_file_to_struct(atm a[]) {
	ifstream fileRead;
	fileRead.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileRead >> a[i].name >> a[i].bank_name >> a[i].account >> a[i].balance;
	} cout << "\n";
	fileRead.close();
}

void save_struct_to_file(atm a[]) {
	ofstream fileWrite;
	fileWrite.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileWrite << a[i].name << " " << a[i].bank_name << " " << a[i].account << " " << a[i].balance << endl;
	} cout << "\n";
	fileWrite.close();
}