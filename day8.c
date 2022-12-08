#include "tylerLIB.h"
#include <stdint.h>


uint8_t** grid = 0;
int gridSize = -1;


void allocate(){
	grid = malloc(sizeof(uint8_t*) * gridSize);
	for (int i = 0; i < gridSize; i ++){
		grid[i] = malloc(sizeof(uint8_t) * gridSize);
	}
}


int traverseScore(int startX, int startY, int xv, int yv){
	int score = 0;
	for (int y = startY + yv; y >= 0 && y < gridSize; y += yv){
		for (int x = startX + xv; x >= 0 && x < gridSize; x += xv){
			score ++;
			if (grid[y][x] >= grid[startY][startX]){
				return score; // Immediately exit if it meets an obstruction
			}
			if (xv == 0){ // Don't get caught in an infinite loop
				break;
			}
		}
		if (yv == 0){ // ditto.
			break;
		}
	}
	// This may look bulky but because of the infinite loop prevention code, it's really quite optimized.
	return score;
}


int getScoreTop(int x, int y){
	return traverseScore(x, y, 0, -1);
}

int getScoreBottom(int x, int y){
	return traverseScore(x, y, 0, 1);
}

int getScoreLeft(int x, int y){
	return traverseScore(x, y, -1, 0);
}

int getScoreRight(int x, int y){
	return traverseScore(x, y, 1, 0);
}


int main(){
	FILE* file = fopen("day8input", "r");
	int lineNum = 0;
	while (true){ // Break a file down into a grid. I might do some Memory Magic(tm) for this later (to make it more pretentious, obviously), but for now it's just real simple and efficient.
		char* line = getLine(file);
		if (feof(file)){
			break;
		}
		if (gridSize == -1){
			gridSize = strlen(line);
			allocate();
		}
		for (int x = 0; x < gridSize; x ++){
			grid[lineNum][x] = line[x] - '0'; // Fun character math. Hahahahhahahahahahahahahahaha
		}
		lineNum ++;
	}
	int highest = 0;
	for (int y = 0; y < gridSize; y ++){
		for (int x = 0; x < gridSize; x ++){
			int score = getScoreTop(x, y) * getScoreLeft(x, y) * getScoreBottom(x, y) * getScoreRight(x, y);
			if (score > highest){
				highest = score;
				printf("%d, %d\n", x, y);
			}
		}
	}
	printf("Answer: %d\n", highest);
	return 177;
}
