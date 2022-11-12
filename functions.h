/*************************
 *Ivan Lin
 *Lucia Wang
 *CPSC 2310 4:30 and 2:00
 *ilin@clemson.edu
 lucia2@clemson.edu
 *************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Struct that holds the type of image, width, height, and may RGB value from the image header
typedef struct Header{
    char type[3];
    int width;
    int height;
    int maxColor;
}Header;

//Struct that holds the RGB value of a pixel on an image
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

/*
 * Parameters: file - input file to be read form
 * Return: None
 * Skips spaces and comments until a digit is reached
 */
void handleSpacesAndComments(FILE* file);
/*
Parameters: width - width of the image to be created
            height - height of the image to be created
Return: void
This function allocates memory for a 2d pixel array of dimension width x height
*/
Pixel** allocateImage(int width, int height);

/*
Parameters: pixels - 2d pixel array that represents an image
            header - header that contains the imformation of the image
Return: void
This function loops through and frees all memory that was allocated for the image
*/
void freeImage(Pixel** pixels, Header* header);

/*
Parameters: file - file pointer to be read from
            image - image composed of struct pixels to reflect file passed in
            header - contains the information of the file passed in
Return: void
This function reads in information from the file passed in to image
*/
void readImage(FILE* file, Pixel*** image, Header* header);

/*
Parameters : file - file pointer to be written to
             image - original image passed in
             height - user chosen new height for the new image
             width - user chosed new width for the new image
             header - header that contains the information of the original image
Return: void
This function creates a resized image of the original with the dimensions passed in and writes it to file
*/
void writeResizeImage(FILE* file, Pixel** image, int height, int width, Header* header);

/*
Parameters: file - file pointer to be written to 
            image - original image passed in
            header - header that contains the information of the image (same for both images)
Return: void
This function creates an image with -255 to all RGB values of the original and writes it to the file passed in
*/
void writeNegativeImage(FILE* file, Pixel** image, Header* header);


#endif
