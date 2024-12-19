#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(int argc,char* argv[])
{
    uint16_t sample = 425;
    uint16_t med = sample;
    printf("Sample");
    printf("%hu",sample);
    float b = atof(argv[1]);
    printf("Factor:");
    printf("%f",b);
    sample = sample * b;
    printf("OUTPUT");
    printf("%hu",sample);





}
