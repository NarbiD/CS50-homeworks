#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]) 
{ 
    if(argc != 2) 
    {
        printf("WRONG!\n");
        return 1;
    }
    
    int* key = malloc(strlen(argv[1]));
    for(int i=0,n=strlen(argv[1]); i<n; ++i)
    {
        if(!isalpha(argv[1][i])) 
        {
            printf("WRONG!\n");
            return 1;
        }
        key[i] = toupper(argv[1][i]);
    }
    
   string s = GetString();
   for(int i = 0, len = strlen(s), count = 0; i<len; ++i)
   {
        char c;
        if(isalpha(s[i]))
        {
            if(islower(s[i]))
            {
                c = 'a' + ((s[i] - 'a') + (key[count] - 'A'))%26;
            }
            else 
            {
                c = 'A' + ((s[i] - 'A') + (key[count] - 'A'))%26;
            }
            if(count < strlen(argv[1]) - 1)
            {
                count++;
            }
            else
            {
                count = 0;
            }
        }
        else 
        {
            c=s[i];
        }
        printf("%c", c);
       
   }
      
   printf("\n");
   return 0;
}