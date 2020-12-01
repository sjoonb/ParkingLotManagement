#include <stdio.h>
#include <curses.h> // system clear
#include <stdlib.h>
#include <string.h> //strcpy, strcmp
#include <unistd.h> //access
#include <time.h>

enum functype {ENTER = 1, EXIT, STATUS, AUTO, QUIT};

struct car {
	char num[10];
	char size[10];
	int time;
	struct car* next;
};

typedef struct car car_t;

// Enum 활용해서 기능 선택 직관화

void init_space(int* pspace, int* pnew);
void init_cars(int new);
void init_rate();
car_t* entering(car_t* main_list_head);
void exiting();
void status(car_t* list_head);
void auto_mode();
void save_and_quit(int new, int space, car_t* list_head);

void reset(); // 초기화 함수는 숨겨놀까? password 까지 구현?

int main() {
	system("clear");

	// 포인터 변수를 통해 주차장 크기, 차량들을 init 하는게 좋을 것 같다. 
	int func;
	int loop;
	int new = 0;
	char ch;

	// 우선 4자리수 차량으로 하고, 시간이 남는다면 가나다라 추가하자
	
	car_t* main_list_head = NULL;
	int space; // 주차장 크기
	// 먼저 프로그램이 주차장 크기, 차량, 요금표를 받아와야 한다. 처음 만들어 진건지 체크는 그 안에서 이루어 지면 된다. 
	// 우선 주차장 사이즈를 가져오고,
	init_space(&space, &new);

	// 그 사이즈에 맞게 struct car 연결리스트를 형성해야 한다.
	init_cars(new);

	init_rate();
	
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
			printf("- 입차\n");
			main_list_head = entering(main_list_head);
			break;
		case EXIT:
			break;
		case STATUS:
			printf("%d\n", space);
			status(main_list_head);
			break;
		case AUTO:
			break;
		case QUIT:
			save_and_quit(new, space, main_list_head);
			break;
		default:
			printf("nope\n");
			break;
	}
	
		// conio 라이브러리 import 오류	
		// 엔터키를 한번 받아 준 다음에
		ch = fgetc(stdin);
		
		printf("엔터키를 입력하세요..");
		// keyboard = (stdin)
		ch = fgetc(stdin);

	}
	
	return 0;

}

void init_space(int* pspace, int* pnew) {	
	FILE* fp = NULL;

	if(access("space.txt", F_OK) == 0) {
		// TODO - 자동차 랜덤 생성할지 묻는다. 아니면 그냥 빈칸으로 냄겨 둔다.
		fp = fopen("space.txt", "r");
		fscanf(fp, "%d\n", pspace); 

		fclose(fp);

	} else {
		printf("주차장 최대 공간을 입력해 주세요: ");
		scanf("%d", pspace);
		*pnew = 1; // 마지막에 저장할 때 사용하기 위한 변수
	} 
	// else
	// TODO - 파일에서 space 와, 차량들을 갖고온다. 이 때 차량이 몇개인지 count 해준다.

	//else 일 때에는 그저 있는 파일에서 읽어와서 배열 혹은 연결리스트와 spacae 를 지정하면 된다.

	// TODO - 동적 메모리 할당 ( 주차장 최대 입차 수 설정 ), 배열 안에 struct 구조, 연결리스트 활용, 포인터 활용
	// int MAX_SPACE = 100;

	// TODO if ~ random init 기능, 자동으로 무작위의 차량을 생성하시겠 습니까? (y/n)
	// init_cars()
	// 1 ~ MAX_SPACE 사이에 수로 차량번호, 차종, 입차시간까지 랜덤으로 설정

}


void init_cars(int new) {
	int a;
	FILE* fp = NULL;
	
	if(new){
	// TODO - new file 이라면, 랜덤 생성 할껀지 묻고 pass
	} else {
		printf("not new\n");
		scanf("%d", &a);
	}


}

void init_rate() {

}


car_t* entering(car_t* main_list_head) {	
	time_t current;
	time(&current);

	struct tm *t = localtime(&current);

	char tmp_num[10];
	char tmp_size[10];
	car_t* new_node;
	car_t* next_p;
	car_t* prev_p;

	printf("차량번호: ");
	scanf("%s", tmp_num);

	printf("소형 / 중형 / 대형\n");
	printf("차량 사이즈: ");
	scanf("%s", tmp_size);

	new_node = (car_t*) malloc (sizeof(car_t));
	strcpy(new_node->num, tmp_num);
	strcpy(new_node->size, tmp_size);
	new_node->time = t->tm_hour*60 + t->tm_min;

	next_p = main_list_head;
	prev_p = NULL;

	while(next_p) {
		if(strcmp(next_p->num, new_node->num) > 0)
			break;
		prev_p = next_p;
		next_p = next_p -> next;
	}

	new_node->next = next_p;

	if(prev_p) {
		prev_p->next = new_node;
	} else {
		main_list_head = new_node;
	}


	return main_list_head;

	// TODO - 만차시, 만차입니다 출력. 차량 받지 않음, 차량 규정에 맞지 않으면 추가해선 안된다.
	// 새로운 차량이 들어올 때 마다 연결리스트에 새로 추가해 줘야한다.
	
}	

void exiting() {

	// TODO - 탐색을 통해 해당 차량을 찾는다. 없다면 없다고 리턴한다.
	// TODO - 요금표에 대입하여 주차요금 받아서, 총 정산액에 저장 해야한다.
	// TODO - 회차인 경우도 고려한다.

}

void status(car_t* list_head) {
	
	while(list_head != NULL){
		printf("%s, %s, %d:%d\n", list_head->num, list_head->size, list_head->time/60, list_head->time%60);
		list_head = list_head->next;
	}
	printf("\n");

	// TODO - 정산
	// TODO - 현재 차량들 출력
	// TODO - 여러 줄 출력할 때 어떻게 할 건지 정해야 한다.	
}

void auto_mode() {
	
	// TODO - 랜덤하게 exiting, entering 실행
}

void save_and_quit(int new, int space, car_t* list_head){
	FILE* fp = NULL; 
	
	if(new){
		fp = fopen("space.txt", "w");
		fprintf(fp, "%d", space);
		fclose(fp);
	} 

	fp = fopen("car.txt", "w");

	while(list_head != NULL){
		fprintf(fp, "%s %s %d\n", list_head->num, list_head->size, list_head->time);
		list_head = list_head->next;
	}
	
	fclose(fp);
	

	exit(0);
}
