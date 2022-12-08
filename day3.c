#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


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


char searchSimilar(char* first, char* last, int len){
	for (int x = 0; x < len; x ++){
		for (int y = 0; y < len; y ++){
			if (first[x] == last[y]){
				return first[x];
			}
		}
	}
	return 0;
}


int getPriority(char thing){
	if (thing >= 'a' && thing <= 'z'){
		return (thing + 1) - 'a';
	}
	else if (thing >= 'A' && thing <= 'Z'){
		return (thing + 27) - 'A';
	}
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


int main(){
	FILE* file = fopen("day3input", "r");
	char* buf = malloc(1);
	int bufLen = 0;
	
	int retSum = 0;
	while (true){
		char* first = getLine(file);
		char* second = getLine(file);
		char* last = getLine(file);
		if (feof(file)){
			break;
		}
		printf("%s : %s : %s\n", first, second, last);
		char sim;
		for (int x = 0; x < strLen(first); x ++){
			for (int y = 0; y < strLen(second); y ++){
				for (int z = 0; z < strLen(last); z ++){
					if (first[x] == second[y] && second[y] == last[z]){
						sim = first[x];
					}
				}
			}
		}
		printf("%c\n", sim);
		retSum += getPriority(sim);
	}
	
	printf("%d\n", retSum);
}
