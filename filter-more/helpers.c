#include "helpers.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            uint8_t avg = (uint8_t) round((image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3.0);

            image[y][x].rgbtBlue = avg;
            image[y][x].rgbtGreen = avg;
            image[y][x].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    int midpoint = width % 2 == 0 ? width / 2 : width / 2 + 1;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < midpoint; x++)
        {
            tmp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            uint16_t blurRed = 0;
            uint16_t blurBlue = 0;
            uint16_t blurGreen = 0;
            float count = 0;

            for (int h = y - 1; h < y + 2; h++)
            {
                for (int v = x - 1; v < x + 2; v++)
                {
                    if (h < 0 || h > height - 1 || v < 0 || v > width - 1)
                        continue;
                    blurRed += image[h][v].rgbtRed;
                    blurGreen += image[h][v].rgbtGreen;
                    blurBlue += image[h][v].rgbtBlue;
                    count++;
                }
            }

            copy[y][x].rgbtRed = (uint8_t) round(blurRed / count);
            copy[y][x].rgbtGreen = (uint8_t) round(blurGreen / count);
            copy[y][x].rgbtBlue = (uint8_t) round(blurBlue / count);
        }
    }

    memcpy(image, copy, height * width * sizeof(RGBTRIPLE));
    free(copy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    return;
}
