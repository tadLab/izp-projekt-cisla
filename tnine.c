#include <stdio.h>
#include <stdlib.h>


//Program has to handle 42 contacts that has 2 lines and maximum of 100 characters
#define MAX_LENGTH 8400

int main(int argc, char *argv[]) {

    int userNumber;
    int character;
    char line[MAX_LENGTH+1];
    int index = 0;

    switch (argc)
    {
    case (2):

        userNumber = atoi(argv[1]);

        printf("Argument that has to be found in the text document is %d\n", userNumber);

        break;
    case (1):
        while((character = getchar()) != EOF){
            line[index++] = character;
        }

        line[index] = '\0';

        printf("%s", line);
        printf("\n");

        break;
    default:

        printf("Too many arguments provided! Try again and put one or two only!\n");

        break;
    }

    return 0;
}