#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
// Store points in an array for easy execution
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int sum = 0; // Initially sum=0

    for (int i = 0, l = strlen(word); i < l; i++) // Iterating through the word
    {
        char u = word[i]; // converted character to a variable for good layout

        if isalpha (u) // Only alphabets given points
        {
            char m = toupper(u); // Only uppercase alphabets have values assigned

            int c = m; // Getting the ASCII value of the alphabet

            for (int s = 0; s < 26; s++) // This will assign POINTS[] values to the alpahbet
            {
                if (c == 65 + s)
                {
                    sum = sum + POINTS[s];
                }
            }
        }
    }

    return sum;
}
