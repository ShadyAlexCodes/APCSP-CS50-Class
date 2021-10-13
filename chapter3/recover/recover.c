#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{


    if(argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    /*
        We're looking for jpg signatures, which are the first 4 bytes
        at the beginning of each 512 block. So we need to create a buffer to store
        each of these 4 invidual bytes correctly.
    */
    BYTE buffer[512];

    // Create a counter to store the number of pictures, but start at one so we go up to 50
    int imageCounter = 0;

    // Create a new file type named `newImage` and set it to NULL
    FILE* newImage = NULL;

    // Create an array to store each picture breifly
    char image[8];

    /*

    fread is a boolean value, and would return 0 (false) if you cant read 512 bytes, and 1 (true) if you can.
    Essentially we test theory with the loop condition `while`. So it reads one block each iteration and leaves once it reaches the end
    The fread will read 1 block of 512 bytes from the file referenced in the inptr and write it into memory location described by our buffer
    The function fills and returns the number of successfully read blocks.

    */
    while(fread(&buffer, 512, 1, inptr) == 1)
    {
        // Check the beginning and the end of the image for .jpg signatures
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Make sure that everything is closed before beginning
            if (imageCounter > 0)
            {
                // Close any already open files
                fclose(newImage);
            }


            // We're giving the string an array that will store the output
            sprintf(image, "%03i.jpg", imageCounter);

            // Open and Write to the new Image
            newImage = fopen(image, "w");

            // We want to make sure that this image isn't a null value
            if (newImage == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", image);
                return 3;
            }

            // Increase the number of images read
            imageCounter++;
        }
        // If the image is not null
        if(newImage != NULL)
        {
            // write it one more time
            fwrite(buffer, 512, 1, newImage);
        }
      }
      // Close everything before grace kills me.
    fclose(newImage);
    fclose(inptr);
    return 0;
 }
