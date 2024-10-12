#include <stdio.h>
#include <stdlib.h>

// Program has to handle 42 contacts that have 2 lines and a maximum of 100 characters each
#define MAX_LENGTH 8400

int stringLength(const char* userNumber){

    int userNumberLength = 0;

    while (userNumber[userNumberLength] != '\0') {
        userNumberLength++;
    }
}

int findNumber(const char* userNumber, char line[MAX_LENGTH+1]) {
    int lineCount = 0;
    int index = 0;
    int userNumberLength = 0;

    userNumberLength = stringLength(userNumber);

    int character;
    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            line[index] = '\0';
            lineCount++;

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
                return lineCount;
            }

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
            int foundMatchLine = findNumber(userNumber, line);

            if (foundMatchLine > 0) {
                printf("Match found on line number %d\n", foundMatchLine);
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
            printf("Too many arguments provided! Try again and put one or two only!\n");
            break;
    }

    return 0;
}
