/*************************
*Ivan Lin
*CPSC 2310 Fall 22
*Lab 8
*UserName:  ilin
*Instructor:  Dr. Yvon Feaster
*************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef struct Header{
    char type[3];
    int width;
    int height;
    int maxColor;
}Header;

typedef struct Pixel{
    unsigned char red, green, blue;
}Pixel;

/*
 * Parameters: header - pointer storing the location of header data
 *             file - input file to be read from
 *
 * Return: None
 * This function reads the magic number, width, height,
 * and maximum color value of ppm stores the data in header.
 * This function ignores the comments while reading.
 */
void readHeader(Header** header, FILE* file);

/*
 * Parameters: header - pointer storing the location of header data
 *             file - output file to be written to
 * Return: None
 * This function writes magic number, width, height,
 * and maximum color value of ppm to the output file.
 */
void writeHeader(Header* header, FILE* file);

/*
 * Parameters: file - input file to be read from
 *
 * Return: None
 * This function reads and discards comments.
 * Comments start with #.
 */
void discardComments(FILE* file);

Pixel** allocateImage(int width, int height);

void freeImage(Pixel** pixels, Header* header);

void readImage(FILE* file, Pixel*** image, Header* header);

void writeResizeImage(FILE* file, Pixel** image, int height, int width, Header* header);

void writeNegativeImage(FILE* file, Pixel** image, Header* header);


#endif
