# ParkingLotManagement

주차장과 관련하여 수동 및 자동으로 차량의 입차 및 출차를 관리하는 프로그램

## 실행 방법

#### 깃 클론
<pre>
<code>
$ git clone https://github.com/sjoonb/ParkingLotManagement.git
</code>
</pre>

#### make
<pre>
<code>
$ make
</code>
</pre>

#### 실행
<pre>
<code>
$ ./ParkingLotManagement
</code>
</pre>

## 기능 설명
### 첫 화면
<img width="551" alt="스크린샷 2020-12-13 오후 9 42 12" src="https://user-images.githubusercontent.com/70687318/102012180-3fcc4700-3d8c-11eb-913e-4535d0444c03.png">

해당 주차장의 최대 수용 가능한 차량 수를 정수로 입력

### 6가지 기능
<img width="515" alt="스크린샷 2020-12-13 오후 9 45 10" src="https://user-images.githubusercontent.com/70687318/102012223-7ace7a80-3d8c-11eb-83ef-79299570c2a1.png">

[1] : 입차 - 차량 번호 직접 입력 (00가0000 식으로 입력), 차량 사이즈 입력 (소형 / 중형 / 대형)     
[2] : 출차 - 차량 번호 직접 입력 (00가0000 식으로 입력), 요금표에 따라 요금 책정하여 금일 수입에 추가    
[3] : 현황 - 주차장크기, 주차 차량 수, 남은 공간 출력, 현재 주차된 모든 차량 출력    
[4] : 과거 내역 - 과거 내역 창으로 이동, 출력, 이전 날짜, 다음 날짜, 메인으로 선택 가능    
[5] : 자동 모드 - 입/출 이 자동으로 실행되는 모드, 실행 중 엔터키 입력시 종료, 자세한 설명은 아래 상세 설명으로    
[6] : 저장 및 종료 - 모든 데이터 저장 후 종료    
[7] : 초기화 - 모든 데이터 초기화 후 프로그램 재실행   

## 상세 설명
### 요금표 수정
#### 현재 사용중인 요금표
![rate](https://user-images.githubusercontent.com/70687318/102012326-15c75480-3d8d-11eb-9180-0b61d4a8235d.png)    

<img width="501" alt="스크린샷 2020-12-13 오후 10 26 28" src="https://user-images.githubusercontent.com/70687318/102013259-4493f980-3d92-11eb-8391-bb2cad326749.png">

rate.txt 파일을 배열에 맞게 수정하여 각자의 주차장의 요금표에 맞게 수정하면 된다.

### 자동 모드
#### 설명
자동 모드는 랜덤으로 차량 번호와 사이즈를 생성하고, 입차 및 출차를 수행하는 모드이다.      
실제 프로그램 사용상에 카메라를 통 입차 및 출차하는 차량 번호의 데이터 입력이 이뤄지는 부분을 우선 랜덤으로 구현해 놓은 것이다.   
후의 데이터 입력이 카메라를 통한 차량번호 입력으로 구현될 것을 고려하여 설계였다.

#### 코드 상세
<pre>
<code>
car_t* auto_mode(car_t* main_list_head, int* pnum_of_car, int space, int* pmoney, int tmp_sm[], int tmp_l[]) {

	srand(time(NULL));

	int mode;
	int min, max, count;
	int rand_time;

	min = 1; // * MINUTES;
	max = 3; // * MINUTES;

	count = 0;
	
	rand_time = rand() % (max - min) +  min; // * MINUTES;
	
	while(!kbhit())
	{

		if(count == rand_time){

			mode = rand() % 2 + 1;

			switch(mode) {
					case ENTER:
						main_list_head = random_enter_info(main_list_head, pnum_of_car, space);
						rand_time = rand() % (max - min) + min; // * MINUTES;
						count = 0;
						break;
					case EXIT:
						if(*pnum_of_car > 0){
							main_list_head = random_exit_info(main_list_head, pnum_of_car, pmoney, tmp_sm, tmp_l);
							rand_time = rand() % (max - min) + min; // * MINUTES;
							count = 0;
						} else {
							printf("차량이 존재하지 않습니다.\n");
							rand_time = rand() % (max - min) + min; // * MINUTES;
							count = 0;
						}
						break;
			}

		}

		count += 1;

		fflush(stdout);
		usleep(1 * SECONDS);
		
	}
		
	//printf("%c", c);

	printf("\n");

	return main_list_head;
	
}
</code>
</pre>
현재는 자동 모드의 출력을 바로 확인하기 위해 MINUTES 기호상수를 주석처리 해 놓았다. 초단위로 출력이 이루어지는데, 이를 분으로 바꾸려면 해당 부분의 주석을 해제하면 된다.
변수 min은 최소 (분), max는 최대 (분) 을 나타내는 변수이다. (현재 코드에서는 초단위로 인식된다.)
즉, 1 ~ 3 (분) 의 주기로 차량 한대의 입차 혹은 출차가 이루어지는 것이다.




