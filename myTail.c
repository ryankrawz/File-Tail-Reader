// File Tail Reader
// Ryan Krawczyk (CSCI227103)

/*
Examples of command line input:
./myTail alpha.txt 8
./myTail intTail.c

Defaults to tail size of 10 if second arg not provided
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 80

char **makeArray(int n);
void storeLines(char **p, char *fName, int n);
char *readALine();
void genTail(char **p, int n);
void shift(char **p, int n, char *next);

FILE *fp;

int main(int argc, char *argv[]) {
	char *name = argv[1];
	int size;
	if (argv[2] == NULL)				size = 10;
	else								size = atoi(argv[2]);
	char **lines = makeArray(size);
	storeLines(lines, name, size);
	genTail(lines, size);
	free(lines);
	fclose(fp);
	return 0;
}

// Dynamically allocates memory for char pointer array
char **makeArray(int n) {
	char **lineArr = (char **) malloc(n * sizeof(long double));
	return lineArr;
}

// Changes pointer values in array to lines read in
void storeLines(char **p, char *fName, int n) {
	fp = fopen(fName, "r");
	int count = 0;
	char *ic = readALine();
	while (ic != NULL) {
		if (count >= n) 	shift(p, n, ic);
		else				*(p + count) = ic;
		count++;
		ic = readALine();
	}
}

// Retrieves line from input stream in form of char array
char *readALine() {
	char *nextLine = (char *) malloc(MAX * sizeof(char));
	nextLine = fgets(nextLine, MAX, fp);
	if (nextLine == NULL) {
		free(nextLine);
		return NULL;
	}
	else {
		int len = strlen(nextLine);
		nextLine[len - 1] = '\0';
		return nextLine;
	}
}

// Outputs final lines of file and size indicated by user
void genTail(char **p, int n) {
	char **i;
	printf("\n");
	for (i = p; i < p + n; i++) {
		printf("%s\n", *i);
		free(*i);
	}
	printf("\n");
}

// Moves addresses in array forward and inserts subsequent char array
void shift(char **p, int n, char *next) {
	char **i;
	free(*p);
	for (i = p; i < p + (n - 1); i++) {
		*i = *(i + 1);
	}
	*(p + (n - 1)) = next;
}

