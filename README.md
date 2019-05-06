# atm_cpp
make simple atm with cpp_start_19_03_07

# functions - 19.05.06(목) 기준
# void main_run();
### main함수 속에는 이 함수만 기술 할 것이다. 즉 나머지 함수가 main_run()에 들어가있다.

# void main_menu();
### do while과 switch구문을 활용하여 atm 화면의 메인메뉴들을 보여주는 역할이다. 
### 각 case에 따라서 다른 함수들을 호출한다.

# void void create_account(atm a[]);
### 전역 변수로 선언되 초기화된 구조체 배열을 인수로 가져간다.
### 이후 고객수만큼 구조체의 멤버변수의 값을 입력받으며
### 고객수만큼 입력받은 정보를 출력한다 => 입력이 잘 됐는지 확인용
### 그 다음, void save_account_file(atm a[]);를 호출

# void save_account_file(atm a[]);
### 구조체 배열을 인수로 받는다. "atm.bin"에 저장을 하는 함수
### for문 사용, 구조체의 크기만큼 반복을 실시한다.
### 이는 파일의 크기는 곧 구조체의 크기이기 때문이다.

# void display_bank_code();
### 각 은행별 번호를 보여주기만 하는 함수이다.

# void display_balance();
### 잔액을 조회하는 함수다. atm 구조체를 지역변수로 가져와 초기화후
### "atm.bin"파일을 고객수만큼 읽어와서 구조체 배열에 저장한다.
### 3자리의 은행 코드와 나머지 계좌번호를 입력받고 strcmp()를 통해 확인한다
### 고객수만큼 for문을 돌리며 if로 대조를 한다. 
### 고객의 정보가 있으면 잔액을 포함한 고객의 정보를 화면에 출력

# void save();
### atm 구조체 배열을 초기화 후, 계좌정보가 저장된 파일을 불러온다
### 불러운 내용을 구조체 배열에 고객수만큼 저장해준다
### 은행코드와 계좌번호를 입력받은 후, strcmp()를 통해 비교한다.
### 일치하면 입금금액을 입력받고, 입금 후의 잔액과 고객 정보를 출력한다.
### 현재 구조체 배열의 저장 내역을 고객수만큼 다시 file에 저장한다.

#### 나머지 함수들은 현재 구현중
#### 구조체만을 써서 atm 의 입금, 출금, 잔액조회, 타행송금, 계좌생성 등이 완료되면
#### 클래스를 활용하는게 그 목적
