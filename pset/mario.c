#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int N;
    do
    {
        printf("height: ");
        N = GetInt();
    }
    while(N < 0 || N>23);
    
    for(int i=1; i<N+1; ++i)
    {
        for(int j=1, len = N-i+1; j<len; ++j)
        {
            printf(" ");
        }
        for(int j=0, len = i+1; j<len; ++j)
        {
            printf("#");
        }
        printf("\n");
    }
}