#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 8400

void findContact(const char* userNumber, char list[MAX_LENGTH+1]) {
    bool foundAny = false;

    for (int index = 0; list[index] != '\0'; index++) {
        int index02;

        for (index02 = 0; index02 < strlen(userNumber); index02++) {
            if (list[index + index02] != userNumber[index02]) {
                break;
            }
        }

        if (index02 == strlen(userNumber)) {
            foundAny = true;

            int lineStart = index;
            while (lineStart > 0 && list[lineStart - 1] != '\n') {
                lineStart--;
            }

            int lineEnd = index;
            while (list[lineEnd] != '\n' && list[lineEnd] != '\0') {
                lineEnd++;
            }

            for (int i = lineStart; i < lineEnd; i++) {
                putchar(list[i]);
            }
            printf("\n");

            index = lineEnd;
        }
    }

    if (!foundAny) {
        printf("Not found.\n");
    }
}

bool isValid(const char* userNumber){
    bool valid = true; 
    int index = 0;

    while(userNumber[index] != '\0'){
        if(userNumber[index] <= '9' && userNumber[index] >= '0'){
            valid = true;
        } else{
            valid = false;
            break;
        }
        index++;
    }

    return valid;

}

int main(int argc, char const *argv[])
{
    int character;
    int index = 0;
    char list[MAX_LENGTH+1];

    while((character = getchar()) != EOF){
        if(index < MAX_LENGTH){
            list[index++] = character;
        } else{
            break;
        }
    }

    list[index] = '\0';

    switch (argc)
    {
    case 2:
        const char* userNumber = argv[1];
        int index = 0;

        if(isValid(userNumber) != 0){
           findContact(userNumber, list); 
        } else {
            printf("Error occurred: Please provide valid input (0-9)\n");
        }
        

        break;
    
    case 1:
        printf("%s", list);
        printf("\n");

        break;

    default:
        printf("Error occurred: Too many arguments provided! Try again with one or two arguments only!\n");
        break;
    }

    return 0;
}
