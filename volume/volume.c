// Modifies the volume of an audio file

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

struct WAVE_HEADER
{
    uint8_t file_container[4];
    uint32_t file_size;
    uint8_t file_type[4];
    uint8_t format[4];
    uint32_t format_length;
    uint16_t format_type;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t samples;
    uint16_t bytes_per_channel_pair;
    uint16_t bits_per_sample;
    uint8_t data_mark[4];
    uint32_t data_size;
};

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    if (sizeof(struct WAVE_HEADER) != HEADER_SIZE)
        return 69;

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE] = {0};
    struct WAVE_HEADER hstruct;
    fread(&header, sizeof(header), 1, input);
    fwrite(&header, sizeof(header), 1, output);

    printf("N Channels: %u\n", hstruct.channels);
    // TODO: Read samples from input file and write updated data to output file
    int16_t data; // damn, took me ages to notice the data is storedas int16_t not uint16_t
    while (fread(&data, sizeof(data), 1, input))
    {
        data *= factor;
        fwrite(&data, sizeof(data), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}