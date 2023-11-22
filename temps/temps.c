// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(string method);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities("bubble");

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(string method)
{
    if (strcmp(method, "bubble") == 0)
    { // bubble sort stops, if no swaps were made in a pass
        int swaps;
        avg_temp temp;
        // - 1 because array of size 1 is already sorted
        for (int i = 0; i < NUM_CITIES - 1; i++)
        {
            swaps = 0;
            /*since the i-th elemnt bubbles up, we don't need
             * to check its index again;
             * to be in line with the pseudo-code given in the lecture however,
             * this optimization is omitted: NUM_CITIES - 1 - i
             */
            for (int j = 0; j < NUM_CITIES - 1; j++)
            {
                if (temps[j].temp < temps[j + 1].temp)
                {
                    swaps++;
                    temp = temps[j + 1];
                    temps[j + 1] = temps[j];
                    temps[j] = temp;
                }
            }
            if (swaps == 0)
                break;
        }
    }
    else if (strcmp(method, "selection") == 0)
    {
        size_t sorted_before = 0, length = NUM_CITIES, smallest_idx;
        avg_temp smallest, temp;
        while (sorted_before < length - 1)
        {
            for (size_t i = sorted_before; i < length; i++)
            {
                if (i == sorted_before || temps[i].temp > smallest.temp)
                {
                    smallest = temps[i];
                    smallest_idx = i;
                }
            }

            temp = temps[sorted_before];
            temps[sorted_before] = smallest;
            temps[smallest_idx] = temp;
            sorted_before++;
        }
    }
}
