#include <cs50.h>
#include <stdio.h>

void to_string(long cn, char dest[]);
int is_valid(long cn);
int is_amex(long cn);
int is_master(long cn);
int is_visa(long cn);

int main(void)
{
    char num_as_string[256] = { 0 };
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    to_string(card_number, &num_as_string[0]);
    printf("%s\n", num_as_string);

    if (!is_valid(card_number)) printf("INVALID\n");
    else if (is_amex(card_number)) printf("AMEX\n");
    else if (is_master(card_number)) printf("MASTERCARD\n");
    else if (is_visa(card_number)) printf("VISA\n");
    else printf("INVALID\n");

    return 0;
}

void to_string(long cn, char *dest)
{
    for (int i = 0; cn > 0; i++)
    {
        dest[i] = cn % 10;
        cn /= 10;
        printf("a%d", dest[i]);
    }
}

int is_valid(long cn)
{
    int nb = sizeof(long);
    return 1;
}

int is_amex(long cn)
{
    return 1;
}

int is_master(long cn)
{
    return 1;
}

int is_visa(long cn)
{
    return 1;
}
