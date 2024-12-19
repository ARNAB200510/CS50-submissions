#include<stdio.h>

int n = 0;
void change();

int main()
{
    change();
    printf("%d",n);
}

void change()
{
    n++;
}