/*************************
 *Ivan Lin
 *Lucia Wang
 *CPSC 2310 your Section
 *ilin@clemson.edu
 *************************/
#include "functions.h"

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

void writeHeader(Header* header, FILE* file){
    fprintf(file, "%s %d %d %d\n",
            header->type, header->width,
            header->height, header->maxColor
    );
}

void discardComments(FILE* file){
    int buffer;
    while ((buffer = (fgetc(file))) != EOF && buffer != '\n');
}

void handleSpacesAndComments(FILE* file){
    int buffer;
    // skip spaces and check for comment until a digit is read
    do{
        // skip spaces
        while ((buffer = (fgetc(file))) != EOF && isspace(buffer));
        // check for comment
        if(buffer == '#') discardComments(file);
    } while (!isdigit(buffer));
    ungetc(buffer, file);
}

Pixel** allocateImage(int width, int height){
    Pixel** image = (Pixel**) malloc(sizeof(Pixel*) * height);
    for(int i = 0; i < height; i++){
        image[i] = (Pixel*) malloc(sizeof(Pixel) * width);
    }
    return image;
}

void freeImage(Pixel** image, Header* header){
    for(int i = 0; i < header->height; i++){
        free(image[i]);
    }
    free(image);
}

void readImage(FILE* file, Pixel*** image, Header* header){
    for(int i = 0; i < header->height; i++){
        fread((*image)[i], sizeof(Pixel), header->width, file);
    }
}

void writeResizeImage(FILE* file, Pixel** image, int height, int width, Header* header){
    Pixel** resizedImage = allocateImage(width, height);
    Header* resizedHeader = (Header*) malloc(sizeof(Header));
    resizedHeader->height = height;
    resizedHeader->width = width;
    strcpy(resizedHeader->type, header->type);
    resizedHeader->maxColor = header->maxColor;

    double relativeWidth = (double) header->width / width;
    double relativeHeight = (double) header->height / height;
    writeHeader(resizedHeader, file);
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int row = (int)(i * relativeHeight);
            int column = (int)(j * relativeWidth);
            resizedImage[i][j] = image[row][column];
        }
        fwrite(resizedImage[i], sizeof(Pixel), resizedHeader->width, file);
    }    
    
    freeImage(resizedImage, resizedHeader);
}

void writeNegativeImage(FILE* file, Pixel** image, Header* header){
    writeHeader(header, file);
    Pixel** negativeImage = allocateImage(header->width, header->height);
    for(int i = 0; i < header->height; i++){
        for(int j = 0; j < header->width; j++){
            negativeImage[i][j].red = 255 - image[i][j].red;
            negativeImage[i][j].blue = 255 - image[i][j].blue;
            negativeImage[i][j].green = 255 - image[i][j].green;
        }
        fwrite(negativeImage[i], sizeof(Pixel), header->width, file);
    }
    freeImage(negativeImage, header);
}
