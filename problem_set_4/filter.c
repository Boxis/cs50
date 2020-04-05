#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0 +.5;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = .393*image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue +.5;
            int sepiaGreen = .349*image[i][j].rgbtRed + .686*image[i][j].rgbtGreen + .168*image[i][j].rgbtBlue +.5;
            int sepiaBlue = .272*image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131*image[i][j].rgbtBlue +.5;

            if (sepiaRed>255) sepiaRed = 255;
            if (sepiaGreen>255) sepiaGreen = 255;
            if (sepiaBlue>255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen =  image[i][width - j-1].rgbtGreen;
            image[i][j].rgbtBlue =  image[i][width - j-1].rgbtBlue;

            image[i][width - j-1].rgbtRed = tempRed;
            image[i][width - j-1].rgbtGreen = tempGreen;
            image[i][width - j-1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Copy each pixel to copy
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            copy[x][y].rgbtRed = image[x][y].rgbtRed;
            copy[x][y].rgbtGreen = image[x][y].rgbtGreen;
            copy[x][y].rgbtBlue = image[x][y].rgbtBlue;
        }
    }

    // Blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempRed;
            int tempGreen;
            int tempBlue;
            // top row
            if (i == 0 && j == 0)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed)/4.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen)/4.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue)/4.0+.5;
            }
            else if (i == 0 && j == width - 1)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed)/4.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen)/4.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue)/4.0+.5;
            }
            else if(i == 0)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j+1].rgbtRed)/6.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j+1].rgbtGreen)/6.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j+1].rgbtBlue)/6.0+.5;
            }
            // deal with bottom row
            else if (i == height-1 && j == 0)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed)/4.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen)/4.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue)/4.0+.5;
            }
            else if (i == height-1 && j == width - 1)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed)/4.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen)/4.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue)/4.0+.5;
            }
            else if(i == height-1)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j+1].rgbtRed)/6.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i-1][j+1].rgbtGreen)/6.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i-1][j+1].rgbtBlue)/6.0+.5;
            }
            // deal with left side
            else if (j == 0)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i+1][j+1].rgbtRed)/6.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen)/6.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue)/6.0+.5;
            }
            // deal with right side
            else if (j == width - 1)
            {
                tempRed = (copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i+1][j-1].rgbtRed)/6.0+.5;
                tempGreen = (copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen)/6.0+.5;
                tempBlue = (copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue)/6.0+.5;
            }
            // the rest (the middle of the image)
            else
            {
                tempRed = (float) (copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed +
                           copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed +
                           copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed)/9.0 +.5;
                tempGreen = (float) (copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen +
                           copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen +
                           copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen)/9.0 +.5;
                tempBlue = (float) (copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue +
                           copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue +
                           copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue)/9.0 +.5;
            }

            image[i][j].rgbtRed = round(tempRed);
            image[i][j].rgbtGreen = round(tempGreen);
            image[i][j].rgbtBlue = round(tempBlue);
        }
    }
    return;
}
