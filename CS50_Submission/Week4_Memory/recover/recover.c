#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define block_size 512

FILE *output;
char filename[100];
int main(int argc, char *argv[])
{
    // Check for command line
    if (argc != 2)
    {
        printf("Usage:./recover File_name\n");
        exit(1);
    }
    // Open card
    FILE *card = fopen(argv[1], "r");
    // Check the validity of the file
    if (card == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    // Buffer for each cluster of size 512B
    uint8_t buffer[block_size];
    // Store how many JPEGS have been created
    int count = 0;
    // Check whether a JPEG is being written
    bool check = false;
    // Check for EOF
    while (fread(buffer, 1, 512, card))
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (check == false)
            {
                // JPEG file initialization
                check = true;
                count++;
                sprintf(filename, "%03i.jpg", count - 1);
                output = fopen(filename, "w");
                // Write onto the JPEG file
                fwrite(buffer, block_size, sizeof(uint8_t), output);
            }
            else
            {
                // Close the previous JPEG file

                fclose(output);
                // Initialize a new JPEG file
                count++;
                sprintf(filename, "%03i.jpg", count - 1);
                output = fopen(filename, "w");
                // Start writing into the new JPEG file
                fwrite(buffer, block_size, sizeof(uint8_t), output);
            }
        }
        else
        {
            if (check == true)
            {
                // Keep writing onto the file
                fwrite(buffer, block_size, sizeof(uint8_t), output);
            }
        }
    }
    fclose(output);
    fclose(card);
}
