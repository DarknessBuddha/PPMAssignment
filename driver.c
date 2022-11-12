/*************************
 *Ivan Lin
 *Lucia Wang
 *CPSC 2310 4:30 and 2:00
 *ilin@clemson.edu
 *lucia2@clemson.edu
 *************************/

#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(int argc, char** argv){
    //Quits the program if 4 arguments are not passed in
    assert(argc == 4);
    
    //Creates file pointers and opens them to be read from or written in
    FILE* inFile = fopen(argv[1], "r");
    FILE* resizedFile = fopen(argv[2], "w");
    FILE* negativeFile = fopen(argv[3], "w");

    //Makes sure all files were opened properly
    assert(inFile);
    assert(resizedFile);
    assert(negativeFile);

    //Allocates memory for the image header and reads the header info
    Header* header = (Header*) malloc(sizeof(Header));
    readHeader(&header, inFile);

    //Allocates memory for a 2d array of pixels and reads the info from the image
    Pixel** image = allocateImage(header->width, header->height);
    readImage(inFile, &image, header);

    //Declares resized height and width
    int height = 0;
    int width = 0;

    //Prompts the user to enter the new image height and exits if the input is invalid
    printf("Enter the new height for the image: ");
    scanf("%d", &height);
    assert(height > 0);

    //Prompts the user to enter the new image width and exits if the input is invalid
    printf("Enter the new width for the image: ");
    scanf("%d", &width);
    assert(width > 0);

    //Calls functions to create a resized image and a negative image
    writeResizeImage(resizedFile, image, height, width, header);
    writeNegativeImage(negativeFile, image, header);

    //Frees the memory allocated for the image and the header
    freeImage(image, header);
    free(header);

    //Closes all files
    fclose(inFile);
    fclose(resizedFile);
    fclose(negativeFile);

    return 0;
}