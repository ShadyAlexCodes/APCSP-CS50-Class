/*

    Initals Program
    Designed by Xander Endre

*/

// Imports
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    // Declared String `getName` gets a string asking for client Name
    string getName = get_string("What is your name? ");
    // Convert the name into a int length.
    int nameLength = strlen(getName);
    // Store a singular letter in the string
    char letter;

    // Get the first position of the array and store it to letter.
    letter = getName[0];
    // Print the first letter of the array in Uppercase.
    printf("%c", toupper(letter));
    // Create a loop that will count until it is equal to the namesLength
    for (int i = 0; i < nameLength; i++)
    {
        // Check if the array's position has a space in it.
        if(getName[i] == ' ')  {
            // Add the next letter to the letter character
            letter = getName[i + 1];
            // Print the character in upercase
            printf("%c", toupper(letter));
        }
    }
    printf("\n");
}