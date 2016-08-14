/*
 * This program implements the Vigenere cipher
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Function checks if the string is composed entirely of alphabetical characters
int CheckString(string key);

int main(int argc, char* argv[])
{

    //Checks validity of the command-line argument
    if(argc!=2 || CheckString(argv[1])!=1)
    {
      printf("Invalid Key.\n");
      return 1; 
    } 
    
    //If the key is valid, then it proceeds to encrypt polyalbhabetically
    else
    {
      //Key and its length
      string key = argv[1];
      int length = strlen(key);
      
      //Capitalize the entire key for uniformity
      for(int a=0; a<length; a++)
        key[a]= toupper(key[a]);
      
      //PLaintext and its length
      string plain = GetString();
      int n= strlen(plain);
      
      //Counters for characters of key and characters of plaintext
      int i, j=0, k;
      
      //Loop to carry out the encryption
      for(i=0; i<n; i++)
      {
        if(!isalpha(plain[i]))
          printf("%c", plain[i]);
        else
        {
          if((isupper(plain[i]) && (plain[i]+key[j]-'A')>'Z') || (islower(plain[i]) && (plain[i]+key[j]-'A')>'z') )  
          {
            k = key[j]-'A';
            plain[i] = plain[i]+ k- 26;
            j++;
            j=j%length;
          } 
          else
          {
            k = key[j]-'A'; 
            plain[i] = plain[i] + k;
            j++;
            j=j%length;
          }
          printf("%c", plain[i]);
        }
      }
      printf("\n");
    }
}

int CheckString(string key)
{
    int n= strlen(key);
    int check=1;
    for(int i=0; i<n; i++)
    {  
       if(!isalpha(key[i]))
       {
        check=0;
        break;
       }
    }  
    return check; 
} 
