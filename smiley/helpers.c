#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            if (image[x][y].rgbtBlue == 0x00 && image[x][y].rgbtGreen == 0x00 && image[x][y].rgbtRed == 0x00)
            {
                image[x][y].rgbtBlue = 0xf0;
                image[x][y].rgbtGreen = 0xf0;
                image[x][y].rgbtRed = 0x3a;
            }
        }
    }
    return;
}
