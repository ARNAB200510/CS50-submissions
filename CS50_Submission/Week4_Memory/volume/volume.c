// Modifies the volume of an audio file

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Creete a buffer dynamically for storing input header
    uint8_t *buff1 = malloc(HEADER_SIZE * sizeof(uint8_t));
    fread(buff1, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(buff1, sizeof(uint8_t), HEADER_SIZE, output);
    // Copy the channels
    // Create a buffer to store the channels
    int16_t *buff2 = malloc(sizeof(int16_t));
    while (fread(buff2, sizeof(int16_t), 1, input))
    {
        *buff2 = (int16_t) ((float) (*buff2) * factor);
        fwrite(buff2, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
    free(buff1);
}
