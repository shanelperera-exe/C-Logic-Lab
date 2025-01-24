#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int avg_color = image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed;
            image[row][col].rgbtBlue = avg_color;
            image[row][col].rgbtGreen = avg_color;
            image[row][col].rgbtRed = avg_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) {
        int start = 0;
        int end = width - 1;
        RGBTRIPLE temp;
        while (start < end) {
            temp.rgbtRed = image[row][start].rgbtRed;
            temp.rgbtGreen = image[row][start].rgbtGreen;
            temp.rgbtBlue = image[row][start].rgbtBlue;

            image[row][start].rgbtRed = image[row][end].rgbtRed;
            image[row][start].rgbtGreen = image[row][end].rgbtGreen;
            image[row][start].rgbtBlue = image[row][end].rgbtBlue;

            image[row][end].rgbtRed = temp.rgbtRed;
            image[row][end].rgbtGreen = temp.rgbtGreen;
            image[row][end].rgbtBlue = temp.rgbtBlue;

            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    RGBTRIPLE temp[height][width];

    // Copy image to temp
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            temp[row][col] = image[row][col];
        }
    }

    // Apply box blur
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int count = 0;

            // Iterate over the 3x3 box
            for (int i = - 1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int new_row = row + i;
                    int new_col = col + j;

                    // Check if the neighboring pixel is within the image boundaries
                    if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width) {
                        red_sum += temp[new_row][new_col].rgbtRed;
                        green_sum += temp[new_row][new_col].rgbtGreen;
                        blue_sum += temp[new_row][new_col].rgbtBlue;
                        count++;
                    }
                }
            }
            // Calculate the average color values
            image[row][col].rgbtRed = red_sum / count;
            image[row][col].rgbtGreen = green_sum / count;
            image[row][col].rgbtBlue = blue_sum / count;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define Sobel kernels
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Create a copy of the original image
    RGBTRIPLE temp[height][width];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            temp[row][col] = image[row][col];
        }
    }

    // Apply Sobel operator
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            // Iterate over the 3x3 box
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int new_row = row + i;
                    int new_col = col + j;

                    // Check if the neighboring pixel is within the image boundaries
                    if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width) {
                        gx_red += temp[new_row][new_col].rgbtRed * gx[i + 1][j + 1];
                        gx_green += temp[new_row][new_col].rgbtGreen * gx[i + 1][j + 1];
                        gx_blue += temp[new_row][new_col].rgbtBlue * gx[i + 1][j + 1];

                        gy_red += temp[new_row][new_col].rgbtRed * gy[i + 1][j + 1];
                        gy_green += temp[new_row][new_col].rgbtGreen * gy[i + 1][j + 1];
                        gy_blue += temp[new_row][new_col].rgbtBlue * gy[i + 1][j + 1];
                    }
                }
            }

            // Calculate the gradient magnitude
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            // Cap the values at 255
            image[row][col].rgbtRed = red > 255 ? 255 : red;
            image[row][col].rgbtGreen = green > 255 ? 255 : green;
            image[row][col].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
    return;
}
