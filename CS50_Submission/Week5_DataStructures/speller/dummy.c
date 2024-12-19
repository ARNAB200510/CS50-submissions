#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a = 2;
    int *p;
    p = &a;
    *p = 1;
    printf ("%d",a);
}
