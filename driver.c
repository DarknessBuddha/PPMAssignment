
#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(int argc, char** argv){
    assert(argc == 4);
    
    FILE* inFile = fopen(argv[1], "r");
    FILE* resizedFile = fopen(argv[2], "w");
    FILE* negativeFile = fopen(argv[3], "w");

    assert(inFile && resizedFile && negativeFile);

    Header* header = (Header*) malloc(sizeof(Header));
    readHeader(&header, inFile);

    Pixel** image = allocateImage(header->width, header->height);

    readImage(inFile, &image, header);

    int height = 0;
    int width = 0;

    printf("Enter the new height for the image: ");
    scanf("%d", &height);
    assert(height > 0);

    printf("Enter the new width for the image: ");
    scanf("%d", &width);
    assert(width > 0);

    writeResizeImage(resizedFile, image, height, width, header);
    writeNegativeImage(negativeFile, image, header);

    freeImage(image, header);
    free(header);

    fclose(inFile);
    fclose(resizedFile);
    fclose(negativeFile);

    return 0;
}