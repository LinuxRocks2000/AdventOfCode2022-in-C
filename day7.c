#include "tylerLIB.h"


struct File {
	int size;
	char* name;
	struct File* next;
	struct Directory* parent;
};


struct Directory {
	char* name;
	struct Directory* firstDir;
	struct File* firstFile;
	struct Directory* next; // Linked List
	struct Directory* parent; // Tree style linked list. Swaous I know.
};


struct File* newFile(char* name, int size){
	struct File* thing = malloc(sizeof(struct File));
	memset(thing, 0, sizeof(struct File)); // Zero it
	thing -> size = size;
	thing -> name = name;
	return thing;
}


struct File* addFile(struct Directory* dir, char* name, int size){
	struct File* thing = newFile(name, size);
	if (dir -> firstFile){
		struct File* pos = dir -> firstFile;
		while (pos -> next){
			pos = pos -> next;
		}
		pos -> next = thing;
	}
	else{
		dir -> firstFile = thing;
	}
	thing -> parent = dir;
	return thing;
}


struct Directory* newDirectory(char* name){
	struct Directory* ret = malloc(sizeof(struct Directory));
	memset(ret, 0, sizeof(struct Directory));
	ret -> name = name;
	printf("Created new directory with name %s\n", name);
	return ret;
}


struct Directory* addDirectory(struct Directory* parent, char* name){
	struct Directory* ret = newDirectory(name);
	if (parent -> firstDir){
		struct Directory* pos = parent -> firstDir;
		while (pos -> next){
			pos = pos -> next;
		}
		pos -> next = ret;
	}
	else{
		parent -> firstDir = ret;
	}
	ret -> parent = parent;
	return ret;
}


void printDir(struct Directory* dir){
	struct Directory* pos = dir -> firstDir;
	printf("Printing directory '%s'\n", dir -> name);
	while (pos){
		printf("dir %s\n", pos -> name);
		pos = pos -> next;
	}
	struct File* fPos = dir -> firstFile;
	while (fPos){
		printf("file %s\n", fPos -> name);
		fPos = fPos -> next;
	}
}


int measureDir(struct Directory* dir){
	struct Directory* pos = dir -> firstDir;
	int total = 0;
	while (pos){
		total += measureDir(pos);
		pos = pos -> next;
	}
	struct File* fPos = dir -> firstFile;
	while (fPos){
		total += fPos -> size;
		fPos = fPos -> next;
	}
	return total;
}


int curUnused = 0;


int treeWalk(struct Directory* dir, int* cBest){
	struct Directory* pos = dir;
	int total = -1;
	while (pos){
		int dirSize = measureDir(pos);
		if (dirSize < cBest[0] && curUnused + dirSize >= 30000000){
			cBest[0] = dirSize;
			total = dirSize;
		}
		int r = treeWalk(pos -> firstDir, cBest);
		if (r > 0){
			total = r;
		}
		pos = pos -> next;
	}
	return total;
}


int main(){
	FILE* file = fopen("day7input", "r");
	int mode = 0;
	struct Directory* root = newDirectory(""); // Root Directory /.
	struct Directory* cwd = root;
	while (true){
		if (feof(file)){
			break;
		}
		char* line = getLine(file);
		int len;
		char** splitted = splitString(line, ' ', &len);
		if (len > 0){
			if (strcmp(splitted[0], "$") == 0){
				if (strcmp(splitted[1], "cd") == 0){
					if (strcmp(splitted[2], "..") == 0){
						cwd = cwd -> parent;
					}
					else if (strcmp(splitted[2], "/") == 0){
						cwd = root;
					}
					else{
						struct Directory* pos = cwd -> firstDir;
						while (pos){
							if (strcmp(splitted[2], pos -> name) == 0){
								cwd = pos;
								break;
							}
							pos = pos -> next;
						}
					}
				}
			}
			else{
				if (len == 2){
					if (strcmp(splitted[0], "dir") == 0){ // it's a directory
						addDirectory(cwd, splitted[1]);
					}
					else{ // it's a file. lame.
						addFile(cwd, splitted[1], atoi(splitted[0]));
					}
				}
			}
		}
	}
	curUnused = 70000000 - measureDir(root);
	int cBest = 100000000;
	printf("Answer: %d\n", treeWalk(root, &cBest));
	return 127;
}
