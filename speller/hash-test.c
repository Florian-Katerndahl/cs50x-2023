#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Histogram
int hist[26 * LENGTH];

int main(void)
{
    FILE *file = fopen(DICTIONARY, "r");
    if (file == NULL)
    {
        return 1;
    }

    char word[LENGTH + 1];
    int index = 0;

    // Spell-check each word in text
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while (fread(&c, sizeof(char), 1, file) && isalpha(c))
                    ;

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while (fread(&c, sizeof(char), 1, file) && isalnum(c))
                ;

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';
            hist[hash(word)] += 1;

            // Prepare for next word
            index = 0;
        }
    }

    for (int i = 0; i < 26 * LENGTH; i++)
    {
        if (hist[i])
            printf("%.3d => %d\n", i, hist[i]);
    }
}
