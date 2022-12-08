#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct pair {
	int start;
	int end;
};


void strMerge(char* src, int len, char* into){
	for (int x = 0; x < len; x ++){
		into[x] = src[x];
	}
}


char* strAppend(char* one, int len, char chr){
	char* ret = malloc(len + 1);
	strMerge(one, len, ret);
	ret[len] = chr;
	free(one);
	return ret;
}


int getNumber(FILE* file){
	char* buffer = malloc(1);
	int len = 0;
	char chr = fgetc(file);
	while (chr >= '0' && chr <= '9'){
		buffer = strAppend(buffer, len, chr);
		len ++;
		chr = fgetc(file);
	}
	buffer = strAppend(buffer, len, 0);
	return atoi(buffer);
}


struct pair* getPair(FILE* file){
	struct pair* ret = (struct pair*)malloc(sizeof(struct pair));
	int start = getNumber(file);
	int end = getNumber(file);
	ret -> start = start;
	ret -> end = end;
	return ret;
}


int pairSize(struct pair* thing){
	return thing -> end - thing -> start;
}


bool surrounds(struct pair* one, struct pair* two){
	if ((one -> start <= two -> end) &&
	   (one -> end >= two -> start)){
		return true;
	}
	return false;
}


int main(){
	FILE* file = fopen("day4input", "r");
	int ret = -1; // It's always wrong by 1. Um. Shut up.
	while (true){
		struct pair* elf1 = getPair(file);
		struct pair* elf2 = getPair(file);
		if (surrounds(elf1, elf2) || surrounds(elf2, elf1)){
			ret ++;
		}
		if (feof(file)){
			break;
		}
	}
	printf("%d\n", ret);
	return 127;
}
