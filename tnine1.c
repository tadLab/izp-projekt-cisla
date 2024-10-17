#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100      //Maximum length of string that can be stored  
#define MAX_CONTACTS 42     //Maximum contacts 
#define MAX_INFO 2          //Number of informations stored in contacts - name, number

//Finds substring if presents return 1 or 0
bool isSubstring(char* substring, char* string) {
    for(int index = 0; string[index] != '\0'; index++){
        if(string[index] == substring[0]){
            bool match = true;
            for(int index02 = 1; index02 < strlen(substring); index02++){
                if(string[index+index02] != substring[index02]){
                    match = false;
                    break;
                } 
            }

        if(match){
            return true;
        }
        
        } 
    }

    return false;

}

/*void findContact(const char* userNumber, char contacts[MAX_CONTACTS][MAX_INFO][MAX_LENGTH]) {

    bool found = false;
    int contact = 0;
    int info = 0;

    for(int position = 0; position < MAX_CONTACTS; position++){
        if(strcmp(contacts[contact][info][position], userNumber) == 0){
            
        }
    }

    if(found == false){
        printf("Not found.\n");
    }

}*/

//Checks if the input is valid 
bool isValid(const char* userNumber) {
    int index = 0;
    
    //Checking if the provided number is Valid (no symbols or characters)
    while (userNumber[index] != '\0') {
        if (userNumber[index] < '0' || userNumber[index] > '9') {
            //Non-Valid
            return false;
        }
        index++;
    }
    
    //Valid
    return true;
}

int main(int argc, char const *argv[]) {
    char contacts[MAX_CONTACTS][MAX_INFO][MAX_LENGTH] = {{{0}}};
    int row = 0;
    int character;
    int column = 0;

    //Loop that goes through every character until it reaches EOF - End Of File
    while ((character = getchar()) != EOF && row < MAX_CONTACTS) {
        if (character != '\n') {
            //Inserts character in the right column 0 - name, 1 - tel. number
            contacts[row][column][strlen(contacts[row][column])] = character; 
        } else {
            //Inserts the end of the string and increments column, to keep the right order
            contacts[row][column][strlen(contacts[row][column])] = '\0'; 
            column++; 
            //If the column reaches number 2, it restarts and set to 0
            if (column == MAX_INFO) {
                column = 0;
                row++; 
            }
        }
    }

    //Switch that controls number of arguments
    switch (argc) {
    //When there is a number on stdin it checks its validity and searches through the contacts
    case 2: {
        //userNumber stores given number on stdin
        const char* userNumber = argv[1];

        char* string = "Ahoj ja jsem Tade.";
        char* substring = "jak";

        if(isSubstring(substring, string)){
            printf("Its substring!\n");
        } else{
            printf("Its not substring!\n");
        }
       

        /*if (isValid(userNumber)) {
            findContact(userNumber, contacts);
        } else {
            printf("Error occurred: Please provide valid input (0-9)\n");
        }*/
        break;
    }
    //When there is no number provided it prints all the contacts 
    case 1: {
        //
        for (int i = 0; i < row+1; i++) {
            printf("%s\n", contacts[i][0]);
            printf("%s\n", contacts[i][1]);
        }
        break;
    }
    //When there is more than that number provided it prints Error
    default:
        printf("Error occurred: Too many arguments provided! Try again with one or two arguments only!\n");
        break;
    }

    return 0;
}


