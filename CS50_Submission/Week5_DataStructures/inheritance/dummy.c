#include <stdio.h>
#include <stdlib.h>

// typedef struct dummy
// {
//     char array[2];

// }dummy;

int main()
{
    // dummy* start = malloc (sizeof (dummy));
    // start -> array[1]= 'b';
    // start -> array[0] = 'b';
    // char p1 = start -> array[1];
    // printf("%c",p1);
    int array[2];
    array[1] =1;
    printf("%d", *(array + 1) );
}
