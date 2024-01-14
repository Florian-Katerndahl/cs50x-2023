#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char plates[8][7];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    // alternaive: fgets
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strncpy(plates[idx], buffer, 7);
        //plates[idx] = buffer;
        idx++;
    }

    // alternative with malloc
    rewind(infile);
    idx = 0;
    char *plates2[8];
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';
        plates2[idx] = malloc(7 * sizeof(char));
        if (plates2[idx] == NULL)
        {
            fprintf(stderr, "Error: Could not allocate memory\n");
            fclose(infile);
            exit(1);
        }

        // Save plate number in array
        strncpy(plates2[idx], buffer, 7);
        idx++;
    }


    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates2[i]);
        free(plates2[i]);
        plates2[i] = NULL;
    }

    fclose(infile);
    return 0;
}
