#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Check if file opened properly
    if (card == NULL)
    {
        printf("Could not open %s. \n", argv[1]);
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // Amount of JPEGs found
    int jpegCount = 0;

    // Name of JPEGs
    char filename[8];

    // Create the image file
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {

    // Create JPEGs from the data

        // Check if we found a JPEG file by studing it's header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // We are inside a while, so we could probably have a JPEG file already open from before
            // therefore we need to check if img is not null, because if it is, it means we have a JPEG
            // file already opened from before and we need to close it to open a new one
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename for the JPEG
            // %03i means print an int with 3 digits and "jpegCount" is what will get written in those 3 digits
            sprintf(filename, "%03i.jpg", jpegCount++);

            // Open a new file to write the newly found JPEG with the filename we just created
            img = fopen(filename, "w");
        }

        // Check if we have an img file open (will mean we found a new JPEG file)
        // per the last lines of code and then we Write the current found JPEG file
        if (img != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // If we are here we are out of the While so there are no data left to read so we close the last img
    if (img != NULL)
    {
        fclose(img);
    }

    // We close the card we were reading beacuse we have fully read it
    fclose(card);
}
