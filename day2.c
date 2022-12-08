#include <stdio.h>
#include <stdbool.h>


int main(){
	int score = 0;
	FILE* file = fopen("day2input", "r");
	while (true){
		char them = fgetc(file) - 'A';
		if (them == EOF){
			break;
		}
		fgetc(file); // Purge the space
		char me = fgetc(file) - 'X';
		if (fgetc(file) == EOF){ // Purge the newline
			break;
		}
		if (me == 0){
			me = them - 1;
			if (me < 0){
				me = 2;
			}
		}
		else if (me == 1){
			me = them;
		}
		else if (me == 2){
			me = them + 1;
			if (me == 3){
				me = 0;
			}
		}
		if (me == 0){
			score += 1;
		}
		else if (me == 1){
			score += 2;
		}
		else if (me == 2){
			score += 3;
		}
		if (them == 0 && me == 1){
			score += 6;
		}
		else if (them == 1 && me == 2){
			score += 6;
		}
		else if (them == 2 && me == 0){
			score += 6;
		}
		else if (them == me){
			score += 3;
		}
	}
	printf("%d\n", score);
}
