#include <stdio.h>
#include <stdbool.h>


int elves[10000]; // 10000 datapoints. Should be enough, eh?

int main(){
	FILE* data = fopen("day1input", "r");
	char chr = fgetc(data);
	int elf = 0;
	int elfCur = 0;
	char num[10];
	int chrNum = 0;
	bool nextElf;
	while (chr != EOF){
		if (chr == '\n'){
			if (nextElf){
				elves[elf] = elfCur;
				elf ++;
				elfCur = 0;
			}
			elfCur += atoi(num);
			chrNum = 0;
			for (int x = 0; x < 10; x ++){
				num[x] = 0;
			}
			nextElf = true;
		}
		else{
			nextElf = false;
		}
		num[chrNum] = chr;
		chrNum ++;
		chr = fgetc(data);
	}
	int biggest1 = 0;
	int biggest2 = 0;
	int biggest3 = 0;
	for (int x = 0; x < 10000; x ++){
		if (elves[x] > biggest1){
			biggest1 = elves[x];
		}
		else if (elves[x] > biggest2){
			biggest2 = elves[x];
		}
		else if (elves[x] > biggest3){
			biggest3 = elves[x];
		}
	}
	printf("%d\n", biggest1 + biggest2 + biggest3);
}
