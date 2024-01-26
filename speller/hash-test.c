#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

int main(void)
{
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

}
