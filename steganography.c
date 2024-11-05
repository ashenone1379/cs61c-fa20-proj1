/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				HQY
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be.
//This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col) {
    Color *result = malloc(sizeof(Color));
    result->R = image->image[row][col].R;
    result->G = image->image[row][col].G;
    result->B = image->image[row][col].B;

    return result;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image) {
    const int rows = image->rows, cols = image->cols;
    Image *new_image = malloc(sizeof(Image));
    new_image->rows = rows;
    new_image->cols = cols;

    new_image->image = malloc(sizeof(Color *) * rows);
    for (int i = 0; i < rows; ++i) {
        new_image->image[i] = malloc(sizeof(Color) * cols);
        for (int j = 0; j < cols; ++j) {
            Color *color = evaluateOnePixel(image, i, j);
            new_image->image[i][j].R = color->R;
            new_image->image[i][j].G = color->G;
            new_image->image[i][j].B = (color->B & 1) ? 0 : 255;
            free(color);
        }
    }

    return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv) {
    if (argc < 2) {
        return -1;
    }

    Image *img = readData(argv[1]);

    Image *result_img = steganography(img);

    writeData(result_img);

    freeImage(img);
    freeImage(result_img);

    return 0;
}
