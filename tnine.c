#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 101      //The maximum length of a string that can be stored
#define MAX_CONTACTS 43     //The maximum number of contacts
#define MAX_INFO 2          //The number of pieces of information stored per contact (name, number)

//FUNCTION TO GET CORRESPONDING LETTERS TO NUMBERS
const char* getLetters(char digit) {
    switch (digit) {
        case '2': return "abc";
        case '3': return "def";
        case '4': return "ghi";
        case '5': return "jkl";
        case '6': return "mno";
        case '7': return "pqrs";
        case '8': return "tuv";
        case '9': return "wxyz";
        case '0': return "+";
        default : return "";
    } 
}

//FINDS CONTACT THAT HAS CORRESPONDING LETTERS
bool isInString(char letters[][5], char* string, int lenghtOfNumber) {
    int stringLen = strlen(string);
    
    //Loops contact's name by every character
    for (int i = 0; i < stringLen; i++) {
        //Index, from where looping starts
        int matchIndex = i;  
        bool match = true;   

        //Loops through the groups of letters corresponding to numbers
        for (int j = 0; j < lenghtOfNumber; j++) {
            if (matchIndex >= stringLen) {
                match = false;
                break;
            }
            
            char currentLetter = tolower(string[matchIndex]);
            bool letterFound = false;

            //Checks if the letter of contact's name is relative to the group of letters
            for (int k = 0; letters[j][k] != '\0' ; k++) {
                if (currentLetter == letters[j][k]) {
                    letterFound = true;
                    break;
                }
            }

            if (!letterFound) {
                match = false;
                break;
            }

            //Increment matchIndex to check the next character in the contact's name
            matchIndex++;
        }

        //If the substring is found return true
        if (match) {
            return true;
        }
    }

    //If the substring is not found return false
    return false;
}


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

        //If match is found return true
        if(match){
            return true;
        }
        
        } 
    }

    //If match is not found return false
    return false;

}

//FINDS THE RELATIVE CONTACT BASED ON THE USER NUMBER
void findContact(const char* userNumber, char contacts[MAX_CONTACTS][MAX_INFO][MAX_LENGTH], char letters[][5]) {

    bool found = false;
    int numberLength = strlen(userNumber);

    //Loops through names and numbers of contacts and calls needed functions
    for(int position = 0; position < MAX_CONTACTS; position++){
        if(isSubstring(userNumber, contacts[position][1])){
            //If the input (stdin) isSubstring of contact's number
            printf("%s, %s\n", contacts[position][0], contacts[position][1]);
            found = true;
        } else if (isInString(letters, contacts[position][0], numberLength)){
            //If the input (stdin) corresponding letters are present in the contact's name
            printf("%s, %s\n", contacts[position][0], contacts[position][1]);
            found = true;
        }
        
    }

    if(!(found)){
        printf("Not found\n");
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

    if (index >= MAX_LENGTH){
        //Invalid
        return false;
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

    //Reads contact names and phone numbers from input and stores them
    while ((character = getchar()) != EOF && row < MAX_CONTACTS) {
        if (character != '\n') {
            //Inserts character into the correct column: 0 - name, 1 - number
            contacts[row][column][strlen(contacts[row][column])] = character;
        } else {
            contacts[row][column][strlen(contacts[row][column])] = '\0';
            column++;
            if (column == MAX_INFO) {
                column = 0;
                row++;
            }
        }
    }

    //Check if the number of contacts exceeds the maximum limit
    if (row >= MAX_CONTACTS) {
        //Return Error 
        fprintf(stderr, "Error: Maximum number of contacts exceeded!\n");
        return 1;
    }

    //Switch statement that handles the number of command-line arguments
    switch (argc) {
    //If a number is provided via stdin, it checks its validity and searches through the contacts
    case 2: {
        //userNumber stores given number on stdin
        const char* userNumber = argv[1];
        char letters[strlen(userNumber)][5];

        for (int i = 0; i < strlen(userNumber); i++) {
            letters[i][0] = '\0';
        }

        //Creates an array to store correspondingLetters
        for(int index = 0; userNumber[index] != '\0'; index++){
            const char* correspondingLetters = getLetters(userNumber[index]);

            strcpy(letters[index], correspondingLetters);
        }

        //Main proccess for looping through the contacts and finding the right contact's info
        if(isValid(userNumber)){
            findContact(userNumber, contacts, letters);
        } else{
            //Return Error
            fprintf(stderr, "Error occurred: Invalid input.\n");
            return 1;
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
        //Return Error
        fprintf(stderr, "Error occurred: Too many arguments provided! Try again with one or two arguments only!\n");
        return 1;
    }

    return 0;
}