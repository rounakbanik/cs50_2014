/*
 * This program implements the Caesar cipher
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
       
    //Checks validity of the command-line argument
    if(argc!=2 || atoi(argv[1])==0)
    {
      printf("Key not found.");
      return 1; 
    } 
    
    //If argument is valid, proceeds to accept and encrypt text using appropriate Caesar shift
    else
    {
      int k = atoi(argv[1]);
      k= k%26;
      string plain = GetString();
      int n= strlen(plain);
      for(int i=0; i<n; i++)
      {
        if(!isalpha(plain[i]))
          printf("%c", plain[i]);
        else
        {
          if((isupper(plain[i]) && (plain[i]+k)>'Z') || (islower(plain[i]) && (plain[i]+k)>'z') )  
            plain[i] = plain[i]+ k- 26;
          else
            plain[i] = plain[i] + k;
          printf("%c", plain[i]);
        }
      }
      printf("\n");
    }
}
