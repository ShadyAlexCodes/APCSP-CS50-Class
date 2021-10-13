#include <cs50.h>
#include <stdio.h>

int main(void)
{

    long long userValue; // Store the user Value
    int numericalValue; // Store the current Information
    int finalValue = 0; // Set the final Value

    userValue = get_long("What is your ISBN? "); //Ask the user for ISBN

    for (int i = 10; i > 0; i--) // Go down from 10 to 0
    {
        numericalValue = userValue % 10; // getting the 10th position
        numericalValue *= i; // Multiply the numerical value based on position
        userValue /= 10; // Divide the user value by 10 to remove from list
        finalValue += numericalValue; // Adding Numerical Value to Final value
    }

    if (finalValue % 11 == 0) // Get the final value and get the 11th position.. Check if equal to 0
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }


    return 0;
}