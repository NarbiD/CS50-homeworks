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
    
   int k = atoi(argv[1]);
   string s = GetString();
   for(int i = 0, len = strlen(s); i<len; ++i)
   {
      char c;
      if(isalpha(s[i]))
      {
          if(islower(s[i])) 
          {
              c = 'a' + ((s[i]-'a'+k)%26);
          }
          else 
          {
              c = 'A' + ((s[i]-'A'+k)%26);
          }
      }
      else 
      {
          c = s[i];
      }
      printf("%c", c);
   }
   printf("\n");
   return 0;
}