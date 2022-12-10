#include "tylerLIB.h"


int cycle = 0;
int x = 1;

int addNextCycle = 0;

char* CRT;


int main(){
	FILE* file = fopen("day10input", "r");
	CRT = malloc(sizeof(char) * 40 * 6);
	int total = 0;
	while (true){
		if ((cycle % 40 >= x - 1) && (cycle % 40 <= x + 1)) {
			CRT[cycle] = '#';
		}
		else{
			CRT[cycle] = ' ';
		}
		cycle ++;
		if (cycle >= 20 && (cycle - 20) % 40 == 0){
			printf("%d, %d: %d\n", cycle, x, cycle * x);
			total += cycle * x;
		}
		if (addNextCycle){
			x += addNextCycle;
			addNextCycle = 0;
		}
		else{
			char* line = getLine(file);
			int len;
			char** splitted = splitString(line, ' ', &len);
			if (len == 2){
				addNextCycle = atoi(splitted[1]);
			}
		}
		if (feof(file)){
			break;
		}
	}
	for (int y = 0; y < 6; y ++){
		for (int x = 0; x < 40; x ++){
			printf("%C", CRT[y * 40 + x]);
		}
		printf("\n");
	}
	return 60249;
}

