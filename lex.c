#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

// Function to check if a given string is a keyword
int isKeyword(char* token) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    int i, flag = 0;

    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], token) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

// Function to check if a given character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=><!&|^~?:";

    int i, flag = 0;

    for (i = 0; i < strlen(operators); ++i) {
        if (ch == operators[i]) {
            flag = 1;
            break;
        }
    }

    return flag;
}

// Function to check if a given string is an integer
int isInteger(char* token) {
    int i, flag = 1;

    for (i = 0; i < strlen(token); ++i) {
        if (!isdigit(token[i])) {
            flag = 0;
            break;
        }
    }

    return flag;
}

// Function to check if a given string is a floating point number
int isFloat(char* token) {
    int i, flag = 1, decimalPointCount = 0;

    for (i = 0; i < strlen(token); ++i) {
        if (!isdigit(token[i])) {
            if (token[i] == '.') {
                decimalPointCount++;

                if (decimalPointCount > 1) {
                    flag = 0;
                    break;
                }
            } else {
                flag = 0;
                break;
            }
        }
    }

    return flag;
}

// Function to write a token and its type to the output file
void writeToken(FILE* outputFile, char* token, char* tokenType) {
    fprintf(outputFile, "%-15s %s\n", tokenType, token);
}

int main() {
    FILE* inputFile;
    FILE* outputFile;
    char inputFileName[100], outputFileName[100];
    char line[1000];
    char token[MAX_TOKEN_LENGTH];
    char tokenType[15];
    int i, tokenLength = 0;
    int keywordCount = 0, operatorCount = 0, integerCount = 0, floatCount = 0, identifierCount = 0, punctuationCount = 0;

    // Get input file name from user
    printf("Enter input file name: ");
    scanf("%s", inputFileName);

    // Get output file name from user
    printf("Enter output file name: ");
    scanf("%s", outputFileName);

    // Open input file
    inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    //
// Open output file
outputFile = fopen(outputFileName, "w");

if (outputFile == NULL) {
    printf("Error opening output file.\n");
    return 1;
}

// Read input file line by line
while (fgets(line, sizeof(line), inputFile)) {
    i = 0;

    // Traverse the line character by character
    while (i < strlen(line)) {
        // If current character is a space or a newline, ignore it
        if (line[i] == ' ' || line[i] == '\n') {
            i++;
            continue;
        }

        // If current character is an operator, write it to output file
        if (isOperator(line[i])) {
            token[0] = line[i];
            token[1] = '\0';
            writeToken(outputFile, token, "Operator");
            operatorCount++;
            i++;
            continue;
        }

        // If current character is a digit, read the whole number and write it to output file
        if (isdigit(line[i])) {
            tokenLength = 0;

            while (isdigit(line[i]) || line[i] == '.') {
                token[tokenLength++] = line[i++];
            }

            token[tokenLength] = '\0';

            if (isInteger(token)) {
                writeToken(outputFile, token, "Integer");
                integerCount++;
            } else if (isFloat(token)) {
                writeToken(outputFile, token, "Float");
                floatCount++;
            } else {
                printf("Invalid number: %s\n", token);
            }

            continue;
        }

        // If current character is an alphabet, read the whole word and determine its type
        if (isalpha(line[i]) || line[i] == '_') {
            tokenLength = 0;

            while (isalnum(line[i]) || line[i] == '_') {
                token[tokenLength++] = line[i++];
            }

            token[tokenLength] = '\0';

            if (isKeyword(token)) {
                writeToken(outputFile, token, "Keyword");
                keywordCount++;
            } else {
                writeToken(outputFile, token, "Identifier");
                identifierCount++;
            }

            continue;
        }

        // If current character is a punctuation mark, write it to output file
        if (ispunct(line[i])) {
            token[0] = line[i];
            token[1] = '\0';
            writeToken(outputFile, token, "Punctuation");
            punctuationCount++;
            i++;
            continue;
        }

        // If current character is none of the above, it is an invalid character
        printf("Invalid character: %c\n", line[i]);
        i++;
    }
}

// Write token counts to output file
fprintf(outputFile, "\nToken counts:\n");
fprintf(outputFile, "Keywords: %d\n", keywordCount);
fprintf(outputFile, "Operators: %d\n", operatorCount);
fprintf(outputFile, "Integers: %d\n", integerCount);
fprintf(outputFile, "Floats: %d\n", floatCount);
fprintf(outputFile, "Identifiers: %d\n", identifierCount);
fprintf(outputFile, "Punctuation: %d\n", punctuationCount);

// Close input and output files
fclose(inputFile);
fclose(outputFile);

return 0;
}