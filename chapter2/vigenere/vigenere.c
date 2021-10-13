/*

    Vigenere Program
    Designed by Xander Endre

*/

// Declaration of include satements
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Declaration of Function
int inputValue(string originalValue, string plainTextValue, string cipherTextValue);
//int encryption();


int main(int argc, char *argv[])
{
    // Create a file storage system
    if (argc != 2)
    {
        // Run check
        printf("Usage: /vigenere <key>\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key must be an alphabetical char only!\n");
                return 1;
            }
        }
    }
    // Store the key under a string
    string key = argv[1];
    // Store the keyPositon in an int
    int keyCounter = 0;
    int keyLength = strlen(argv[1]);
    int shiftKey;
    // Store the plain text in a string
    string plainText;
    char cipherText[100];
    // Check and ensure that argc is greater than or equal to two


    // Ask the user for the plainText
    plainText = get_string("Plaintext: ");
    printf("ciphertext: ");

    // Create a foorloop to loop through each chracter
    for (int i = 0; i <  strlen(plainText); i++)
    {
        shiftKey = tolower(key[keyCounter % keyLength]) - 97;
        if (isupper(plainText[i]))
        {
            printf("%c", 65 + (plainText[i] - 65 + shiftKey) % 26);
            cipherText[i] = (65 + (plainText[i] - 65 + shiftKey) % 26);
            keyCounter++;
        }
        else if (islower(plainText[i]))
        {
            printf("%c", 97 + (plainText[i] - 97 + shiftKey) % 26);
            cipherText[i] = (97 + (plainText[i] - 97 + shiftKey) % 26);
            keyCounter++;
        }
        else
        {
            printf("%c", plainText[i]);
        }
    }
    inputValue(key, plainText, cipherText);
    printf("\n");
    return 0;
}



int inputValue(string originalValue, string plainTextValue, string cipherTextValue)
{
    FILE *vigenereStorage;
    char *vigenereFile = "vigenere.txt";
    int positionInFile;
    vigenereStorage = fopen(vigenereFile, "a");
    positionInFile = ftell(vigenereStorage);
    fseek(vigenereStorage, positionInFile, SEEK_SET);
    fprintf(vigenereStorage, "Original: %s  |  Plaintext: %s  |  ChiperText: %s \n", originalValue, plainTextValue, cipherTextValue);
    fclose(vigenereStorage);

    return 0;
}

