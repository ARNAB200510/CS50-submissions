#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calc_words(char array[]); // Calc the no of stuffs

int calc_letters(char array[]);

int calc_sentences(char array[]);

int calc_index(int, int, int);

int main(void)
{
    char sent[1000000]; // Only for the upper limit

    printf("Enter the text:");
    fgets(sent, sizeof(sent), stdin);

    int words = calc_words(sent);

    int letters = calc_letters(sent);

    int sentences = calc_sentences(sent);

    int result = calc_index(words, letters, sentences);

    if (result > 1 && result < 16)
    {
        printf("Grade %d\n", result); // Only grade between 1 and 16 needed
    }

    else if (result < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade 16+\n");
    }
}

int calc_words(char array[])
{
    int space = 0;

    for (int i = 0, l = strlen(array); i < l - 1; i++) // looping through the paragraph
    {
        char c = array[i];

        if (c == ' ')
        {
            space += 1;
        }
    }
    return space + 1; // No of words is space + 1 + special
}

int calc_letters(char array[])
{
    int alpha = 0;

    for (int i = 0, l = strlen(array); i < l - 1; i++)
    {
        char c = array[i];

        if (isalpha(c))
        {
            alpha += 1;
        }
    }
    return alpha;
}

int calc_sentences(char array[])
{
    int senten = 0;

    for (int i = 0, l = strlen(array); i < l - 1; i++)
    {
        char c = array[i];

        if (c == '!' || c == '.' || c == '?') // Sentences end with !,. or ?
        {
            senten += 1;
        }
    }
    return senten;
}

int calc_index(int wor, int lett, int sent)
{

    float L = (100.0 / wor) * lett; // letters and sentences should be out of 100

    float S = (100.0 / wor) * sent;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}