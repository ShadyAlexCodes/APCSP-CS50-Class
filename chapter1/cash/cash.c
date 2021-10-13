#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    float changeOwed; // Prompt user for ammount of change due
    float centConversion; // The conversion storage for after the ammount is rounded and multipied by 100.
    float ammountProcessed; // Store the ammount processed as a seperate varliable
    int coinsUsed = 0; // Keep track of how many coins we're using

    // Get ammount in Dollars through a Do-While loop.
    do
    {
        changeOwed = get_float("Hello! How much change is owed? "); // Ask how much change you need.
        printf("Changed Owed: %0.2f\n", changeOwed); // Print the ammount that is owed.
    }
    while (changeOwed < 0); // Repeat the Do-While loop as long as the inital value is less than 0

    centConversion = round(changeOwed * 100); // Multiply the changed ammount and round off value using math.h library.
    printf("Current Change: %0.2f\n", centConversion);
    ammountProcessed = centConversion; // Store the ammount in a different variable

    // While Quarters can be used
    while (ammountProcessed >= 25)
    {
        ammountProcessed -= 25; // Subtract 25 from value
        coinsUsed += 1; // Increase coins by 1
    }

    // While Dimes can be used.
    while (ammountProcessed >= 10)
    {
        coinsUsed += 1; // Increase coins by 1
        ammountProcessed -= 10; // Subtract 10 from value
    }

    // While Nickles can be used.
    while (ammountProcessed >= 5)
    {
        coinsUsed += 1; // Increase coins by 1
        ammountProcessed -= 5; // Subtract 5 from value
    }

    // While Pennies can be
    while (ammountProcessed >= 1)
    {
        coinsUsed += 1; // Increase coins by 1
        ammountProcessed -= 1; // Subtract 1 from value
    }

    printf("Total Ammount: %0.2f\n", ammountProcessed); // Ensure that the value is set to 0
    printf("Total Coins Used: %i\n", coinsUsed); // Print the total ammount of coins

}

