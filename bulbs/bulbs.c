#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    char *message;
    do
    {
        message = get_string("Message: ");
    }
    while (message == NULL);

    size_t ssize = strlen(message);
    for (size_t i = 0; i < ssize; i++)
    {
        for (size_t j = 0; j < BITS_IN_BYTE; j++)
        {
            printf("%d ", message[i] & (1 << j));

            //print_bulb(message[i] & (1 << j));
        }
        printf("\n");
    }

    // see readibilty
    //free(message);
    return 0;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
