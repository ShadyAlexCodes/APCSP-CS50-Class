


// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // UNDERWOOD: Changed the number of arguments to 4 and changed the error string
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    // Remember filenames
    // UNDERWOOD: Changed the arguments to what they should be for the input and output files
    char *infile = argv[2];
    char *outfile = argv[3];

    // UNDERWOOD: Create a new variable for the scale of the resize and assigned the appropriate
    //            argument to it.
    float scale = atof(argv[1]);

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    // UNDERWOOD: I opened the file with an w+ so I could read and write the file at the same time
    //            If you do not do this, even though you can move the cursor, a read of the file
    //            does not move the cursor. (Took a little to discover that)
    FILE *outptr = fopen(outfile, "w+");
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

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // UNDERWOOD: Need to remember some variables from the header so I can use them
    //            to read the input file
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    // UNDERWOOD: Now I need to change 4 different header variables for the new larger
    //            or smaller output file that I'm creating.
    //            First I'll change the height and width variables by multiplying them
    //            by the scale that was input on command line
    bi.biWidth = oldWidth * scale;
    bi.biHeight = oldHeight * scale;

    // UNDERWOOD: Since the padding in the input file is different from the padding in the
    //            output file then I'll figure out both of them right here. I can use the
    //            algorithm that is already here for padding
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth  * sizeof(RGBTRIPLE)) % 4) % 4;

    // UNDERWOOD: Now I'll change the other header information.
    //            bfSize in the BITMAPFILEHEADER. It is the total size of file, Pixel bytes, padding bytes, and header bytes
    //            bi.biWidth and bi.biHeight are both measures of pixels so I need to multiply by
    //            3 to get byte information. newPadding is just the padding per row so I need to
    //            multiply it by bi.biHeight. bi.biHeight is also negative so you must use the absolute
    //            value to make sure you get a negative number. The bf.bfOffBits field is the size of the header
    //            biSizeImage in the BITMAPINFOHEADER. It is the bfSize minus the header total.
    bf.bfSize = (((bi.biWidth * abs(bi.biHeight)) * 3) + (newPadding * abs(bi.biHeight)) + bf.bfOffBits);
    bi.biSizeImage = bf.bfSize - bf.bfOffBits;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    // UNDERWOOD: Deleted this line for padding since I already did this

    // Iterate over infile's scanlines
    // UNDERWOOD: Since we are reading the input file (the old file size) we need to change the loop variable
    //            to reflect the height and width of the source file
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        // UNDERWOOD: Since we are reading the input file (the old file size) we need to change the loop variable
        for (int j = 0; j < oldWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            // UNDERWOOD: No matter the size of scale we always read just one pixel at a time
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Write RGB triple to outfile
            // UNDERWOOD: depending on the scale we need to do a few differnt things. If the scale is
            //            greater then or equal to one, meaning we are making it bigger, in that case we
            //            have to write the
            //            pixel we read the number of times of scale. If it is less then 1 it means
            //            that we want to reduce the size of the file. This program will only use .5
            //            for file reduction, other numbers will cause us to change the pixel
            //            information as well.
            if (scale >= 1) {
                // UNDERWOOD: A simple for loop, to write the pixel we read, scale number of times
                for (int k = 0; k < scale; k++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            else {
                // UNDERWOOD: In this case I need to only write the pixel I read but then use the
                //            seek command to skip over the next pixel. I also need to advance the
                //            counter of the for loop so it doesn't write as many columns of info.
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                j++;

            }
        }

        // Skip over padding, if any in the source file
        fseek(inptr, oldPadding, SEEK_CUR);

        // Then add it to the correct amount to the new file
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }

        // UNDERWOOD: The part of the program is for expanding or reducing vertically.
        //            Now, if the scale is over one, I need to write that whole row as many times
        //            as scale - 1. If it is less then one I need to skip over the next row in
        //            the source file and not read that row.
        if (scale > 1) {
            // UNDERWOOD: Now I will just move the cursor in my output file to read the last row
            //            I have just writen to the output file. I must now move the cursor back
            //            to the beginning of the line and read the whole line at once, (excluding
            //            the padding) Notice
            //            I do not want this to happen if scale is 1 that is why my if statement
            //            is scale > 1 and I use an else if instead of an else.

            // UNDERWOOD: Now take the cursor and move it back all the way to the beginning of
            //            the previous line
            fseek(outptr, (sizeof(RGBTRIPLE) * bi.biWidth + newPadding) * -1 , SEEK_CUR);

            // UNDERWOOD: Create an array of RGBTRIPLE type the width of the new pixel width so
            //            I can read the whole row, but not the padding. Then I have to skip the
            //            padding that I did not read in the last row because I need my cursor to be
            //            at the beginning of the next line for writing
            RGBTRIPLE row[bi.biWidth];
            fread(&row, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            fseek(outptr, newPadding, SEEK_CUR);




            // UNDERWOOD: A simple for loop to write the row we read, scale - 1 number of times
            for (int l = 0; l < scale - 1; l++) {
                fwrite(row, sizeof(RGBTRIPLE), bi.biWidth, outptr);
                // UNDERWOOD: I still need to add the padding to the row I just wrote to the
                //            output file.
                for (int k = 0; k < newPadding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        // UNDERWOOD: I use this to catch the 0.5 but I don't want to make it equal to 0.5 because
        //            It's a float and I worried about errors
        else if (scale > 0 && scale < 1) {
            // UNDERWOOD: In this case I need to only skip over the next line in the source file
            //            completely and that means skipping the pixels and the padding and increment
            //            the loop variable as well so it doesn't go too far.
            //printf("%ld    ", ftell (inptr));
            fseek(inptr, sizeof(RGBTRIPLE) * oldWidth + oldPadding, SEEK_CUR);
            //printf("%ld    \n", ftell (inptr));
            i++;
            //return 1;
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}