#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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


char* getLine(FILE* file){
	char* ret = malloc(1);
	int len = 0;
	while (true){
		char chr = fgetc(file);
		if (chr == EOF || chr == '\n'){
			break;
		}
		else{
			ret = strAppend(ret, len, chr);
			len ++;
		}
	}
	ret = strAppend(ret, len, 0);
	return ret;
}


int strLen(char* str){
	int ret = 0;
	while (true){
		if (str[ret] == 0){
			break;
		}
		ret ++;
	}
	return ret;
}


struct crate{
	char name;
	int stack;
	int pos;
};


struct stack{
	struct crate** items;
	int size;
};


struct stack stacks[10];


void pushCrate(int sN, struct crate* c){
	struct stack* s = &stacks[sN];
	s -> size ++;
	struct crate** old = s -> items;
	s -> items = (struct crate**)malloc(sizeof(struct crate*) * s -> size);
	for (int x = 0; x < s -> size - 1; x ++){
		s -> items[x] = old[x];
	}
	free(old);
	s -> items[s -> size - 1] = c;
	c -> stack = sN;
	c -> pos = s -> size - 1;
}


void insertCrate(int sN, struct crate* c, int pos){
	struct stack* s = &stacks[sN];
	s -> size ++;
	struct crate** old = s -> items;
	s -> items = (struct crate**)malloc(sizeof(struct crate*) * s -> size);
	for (int x = 0; x < pos; x ++){
		s -> items[x] = old[x];
		s -> items[x] -> pos ++;
	}
	s -> items[pos] = c;
	for (int x = pos + 1; x < s -> size; x ++){
		s -> items[x] = old[x - 1];
		s -> items[x] -> pos ++;
	}
	free(old);
	c -> stack = sN;
	c -> pos = 0;
}


struct crate* popCrate(int sN){
	struct stack* s = &stacks[sN];
	s -> size --;
	struct crate** old = s -> items;
	struct crate* ret = old[s -> size];
	s -> items = (struct crate**)malloc(sizeof(struct crate*) * s -> size);
	for (int x = 0; x < s -> size; x ++){
		s -> items[x] = old[x];
	}
	free(old);
	return ret;
}


struct crate* newCrate(char name){
	struct crate* ret = (struct crate*)malloc(sizeof(struct crate));
	ret -> name = name;
	ret -> stack = -1;
	ret -> pos = -1;
	return ret;
}


int getNumberFrom(FILE* file){
	char* buf = malloc(1); // Look, I hate it just as much as you do, but this is C and we shall FIGHT!
	int len = 0;
	while (true){
		char chr = fgetc(file);
		if (feof(file) || chr < '0' || chr > '9'){
			break;
		}
		buf = strAppend(buf, len, chr);
		len ++;
	}
	buf = strAppend(buf, len, 0);
	return atoi(buf);
}


void printStack(int sN){
	struct stack s = stacks[sN];
	if (s.size > 0){
		printf("\n");
	}
	printf(":");
	for (int x = 0; x < s.size; x ++){
		printf("%c", s.items[x] -> name);
	}
}

void printAll(){
	for (int x = 0; x < 10; x ++){
		printStack(x);
	}
	printf("\n");
}


int main(){
	FILE* file = fopen("day5input", "r");
	for (int x = 0; x < 10; x ++){
		stacks[x].size = 0; // Init
	}
	int curS = 0;
	while (true){
		char chr = fgetc(file); // Purge [
		chr = fgetc(file);
		if (chr == '1'){
			break;
		}
		else if (chr != ' '){
			struct crate* c = newCrate(chr);
			insertCrate(curS, c, 0);
		}
		fgetc(file); // Purge ]
		chr = fgetc(file); // Purge whitespace
		curS ++;
		if (chr == '\n'){
			curS = 0;
		}
	}
	getLine(file); // Purge the numbers
	getLine(file); // Purge the empty line
	while (true){
		if (feof(file)){
			break;
		}
		fgetc(file); // m
		fgetc(file); // o
		fgetc(file); // v
		fgetc(file); // e
		fgetc(file); // <whitespace>
		// For the record I know what the better solution is and am merely far too lazy to implement it.
		// Also I know this is going to annoy ryleu, which is very much worth it ;)
		int quantity = getNumberFrom(file);
		fgetc(file); // f
		fgetc(file); // r
		fgetc(file); // o
		fgetc(file); // m
		fgetc(file); // <whitespace>
		int source = getNumberFrom(file) - 1;
		fgetc(file); // t
		fgetc(file); // o
		fgetc(file); // <whitespace>
		int to = getNumberFrom(file) - 1;
		for (int x = 0; x < quantity; x ++){
			if (stacks[source].size > 0){
				int insertPos = stacks[to].size - x;
				insertCrate(to, popCrate(source), insertPos);
			}
			else {
				printf("FIAL BAD OOWOWOOTOOT");
			}
		}
		printAll();
	}
	for (int x = 0; x < 10; x ++){
		if (stacks[x].size > 0){
			printf("%c\n", popCrate(x) -> name);
		}
	}
	return 127;
}
