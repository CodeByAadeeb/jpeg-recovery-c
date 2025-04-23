#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int file_count = 0;
    char filename[9];
    FILE *img = NULL;
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //how to make a condition for 1st jpeg
            //i know that 000.jpeg is the first jpeg
            if (img == NULL)
            {
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                file_count++;
                // should i write all the 512 bytes bcoz there is a chance of slack space and should also be written
                //if nit how to stop writing when the jpeg ends
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                file_count++;
            }
            //how to make the header for the jpeg
            //to start writing in a new file

        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }

    }
    fclose(img);
    fclose(card);
    return 0;
    //i dont undertand are there 512 bytes in total in a memory card or the storage is grouped into 512 bytes each unit
    //in the fread size parameter do i enter 512 bytes or like 4 bytes of 512 byte blocks

}
