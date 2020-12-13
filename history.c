#include "mylib.h"
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>

enum functype {PRINT = 1, BACK, NEXT, MAIN};

// 입차시 차량, 시간
// 출차시 차량, 시간 요금
// 입차 11:08 24가1832
// 출차 13:12 24가1832 요금: 3000 
int enter_history();
int exit_history();
int print_history();

int enter_history(int enter_time, char car_num[] ) {

	FILE* fp = NULL;
	char today[9];
	char path_history[30];
	char path_total_money[30];

	time_t current;
	time(&current);	
	struct tm *t = localtime(&current);

	sprintf(today, "%d%d%d", t->tm_year + 1900,  t->tm_mon+1, t->tm_mday); 
	sprintf(path_history, "%s/history.txt", today);
	sprintf(path_total_money, "%s/total_money.txt", today);


	if(access(today, F_OK) == 0) {
		fp = fopen(path_history, "a");
		fprintf(fp, "\n%d:%d 입차 %s", enter_time/60, enter_time%60, car_num);
		fclose(fp);

	} else {
		mkdir(today,0700);
	
		fp = fopen(path_history, "w");
		fprintf(fp, "%d:%d 입차 %s", enter_time/60, enter_time%60, car_num);
		fclose(fp);

		fp = fopen(path_total_money, "w");
		fprintf(fp, "0");
		fclose(fp);

	}	

	return 0;

}

int exit_history(int exit_time, char car_num[], int curr_money, int total_money) {

	FILE* fp = NULL;
	char today[9];
	char path_history[30];
	char path_total_money[30];

	time_t current;
	time(&current);	
	struct tm *t = localtime(&current);

	sprintf(today, "%d%d%d", t->tm_year + 1900,  t->tm_mon+1, t->tm_mday); 
	sprintf(path_history, "%s/history.txt", today);
	sprintf(path_total_money, "%s/total_money.txt", today);


	if(access(today, F_OK) == 0) {
		fp = fopen(path_history, "a");
		fprintf(fp, "\n%d:%d 출차 %s 요금 %d원", exit_time/60, exit_time%60, car_num, curr_money);
		fclose(fp);

		fp = fopen(path_total_money, "w");
		fprintf(fp, "%d", total_money);
		fclose(fp);
	} else {
		mkdir(today,0700);
	
		fp = fopen(path_history, "w");
		fprintf(fp, "%d:%d 출차 %s 요금 %d원", exit_time/60, exit_time%60, car_num, curr_money);
		fclose(fp);

		fp = fopen(path_total_money, "w");
		fprintf(fp, "%d", total_money);
		fclose(fp);

	}	

	return 0;

}

int main_history(){
	time_t current;
	int func;
	char today[9];
	char tmp_day[9];
	int now_day;
	char ch;

	time(&current);	
	struct tm *t = localtime(&current);

	sprintf(today, "%d%d%d", t->tm_year + 1900,  t->tm_mon+1, t->tm_mday); 
	
	if(access(today, F_OK) != 0){
		printf("데이터가 존재하지 않습니다.\n");
		return 0;
	}

	// int_day = atoi(today);

	while(1){
		system("clear");
		printf("<과거 내역>\n");
		printf("현재 날짜: %s\n", today);
		printf("[1] : 출력\n[2] : 이전 날짜\n[3] : 다음 날짜\n[4] : 메인으로\n");
		printf("기능을 선택하세요: ");
		scanf("%d", &func);

	switch(func){
		case PRINT:
			print_history(today);
			break;
		case BACK:	
			sprintf(today, "%d", atoi(today)-1);
			if(access(today, F_OK) != 0){
				printf("데이터가 존재하지 않습니다.\n");
				sprintf(today, "%d", atoi(today)+1);
			}
			break;
		case NEXT:
			sprintf(today, "%d", atoi(today)+1);
			if(access(today, F_OK) != 0){
				printf("데이터가 존재하지 않습니다.\n");
				sprintf(today, "%d", atoi(today)-1);
			}
			break;
		case MAIN:
			return 0;
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

int print_history(char day[]) {
	FILE* fp = NULL;
	char line[255];

	char ch;
	int count = 0;

	char path_history[30];
	char path_total_money[30];
	
	sprintf(path_history, "%s/history.txt", day);
	sprintf(path_total_money, "%s/total_money.txt", day);
	
	ch = fgetc(stdin);


	fp = fopen(path_history, "r");
	while(fgets(line, sizeof(line), fp)){
		count += 1;
		if(count % 60 == 0){
			printf("엔터키를 입력하세요..");
			ch = fgetc(stdin);
		}
		printf("%s", line);
	}
	fp = fopen(path_total_money, "r");
	fgets(line, sizeof(line), fp);
	printf("\n총 수입: %s", line);
	fclose(fp);

	fclose(fp);


	return 0;
}

