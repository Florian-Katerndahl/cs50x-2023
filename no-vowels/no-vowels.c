// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    string converted = replace(&argv[1]);
    printf("%s\n", converted);
    return 0;
}

string replace(string input[])
{
    int length = strlen(*input) + 1;
    string converted[length] = {0};
    for (int i = 0, l = strlen(input); i < l; i++)
    {
        switch(input[i])
        {
            case 'a':
                converted[i] = '6';
                break;
            case 'e':
                converted[i] = '3'
                break;
            case 'i':
                converted[i] = '1';
                break;
            case 'o':
                converted[i] = '0';
                break;
            default:
                converted[i] = input[i];
                break;
        }
    }
    return converted;
}
