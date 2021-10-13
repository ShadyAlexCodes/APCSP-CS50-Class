/*

    Calculator Program
    Designed by Xander Endre

*/

// Required Imports
#include <cs50.h>
#include <stdio.h>
// Include <stdlib.h> to get argument position
#include <stdlib.h>
// Include <math.h> to get a float's mod
#include <math.h>

int main(int argc, string argv[])
{
    // Check the args length, and ensure it's exactly equal to 4
    if (argc != 4)
    {
        // Print an usage message
        printf("Usage: ./calc <numberOne> <sign> <numberTwo>\n ");
        // return statement as false
        return 1;
    }

    // Declaring Variables (Getting position of everything)
    float numberOne = atof(argv[1]);
    float sign = atof(argv[2]);
    float numberTwo = atof(argv[3]);
    // Store the outcome of the values somewhere
    float holder;

    // Create a switch statement that is checking the second argument
    switch (argv[2][0])
    {
        // Check if the argument is a `+`
        case '+':
            // Add One and Two
            holder = numberOne + numberTwo;
            // Print the value
            printf("Calculator: %f\n", holder);
            // Break the switch statement
            break;
        // Check if the argument is a `-`
        case '-':
            // Subtract One and Two
            holder = numberOne - numberTwo;
            // Print the value
            printf("Calculator: %f\n", holder);
            // Break the switch statement
            break;
        // Check if argument is an X for multiplication
        case 'x':
        case 'X':
            // Multiply One and Two
            holder = numberOne * numberTwo;
            // Print the value
            printf("Calculator: %f\n", holder);
            // Break the switch statement
            break;
        // Check if the argument is `/`
        case '/':
            // Divide One and Two
            holder = numberOne / numberTwo;
            // Print the value
            printf("Calculator: %f\n", holder);
            // Break the switch statement
            break;
        case '%':
            //
            holder = fmod(one, two);
            // Print the value
            printf("Calculator: %f\n", holder);
            // Break the switch statement
            break;
        default:
            printf("There was an error executing this program\n");
            return 1;
            break;
    }

}