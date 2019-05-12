#include<iostream>
#include<fstream>
#include<string>
#define CUSTOMER 4
using namespace std;

typedef struct atm { //고객명 계좌 은행코드 잔액  을 멤버로 갖는 구조체
	char name[20];
	char account[20];
	char bank_name[3];
	int balance;
}atm;

atm a[CUSTOMER] = { 0, };

void main_run();
//main함수 속에 이 함수만 기술한다. run()속에 main_menu()가 있고
//switch구문을 통해 각 선택에 의해 발휘되는 함수의 종류를 달리 하였다.
void main_menu();
//atm기의 메인화면을 보여준다. 선택에 따라 지정된 기능을 수행하는 함수들이
//실행되게 하였고, 0을 누르면 종료된다.
void create_account(atm a[]);
// 구조체 배열을 함수 외부에서 초기화 후, 매개변수로 받는다.
// 이후 고객의 수만큼 입력을 시작하고 구조체 배열에 저장한다.
// 모든 입력이 끝나면 입력된 내역들을 화면에 보여준다.
// 이후 파일로 입력된 내용들을 저장한다.
void display_bank_code();
// 각 은행의 고유번호를 보여준다.
void save_account_file(atm a[]);
// 구조체 배열을 함수 외부에서 초기화 후, 매개변수로 받는다.
// 입금, 예금 출금 등으로 인한 구조체 배열의 변동 내역을 파일에 저장하여 갱신한다.
void display_balance();
// 현재 잔액을 보여준다. 
// 파일을 불러와서 구조체 배열에 저장한다.
// 사용자로부터 은행코드와 나머지 계좌번호를 입력받고, 두 가지가 모두 맞아야 잔액을 보여준다.
void save();
// 저축을 한다.
// 파일을 불러와서 구조체 배열에 저장한다.
// 사용자로부터 은행코드와 나머지 계좌번호를 입력받고, 두 가지가 모두 맞아야 예금액 입력을 시작한다.
// 예금하는 금액을 구조체 배열에 더해준다.
void withdraw();
//계좌 출금
// 사용자로부터 은행코드와 나머지 계좌번호를 입력받고, 두 가지가 모두 맞아야 출금액 입력을 시작한다.
// 이 때, 출금액이 잔액보다 많으면 잔액이 부족하단 메세지와 함께 중지
// 잔액이 충분하면, 정상적으로 출금하고, 출금 결과를 출력한다.
void remittance(); // 송금 & 타행송금
// 송금 & 타행송금
// 사용자로부터 은행코드와 나머지 계좌번호를 입력받고, 두 가지가 모두 맞아야 송금액 입력을 시작한다.
// 송금액 입력 전에, 받는 이의 은행코드와 나머지 계좌번호를 입력받아야 송금액을 입력받는다
// 송수신자간 은행코드를 비교해 다르면 타행송금으로 인한 수수료 부과를 실시한다
// 송신자의 잔액 - 수수료부과된 송금액 or 동행송금시의 송금액 < 0인지 확인한다 

//subfunctions
void get_file_to_struct(atm a[]);
//파일을 불러와서 구조체 배열에 저장
void save_struct_to_file(atm a[]);
//구조체의 변동 내역을 파일에 저장
void display_result(atm a[], int i);
//출금 송금 예금 등이 끝나면 결과를 화면에 출력
void display_create_account(atm a[]);
//create account 이후 입력된 고객 정보를 화면에 출력
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
		cout << "5. 계좌생성 \n"; //기능 테스트를 위하여 계좌를 임의로 입력하게 하는 기능
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
	display_create_account(a);
	save_account_file(a);
}
void display_bank_code() {
	cout << "은행코드 => " << "신한 : 001  " << "국민 : 002  " << "농협 : 003" << "\n";
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
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
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
			display_result(a, i);
			checksum++;
			break;
		}
	} cout << "\n";
	if (checksum == 0) {
		cout << "알맞는 계좌번호가 없습니다. 다시 입력하세요 \n";
	}
}

void save() {
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	//파일을 불러와서 구조체 배열에 저장한 상태
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
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
			display_result(a, i);
			checksum++;
			break;
		}
	}cout << "\n";
	if (checksum == 0) {
		cout << "알맞는 계좌번호가 없습니다. 다시 입력하세요 \n";
	}
	save_struct_to_file(a);
}
void withdraw() { //출금
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	//파일을 불러와서 구조체 배열에 저장한 상태
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
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
				checksum++;
				return;
			}
			else {
				a[i].balance -= withdraw;
				cout << "출금 완료" << "\n";
				cout << "출금 결과" << "\n";
				display_result(a, i);
				checksum++;
				break;
			}
		}
	}cout << "\n";
	if (checksum == 0) {
		cout << "알맞는 계좌번호가 없습니다. 다시 입력하세요 \n";
	}
	//출금 내역을 저장한다. 
	save_struct_to_file(a);
}

void remittance() { //송금 & 타행송금
	int checksum = 0;
	int checksum_sender = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열, but 오버플로우 방지를 위해 크기를 넉넉히줌
	char check_account[20];
	display_bank_code();
	cout << "본인의 은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호를 입력하세요 : ";
	cin >> check_account;
	for (int i = 0; i < CUSTOMER; i++) {
		if (strcmp(check_bankcode, a[i].bank_name) == 0 &&
			strcmp(check_account, a[i].account) == 0) {
			checksum_sender++;
			int withdraw = 0;
			cout << "송금 금액 : ";
			cin >> withdraw;
			if (a[i].balance - withdraw < 0) {
				cout << "잔액보다 송금금액이 많아서 송금할 수 없습니다. " << "\n";
				checksum++;
				return;
			}
			else {
				checksum++;
				//잔액이 송금금액 이상일 때만 실행
				//수신자의 뱅크코드와 계좌번호를 입력받는다.
				char check_bankcode_other[4]; //3자리의 은행코드 + null = 문자열
				char check_account_other[20];
				display_bank_code();
				cout << "수신자의 은행 코드 세자리를 입력하세요 : ";
				cin >> check_bankcode_other;
				cout << "수신자의 나머지 계좌번호를 입력하세요 : ";
				cin >> check_account_other;
				for (int j = 0; j < CUSTOMER; j++) {
					if (strcmp(check_bankcode_other, a[j].bank_name) == 0 &&
						strcmp(check_account_other, a[j].account) == 0) {
						if (strcmp(check_bankcode, check_bankcode_other) != 0) {
							cout << "타행송금에 따른 수수료 500원이 부과됩니다." << "\n";
							int send_money = withdraw + 500;
							cout << "수수료가 적용된 송금금액 : " << send_money << "\n";
							if (a[i].balance - send_money < 0) {
								cout << "잔액이 송금수수료와 송금금액을 더한 것보다 작아서 송금에 실패했습니다" << "\n";
								return;
							}
							a[i].balance -= send_money;
							a[j].balance += withdraw;
							checksum++;
							cout << "송금 완료" << "\n";
							cout << "송금 결과" << "\n";
							display_result(a, i);
							break;
						}
						else { //타행송금이 아닐때, 수수료가 부과안됨
							cout << "동일한 은행에 송금을 진행하므로 수수료가 없습니다." << "\n";
							a[i].balance -= withdraw;
							a[j].balance += withdraw;
							checksum++;
							cout << "송금 완료" << "\n";
							cout << "송금 결과" << "\n";
							display_result(a, i);
							break;
						}
					}
					else {
						checksum = 0;
					}
				}
			}
		}
	}cout << "\n";
	if (checksum_sender == 0) {
		cout << "일치하는 송신자가 없습니다. 다시 입력하세요 \n";
		return;
	}
	if (checksum == 0) {
		cout << "일치하는 수신자가 없습니다. 다시 입력하세요 \n";
		return;
	}
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

void display_result(atm a[], int i) {
	string A = a[i].bank_name;
	string B = a[i].account;
	cout << "고객명 : " << a[i].name << "\n";
	cout << "은행코드 :	" << A << "\n";
	cout << "전체 계좌번호 : " << A + B << "\n";
	cout << "잔액 : " << a[i].balance << "\n";
}

void display_create_account(atm a[]) {
	for (int i = 0; i < CUSTOMER; i++) {
		cout << "이름 : " << a[i].name << "\n";
		cout << "은행코드 : " << a[i].bank_name << "\n";
		cout << "계좌번호 : " << a[i].account << "\n";
		cout << "잔액 : " << a[i].balance << "\n";
	} cout << "\n";
}