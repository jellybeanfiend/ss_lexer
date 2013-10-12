// Eric Bousquet, Sevena Skeels
// COP 3402 Systems Software
// Professor Montagne
// October 8 2013
// Homework 2: Lexical Analysis (Scanner)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions
#define NUMRESERVED 13      // Number of reserved words
#define NUMSYMBOLS 13       // Number of special symbols
#define INTMAX 32767        // Maximum integer value
#define CHARMAX 11          // Maximum number of chars for idents
#define NESTMAX 5           // Maximum depth of block nesting
#define STRMAX 256          // Maximum length of strings
#define DIGITMAX 5 			// Maximum number of digits in a number

// Structs
typedef struct{
	int lexeme;
	int tokentype;
}lexeme;

// Globals
// Defining token types
typedef enum {
	nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,
	slashsym = 7, oddsym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
	gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
	semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22,
	ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28,
	intsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33
} token_type;

// Defining reserved words
char *word[] = { "const", "int", "procedure", "call", "begin", "end", "if",
							"then", "else", "while", "do", "read", "write" };
// Defining word symbols integer array
// Example: wordsym[2] contains reference to "procsym" which will output 30.
int wordsym[] = { constsym, intsym, procsym, callsym, beginsym, endsym, ifsym,
							 thensym, elsesym, whilesym, dosym, readsym, writesym };
// Defining reserved symbols
char symbols[] = { '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':' };

// Defining symbol symbols integer array
// Example: symbolsym[2] contains reference to "multsym" which will output 6.
int symbolsym[] = { plussym, minussym, multsym, slashsym, lparentsym, rparentsym,
							  eqlsym, commasym, periodsym, lessym, gtrsym, semicolonsym, becomessym };

// Position of the program currently being processed
int currentpos;
							  
void comments(char* program);
int alpha(char* program, int save);
int isReserved(char* str);
int number(char* program, int save);

// Main function
int main() {

    // File pointers for input and output files
    FILE *input = fopen("InputFile.txt", "r");
    FILE *output = fopen("OutputFile.txt", "w");

	char program[10000];
	int c, length = 0;
	// Save the program in the input file to an array
	while((c = fgetc(input)) != EOF){
		program[length] = c;
		length++;
	}
	
	// Process each character of the program array
	while(currentpos < length-1){
		
		int save = currentpos;
		// Ident or Reserved Word - must start with alpha character
		if(isalpha(program[currentpos])){
			int success = alpha(program, save);
			if(!success){
				printf("ERROR");
			}
		}
		
		else if(isdigit(program[currentpos])){
			int success = number(program, save);
			if(!success){
				printf("ERROR");
			}
		}
		// other cases here
		else
			currentpos++;
		
	}
	
    // Closing input/output files
    fclose(input);
    fclose(output);

    return 0;
}

// Finds comments in the program
void comments(char* program){
	// If the current character is a / and the next character is a *, we got ourselves a comment!
	if(program[currentpos] == '/' && program[currentpos+1] == '*'){
		// Set the current position to be after the /*
		currentpos += 2;
		// Iterate through each character in the comment until the ending */ is found
		while(program[currentpos] != '*' && program[currentpos+1] != '/'){
			printf("%c", program[currentpos]);
			currentpos++;
		}
		// On offset the position for the *, since the main loop will increase the currentpos by 1 after this function call
		currentpos+=1;
	}
}

// Handles tokens that start with a letter: reserved words and identifiers
int alpha(char* program, int save){
	// Character after the initial alpha character
	currentpos++;
	// Keep looking forward until a character is not alphanumeric
	while(isalnum(program[currentpos])){
		currentpos++;
	}
	// Get the length of the string by subtracting the first character
	// position from the last character position in the program array
	int strlength = currentpos - save;
	// String is too long - this is an error!
	if(strlength > CHARMAX)
		return 0;
	// Copy the string from the program array into a new char array
	// so that it can be compared to the reserved words
	char str[strlength+1];
	strncpy(str, &program[save], strlength);
	str[strlength] = '\0';
	int reserved = isReserved(str);
	if(reserved != -1){
		printf("%s is reserved\n", str);
	}
	else
		printf("%s is an ident\n", str);
	return 1;
}

int isReserved(char* str){
	int i;
	for(i = 0; i < NUMRESERVED; i++){
		if(strcmp(str, word[i]) == 0){
			return i;
		}
	}
	return -1;
}


int number(char* program, int save){
	// Convert the starting digit from a char to an int
	int num = program[save]-'0';
	// Advance to the next character after the saved character
	currentpos++;
	// Keep advancing until a non-digit character is found
	while(isdigit(program[currentpos])){
		// Adjust the number so that the new number is in the ones place
		num = num*10 + (program[currentpos]-'0');
		currentpos++; 
	}
	// Error - Probably an ident that starts with a number!
	if(isalpha(program[currentpos]))
		return 0;
	// Error - Number is too big!
	if((currentpos - save) > DIGITMAX)
		return 0;
	printf("%d", num);
	return 1;
}
