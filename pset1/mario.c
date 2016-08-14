/* 
 * This program prints a mario half pyramid of a certain height
 */

#include <stdio.h>
#include <cs50.h>

//Function to get an appropriate height from the user
int GetHeight(void);

int main(void)
{
   //Prompt the user for the height
   int height = GetHeight();
   
   //Generate the half pyramid
   for(int i=0; i<height; i++)
   {
     //Generate spaces in a row
     for(int j=0; j<=height-i-2; j++)
        printf(" ");
        
     //Generate hashes in a row
     for(int k=0; k<i+2; k++)
       printf("#");
       
     //Generate a new line
     printf("\n");
   }
   
}

int GetHeight(void)
{
    int n;
    //Prompt for input until the user gives a desirable integer
    do
    {
      printf("Height: ");
      n = GetInt();
    }
    while(n<0 || n>23);
    return n;
}  
