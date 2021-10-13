#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    int totalDays = 0; // Set total days to 0
    long long initalAmmount = -1; // Set inital ammount to -1
    long long totalAmmount = 0; // Set the total ammount to 0
    long long givenAmmount; // Ammount used to store pennies
    double totalDollars; // The ammount of money after all the pennies.

    while (totalDays < 28 || totalDays > 31) // Make sure the total days are greater than 28 and less than 31
    {
        totalDays = get_int("How many days are in this month: "); // Ask for days
    }

    while (initalAmmount <= 0 || initalAmmount > 30) // Make sure the pennies ammount if greater than 0 and less then 30
    {
        initalAmmount = get_int("How many pennies did you start with: "); // Asks for ammount of pennies
    }

    givenAmmount = initalAmmount; // Set the given ammount to store the inital ammount

    for (int i = 0; i < totalDays; i++)
    {

        totalAmmount += givenAmmount; // Add the given ammount of pennies to the total

        givenAmmount *= 2; // Multiply the given ammount by 2

    }

    totalDollars = totalAmmount / 100.00; // Divide by 100

    printf("Total days in month: %i\n", totalDays);
    printf("Inital ammount of Pennies on first day: %lli\n", initalAmmount);
    printf("Total ammount of pennies: %lli\n", totalAmmount);
    printf("Total ammount in dollars: $%0.2f\n", totalDollars);
    return 0;
}
