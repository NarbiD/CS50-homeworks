#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// size of memory block
#define blockSize 512

// length of outfile names
#define titleLength 8

// define outfile names
void defFileName(char* title, uint8_t num);


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
    
    // identify the first characters of jpg
    uint8_t jpgHead1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t jpgHead2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    // pointer to the outfiles
    FILE* outptr;
    
    // the names of the output files
    char* title = malloc(titleLength);
    
    // number of current outfile
    uint8_t count = 0;
    
    // buffer memory for storing blocks
    uint8_t* buffer = malloc(blockSize);
    
    // ignoring garbage
    do
    {
        fread(buffer, blockSize, 1, inptr);
    }
    while(memcmp(jpgHead1, buffer, 4) && memcmp(jpgHead2, buffer, 4));
    
    // read card and create result files
    do
    {
        // write the first block of file
        if (!(memcmp(jpgHead1, buffer, 4) && memcmp(jpgHead2, buffer, 4)))
        {
            // it works in each iteration except the first
            if (count!=0) 
            {
                fclose(outptr);
            }
            
            // create the new file for image
            defFileName(title, count++);
            outptr = fopen(title, "w");
            if (outptr == NULL)
            {
                printf("Could not open new file for write.\n");
                return 3;
            }
            
            fwrite(buffer, blockSize, 1, outptr);
        }
        // wtite the other blocks
        else 
        {
            fwrite(buffer, blockSize, 1, outptr);
        }
        
    } while (fread(buffer, blockSize, 1, inptr));
    
    // frees memory
    free(title);
    free(buffer);
    
    // close infile and outfile
    fclose(inptr);
    fclose(outptr);
    
    return 0;
}

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
