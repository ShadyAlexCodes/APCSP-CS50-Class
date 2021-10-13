#include <cs50.h>
#include <stdio.h>

int main(void)
{

    char userResponse;

    printf("Please type `F` to convert Fahrenheit to Celsius\n Or type `C` to convert Celsius to Fahrenheit");
    scanf("%c", &userResponse);

    if(userResponse == 'F' || userResponse == 'f') {
        float fahrenheitValue = get_float("Enter a temperature: "); // Gets the celsius Value
        float celsiusConversion = ((fahrenheitValue) - 32) * 5/9; // converts the celsius value to fahrenheit (32°F − 32) × 5/9
        printf("C: %.1f\n", celsiusConversion); // prints the float `celsius` with 1 decimal place
        printf("F: %.1f\n", fahrenheitValue); // prints the float `convertedValue` with 1 decimal place.
    } else
    if(userResponse == 'C' || userResponse == 'c') {
        float celsiusValue = get_float("Enter a temperature: "); // Gets the celsius Value
        float celsiusConversion = ((celsiusValue) * 9 / 5) + 32; // converts the celsius value to fahrenheit
        printf("C: %.1f\n", celsiusValue); // prints the float `celsius` with 1 decimal place
        printf("F: %.1f\n", celsiusConversion); // prints the float `convertedValue` with 1 decimal place.
    } else {

    }
}
