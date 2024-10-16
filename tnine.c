#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Program has to handle 42 contacts that have 2 lines and a maximum of 100 characters each
#define MAX_LENGTH 8400

int stringLength(const char* userNumber) {
    int userNumberLength = 0;

    while (userNumber[userNumberLength] != '\0') {
        userNumberLength++;
    }

    return userNumberLength;
}

bool isValid(const char* userNumber) {
    bool valid = true;
    int length = stringLength(userNumber);

    for (int position = 0; position < length; position++) {
        if (userNumber[position] >= '0' && userNumber[position] <= '9') {
            continue;
        } else {
            valid = false;
            return valid;
        }
    }

    return valid;
}

int findNumber(const char* userNumber, char line[MAX_LENGTH+1]) {
    int lineCount = 0;
    int index = 0;
    int userNumberLength = stringLength(userNumber);
    char previousLine[MAX_LENGTH+1] = ""; // To store the previous line

    int character;
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            line[index] = '\0';
            lineCount++;

            // Check if the current line contains the userNumber
            int found = 0;
            for (int i = 0; i <= index - userNumberLength; i++) {
                int match = 1;
                for (int j = 0; j < userNumberLength; j++) {
                    if (line[i + j] != userNumber[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("Line above: %s\n", previousLine);
                printf("Matching line: %s\n", line);
                return lineCount;
            }

            // Save the current line as the previous line and reset the index
            snprintf(previousLine, MAX_LENGTH, "%s", line);
            index = 0;
        } else {
            if (index < MAX_LENGTH) {
                line[index++] = character;
            }
        }
    }

    printf("Not found.\n");
    return 0;
}

int main(int argc, char *argv[]) {
    char line[MAX_LENGTH+1];
    int character;
    int index = 0; 

    switch (argc) {
        case 2: {
            const char* userNumber = argv[1];

            if (isValid(userNumber)) { 
                findNumber(userNumber, line);
            } else {
                printf("Error occurred: Please provide valid input (0-9)\n");
            }

            break;
        }
        case 1: {
            while ((character = getchar()) != EOF) {
                if (index < MAX_LENGTH) {
                    line[index++] = character;
                } else {
                    break;
                }
            }

            line[index] = '\0';

            printf("%s", line);
            printf("\n");

            break;
        }
        default:
            printf("Error occurred: Too many arguments provided! Try again with one or two arguments only!\n");
            break;
    }

    return 0;
}

