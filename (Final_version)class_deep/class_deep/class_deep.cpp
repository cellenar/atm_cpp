#include<iostream>
#include<fstream> //파일시스템을 사용하므로 fstream 추가
#include<string> //전체계좌번호를 출력해주기 위해 string 추가

#define CUSTOMER 4 //구조체배열에 저장할 고객의 수

using namespace std;
	
class Basic_ATM
{
protected:
	typedef struct atm { 
		char name[20]; //고객명
		char account[20]; //계좌번호
		char bank_name[3]; //은행번호 3자리 
		int balance;//잔액
	}atm;
public:
//오버라이딩 후, 메뉴를 화면에 출력
virtual void main_menu() = 0; 
//오버라이딩 후, 은행별 고유 번호를 화면에 출력
virtual void display_bank() = 0; 
};


class ATM : public Basic_ATM
{
protected:
//파일 입출력을 위해 0으로 초기화
atm bank[CUSTOMER] = { 0, };
int new_A;

public:
//생성자 함수, friend함수, 오버라이딩함수
ATM(); 
ATM(int some);
//생성자가 0이면 사용불가 메세지 출력
friend int is_okay(ATM *one);
//오버라이딩됨, 은행별 고유번호 출력
void display_bank(); 
//오버라이딩됨, 메뉴를 출력 후 선택에 따른 기능실행
void main_menu(); 

//주요기능
void display(); //잔액조회
void save(); //입금
void withdraw(); //출금
void remittance(); //송금
//계좌생성. 테스트용기능
void create_account(atm bank[]); 

//보조기능
//파일을 구조체배열로 불러와 저장
void get_file_to_struct(atm bank[]); 
//입출금 등으로 인한 변동내역을 파일로 저장
void save_struct_to_file(atm bank[]); 
//입출금 등 이후 거래 결과를 화면에 출력
void display(atm bank[], int i) const; 
	
};

ATM::ATM() 
{	
	new_A = 0;
}
ATM::ATM(int some=1) {
	new_A = some;
}
int is_okay(ATM *one) {
	return (one->new_A == 1);
}

//주요함수들
void ATM::main_menu()
{
	int main_menu = 10;

	do {
		cout << "========메뉴를 입력하세요========" << "\n";
		cout << "1. 잔액조회 \t" << "2. 입금 \n";
		cout << "3. 출금 \t" << "4. 송금 \n";
		cout << "5. 계좌생성 \t" << "0. 종료 \n";
		cout << "번호입력 : ";
		cin >> main_menu;
		switch (main_menu) {
		case 1: cout << "잔액조회 선택" << "\n"; display(); break;
		case 2: cout << "입금 선택" << "\n"; save(); break;
		case 3: cout << "출금 선택" << "\n"; withdraw(); break;
		case 4: cout << "송금 선택" << "\n"; remittance();  break;
		case 5: cout << "계좌생성 선택" << "\n"; create_account(bank); break;
		case 0: cout << "종료 선택" << "\n"; break;
		default:
			cout << "메뉴를 다시 선택하세요 \n";
			break;
		}
	} while (main_menu != 0);
	cout << "시스템종료" << "\n";
}
void ATM::display()
{
	//잔액조회시 잔액을 보여주는 함수
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10];
	char check_account[20];
	display_bank();
	cout << "은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호 6자리를 입력하세요 : ";
	cin >> check_account;

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
void ATM::save()
{
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10];
	char check_account[20];
	display_bank();
	cout << "은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호 6자리를 입력하세요 : ";
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
void ATM::withdraw()
{
	int checksum = 0;
	atm a[CUSTOMER] = { 0, };
	get_file_to_struct(a);
	char check_bankcode[10];
	char check_account[20];
	display_bank();
	cout << "은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호 6자리를 입력하세요 : ";
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
void ATM::remittance() 
{
	int checksum = 0;
	int checksum_sender = 0;
	atm bank[CUSTOMER] = { 0, };
	get_file_to_struct(bank);
	char check_bankcode[10];
	char check_account[20];
	display_bank();
	cout << "본인의 은행 코드 세자리를 입력하세요 : ";
	cin >> check_bankcode;
	cout << "나머지 계좌번호 6자리를 입력하세요 : ";
	cin >> check_account;
	for (int i = 0; i < CUSTOMER; i++) {
		if (strcmp(check_bankcode, bank[i].bank_name) == 0 &&
			strcmp(check_account, bank[i].account) == 0) {
			checksum_sender++;
			int withdraw = 0;
			cout << "\n";
			cout << "송금 금액 : ";
			cin >> withdraw;
			if (bank[i].balance - withdraw < 0) {
				cout << "잔액보다 송금금액이 많아서 송금할 수 없습니다. " << "\n";
				checksum++;
				return;
			}
			else {
				checksum++;
				char check_bankcode_other[4]; 
				char check_account_other[20];
				display_bank();
				cout << "수신자의 은행 코드 세자리를 입력하세요 : ";
				cin >> check_bankcode_other;
				cout << "수신자의 나머지 계좌번호 6자리를 입력하세요 : ";
				cin >> check_account_other;
				for (int j = 0; j < CUSTOMER; j++) {
					if (strcmp(check_bankcode_other, bank[j].bank_name) == 0 &&
						strcmp(check_account_other, bank[j].account) == 0) {
						if (strcmp(check_bankcode, check_bankcode_other) != 0) {
							cout << "타행송금에 따른 수수료 500원이 부과됩니다." << "\n";
							int send_money = withdraw + 500;
							cout << "수수료가 적용된 송금금액 : " << send_money << "\n";
							if (bank[i].balance - send_money < 0) {
								cout << "잔액이 송금수수료와 송금금액을 더한 것보다 작아서 송금에 실패했습니다" << "\n";
								cout << "\n";
								return;
							}
							bank[i].balance -= send_money;
							bank[j].balance += withdraw;
							checksum++;
							cout << "\n";
							cout << "송금 완료" << "\n";
							cout << "송금 결과" << "\n";
							display(bank, i);
							cout << "\n";
							break;
						}
						else { //타행송금이 아닐때, 수수료가 부과안됨
							cout << "\n";
							cout << "동일한 은행에 송금을 진행하므로 수수료가 없습니다." << "\n";
							bank[i].balance -= withdraw;
							bank[j].balance += withdraw;
							checksum++;
							cout << "송금 완료" << "\n";
							cout << "송금 결과" << "\n";
							cout << "\n";
							display(bank, i); //거래완료후 결과출력
							cout << "\n";
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
	save_struct_to_file(bank);
}
void ATM::create_account(atm bank[])
{
	for (int i = 0; i < CUSTOMER; i++) {
		display_bank();
		cout << "이름 : ";
		cin >> bank[i].name;
		cout << "은행코드 : ";
		cin >> bank[i].bank_name;
		cout << "나머지 계좌번호 6자리를 입력하세요 : ";
		cin >> bank[i].account;
		cout << "잔액 : ";
		cin >> bank[i].balance;
		cout << "\n";
	} cout << "\n";
	save_struct_to_file(bank);
}
//서브함수들

void ATM::display_bank()
{
	cout << "은행코드 => " << "신한 : 001  " 
		<< "국민 : 002  " << "농협 : 003" << "\n";
}

void ATM::get_file_to_struct(atm bank[])
{	
	ifstream fileRead;
	fileRead.open("atm.dat");
	for (int i = 0; i < CUSTOMER; i++) {
		fileRead >> bank[i].name >> bank[i].bank_name >> bank[i].account >> bank[i].balance;
	} cout << "\n";
	fileRead.close();
}

void ATM::save_struct_to_file(atm bank[])
{
	ofstream fileWrite;
	fileWrite.open("atm.dat");
	for (int i = 0; i < CUSTOMER; i++) {
		fileWrite << bank[i].name << " " << bank[i].bank_name << " " 
			<< bank[i].account << " " << bank[i].balance << endl;
	} cout << "\n";
	fileWrite.close();
}

void ATM::display(atm bank[], int i) const
{
	string A = bank[i].bank_name;
	string B = bank[i].account;
	cout << "\n";
	cout << "고객명 : " << bank[i].name << "\n";
	cout << "은행코드 :	" << A << "\n";
	cout << "전체 계좌번호 : " << A + B << "\n";
	cout << "잔액 : " << bank[i].balance << "\n";
	cout << "\n";
}


int main() {
	//업 캐스팅 사용
	Basic_ATM * basicp = new ATM(1);
	//다운 캐스팅 사용
	ATM *p = (ATM *)basicp;
	int checker = is_okay(p);
	if (checker == 1) {
		p->main_menu();
	}
	else {
		cout << "시스템이 점검중이므로 사용이 불가합니다 \n";
		return 0;
	}
	return 0;
}


