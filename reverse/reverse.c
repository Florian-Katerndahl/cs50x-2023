#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    if (strstr(argv[1], "wav") == NULL || strstr(argv[2], "wav") == NULL)
    {
        fprintf(stderr, "Input is not a WAV file.\n");
        return 10;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    if (fread(&header, sizeof(WAVHEADER), 1, input) != 1)
    {
        fprintf(stderr, "Error: Could not read from input file\n");
        fclose(input);
        return 1;
    }

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header))
    {
        fprintf(stderr, "Input is not a WAV file.\n");
        fclose(input);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", argv[2]);
        fclose(input);
        return 1;
    }

    // Write header to file
    // TODO #6
    if (fwrite(&header, sizeof(WAVHEADER), 1, output) != 1)
    {
        fprintf(stderr, "Error: Could not write to output file\n");
        fclose(input);
        fclose(output);
        return 1;
    }


    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    uint8_t *data = calloc(header.subchunk2Size, sizeof(uint8_t));
    if (data == NULL)
    {
        fprintf(stderr, "Error: Could not allocate buffer\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    uint8_t *block = calloc(block_size, sizeof(uint8_t));
    if (block == NULL)
    {
        fprintf(stderr, "Error: Could not allocate buffer\n");
        fclose(input);
        fclose(output);
        free(data);
        return 1;
    }

    if (fread(data, 1, header.subchunk2Size, input) != header.subchunk2Size)
    {
        fprintf(stderr, "Error: Could not read data from file\n");
        fclose(input);
        fclose(output);
        free(data);
        free(block);
        return 1;
    }

    int midpoint = header.subchunk2Size % 2 ? header.subchunk2Size / 2 : (header.subchunk2Size / 2) + 1;
    for (int i = 0; i < midpoint; i += (block_size) - 1)
    {
        for (int j = 0; j < block_size; j++)
        {
            block[j] = data[i + j];
        }
        for (int j = 0; j < block_size; j++)
        {
            data[i + j] = data[header.subchunk2Size - ((1 + i) * block_size - 1) + j];
        }
        for (int j = 0; j < block_size; j++)
        {
            data[header.subchunk2Size - ((1 + i) * block_size - 1) + j] = block[j];
        }

        /*printf("Copying data from %p to %p; EOB is at %p\n", data + i, data + header.subchunk2Size - ((1 + i) * block_size), data + header.subchunk2Size);
        memcpy(block, data + i, block_size);
        memmove(data + i, data + header.subchunk2Size - ((1 + i) * block_size), block_size);
        memcpy(data + header.subchunk2Size - 1 - i, block, block_size);*/
    }

    if (fwrite(data, 1, header.subchunk2Size, output) != header.subchunk2Size)
    {
        fprintf(stderr, "Error: Failed to write revered data to file\n");
        fclose(input);
        fclose(output);
        free(data);
        free(block);
        return 1;
    }

    fclose(input);
    fclose(output);
    free(data);
    free(block);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (strncmp((char*) header.format, "WAVE", 4))
        return 1;

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}
