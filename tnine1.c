#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100      //The maximum length of a string that can be stored
#define MAX_CONTACTS 42     //The maximum number of contacts
#define MAX_INFO 2          //The number of pieces of information stored per contact (name, number)

//FINDS A SUBSTRING IF PRESENT
bool isSubstring(const char* substring, char* string) {
    //Loops through all characters in the provided string
    for(int index = 0; string[index] != '\0'; index++){
        //If any character in the string matches the first character of the substring
        if(string[index] == substring[0]){
            bool match = true;
            //If they match, it checks if the entire substring is present
            for(int index02 = 1; index02 < strlen(substring); index02++){
                //If it finds different character, match = false and breaks out of the loop
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

//FINDS THE RELATIVE CONTACT BASED ON THE USER NUMBER
void findContact(const char* userNumber, char contacts[MAX_CONTACTS][MAX_INFO][MAX_LENGTH]) {

    bool found = false;

    for(int position = 0; position < 42; position++){
        if(isSubstring(userNumber, contacts[position][1])){
            printf("%s, %s\n", contacts[position][0], contacts[position][1]);
            found = true;
        }
    }

    if(!(found)){
        printf("Not found.\n");
    }

}

//CHECKS IF THE INPUT IS VALID 
bool isValid(const char* userNumber) {
    int index = 0;
    
    //Checks if the provided number is valid (no symbols or characters)
    while (userNumber[index] != '\0') {
        if (userNumber[index] < '0' || userNumber[index] > '9') {
            //Invalid
            return false;
        }
        index++;
    }
    //Valid
    return true;
}

//MAIN FUNCTION
int main(int argc, char const *argv[]) {
    char contacts[MAX_CONTACTS][MAX_INFO][MAX_LENGTH] = {{{0}}};
    int row = 0;
    int character;
    int column = 0;

    //Loops through each character until it reaches EOF - End Of File
    while ((character = getchar()) != EOF && row < MAX_CONTACTS) {
        if (character != '\n') {
            //Inserts the character into the correct column: 0 - name, 1 - tel. number
            contacts[row][column][strlen(contacts[row][column])] = character; 
        } else {
            //Adds the null terminator and increments the column to maintain the correct order
            contacts[row][column][strlen(contacts[row][column])] = '\0'; 
            column++; 
            //If the column reaches number 2, it resets to 0
            if (column == MAX_INFO) {
                column = 0;
                row++; 
            }
        }
    }

    //Switch statement that handles the number of command-line arguments
    switch (argc) {
    //If a number is provided via stdin, it checks its validity and searches through the contacts
    case 2: {
        //userNumber stores given number on stdin
        const char* userNumber = argv[1];

        if(isValid(userNumber)){
            findContact(userNumber, contacts);
        } else{
            printf("Error occurred: Please provide valid input on stdin (0-9).\n");
        }

        break;
    }
    //If no number is provided, it prints all the contacts 
    case 1: {
        for (int i = 0; i < row+1; i++) {
            printf("%s, %s\n", contacts[i][0], contacts[i][1]);
        }
        break;
    }
    //If more than one number is provided, it prints an Error
    default:
        printf("Error occurred: Too many arguments provided! Try again with one or two arguments only!\n");
        break;
    }

    return 0;
}


