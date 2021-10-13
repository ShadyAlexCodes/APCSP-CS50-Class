// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize <size> <infile> <outfile>\n");
        return 1;
    }


    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    float resizeNumber = atof(argv[1]);
    float MAX = 100;
    float MIN = 0;

    if(resizeNumber > MAX | resizeNumber <= MIN)
    {
        printf("The resize factor number is between 1\n");
        return 0;
    }

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }



    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

//    BITMAPINFOHEADER biNew;
//    BITMAPFILEHEADER bfNew;

//    biNew = bi;
//    bfNew = bf;

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    printf("Resize Number: %f\n", resizeNumber);
    // Initalialized inital width and height as the width and height of infile
    // Easier than making new variabvles
    int initialWidth = bi.biWidth;
    int initialHeight = bi.biHeight;
    printf("Original Width: %d\n", bi.biWidth);
    printf("Original Height: %d\n", bi.biHeight);

    // Because of the initialization above, biWidth and hieght can be maniupulated
    bi.biWidth *= resizeNumber;
    bi.biHeight *= resizeNumber;

    printf("New Width: %d\n", bi.biWidth);
    printf("New Height: %d\n", bi.biHeight);
    printf("RGBTRIPLE: %lu\n", sizeof(RGBTRIPLE));

    // Determine padding for scanlines
    int initialPadding = (4 - (initialWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int finalPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    // bi.biSize is the number of bytes required by the structure.
    // bi.biSizeImage is the size, in bytes, of the images.
    // bf.bfSIze is the size in bites of a bitmap file.

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + finalPadding) * abs(bi.biHeight);
    //          Pixel information                       Padding Information                 Bitmap Number                                           Add 54 for new line
    bf.bfSize = ((bi.biWidth * abs(bi.biHeight)) * 3) + (finalPadding * abs(bi.biHeight))  + bf.bfOffBits;
    // MAKE SURE EVERYTHING IS ABOVE HERE

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);




// Lets try moving the RGBTRIPLE out here..


                    printf("Original Padding: %d \n", initialPadding);
                    printf("Final padding: %d \n", finalPadding);

    // Create our row and width loops right here..

    // Iterate over infile's scanlines, more specifically the hiehgt
    for(int i = 0; i < abs(initialHeight); i++) {
            // Height has the be recopied by the *resizeNumber times
            for(int j = 0; j < resizeNumber; j++) {
                // Ensure that the remaining padding is covered from the infile
                // Multiply by 3 to get the number of bytes

                fseek(inptr, (54 + ((initialWidth * 3 + initialPadding) * i)), SEEK_SET);

                    // Iterate over pixels in the scaneline, more specifically the width
                    for(int k = 0; k < initialWidth; k++) {

                        // Temp Storage
                        RGBTRIPLE triple;

                        // Read the RGB triple from the infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        // Write the RGBTRIPLE to the outfile
                        for(int l = 0; l < resizeNumber; l++) {
                                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                        }
                    }

                // Skip over padding if any


                // Add the final padding of the outfile
                for (int m = 0; m < finalPadding; m++)
                {
                    fputc(0x00, outptr);
                }
            }

    }



/*
    Start with a 3x2 drawing to represent the original image.

    +-----+-----+-----+
    | 0,0 | 1,0 | 2,0 |
    +-----+-----+-----+
    | 0,1 | 1,1 | 2,1 |
    +-----+-----+-----+

    If we multiply the image by 2 (doubles the image..) it becomes a 6x4 image
        - We enlarge the picture
        - We must enlarge the pixels by doubling them in all directions
        - So each pixel is now four pixels in the new image..
        - So the size grows the square by the multiplier.
        ** So like a multiplier of 3 would mean each pixel becomes 9 pixels in the new image.
    +-----+-----+-----+-----+-----+-----+
    | 0,0 | 0,0 | 1,0 | 1,0 | 2,0 | 2,0 |
    +-----+-----+-----+-----+-----+-----+
    | 0,0 | 0,0 | 1,0 | 1,0 | 2,0 | 2,0 |
    +-----+-----+-----+-----+-----+-----+
    | 0,1 | 0,1 | 1,1 | 1,1 | 2,1 | 2,1 |
    +-----+-----+-----+-----+-----+-----+
    | 0,1 | 0,1 | 1,1 | 1,1 | 2,1 | 2,1 |
    +-----+-----+-----+-----+-----+-----+

    What's the easiest way to do this?
        - How to double image pixels?
            - Create a loop to fetch each single pixel
                - Nest a loop that writes to all new locations in image.

    Think about it as rows and columns that you loop through (so nested loops)
    So we need to loop through left and right the width of this then the height.
    So the first loop is the height because we start with (0, 0) then (1, 0) etc.

    **REMINDER**
    There must be padding added before we loop to the next row. So part of it sorta lives under
    a loop that goes through each pixel in a singular row.


*/


            /*

                        - Don't need to keep track of pointers.
                            - Why?
                                - ** Pointer reads and moves onto the next pixel each time the fread() function is read


                // So read to the file.

                We want the input point to skip over the padding
                so the outer loop (newHeight loop) helps bring us to the next row of pixels

                Then we want to manually add padding to our output file
                so everything is on the same page when reading and writing..

                So we only keep track of 2 pointes here.

                Ex.
                    - When I run an f Read the I moves
                        +-----+-------+----+
                        | 0,0O | 1,0I | 2,0|
                        +-----+-------+----+
                    - When I run an f write the J moves
                        +-----+-------+----+
                        | 0,0 | 1,0JI | 2,0|
                        +-----+-------+----+

                After we reach the end we need to skip the input over the padding
                Then we will manually add the padding to the output only.

                fseek (https://www.geeksforgeeks.org/fseek-in-c-with-example/)
                int fseek(FILE *pointer, long int offset, int position)
                pointer: pointer to a FILE object that identifies the stream.
                offset: number of bytes to offset from position
                position: position from where offset is added.

            */



            /*

                Now we must add the padding in the loop to the output.
                REMINDER: Padding is just a byte of zeros so it's represented by
                0x00. We just right 0x00 number of resizeNumber times.

                fputc (https://www.geeksforgeeks.org/fgetc-fputc-c/)
                int fgetc(FILE *pointer)
                pointer: pointer to a FILE object that identifies

https://cs50.stackexchange.com/questions/33159/pset3-resize-more-comfortable-resizing-f-1-correctly-but-pixels-are-differ
https://cs50.stackexchange.com/questions/23291/problem-with-horizontal-resizing-pset4-resize
https://www.google.com/search?q=resize+cs50+sizing+down+rgb+pixels+site:cs50.stackexchange.com&safe=strict&rlz=1C1GGRV_enUS760US760&sa=X&ved=2ahUKEwjokeOK_LLmAhXHrJ4KHeczCI0QrQIoBDAAegQIARAN&biw=1600&bih=789

            */


/*
    for (int i = 0; i < newHeight; i++)
    {
        // Figure out a way to get old bytes..
        fseek(inptr,  newPadding, SEEK_CUR);

        // Iterate over pixels in scanline
        for (int resizeHeight = 0; resizeHeight < resizeNumber; resizeHeight++)
        {
            // Temporary storage
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Begin to write each pixel resizeNumber times

            for(int resizeWidth = 0; resizeWidth < resizeNumber; resizeWidth++){
                fwrite(&triple, sizeof(RGBTRIPLE), 1, inptr);
            }
        }

            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
    }
    */

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}
