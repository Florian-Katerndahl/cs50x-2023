#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t JPEG_signature[4] = {0xff, 0xd8, 0xff, 0xe0}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "Error: Coul not read file %s\n", argv[1)
    }

    return 0;
}
