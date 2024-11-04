/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found\n");
        exit(0);
    }

    char type[3];
    Image *result = malloc(sizeof(Image));
    int t;
    fscanf(fp, "%s", type);
    fscanf(fp, "%d %d", &result->cols, &result->rows);
    fscanf(fp, "%d", &t);

    result->image = (Color **) malloc(result->cols * sizeof(Color *));
    for (int i = 0; i < result->rows; ++i) {
        result->image[i] = (Color *) malloc(sizeof(Color) * result->cols);
    }
    for (int i = 0; i < result->rows; ++i) {
        for (int j = 0; j < result->cols; ++j) {
            fscanf(fp, "%hhu %hhu %hhu",
                   &result->image[i][j].R,
                   &result->image[i][j].G,
                   &result->image[i][j].B);
        }
    }

    fclose(fp);
    return result;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image) {
    const uint32_t cols = image->cols;
    const uint32_t rows = image->rows;

    printf("P3\n");
    printf("%d %d\n", cols, rows);
    printf("255\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const Color *color = &image->image[i][j];
            printf("%3hhu %3hhu %3hhu", color->R, color->G, color->B);
            if (j != cols - 1) {
                printf("   ");
            }
        }
        printf("\n");
    }
}

//Frees an image
void freeImage(Image *image) {
    Color **colors = image->image;
    for (int i = 0; i < image->rows; ++i) {
        free(colors[i]);
    }
    free(colors);
}
