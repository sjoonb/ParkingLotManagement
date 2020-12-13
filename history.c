#include "myutil.h"
#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

// 입차시 차량, 시간
// 출차시 차량, 시간 요금
// 입차 11:08 24가1832
// 출차 13:12 24가1832 요금: 3000 

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

	printf("%s\n", path_history);

	if(access(today, F_OK) == 0) {
		printf("%s exist\n", today);
		fp = fopen(path_history, "a");
		fprintf(fp, "\n%d:%d 입차 %s", enter_time/60, enter_time%60, car_num);
		fclose(fp);

	} else {
		printf("%s doesn't exist\n", today);
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

	printf("%s\n", path_history);

	if(access(today, F_OK) == 0) {
		printf("%s exist\n", today);
		fp = fopen(path_history, "a");
		fprintf(fp, "\n%d:%d 출차 %s 요금 %d원", exit_time/60, exit_time%60, car_num, curr_money);
		fclose(fp)

		fp = fopen(path_total_money, "w");
		fprintf(fp, "%d", total_money);
		fclose(fp);
	} else {
		printf("%s doesn't exist\n", today);
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

int main(){
	time_t current;
	time(&current);	
	struct tm *t = localtime(&current);

	sprintf(today, "%d%d%d", t->tm_year + 1900,  t->tm_mon+1, t->tm_mday); 

	printf

	return 0;

}
