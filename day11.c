#include "tylerLIB.h"


struct Item {
	long long num;
	struct Item* next;
};


struct Operation {
	char mode;
	long long num;
};


struct Monkey {
	struct Item* items; // linked list. yey.
	long long divisbler;
	struct Operation* operation;
	long long tossif; // if the test evaluates to true, throw here
	long long tosselse; // else here
	long long inspected;
	long long number;
};


struct Monkey monkeys[10]; // we probably won't ever need to deal with more than 10 monkeys; this makes life easier


long long readNextNumber(FILE* file){ // purge until it hits a number
	char* thing = malloc(1);
	long long len = 0;
	char chr = fgetc(file);
	while (!((chr >= '0' && chr <= '9') || chr == '-' || chr == '.')){
		chr = fgetc(file);
		if (chr == EOF){
			printf("ERROR: readNextNumber encountered an EOF\n");
			return -2;
		}
	}
	while ((chr >= '0' && chr <= '9') || chr == '-' || chr == '.'){
		thing = strAppend(thing, len, chr);
		len ++;
		chr = fgetc(file);
	}
	ungetc(chr, file);
	long long ret = atoi(thing);
	free(thing);
	return ret;
}


void appendItemTo(long long num, long long thing){
	struct Item* newbie = malloc(sizeof(struct Item));
	newbie -> num = thing;
	newbie -> next = 0;
	struct Item* cur = monkeys[num].items;
	if (cur){
		while (cur -> next){
			cur = cur -> next;
		}
		cur -> next = newbie;
	}
	else{
		monkeys[num].items = newbie;
	}
}


long long applyOperation(long long initial, struct Operation* oper){
	long long operator = oper -> num;
	if (operator == -1){
		operator = initial;
	}
	switch (oper -> mode){
		case '*':
			return initial * operator;
			break;
		case '/':
			return initial / operator;
			break;
		case '+':
			return initial + operator;
			break;
		case '-':
			return initial - operator;
			break;
	};
	return initial; // No-op, if the switch don't nothin'
}


void passItem(struct Monkey* src, struct Monkey* dest, long long newWorry){
	printf("Passing item with worry level %d from monkey %d to monkey %d\n", newWorry, src -> number, dest -> number);
	struct Item* popped = src -> items;
	src -> items = src -> items -> next;
	popped -> num = newWorry;
	popped -> next = 0;
	struct Item* cur = dest -> items;
	if (cur){
		while (cur -> next){
			cur = cur -> next;
		}
		cur -> next = popped;
	}
	else {
		dest -> items = popped;
	}
}


void monkeyRound(long long monkeyNum){
	struct Monkey* monkey = &(monkeys[monkeyNum]);
	struct Item* item = monkey -> items;
	printf("::: MONKEY %d :::\n", monkeyNum);
	while (item){
		long long worry = item -> num;
		printf("Monkey %d inspects %d\n", monkeyNum, worry);
		worry = applyOperation(worry, monkey -> operation);
		printf("Monkey %d applies operation; is now %d\n", monkeyNum, worry);
		//worry = worry / 3; // Because it's a long long, it's gonna round it down
		//printf("Monkey %d applies division; is now %d\n", monkeyNum, worry);
		long long passTo = -1;
		if (worry % monkey -> divisbler == 0){ // If it's *not* divisible
			passTo = monkey -> tossif;
		}
		else{
			passTo = monkey -> tosselse;
		}
		monkey -> inspected ++;
		item = item -> next;
		passItem(monkey, &(monkeys[passTo]), worry);
	}
}


void printMonkey(long long number){
	struct Item* cur = monkeys[number].items;
	while (cur){
		printf("%d,", cur -> num);
		cur = cur -> next;
	}
	printf("\n");
}


long long main(){
	FILE* file = fopen("day11input", "r");
	long long monkeyNumber = 0;
	while (true){
		free(getLine(file)); // purge the monkey number, we're determining that by order
		monkeys[monkeyNumber].items = 0;
		printf("%d\n", monkeyNumber);
		while (true){
			long long num = readNextNumber(file);
			if (num == -2){
				break;
			}
			appendItemTo(monkeyNumber, num);
			printf("Added %d to %d\n", num, monkeyNumber);
			if (fgetc(file) == 10){
				break;
			}
			if (feof(file)){
				break;
			}
		}
		purgeUntil(file, '=');
		fgetc(file); // the whitespace.
		char* line = getLine(file);
		long long len;
		char** splitted = splitString(line, ' ', &len);
		if (len != 3){
			break;
		}
		free(line);
		struct Operation* oper = malloc(sizeof(struct Operation));
		oper -> mode = splitted[1][0];
		if (strcmp(splitted[2], "old") == 0){
			oper -> num = -1;
		}
		else{
			oper -> num = atoi(splitted[2]);
		}
		monkeys[monkeyNumber].operation = oper;
		purgeUntil(file, 'y');
		fgetc(file); // The space
		if (feof(file)){
			break;
		}
		monkeys[monkeyNumber].divisbler = atoi(getLine(file));
		if (feof(file)){
			break;
		}
		monkeys[monkeyNumber].tossif = readNextNumber(file);
		monkeys[monkeyNumber].tosselse = readNextNumber(file);
		monkeys[monkeyNumber].inspected = 0;
		monkeys[monkeyNumber].number = monkeyNumber; // for debugging
		monkeyNumber ++;
		free(getLine(file)); // purge the monkey number, we're determining that by order
		free(getLine(file)); // purge the monkey number, we're determining that by order
	}
	for (long long i = 0; i < 20; i ++){
		for (long long m = 0; m < 10; m ++){
			monkeyRound(m);
		}
	}
	long long max = 0;
	long long second = 0;
	for (long long m = 0; m < 10; m ++){
		if (monkeys[m].inspected > max){
			second = max;
			max = monkeys[m].inspected;
		}
		else if (monkeys[m].inspected > second){
			second = monkeys[m].inspected;
		}
	}
	printf("Max: %d, Second: %d, Result: %d\n", max, second, max * second);
	return 0;
}
