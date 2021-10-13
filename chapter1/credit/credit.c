/*

    Credit Card Program
    Designed by Xander Endre

*/

// Import Types
#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{

// Test Number 378282246310005

    // Declare variable to count card length
    int countPos = 0;
    // Declare variable to work as external storage for cardNumber
    long long cardValue;

    // Declare and initialize a variable to ask for user input
    long long cardNumber = 0;
    do
    {
        cardNumber = get_long("What is your credit card number: ");
    }
    while (cardNumber < 0);

    // Set the variable cardValue equal to the cardNumber
    cardValue = cardNumber;

    // Begin counting the length of cardNumber
    while (cardValue > 0)
    {
        // Divide by 10 until equal to 0
        cardValue = cardValue / 10;
        // Increase card count length by 1
        countPos++;
    }

    // Ensure that the cards length is strictly equal to 13, 15, or 16.
    if ((countPos != 13) && (countPos != 15) && (countPos != 16))
    {
        // Print if invalid
        printf("INVALID\n");

    }

    // Create an arraylist to store the card Length
    int trackedNum[countPos];
    // Create a for loop that will set each number to a position in array list
    for (int i = 0; i < countPos; i++)
    {
        // Places number into array list based off of last position
        trackedNum[i] = cardNumber % 10;
        // Divides by 10 to decrease ammount
        cardNumber = cardNumber / 10;

    }

    // Create a second arraylist to store the originalNumber for tracking purposes
    int originalNumber[countPos];
    // Create a for loop that will get the odd numbers from the array list
    for (int i = 0; i < countPos; i++)
    {
        // Store the trackedNumber in the originalNumber
        originalNumber[i] = trackedNum[i];

    }

    // Create a for loop that will get the odd  numbers from the array list
    for (int i = 1; i < countPos; i += 2)
    {
        // Get the numbers position, and mulitply by 2.
        // The arraylist ensures that the no other number will be affected!s
        trackedNum[i] = trackedNum[i] * 2;
    }

    int tempHold = 0;
    int finalHolder = 0;
    // Create a for loop that will add the sum of the total.
    for (int i = 0; i < countPos; i++)
    {
        // Create a temporary value which gets the last position of the number, and add's it to the second to last digit
        tempHold = (trackedNum[i] % 10) + (trackedNum[i] / 10 % 10);
        // Add the final ammount to the temporary holder
        finalHolder = finalHolder + tempHold;
    }
    // Check if card length is equal to 13
    if (countPos == 13)
    {
        // Get the last position, and check if it was equal to 4.
        // Ensure ththat the final remainder was 0!!
        if (originalNumber[12] == 4 && finalHolder % 10 == 0)
        {
            // Print it was a VISA card
            printf("VISA\n");
        }
        else
        {
            // Otherwise the card is a flakey.. like my grades
            printf("INVALID\n");
        }
    }
    // Check if card length is equal to 15
    if (countPos == 15)
    {
        // Get the last potion and check if equal to 3
        // Ensure that final remainder is 0
        // Cgeck that the 13th character is either a 4 or 7
        if (originalNumber[14] == 3  && finalHolder % 10 == 0 && (originalNumber[13] == 4 || originalNumber[13] == 7))
        {
            // Print AMEX Card
            printf("AMEX\n");
        }
        else
        {
            // Otherwise... it's even more flakey than Grace's Grades
            printf("INVALID\n");
        }
    }
    // Check if card length is equal to 16
    if (countPos == 16)
    {
        // Get the last position and check if it's equal to 5
        // Ensure the final remainder is 0
        // check if the second to last number is a number between 1 and 5
        if (originalNumber[15] == 5  && finalHolder % 10 == 0 && (originalNumber[14] == 1 || originalNumber[14] == 2
                || originalNumber[14] == 3 || originalNumber[14] == 4 || originalNumber[14] == 5))
        {
            // Print MASTERCARD card
            printf("MASTERCARD\n");
        }
        else

            // Check if the last position is 4, for VISA
            // Ensure that remainder is equal to 0
            if (originalNumber[15] == 4  && finalHolder % 10 == 0)
            {
                // Print VISA
                printf("VISA\n");
            }
            else
            {
                // Otherwise..... My jokes are screwing up this code.
                printf("INVALID\n");
            }
    }
    return 0;
}