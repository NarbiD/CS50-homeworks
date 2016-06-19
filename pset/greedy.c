#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float f;
    int count=0;
    printf("O hai! ");
    do
    {
        printf("How much change is owed?\n");
        f = GetFloat();
    }
    while(f<0);
    
    f *= 100;
    int i = (int)roundf(f);

    count += i / 25;
    count += (i % 25) / 10;
    count += (i % 25 % 10) / 5;
    count += (i % 25 % 10 % 5);

    printf("%d\n", count);
}
