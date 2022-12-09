#include "tylerLIB.h"


struct RopeUnique{ // linked list
	int x;
	int y;
	struct RopeUnique* next;
};


struct RopeUnique* start;
struct RopeUnique* cur;

int knots[2][10];


struct RopeUnique* newRopePos(int x, int y){
	struct RopeUnique* rope = malloc(sizeof(struct RopeUnique));
	memset(rope, 0, sizeof(struct RopeUnique));
	rope -> x = x;
	rope -> y = y;
	return rope;
}


struct RopeUnique* addRopePos(int x, int y){
	struct RopeUnique* ret = newRopePos(x, y);
	cur -> next = ret; // Appending to a linked list.
	cur = ret;
	return ret;
}


bool positionInList(int x, int y){
	struct RopeUnique* pos = start;
	while (pos){
		if (pos -> x == x && pos -> y == y){
			return true;
		}
		pos = pos -> next;
	}
	return false;
}


void calculateRope(){
	for (int i = 8; i >= 0; i --){
		if ((knots[i][0] >= knots[i + 1][0] - 1) && (knots[i][0] <= knots[i + 1][0] + 1) && (knots[i][1] >= knots[i + 1][1] - 1) && (knots[i][1] <= knots[i + 1][1] + 1)){
			return;
		}
		if (knots[i][0] < knots[i + 1][0]){
			knots[i][0] ++;
		}
		if (knots[i][0] > knots[i + 1][0]){
			knots[i][0] --;
		}
		if (knots[i][1] < knots[i + 1][1]){
			knots[i][1] ++;
		}
		if (knots[i][1] > knots[i + 1][1]){
			knots[i][1] --;
		}
	}
	if (!positionInList(knots[0][0], knots[0][1])){
		addRopePos(knots[0][0], knots[0][1]);
	}
}


void moveDirection(char direction){
	if (direction == 'R'){
		knots[9][0] ++;
	}
	else if (direction == 'L'){
		knots[9][0] --;
	}
	else if (direction == 'U'){
		knots[9][1] --;
	}
	else if (direction == 'D'){
		knots[9][1] ++;
	}
	calculateRope();
}


int getLength(){
	struct RopeUnique* pos = start;
	int ret = 0;
	while (pos){
		ret ++;
		pos = pos -> next;
	}
	return ret;
}


int main(){
	FILE* file = fopen("day9input", "r");
	start = newRopePos(0, 0);
	cur = start;
	while (true){
		char direction = fgetc(file);
		if (feof(file)){
			break;
		}
		fgetc(file); // Purge the space
		char* _amount = getLine(file);
		int amount = atoi(_amount);
		free(_amount);
		for (int i = 0; i < amount; i ++){
			moveDirection(direction);
		}
	}
	printf("Answer: %d\n", getLength());
	return 78109; // I taught a coder on my robotics team about processor return codes AND signed 16-bit integers at the same time. The result should have been obvious in hindsight. (it has become tradition to return ridiculous numbers from int main)
}
