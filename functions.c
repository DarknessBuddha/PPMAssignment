/*************************
 *Ivan Lin
 *Lucia Wang
 *CPSC 2310 4:30 and 2:00
 *ilin@clemson.edu
 lucia2@clemson.edu
 *************************/
#include "functions.h"

//This function reads in image information from the header and eliminates comments
void readHeader(Header** header, FILE* file){
    // scan ppm type
    fscanf(file, "%2s ", (*header)->type);
    handleSpacesAndComments(file);

    // scan width of image
    fscanf(file, "%d", &(*header)->width);
    handleSpacesAndComments(file);


    // scan height of image
    fscanf(file, "%d", &(*header)->height);
    handleSpacesAndComments(file);

    // scan maximum color value
    fscanf(file, "%d ", &(*header)->maxColor);
}

//This function writes header information to the file passed in
void writeHeader(Header* header, FILE* file){
    fprintf(file, "%s %d %d %d\n",
            header->type, header->width,
            header->height, header->maxColor
    );
}


//This function skips over comments on a line of code
void discardComments(FILE* file){
    int buffer;
    while ((buffer = (fgetc(file))) != EOF && buffer != '\n');
}

void handleSpacesAndComments(FILE* file){
    int buffer;
    do{
        // skip spaces
        while ((buffer = (fgetc(file))) != EOF && isspace(buffer));
        // check for comment
        if(buffer == '#') discardComments(file);
    } while (!isdigit(buffer));
    ungetc(buffer, file);
}


//This function allocates memory for a 2D pixel array
Pixel** allocateImage(int width, int height){
    //allocates an array of pixel pointers that represents the image height block
    Pixel** image = (Pixel**) malloc(sizeof(Pixel*) * height);

    //Loops through and sets each height pointer to point at a block of pixels representing the width of an image
    for(int i = 0; i < height; i++){
        image[i] = (Pixel*) malloc(sizeof(Pixel) * width);
    }
    return image;
}

//This function frees the memory allocated for a 2d array
void freeImage(Pixel** image, Header* header){
    //First frees the rows 
    for(int i = 0; i < header->height; i++){
        free(image[i]);
    }

    //Frees the pixel pointer array
    free(image);
}

//This function reads in all pixels of the image passed in
void readImage(FILE* file, Pixel*** image, Header* header){
    //Reads in all pixels from the image file and stores it in the 2d pixel array
    for(int i = 0; i < header->height; i++){
        fread((*image)[i], sizeof(Pixel), header->width, file);
    }
}

//This function resizes the image to the height and width the user chose
void writeResizeImage(FILE* file, Pixel** image, int height, int width, Header* header){
    //Allocates memory for the new resized image with a new header with the dimesnions of the resized
    Pixel** resizedImage = allocateImage(width, height);
    Header* resizedHeader = (Header*) malloc(sizeof(Header));

    //Initializes the resized header info to reflect the dimensions the user chose
    resizedHeader->height = height;
    resizedHeader->width = width;
    strcpy(resizedHeader->type, header->type);
    resizedHeader->maxColor = header->maxColor;

    //Resizes the image's width and height
    double relativeWidth = (double) header->width / width;
    double relativeHeight = (double) header->height / height;
    //Writes the resized header info to the outfile
    writeHeader(resizedHeader, file);
    
    //Traverses the 2d array and fills the resized image with select pixels from the original image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int row = (int)(i * relativeHeight);
            int column = (int)(j * relativeWidth);
            resizedImage[i][j] = image[row][column];
        }
        //Writes a block of the resized image to the file passed in
        fwrite(resizedImage[i], sizeof(Pixel), resizedHeader->width, file);
    }    
    
    //Frees the resized image memory
    freeImage(resizedImage, resizedHeader);
    free(resizedHeader);
}

//This function creates a negative image of what is passed in
void writeNegativeImage(FILE* file, Pixel** image, Header* header){
    //Writes the header info as it does not change
    writeHeader(header, file);
    //Allocates memory for a new 2d pixel array that will store the opposite values of the original image
    Pixel** negativeImage = allocateImage(header->width, header->height);

    //Iterates through the image to access individual pixels
    for(int i = 0; i < header->height; i++){
        for(int j = 0; j < header->width; j++){
            //Sets the negative image RGB values to 255 - the original RGB value
            negativeImage[i][j].red = 255 - image[i][j].red;
            negativeImage[i][j].blue = 255 - image[i][j].blue;
            negativeImage[i][j].green = 255 - image[i][j].green;
        }
        //Writes the new values to the outfile
        fwrite(negativeImage[i], sizeof(Pixel), header->width, file);
    }
    //Frees the negative image memory
    freeImage(negativeImage, header);
}
