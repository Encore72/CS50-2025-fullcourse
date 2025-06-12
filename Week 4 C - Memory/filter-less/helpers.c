#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int Red = image[i][j].rgbtRed;
            int Green = image[i][j].rgbtGreen;
            int Blue = image[i][j].rgbtBlue;

            int avgRGB = round((Red + Green + Blue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = avgRGB;
            image[i][j].rgbtGreen = avgRGB;
            image[i][j].rgbtBlue = avgRGB;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update pixel values with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            RGBTRIPLE tempImage = image[i][width - j - 1];

            image[i][width - j - 1] = image[i][j];

            image[i][j] = tempImage;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // getting average of 3x3 neighbouring RBG values for each pixel
    for (int currentRow = 0; currentRow < height; currentRow++)
    {
        for (int currentColumn = 0; currentColumn < width; currentColumn++)
        {
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;
            float neighbourPixelCounter = 0;

            for (int neighbouringRow = -1; neighbouringRow <= 1; neighbouringRow++)
            {
                for (int neighbouringColumn = -1; neighbouringColumn <= 1; neighbouringColumn++)
                {
                    int currNeighbRow = currentRow + neighbouringRow;
                    int currNeighbCol = currentColumn + neighbouringColumn;

                    // check boundaries
                    if (currNeighbRow >= 0 && currNeighbRow < height &&
                        currNeighbCol >= 0 && currNeighbCol < width)
                    {
                        sumRed += copy[currNeighbRow][currNeighbCol].rgbtRed;
                        sumGreen += copy[currNeighbRow][currNeighbCol].rgbtGreen;
                        sumBlue += copy[currNeighbRow][currNeighbCol].rgbtBlue;
                        neighbourPixelCounter++;
                    }
                }
            }

            // Applying blur
            image[currentRow][currentColumn].rgbtRed = round(sumRed / neighbourPixelCounter);
            image[currentRow][currentColumn].rgbtGreen = round(sumGreen / neighbourPixelCounter);
            image[currentRow][currentColumn].rgbtBlue = round(sumBlue / neighbourPixelCounter);
        }
    }
}
