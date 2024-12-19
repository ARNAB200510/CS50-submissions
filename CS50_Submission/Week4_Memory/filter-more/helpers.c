#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Set the RGB values to their average values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;

            int r_avg = round(avg);

            image[i][j].rgbtRed = r_avg;
            image[i][j].rgbtGreen = r_avg;
            image[i][j].rgbtBlue = r_avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Put the right side bits to the left
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j]; // Store the pixel to be repleced
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // To avoid side cases, add zero rows and columns
    RGBTRIPLE use[height + 2][width + 2];

    // Store image to use
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == width + 1 || i == height + 1 || j == 0)
            {
                use[i][j].rgbtRed = 0;
                use[i][j].rgbtBlue = 0;
                use[i][j].rgbtGreen = 0;
            }
            else
            {
                use[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
                use[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                use[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            }
        }
    }

    // Blur the image
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            float ravg = 0.0;
            float gavg = 0.0;
            float bavg = 0.0;

            for (int r = i - 1; r <= i + 1; r++)
            {
                for (int c = j - 1; c <= j + 1; c++)
                {
                    BYTE red = use[r][c].rgbtRed;
                    BYTE blue = use[r][c].rgbtBlue;
                    BYTE green = use[r][c].rgbtGreen;
                    ravg += red;
                    bavg += blue;
                    gavg += green;
                }
            }

            if (i == 1 || i == height || j == width || j == 1)
            {
                if ((i == 1 && j == 1) || (i == height && j == width) || (i == 1 && j == width) || (i == height && j == 1))
                {
                    ravg = round(ravg / 4);
                    bavg = round(bavg / 4);
                    gavg = round(gavg / 4);
                }
                else
                {
                    ravg = round(ravg / 6);
                    bavg = round(bavg / 6);
                    gavg = round(gavg / 6);
                }
            }
            else
            {
                ravg = round(ravg / 9);
                bavg = round(bavg / 9);
                gavg = round(gavg / 9);
            }
            image[i - 1][j - 1].rgbtRed = ravg;
            image[i - 1][j - 1].rgbtBlue = bavg;
            image[i - 1][j - 1].rgbtGreen = gavg;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create Gx and Gy
    int Gx[3][3];
    int Gy[3][3];

    // Sobel kernel for horizontal gradient (Gx)
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;

    // Sobel kernel for vertical gradient (Gy)
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;

    RGBTRIPLE use[height + 2][width + 2];
    // Create the temp matrix
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == width + 1 || i == height + 1 || j == 0)
            {
                use[i][j].rgbtRed = 0;
                use[i][j].rgbtBlue = 0;
                use[i][j].rgbtGreen = 0;
            }
            else
            {
                use[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
                use[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                use[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            }
        }
    }

    // Calculate the Gx and Gy values for all the channels

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            int x_red = 0;
            int x_blue = 0;
            int x_green = 0;
            int y_red = 0;
            int y_green = 0;
            int y_blue = 0;
            for (int r = i - 1, r1 = 0; r <= i + 1 && r1 < 3; r++, r1++)
            {
                for (int c = j - 1, c1 = 0; c <= j + 1 && c1 < 3; c++, c1++)
                {
                    x_red = x_red + (use[r][c].rgbtRed * Gx[r1][c1]);
                    x_blue = x_blue + (use[r][c].rgbtBlue * Gx[r1][c1]);
                    x_green = x_green + (use[r][c].rgbtGreen * Gx[r1][c1]);

                    y_red = y_red + (use[r][c].rgbtRed * Gy[r1][c1]);
                    y_blue = y_blue + (use[r][c].rgbtBlue * Gy[r1][c1]);
                    y_green = y_green + (use[r][c].rgbtGreen * Gy[r1][c1]);
                }
            }
            int res_red = round(sqrt(pow(x_red, 2) + pow(y_red, 2)));
            int res_blue = round(sqrt(pow(x_blue, 2) + pow(y_blue, 2)));
            int res_green = round(sqrt(pow(x_green, 2) + pow(y_green, 2)));
            image[i - 1][j - 1].rgbtRed = (res_red > 255) ? 255 : res_red;
            image[i - 1][j - 1].rgbtBlue = (res_blue > 255) ? 255 : res_blue;
            image[i - 1][j - 1].rgbtGreen = (res_green > 255) ? 255 : res_green;
        }
    }
}
