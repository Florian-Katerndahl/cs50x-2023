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
        fprintf(stderr, "Error: Coul not read file %s\n", argv[1]);
        return 1;
    }

    char outname[8] = { 0 };
    uint8_t data[512];
    size_t out_index = 0;

    while (fread(data, 1, 512, infile) == 512)
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && ((data[3] & 0xe0) == 0xe0))
    }

    return 0;
}
