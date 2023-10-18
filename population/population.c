#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    long start_size;
    do
    {
        start_size = get_long("Enter the start size of your llama population: ");
    } while (start_size < 9);

    /* Prompt for end size
    *  Dislike the style guide, this isn't neater, but whatever
    *   while ((end_size = get_long("Enter the final size of your llama population: ")) < start_size);
    *  HOWEVER: Usually, you shouldn't be smart about in **this** regard
    */
    long end_size = 0;
    do
    {
        end_size = get_long("Enter the final size of your llama population: ");
    } while (end_size < start_size);

    // Calculate number of years until we reach threshold
    int year = 0;
    long curr = start_size;
    while (curr < end_size) {
        curr += curr / 3 - curr / 4;
        year++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", year);
}
