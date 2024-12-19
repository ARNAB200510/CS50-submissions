#include <cs50.h>
#include <stdio.h>

void mario(int); // To print the pyramid

int main(void)
{
    int height;

    do
    {
        height = get_int("Height:");
    }
    while (height < 1 || height > 8);

    mario(height);
}

void mario(int h)
{
    for (int i = 0; i < h; i++)
    {
        for (int sp = 0; sp < h - i - 1; sp++) // For the spaces at the beginning
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++) // For the first pyramid
        {
            printf("#");
        }

        for (int sp2 = 0; sp2 < 2; sp2++) // For the second set of spaces
        {
            printf(" ");
        }

        for (int j1 = 0; j1 < i + 1; j1++) // For the second pyramid
        {
            printf("#");
        }

        printf("\n");
    }
}