#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void strMerge(char* src, int len, char* into){
	for (int x = 0; x < len; x ++){
		into[x] = src[x];
	}
}


char** appendToStringList(char** init, int len, char* thing){
	char** ret = malloc((len + 1) * sizeof(char*));
	memcpy(ret, init, len * sizeof(char*));
	ret[len] = thing;
	free(init);
	return ret;
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


char** splitString(char* string, char split, long long* length){
	int len = 0;
	int bufLen = 0;
	char* buf = malloc(1); // Hate this? So do I!
	char** ret = malloc(1);
	for (int i = 0; string[i] != 0; i ++){
		if (string[i] == split){ // if it's reached a terminating character do the append routine
			buf = strAppend(buf, bufLen, 0); // Terminating character to make c strings happy
			ret = appendToStringList(ret, len, buf);
			len ++;

			bufLen = 0;
			buf = malloc(1); // Don't free buf! Otherwise we'll have segfaults.
		}
		else{
			buf = strAppend(buf, bufLen, string[i]);
			bufLen ++;
		}
	}
	buf = strAppend(buf, bufLen, 0); // Terminating character to make c strings happy
	ret = appendToStringList(ret, len, buf); // There's always gonna be *summat* in that thar buff'r
	len ++;
	length[0] = len; // I don't want to figure out how to do this properly
	return ret;
}


void purgeUntil(FILE* file, char thang){
	char chr = fgetc(file);
	while (chr != thang && chr != EOF){
		chr = fgetc(file);
	}
}

