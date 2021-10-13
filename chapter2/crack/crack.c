/*

    Crack Program
    Designed by Xander Endre
 (P.S. Message From Grace - "Xander got this done before me.")

*/

// Imports
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <crypt.h>
#define _XOPEN_SOURCE
#include <unistd.h>

/*
            Passwords
    anushree:50xcIMJ0y.RXo   |   YES
    brian:50mjprEcqC/ts      |   CA
    bjbrown:50GApilQSG3E2    |   UPenn
    **lloyd:50n0AAUD.pL8g    |   lloyd
    malan:50CcfIk1QrPr6      |   maybe
    maria:509nVI8B9VfuA      |   TF
    natmelo:50JIIyhDORqMU    |   nope
    rob:50JGnXUgaafgc        |   ROFL
    stelios:51u8F0dkeDSbY    |   NO
    zamyla:50cI2vYkF0YU2     |   LOL


    A | 50OqznXGVcOJU [x]
    AA | 50/A0MHdXAgbA [x]
    AAA | 50Utc9urfPxko [x]
    AAAA | 50k72iioeOiJU [x]
    AAAAA | 50XcgR31jl/4M [x]
*/

int main(int argc, string argv[])
{
    FILE* outputFile;
    char* passwordFile = "passwords.txt";
    int filecount = 0;
    int positionInFile;
    // Store the client encrypted password
    string password;
    // Store the salt in an array of salt 3
    char salt[3];
    // Create a second arraylist to store input
    char temp[6];


    bool oneLetterPass = true;
    bool twoLetterPass;
    bool threeLetterPass;
    bool fourLetterPass;
    bool fiveLetterPass;

    // Check the args length, and ensure it's exactly equal to 2
    if (argc != 2)
    {
        // Print Error Message
        printf("Usage: ./crack <password>\n");
        return 1;
    }

    // Store the password an external variable
    password = argv[1];
    // Set the first number to the first letter/number in the client input
    salt[0] = argv[1][0];
    // Set the second number to the second letter/number from the client input
    salt[1] = argv[1][1];
    // Finally close the char with a '\0' to signify the char is over.
    salt[2] = '\0';

    // Store the entire alphabet in a string, but ensure the first variable/letter is NULL!!!
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int letterLength = strlen(letters);

    // Creates 5 for-loops to loop through every letter
    // Loops through 53 times. Reason The entire alphabet upper and lower case is 26 + 26 wh
    for(int fifth = 0; fifth < letterLength; fifth++) {
        for(int fourth = 0; fourth < letterLength; fourth++) {
            for(int third = 0; third < letterLength; third++) {
                for(int second = 0; second < letterLength; second++) {
                    for(int first = -1; first < letterLength; first++) {
                        if(fiveLetterPass)
                        {
                            temp[0] = letters[first];
                            temp[1] = letters[second];
                            temp[2] = letters[third];
                            temp[3] = letters[fourth];
                            temp[4] = letters[fifth];
                            temp[5] = '\0';
                            if(fifth == letterLength - 1) {
                                fiveLetterPass = false;
                                printf("Pass5\n");
                            }
                        }
                        if(fourLetterPass)
                        {
                            temp[0] = letters[first];
                            temp[1] = letters[second];
                            temp[2] = letters[third];
                            temp[3] = letters[fourth];
                            temp[4] = '\0';
                            if(fourth == letterLength - 1) {
                                fourLetterPass = false;
                                fiveLetterPass = true;
                                printf("Pass4\n");
                            }
                        }
                        if(threeLetterPass)
                        {
                            temp[0] = letters[first];
                            temp[1] = letters[second];
                            temp[2] = letters[third];
                            temp[3] = '\0';
                            if(third == letterLength - 1) {
                                threeLetterPass = false;
                                fourLetterPass = true;
                                printf("Pass3\n");
                            }
                        }
                        if(twoLetterPass)
                        {
                            temp[0] = letters[first];
                            temp[1] = letters[second];
                            temp[2] = '\0';
                            if(second == letterLength - 1) {
                                twoLetterPass = false;
                                threeLetterPass = true;
                                printf("Pass2\n");
                            }
                        }
                        if(oneLetterPass)
                        {
                            temp[0] = letters[first];
                            temp[1] = '\0';
                            if(first == letterLength - 1) {
                                oneLetterPass = false;
                                twoLetterPass = true;
                                printf("Pass1\n");
                            }
                        }

                        string new_hash = crypt(temp, salt);
                        if(strcmp(new_hash, password) == 0) {
                            outputFile = fopen(passwordFile, "a");
                            positionInFile = ftell(outputFile);
                             fseek(outputFile,positionInFile,SEEK_SET);
                            fprintf(outputFile, "Final: %s  |  %s   CLEAR: %s\n", new_hash, password, temp);
                            fclose(outputFile);
                            printf("Final: %s  |  %s   \n  CLEAR: %s\n", new_hash, password, temp);
                            return 0;
                    }
                }
            }
        }
    }
}
    printf("\n");
    return 0;
}

