#include <stdio.h>
#include <curses.h> // system clear
#include <stdlib.h>
#include <string.h> //strcpy, strcmp
#include <unistd.h> //access
#include <time.h>

// Enum 활용해서 기능 선택 직관화
enum functype {ENTER = 1, EXIT, STATUS, AUTO, QUIT, RESET};

struct car {
	char num[10];
	char size[10];
	int time;
	struct car* next;
};

typedef struct car car_t;


void init_space(int* pspace, int* pnew);
car_t* init_cars(int new, car_t* main_list_head, int* pnum_of_car);
void init_rate();
car_t* enter_info(car_t* main_list_head, int* pnum_of_car, int space);
car_t* entering(car_t* main_list_head, char tmp_num[], char tmp_size[], int enter_time, int* pnum_of_car);
car_t* exit_info(car_t* main_list_head, int* pnum_of_car);
car_t* exiting(car_t* main_list_head, char tmp_nump[], int* pnum_of_car);
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
	int num_of_car;
	// TODO - 차량 수 체크, 만차시 만차라고 하고 다시 못나오게
	int car_count; // 차량 수
	// 먼저 프로그램이 주차장 크기, 차량, 요금표를 받아와야 한다. 처음 만들어 진건지 체크는 그 안에서 이루어 지면 된다. 
	// 우선 주차장 사이즈를 가져오고,
	init_space(&space, &new);

	// 그 사이즈에 맞게 struct car 연결리스트를 형성해야 한다.
	main_list_head = init_cars(new, main_list_head, &num_of_car);

	init_rate();
	
	// TODO - if true, 파일에서 읽어와서 구조체로 형성하기, 주차장 크기도 가져오기.
	
	// Space 가 존재하는 상태이므로 이제 요금표를 가져와야함
	// TODO - 요금표 가져오기 (일단은 직접 작성)

	// Main Loop 실행
	loop = 1;
	while(loop){
		system("clear");
		printf("[1] : 입차\n[2] : 출차\n[3] : 현황\n[4] : 자동 모드\n[5] : 저장 및 종료\n[6] : 초기화\n");
		printf("기능을 선택하세요: ");
		scanf("%d", &func);
	
	switch(func){
	// TODO - 입력 오류 처리하기. 기능 외에 숫자가 들어왔을때, 무한루프가 되는 현상 해결.
		case ENTER:
			printf("- 입차\n");
			main_list_head = enter_info(main_list_head, &num_of_car, space);
			break;
		case EXIT:
			printf("- 출차\n");
			main_list_head = exit_info(main_list_head, &num_of_car);
			break;
		case STATUS:
			printf("- 현황\n");
			printf("주차장 크기: %d\n주차 차량 수: %d\n남은 공간: %d\n", space, num_of_car, space-num_of_car);
			printf("[현재 주차된 차량]\n");
			status(main_list_head);
			break;
		case AUTO:
			break;
		case QUIT:
			save_and_quit(new, space, main_list_head);
			break;
		case RESET:
			reset();
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
	// 1 ~ MAX_SPACE 사이에 수로 차량번호, 차종, 입차시간까지 랜덤으로 설정

}


car_t* init_cars(int new, car_t* main_list_head, int* pnum_of_car) {
	FILE* fp = NULL;

	char tmp_num[10];
	char tmp_size[10];
	int enter_time;
	
	if(new){
		fp = fopen("car.txt", "w");
		fclose(fp);
	// TODO - new file 이라면, 랜덤 생성 할껀지 묻고 pass
	} else {
		fp = fopen("car.txt", "r");
		if(fp == NULL) {
			printf("파일을 열 수 없습니다.\n");
		} else {
			while(!feof(fp)){
				fscanf(fp, "%s %s %d\n", tmp_num, tmp_size, &enter_time);
				main_list_head = entering(main_list_head, tmp_num, tmp_size, enter_time, pnum_of_car);
			}
		
			fclose(fp);
		}
	}

	return main_list_head;

}

void init_rate() {

}

car_t* enter_info(car_t* main_list_head, int* pnum_of_car, int space) {
	if(*pnum_of_car >= space){
		printf("만차 입니다. 차량을 더 이상 받을 수 없습니다.\n");
		return main_list_head;
	}	   

	time_t current;
	time(&current);

	struct tm *t = localtime(&current);

	int enter_time = t->tm_hour*60 + t->tm_min;

	char tmp_num[10];
	char tmp_size[10];

	printf("차량번호: ");
	scanf("%s", tmp_num);

	printf("소형 / 중형 / 대형\n");
	printf("차량 사이즈: ");
	scanf("%s", tmp_size);

	
	main_list_head = entering(main_list_head, tmp_num, tmp_size, enter_time, pnum_of_car);

	return main_list_head;

}

car_t* entering(car_t* main_list_head, char tmp_num[], char tmp_size[], int enter_time, int* pnum_of_car) {			
	*pnum_of_car += 1;

	car_t* new_node;
	car_t* next_p;
	car_t* prev_p;

	new_node = (car_t*) malloc (sizeof(car_t));
	strcpy(new_node->num, tmp_num);
	strcpy(new_node->size, tmp_size);
	new_node->time = enter_time;

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

		printf("차량번호 %s %s차량 %d:%d 부로 입차하였습니다.\n", new_node->num, new_node->size, new_node->time/60, new_node->time%60);

	return main_list_head;

	// TODO - 만차시, 만차입니다 출력. 차량 받지 않음, 차량 규정에 맞지 않으면 추가해선 안된다.
	// 새로운 차량이 들어올 때 마다 연결리스트에 새로 추가해 줘야한다.
	
}	

car_t* exit_info(car_t* main_list_head, int* pnum_of_car) {
	status(main_list_head);

	time_t current;
	time(&current);

	struct tm *t = localtime(&current);

	int enter_time = t->tm_hour*60 + t->tm_min;

	char tmp_num[10];

	printf("차량번호: ");
	scanf("%s", tmp_num);
	
	main_list_head = exiting(main_list_head, tmp_num, pnum_of_car);

	return main_list_head;

}

car_t* exiting(car_t* main_list_head, char tmp_num[], int* pnum_of_car) {
	int found = 0;

	car_t* next_p;
	car_t* prev_p;

	next_p = main_list_head;
	prev_p = NULL;

	while(next_p) {
		if(strcmp(next_p->num, tmp_num) == 0){
			found = 1;
			break;
		}
		prev_p = next_p;
		next_p = next_p -> next;
	}

	if(found){
		if(prev_p) {
			prev_p -> next = next_p -> next;
		} else {
			main_list_head = next_p -> next;
		}

		free(next_p);
		*pnum_of_car -= 1;

	} else {
		printf("해당 차량이 존재하지 않습니다.\n");
	}

	return main_list_head;

}

void status(car_t* list_head) {
	while(list_head != NULL){
		printf("%s / %s / %d:%d\n", list_head->num, list_head->size, list_head->time/60, list_head->time%60);
		list_head = list_head->next;
	}

	// TODO - 정산
	// TODO - 현재 차량들 출력
	// TODO - 여러 줄 출력할 때 어떻게 할 건지 정해야 한다.	
}

void auto_mode() {
	
	// TODO - 랜덤하게 exiting, entering 실행
}

void save_and_quit(int new, int space, car_t* list_head){
	FILE* fp = NULL; 
	car_t* tmp_node;
	
	if(new){
		fp = fopen("space.txt", "w");
		fprintf(fp, "%d", space);
		fclose(fp);
	} 

	fp = fopen("car.txt", "w");

	while(list_head != NULL){
		tmp_node = list_head;
		fprintf(fp, "%s %s %d\n", list_head->num, list_head->size, list_head->time);
		list_head = list_head->next;
		free(tmp_node);
	}
	
	fclose(fp);
	

	exit(0);
}

void reset() {
	int recheck;
	char ch;

	printf("정말 초기화 하시겠습니까?\n");
	printf("[1] : 네 [2] : 아니오\n");
	printf("입력: ");
	scanf("%d", &recheck);

	if(recheck == 1){
		remove("space.txt");
		remove("car.txt");
		printf("초기화가 완료되었습니다.\n");
		ch = fgetc(stdin);
		
		printf("엔터키를 입력하여 재실행..");
		ch = fgetc(stdin);

		main();

	} else if (recheck == 2) {
		printf("취소되었습니다.\n");	
	}

}
