#include<iostream>
#include<fstream>
#include<string>
#define CUSTOMER 4
using namespace std;

class ATM {
private :
	typedef struct atm { //고객명 계좌 은행코드 잔액  을 멤버로 갖는 구조체
		//자료의 가장 기본적인 구조이므로 함부로 변하면 안된다.
		char name[20];
		char account[20];
		char bank_name[3];
		int balance;
	}atm;
	atm a[CUSTOMER] = { 0, };
public :
	
	void main_run();
	void main_menu();
	void create_account(atm a[]);
	void save_account_file(atm a[]);
	void save();
	void withdraw();
	void remittance();
	void get_file_to_struct(atm a[]);
	void save_struct_to_file(atm a[]);

	void display(); //은행고유의 코드를 보여주는 함수
	void display(atm *a); //계좌 생성시 입력된 고객 정보를 화면에 출력
	void display(atm a[], int i); // 송금, 입출금 등이 다 된 후의 잔액을 화면에 출력
	void display_balance();
};
void ATM::main_run() {
	cout << "신한은행에 오신 것을 환영합니다 \n";
	main_menu();
}
void ATM::main_menu() {
	int main_menu = 10;
	do {
		cout << "1. 잔액조회 \n";
		cout << "2. 입금 \n";
		cout << "3. 출금 \n";
		cout << "4. 송금 \n";
		cout << "5. 계좌생성 \n"; //기능 테스트를 위하여 계좌를 임의로 입력하게 하는 기능
		cout << "0. 종료 \n";
		cout << "메뉴입력 : ";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "잔액조회 선택" << "\n"; display_balance(); break;
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
void ATM::create_account(atm a[]) {
	for (int i = 0; i < CUSTOMER; i++) {
		display();
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
	display(a);
	save_account_file(a);
}
void ATM::save_account_file(atm a[]) {
	ofstream fileWrite;
	fileWrite.open("atm.bin");
	for (int i = 0; i < sizeof(a); i++) {
		fileWrite << a[i].name << " " << a[i].bank_name << " " << a[i].account << " " << a[i].balance << endl;
	}cout << "\n";
	fileWrite.close();
}
void ATM::save() {
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	//파일을 불러와서 구조체 배열에 저장한 상태
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display();
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
			display(a, i);
			checksum++;
			break;
		}
	}cout << "\n";
	if (checksum == 0) {
		cout << "알맞는 계좌번호가 없습니다. 다시 입력하세요 \n";
	}
	save_struct_to_file(a);
}
void ATM::withdraw() {
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	//파일을 불러와서 구조체 배열에 저장한 상태
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display();
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
				display(a, i);
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
void ATM::remittance() {
	int checksum = 0;
	int checksum_sender = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열, but 오버플로우 방지를 위해 크기를 넉넉히줌
	char check_account[20];
	display();
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
				display();
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
							display(a, i);
							break;
						}
						else { //타행송금이 아닐때, 수수료가 부과안됨
							cout << "동일한 은행에 송금을 진행하므로 수수료가 없습니다." << "\n";
							a[i].balance -= withdraw;
							a[j].balance += withdraw;
							checksum++;
							cout << "송금 완료" << "\n";
							cout << "송금 결과" << "\n";
							display(a, i);
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
void ATM::get_file_to_struct(atm a[]) {
	ifstream fileRead;
	fileRead.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileRead >> a[i].name >> a[i].bank_name >> a[i].account >> a[i].balance;
	} cout << "\n";
	fileRead.close();
}
void ATM::save_struct_to_file(atm a[]) {
	ofstream fileWrite;
	fileWrite.open("atm.bin");
	for (int i = 0; i < CUSTOMER; i++) {
		fileWrite << a[i].name << " " << a[i].bank_name << " " << a[i].account << " " << a[i].balance << endl;
	} cout << "\n";
	fileWrite.close();
}
void ATM::display_balance(){
	//잔액조회시 잔액을 보여주는 함수
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10]; //3자리의 은행코드 + null = 문자열
	char check_account[20];
	display();
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
			display(a, i);
			checksum++;
			break;
		}
	} cout << "\n";
	if (checksum == 0) {
		cout << "알맞는 계좌번호가 없습니다. 다시 입력하세요 \n";
	}
}
void ATM::display(atm *a) {
	//메소드 오버로딩 대상함수
	//계좌 생성시 입력된 고객 정보를 화면에 출력
	for (int i = 0; i < CUSTOMER; i++) {
		cout << "이름 : " << a[i].name << "\n";
		cout << "은행코드 : " << a[i].bank_name << "\n";
		cout << "계좌번호 : " << a[i].account << "\n";
		cout << "잔액 : " << a[i].balance << "\n";
		cout << "\n";
	} cout << "\n";
}
void ATM::display() {
	//메소드 오버로딩 대상함수
	//은행의 고유코드를 화면에 출력
	cout << "은행코드 => " << "신한 : 001  " << "국민 : 002  " << "농협 : 003" << "\n";
}
void ATM::display(atm a[], int i) {
	//입출금, 송금 등 이후 자신의 계좌잔액 및 정보를 화면에 출력
	string A = a[i].bank_name;
	string B = a[i].account;
	cout << "고객명 : " << a[i].name << "\n";
	cout << "은행코드 :	" << A << "\n";
	cout << "전체 계좌번호 : " << A + B << "\n";
	cout << "잔액 : " << a[i].balance << "\n";
}

int main() {
	ATM a;
	a.main_run();
	return 0;
}