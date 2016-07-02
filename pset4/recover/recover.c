/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// size of memory block
#define blockSize 512

#define titleLength 8

void defFileName(char* title, uint8_t num)
{
    if((num / 10) == 0) 
    {
        sprintf(title, "%i%i%i.jpg", 0, 0, num);
    }
    else 
    {
        sprintf(title, "%i%i.jpg", 0, num);
    }
    return;
}

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 1)
    {
        printf("Usage: ./recover\n");
        return 1;
    }
    
    // open file of card
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.\n");
        return 2;
    }
    
    uint8_t jpgHead1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t jpgHead2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    char* title = malloc(titleLength);
    FILE* outptr;
    uint8_t count = 0;
    uint8_t* buffer = malloc(blockSize);
    
    do
    {
        fread(buffer, blockSize, 1, inptr);
    }
    while(memcmp(jpgHead1, buffer, 4) && memcmp(jpgHead2, buffer, 4));
    
    do
    {
        if (!(memcmp(jpgHead1, buffer, 4) && memcmp(jpgHead2, buffer, 4)))
        {
            if (count!=0) 
            {
                fclose(outptr);
            }
            
            defFileName(title, count++);
            outptr = fopen(title, "w");
            if (outptr == NULL)
            {
                printf("Could not open new file for write.\n");
                return 3;
            }
            fwrite(buffer, blockSize, 1, outptr);
        }
        else 
        {
            fwrite(buffer, blockSize, 1, outptr);
        }
        
    } while (fread(buffer, blockSize, 1, inptr));
    
    free(title);
    free(buffer);
    
    fclose(inptr);
    fclose(outptr);
    
    return 0;
}