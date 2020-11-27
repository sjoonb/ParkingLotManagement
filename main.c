#include <stdio.h>
#include <curses.h> // clear 를 위한 library
#include <stdlib.h>

enum functype {ENTER = 1, EXIT, STATUS, AUTO, QUIT};

// Enum 활용해서 기능 선택 직관화

void init_cars();
void entering();
void exiting();
void status();
void auto_mode();
void save_and_quit();

int main() {

	enum functype func;
	int loop;
	char ch;

	// This is main loop 
	
	// TODO - Check first implementation
	// if ~~ 파일이 존재하는가? 존재하지 않는가?
	// TODO - if not, init_space()
	// TODO - if true, 파일에서 읽어와서 구조체로 형성하기, 주차장 크기도 가져오기.
	
	// Space 가 존재하는 상태이므로 이제 요금표를 가져와야함
	// TODO - 요금표 가져오기 (일단은 직접 작성)

	// Main Loop 실행
	loop = 1;
	while(loop){
		system("clear");
		printf("[1] : 입차\n[2] : 출차\n[3] : 현황\n[4] : 자동 모드\n[5] : 저장 및 종료\n");
		printf("기능을 선택하세요: ");
		scanf("%d", &func);
	
	switch(func){
	// TODO - 입력 오류 처리하기. 기능 외에 숫자가 들어왔을때, 무한루프가 되는 현상 해결.
		case ENTER:
			printf("enter\n");
			break;
		case EXIT:
			break;
		case STATUS:
			break;
		case AUTO:
			break;
		case QUIT:
			break;
		default:
			printf("nope\n");
			break;
	}
		
		// 엔터키를 한번 받아 준 다음에
		ch = fgetc(stdin);
		
		printf("엔터키를 입력하세요..");
		// keyboard = (stdin)
		ch = fgetc(stdin);

	}
	
	return 0;

}

void init_space() {
	
	// TODO - 동적 메모리 할당 ( 주차장 최대 입차 수 설정 ), 배열 안에 struct 구조, 연결리스트 활용, 포인터 활용
	// int MAX_SPACE = 100;

	// TODO if ~ random init 기능, 자동으로 무작위의 차량을 생성하시겠 습니까? (y/n)
	// 1 ~ MAX_SPACE 사이에 수로 차량번호, 차종, 입차시간까지 랜덤으로 설정


}

void entering() {

	// TODO - 만차시, 만차입니다 출력. 차량 받지 않음, 차량 규정에 맞지 않으면 추가해선 안된다.
	// 새로운 차량이 들어올 때 마다 연결리스트에 새로 추가해 줘야한다.
	
}	

void exiting() {

	// TODO - 탐색을 통해 해당 차량을 찾는다. 없다면 없다고 리턴한다.
	// TODO - 요금표에 대입하여 주차요금 받아서, 총 정산액에 저장 해야한다.

}

void status() {
	
	// TODO - 정산
	// TODO - 현재 차량들 출력
	// TODO - 여러 줄 출력할 때 어떻게 할 건지 정해야 한다.
	
}	

void auto_mode() {
	
	// TODO - 랜덤하게 exiting, entering 실행
}

