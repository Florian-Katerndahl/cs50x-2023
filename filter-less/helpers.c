#include "helpers.h"
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
            uint8_t avg = (image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3;

            image[y][x].rgbtBlue = avg;
            image[y][x].rgbtGreen = avg;
            image[y][x].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            uint16_t sepiaRed = 0.393 * image[y][x].rgbtRed + 0.769 * image[y][x].rgbtGreen + 0.189 * image[y][x].rgbtBlue;
            uint16_t sepiaGreen = 0.349 * image[y][x].rgbtRed + 0.686 * image[y][x].rgbtGreen + 0.168 * image[y][x].rgbtBlue;
            uint16_t sepiaBlue = 0.272 * image[y][x].rgbtRed + 0.534 * image[y][x].rgbtGreen + 0.131 * image[y][x].rgbtBlue;

            image[y][x].rgbtRed = sepiaRed > UINT8_MAX ? UINT8_MAX : sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen > UINT8_MAX ? UINT8_MAX : sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue > UINT8_MAX ? UINT8_MAX : sepiaBlue;
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
            image[y][x] = image[y][width - x];
            image[y][width - x] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (!y || y == height - 1 || !x || x == width - 1) continue;
            uint8_t blurRed = (
                image[y - 1][x - 1].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed +
                image[y]    [x - 1].rgbtRed + image[y]    [x].rgbtRed + image[y]    [x + 1].rgbtRed +
                image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed
            ) / 9;
            uint8_t blurGreen = (
                image[y - 1][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen +
                image[y]    [x - 1].rgbtGreen + image[y]    [x].rgbtGreen + image[y]    [x + 1].rgbtGreen +
                image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen
            ) / 9;
            uint8_t blurBlue = (
                image[y - 1][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue +
                image[y]    [x - 1].rgbtBlue + image[y]    [x].rgbtBlue + image[y]    [x + 1].rgbtBlue +
                image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue
            ) / 9;

            copy[y][x].rgbtRed = blurRed;
            copy[y][x].rgbtGreen = blurGreen;
            copy[y][x].rgbtBlue = blurBlue;
        }
    }

    memcpy(image, copy, height * width * sizeof(RGBTRIPLE));
    free(copy);
    return;
}
