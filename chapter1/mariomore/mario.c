#include <cs50.h>
#include <stdio.h>


int main()
{

    int userValue; // Store the user value
    int spaceCount; // Count the number of spaces
    int position = 1; // Check the position of the first value
    char spacePlacement = ' ';


    // Get the user value, ensure it's less than 23 and greater than 1
    do
    {
        userValue = get_int("How tall is the pyramid? ");
    }
    while ((userValue >= 23) || (userValue <= 1));


    spaceCount = userValue; // Set the space count equal to the userValue
    for (int i = 0; i != userValue; i++)  // Loop through code as long as the position is NOT equal to the userValue
    {
        spaceCount--; // Subtract a space as it counts through
        for (int space = spaceCount; space > 0; space--) // Create for(loop) and set spaces equal spaceCount and subtract one
        {
            printf("%c", spacePlacement);
        }

        for (int hash = 0; hash < position; hash++) // Place the hash based on the inital position
        {
            printf("#");
        }

        printf("%c%c", spacePlacement, spacePlacement); // Place double spaces

        for (int hash = 0; hash < position; hash++) // Place the hash based on the inital position
        {
            printf("#");
        }
        position++; // Increase the position count
        printf("\n");

    }
    return 0;
}
