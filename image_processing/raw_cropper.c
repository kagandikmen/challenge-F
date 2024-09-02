// Raw image cropper
// Author: Kagan Dikmen
// Created: 2024-08-21
// Modified: 2024-09-02 (status: working fine)

#include <stdio.h> 
#include <stdlib.h>

//////////////////////////////////////////////////////
//// Replace this part with your own parameters
//////////////////////////////////////////////////////

#define WIDTH_IN_PIXELS 750
#define HEIGHT_IN_PIXELS 750
#define NUM_CHANNELS 1

#define PATH_SOURCE "/path/to/image/image.raw"
#define PATH_TARGET "/path/to/target/image/image.raw"

#define CROP_BEFORE_ROW 373         // not inclusive
#define CROP_AFTER_ROW 501          // inclusive
#define CROP_BEFORE_COLUMN 311      // not inclusive
#define CROP_AFTER_COLUMN 439       // inclusive

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
 
int main() { 
    FILE *fp; 
    size_t size = WIDTH_IN_PIXELS * HEIGHT_IN_PIXELS * NUM_CHANNELS * sizeof(unsigned char); 
    unsigned char *image_data = (unsigned char *)malloc(size); 
 
    fp = fopen(PATH_SOURCE, "rb"); 
    if (fp == NULL) { 
        fprintf(stderr, "Error opening file\n"); 
        return 1; 
    } 
 
    fread(image_data, 1, size, fp); 
 
    fclose(fp); 

    fp = fopen(PATH_TARGET, "a"); 

    for(int i=CROP_BEFORE_ROW; i < CROP_AFTER_ROW; i++) {
        for(int j=CROP_BEFORE_COLUMN; j < CROP_AFTER_COLUMN; j++ ) {
            unsigned char temp = *(image_data + i*WIDTH_IN_PIXELS + j);
            fprintf(fp, "%c", temp);
        }
        // printf("\n");
    }
    
    fclose(fp);
    free(image_data); 
    return 0; 
} 
