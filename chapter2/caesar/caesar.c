/*

    Caesar Program
    Designed by Xander Endre

*/

// Imports

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Store the number of shift
    int shiftNum = 0;
    // store the user input
    string plainText;

    // Check the args length, and ensure it's exactly equal to 2
    if (argc != 2)
    {
        // Print Error Message
        printf("Usage: /caesar <number>\n");
        return 1;
    }

    // Store the first argument from the command in shiftNum
    shiftNum = atoi(argv[1]);
    // Ask the user for their input
    plainText = get_string("plaintext: ");

    // Print `ciphertext` cuz grace said so.
    printf("ciphertext: ");

    // Create a for loop based on the length of the plainText
    for (int i = 0; i < strlen(plainText); i++)
    {
        // Check if the letter based on position is between a -> z and is lowercase
        if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            /*
                Cipher Explanation
                    - The letter in the list
                    - Subtract lowercase `a` ensure the problem will wrap-around
                    - Add the shift
                    - Then get the mod
                    - Add back the lowercase `a` to get the final value
                Print the Cipher
            */
            printf("%c", ((plainText[i] - 97) + shiftNum) % 26 + 97);
        }
        // Check if the letter based on position is between A -> A and is uppercase
        else if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            /*
                Cipher Explanation
                    - The letter in the list (plainText[i])
                    - Subtract lowercase `A` ensure the problem will wrap-around (-65)
                    - Add the shift (+ shiftNum)
                    - Then get the mod (Outside of it, % 26)
                    - Add back the lowercase `A` to get the final value (Add back the 65)
                Print the Cipher
            */
            printf("%c", ((plainText[i] - 65) + shiftNum) % 26 + 65);
        }
        // If the character is not between A/a -> Z/z then print as is.
        else
        {
            // Prints spaces, commans, brackets, etc.
            printf("%c", plainText[i]);
        }
    }
    // Print a new line to make this look perty.
    printf("\n");
    return 0;
}

/*

    F. Y. I.
 My code is better
 than Grace Gabrielson's
 code. Plus.. i'm just
 better than her.


*/