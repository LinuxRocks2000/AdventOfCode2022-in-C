#include "tylerLIB.h" // Commands for things like string merging; ain't nuttin' y'all ain't seen
#define TOOL_SIZE 14


char* buf;


void shiftDown(){
	for (int i = 0; i < TOOL_SIZE - 1; i ++){
		buf[i] = buf[i + 1];
	}
	buf[TOOL_SIZE - 1] = 0;
}


int countOccurrences(char chr){
	int ret = 0;
	for (int i = 0; i < TOOL_SIZE; i ++){
		if (buf[i] == chr){
			ret ++; // Expected to return minimum of 1
		}
	}
	return ret;
}


bool isAllDifferent(){
	for (int i = 0; i < TOOL_SIZE; i ++){
		if (countOccurrences(buf[i]) > 1){
			return false;
		}
	}
	return true;
}


bool isFull(){
	return countOccurrences(0) == 0;
}


int main(){
	FILE* file = fopen("day6input", "r"); // All the standard libraries are also included with tylerLIB.h
	buf = malloc(TOOL_SIZE);
	for (int x = 0; x < TOOL_SIZE; x ++){
		buf[x] = 0;
	}
	int index = 1;
	char chr = fgetc(file);
	while (true){
		shiftDown();
		buf[TOOL_SIZE - 1] = chr;
		if (isFull() && isAllDifferent()){
			break;
		}
		chr = fgetc(file);
		index ++;
	}
	printf("Answer: %d, %s\n", index, buf);
	return 127; // Just to screw around
}
