#include "myutil.h" //kbhit 
#include <stdio.h>
#include <curses.h> // system clear
#include <stdlib.h>
#include <string.h> //strcpy, strcmp
#include <unistd.h> //access
#include <ctype.h> //isdigit
#include <time.h>

#define SECONDS 1000000
#define MINUTES 60 

// Enum 활용해서 기능 선택 직관화
enum functype {ENTER = 1, EXIT, STATUS, AUTO, QUIT, RESET};
enum ratetype {DEFAULT, PLUS, MAX, TURN};

struct car {
	char num[10];
	char size[10];
	int time;
	struct car* next;
};

typedef struct car car_t;


void init_space();
car_t* init_cars();
int init_money();
void init_rate();
car_t* enter_info();
car_t* entering();
car_t* exit_info();
car_t* exiting();
int get_now_time();
void get_money();
void get_money_by_size();
void status();
car_t* auto_mode(); 
car_t* random_enter_info();
car_t* random_exit_info();
void save_and_quit();
void reset(); 

int main() {
	system("clear");

	// 포인터 변수를 통해 주차장 크기, 차량들을 init 하는게 좋을 것 같다. 
	int func;
	int loop;
	int new = 0;
	char ch;
	
	// 요금을 위한 변수
	int sm[4] = {0}; // small, mid size
	int l[4] = {0}; // large size
	
	car_t* main_list_head = NULL;
	int space = 0; // 주차장 크기
	int num_of_car = 0;
	int money = 0;

	// 우선 주차장 사이즈를 가져오고,
	init_space(&space, &new);

	// 그 사이즈에 맞게 struct car 연결리스트를 형성해야 한다.
	main_list_head = init_cars(new, main_list_head, &num_of_car, space);
	
	money = init_money(new);

	// 그 후 요금을 가져온다.
	init_rate(sm, l);
	
	
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
			main_list_head = exit_info(main_list_head, &num_of_car, &money, sm, l);
			break;
		case STATUS:
			printf("- 현황\n");
			printf("< 금일 수입: %d원 >\n", money);
			printf("주차장 크기: %d\n주차 차량 수: %d\n남은 공간: %d\n", space, num_of_car, space-num_of_car);
			printf("[현재 주차된 차량]\n");
			status(main_list_head);
			break;
		case AUTO:
			printf("- 자동모드\n");
			printf("자동모드를 중지하시려면 엔터키를 입력하세요..\n");
			main_list_head = auto_mode(main_list_head, &num_of_car, space, &money, sm, l);
			printf("데이터를 저장하고 종료합니다. 프로그램을 재실행해 주세요.\n");
			ch = fgetc(stdin);
		case QUIT:
			save_and_quit(new, space, money, main_list_head);
			break;
		case RESET:
			reset();
			break;
		default:
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
	// 1 ~ MAX_SPACE 사이에 수로 차량번호, 차종, 입차시간까지 랜덤으로 설정

}


car_t* init_cars(int new, car_t* main_list_head, int* pnum_of_car, int space) {
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
				main_list_head = entering(main_list_head, tmp_num, tmp_size, enter_time, pnum_of_car, space);
			}
		
			fclose(fp);
		}
	}

	return main_list_head;

}

int init_money(int new) {
	FILE* fp = NULL;
	int tmp_money = 0;
	
	if(!new) {
		fp = fopen("money.txt", "r");
		if(fp == NULL) {
			printf("파일을 열 수 없습니다.\n");
		} else {
			fp = fopen("money.txt", "r");
			fscanf(fp, "%d\n", &tmp_money); 
		}
		fclose(fp);
	}

	return tmp_money;
	
}

void init_rate(int tmp_sm[], int tmp_l[]) {
	FILE* fp = NULL;
	int i = 0;
	
	fp = fopen("rate.txt", "r");
	if(fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
	} else {
		while(!feof(fp)){
			fscanf(fp, "%d %d\n", &tmp_sm[i], &tmp_l[i]);
			i += 1;
		}
	
		fclose(fp);
	}

}

car_t* enter_info(car_t* main_list_head, int* pnum_of_car, int space) {
	if(*pnum_of_car >= space){
		printf("만차 입니다. 차량을 더 이상 받을 수 없습니다.\n");
		return main_list_head;
	}	   

	int enter_time = get_now_time(); 

	char tmp_num[10];
	int i;

	char tmp_size[10];
	char size_arr[] = "소형|중형|대형";
	char *is_in_size;

	printf("차량번호: ");
	scanf("%s", tmp_num);

	for(i = 0; i < 10; i++){
		if(i >= 2 && i <= 4){
			if(!(tmp_num[i] & 0x80)){
				printf("올바른 차량 형식이 아닙니다.\n");
				return main_list_head;
			}
		} else if(i == 9) {
			if(tmp_num[i] != '\0'){
				printf("올바른 차량 형식이 아닙니다.\n");
				return main_list_head;
			}
		} else {	
			if(!(isdigit(tmp_num[i]))){
				printf("올바른 차량 형식이 아닙니다.\n");
				return main_list_head;
			}
		}
	}

	printf("소형 / 중형 / 대형\n");
	printf("차량 사이즈: ");
	scanf("%s", tmp_size);

	is_in_size = strstr(size_arr, tmp_size);
	if(is_in_size == NULL){
		printf("올바른 차량 크기 형식이 아닙니다.\n");
		return main_list_head;
	}

	
	main_list_head = entering(main_list_head, tmp_num, tmp_size, enter_time, pnum_of_car, space);

	return main_list_head;

}

car_t* entering(car_t* main_list_head, char tmp_num[], char tmp_size[], int enter_time, int* pnum_of_car, int space) {			
	if(*pnum_of_car >= space){
		printf("만차 입니다. 차량을 더 이상 받을 수 없습니다.\n");
		return main_list_head;
	}	   

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

}	

car_t* exit_info(car_t* main_list_head, int* pnum_of_car, int* pmoney,  int tmp_sm[], int tmp_l[]) {
	status(main_list_head);

	char tmp_num[10];

	printf("차량번호: ");
	scanf("%s", tmp_num);
	
	main_list_head = exiting(main_list_head, tmp_num, pnum_of_car, pmoney, tmp_sm, tmp_l);

	return main_list_head;

}

car_t* exiting(car_t* main_list_head, char tmp_num[], int* pnum_of_car, int* pmoney, int tmp_sm[], int tmp_l[]) {
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

		get_money(next_p, tmp_sm, tmp_l, pmoney);
	
			
		free(next_p);
		*pnum_of_car -= 1;

	} else {
		printf("해당 차량이 존재하지 않습니다.\n");
	}


	return main_list_head;

}

int get_now_time(){
	time_t current;
	time(&current);

	struct tm *t = localtime(&current);

	int enter_time = t->tm_hour*60 + t->tm_min;

	return enter_time;
}

void get_money(car_t* node, int tmp_sm[], int tmp_l[], int* pmoney){	
	if(!strcmp("소형", node->size) || !strcmp("중형", node->size)) {
		get_money_by_size(node, tmp_sm, pmoney);
	} else if (!strcmp("대형", node->size)) {
		get_money_by_size(node, tmp_l, pmoney);
	}	
}

void get_money_by_size(car_t* node, int tmp_cs[], int* pmoney){
	time_t current;
	time(&current);

	struct tm *t = localtime(&current);

	int now_time = t->tm_hour*60 + t->tm_min;
	int total_time;
	int rate;
	
	if(now_time < node->time){
		now_time += 1440;
	}

	total_time = now_time - node->time;

	if(total_time <= tmp_cs[TURN]){
		printf("%s 차량은 회차 차량입니다. 요금을 받지 않습니다.\n", node->num);
	} else if(total_time <= 30) {
		printf("%s 차량의 요금은 기본 요금인 %d원 입니다.\n", node->num, tmp_cs[DEFAULT]); 
		*pmoney += tmp_cs[DEFAULT];
	} else {
		rate = tmp_cs[DEFAULT] + tmp_cs[PLUS] * ((total_time - 30) / 10 + 1);
		if(rate > tmp_cs[MAX]){
			printf("%s 차량의 요금은 하루 최대 요금인 %d원 입니다.\n", node->num, tmp_cs[MAX]); 
			*pmoney += tmp_cs[MAX];
		} else {
			printf("%s 차량의 요금은 %d원 입니다.\n", node->num, rate); 
			*pmoney += rate;
		}
	}




}

void status(car_t* list_head) {
	while(list_head != NULL){
		printf("%s / %s / %d:%d\n", list_head->num, list_head->size, list_head->time/60, list_head->time%60);
		list_head = list_head->next;
	}
}

car_t* auto_mode(car_t* main_list_head, int* pnum_of_car, int space, int* pmoney, int tmp_sm[], int tmp_l[]) {
	// TODO - 랜덤하게 exiting, entering 실행
	

	srand(time(NULL));

	int mode;
	int min, max, count;
	int rand_time;

	min = 5; // * MINUTES;
	max = 10; // * MINUTES;

	count = 0;
	
	rand_time = rand() % (max - min) +  5; // * MINUTES;
	
	while(!kbhit())
	{

		if(count == rand_time){

			mode = rand() % 2 + 1;

			switch(mode) {
				case ENTER:
					main_list_head = random_enter_info(main_list_head, pnum_of_car, space);
					rand_time = rand() % (max - min) + 5;
					count = 0;
					break;
				case EXIT:
					if(*pnum_of_car > 0){
						main_list_head = random_exit_info(main_list_head, pnum_of_car, pmoney, tmp_sm, tmp_l);
						rand_time = rand() % (max - min) + 5;
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

car_t* random_enter_info(car_t* main_list_head, int* pnum_of_car, int space) {
	// number
	char num_kr[14][10] = {"가", "나", "다", "라", "마", "바", "사", "아", "자", "차", "카", "타", "파", "하"};

	char ran_num[10];
	int i;
	int r = rand() % 14;

	for(i = 0; i < 9; i++){
		if(i == 2){
			strcat(ran_num, num_kr[r]);
			i += 3;
		}
		sprintf(&ran_num[i], "%d", rand() % 10);
	}


	// size
	char size[3][10] = {"소형", "중형", "대형"};
	char ran_size[10];
	int j = rand() % 3;
	
	strcpy(ran_size, size[j]);


	// time
	int enter_time = get_now_time();

	main_list_head = entering(main_list_head, ran_num, ran_size, enter_time, pnum_of_car, space);

	return main_list_head;


}

car_t* random_exit_info(car_t* main_list_head, int* pnum_of_car, int* pmoney, int tmp_sm[], int tmp_l[]){
	car_t* list_head = main_list_head;
	int rand_car_num = rand() % *pnum_of_car;
	int i = 0;

	while(i != rand_car_num){
		list_head = list_head->next;
		i += 1;
	}


	main_list_head = exiting(main_list_head, list_head->num, pnum_of_car, pmoney, tmp_sm, tmp_l);

	return main_list_head;

}

void save_and_quit(int new, int space, int money, car_t* list_head){
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

	fp = fopen("money.txt", "w");
	fprintf(fp, "%d", money);
	fclose(fp);	

	printf("데이터를 저장합니다..");

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
		remove("money.txt");
		printf("초기화가 완료되었습니다.\n");
		ch = fgetc(stdin);
		
		printf("엔터키를 입력하여 재실행..");
		ch = fgetc(stdin);

		main();

	} else if (recheck == 2) {
		printf("취소되었습니다.\n");	
	}

}
