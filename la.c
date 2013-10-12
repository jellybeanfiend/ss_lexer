// Eric Bousquet, Sevena
// COP 3402 Systems Software
// Professor Montagne
// October 8 2013
// Homework 2: Lexical Analysis (Scanner)

#include <stdio.h>
#include <stdlib.h>

// Definitions
#define NUMRESERVED 13      // Number of reserved words
#define NUMSYMBOLS 13       // Number of special symbols
#define INTMAX 32767        // Maximum integer value
#define CHARMAX 11          // Maximum number of chars for idents
#define NESTMAX 5           // Maximum depth of block nesting
#define STRMAX 256          // Maximum length of strings

// Globals

// Position of the program currently being processed
int currentpos;

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
							  
void comments(char* program);

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
		i++;
	}
	
	// Process each character of the program array
	while(currentpos < length-1){
		comments(program);
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
	if(program[currentpos] == '/' && program[currentpos++] == '*'){
		// Iterate through each character in the comment until the ending */ is found
		while(program[currentpos++] != '*' && program[currentpos+1] != '/'){
			currentpos++;
		}
	}
}
