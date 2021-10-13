// Greets a user by their name

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./hello <name>\n");
        return 1;
    }
    // Collect a string from the user, then print their name
    string name = argv[1];
    printf("Hello, %s!\n", name);
}
