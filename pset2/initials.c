#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) 
{ 
   string s;
   s = GetString();
   if(isalpha(s[0]))
   {
       printf("%c", toupper(s[0]));
   }
   for(int i = 0, len = strlen(s); i < len; ++i)
   {
       char c = s[i+1];
       if(s[i] == ' ' && isalpha(c))
       {
           c = toupper(c);
           printf("%c", c);
       }
   }
   printf("\n");
}