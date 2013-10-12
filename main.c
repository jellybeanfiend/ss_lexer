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

// Structs
typedef struct nameRecord {
    int kind;                   // const = 1, var = 2, proc = 3
    char name[10];              // Name (max length: 11 chars)
    int val;                    // Number (ASCII value)
    int level;                  // L level
    int addr;                   // M address
    struct nameRecord *next;    // Linked list allocator
} NameRecordTable;

// Function prototypes
char* readLine(FILE* input);

// Main function
int main() {

    // File pointers for input and output files
    FILE *input = fopen("InputFile.txt", "r");
    FILE *output = fopen("OutputFile.txt", "w");

    // Processing input file if it exists
    if (input != NULL) {
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
        char *word[NUMRESERVED] = { "const", "int", "procedure", "call", "begin", "end", "if",
                                    "then", "else", "while", "do", "read", "write" };

        // Defining word symbols integer array
        // Example: wordsym[2] contains reference to "procsym" which will output 30.
        int wordsym[NUMRESERVED] = { constsym, intsym, procsym, callsym, beginsym, endsym, ifsym,
                                     thensym, elsesym, whilesym, dosym, readsym, writesym };

        // Defining reserved symbols
        char *symbols[NUMSYMBOLS] = { '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':' };

        // Defining symbol symbols integer array
        // Example: symbolsym[2] contains reference to "multsym" which will output 6.
        int symbolsym[NUMSYMBOLS] = { plussym, minussym, multsym, slashsym, lparentsym, rparentsym,
                                      eqlsym, commasym, periodsym, lessym, gtrsym, semicolonsym, becomessym };


        char *storedLine = readLine(input);
        int i = 0;

        // Debugging: just printing out lines as stored
        while(storedLine != NULL) {
            i = 0;
            while (storedLine[i] != '\0') {
                printf("%c", storedLine[i]);
                i++;
            }
            printf("\n");
            storedLine = readLine(input);
        }
    }
    else {
        // ERROR: Input file not found
        printf("ERROR: Input file not found.\n");
    }

    // Closing input/output files
    fclose(input);
    fclose(output);

    return 0;
}

// Creates a new entry for the name table
char* readLine(FILE* input) {

    int i = 0;

    // What the input file's pointer is currently pointing at
    char pointerChar = getc(input);

    // Stores contents of a line of PL/0 code
    char line[STRMAX];

    // Initializing char array
    for (i = 0; i < STRMAX; i++) {
        line[i] = NULL;
    }

    i = 0;
    while (pointerChar != '\n' && pointerChar != '\0') {
        // Adding to the line char array, so long as newline or EOF hasn't been read
        line[i] = pointerChar;
        pointerChar = getc(input);
        i++;
    }

    return line;
}
