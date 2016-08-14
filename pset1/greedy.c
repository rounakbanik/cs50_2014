/*
 * This program implements the 'Greedy Algorithm
*/

#include<cs50.h>
#include<math.h>
#include<stdio.h>

//Function to get the change owed to the user
float GetChange(void);

int main(void)
{
    int coins= 0;
    
    //Get the amount of money owed to the user
    float dollars = GetChange();
    
    //Convert the value to cents (and store it in an int)
    float temp = roundf(dollars*100);
    int cents = (int) temp;
    
    //Calculate number of coins
    int i,j;
    for(i=25,j=0; j<4; i/=5, j++)
    {
      if(j==1)
      {
       coins = coins + cents/10;
       cents = cents%10;
       i=25;
      }
      else
      { 
       coins = coins + cents/i;
       cents = cents%i;
      }
    }
    
    //Print number of coins
    printf("%d\n", coins);
    
}

float GetChange(void)
{
    float f;
    printf("O hai! "); 
    do
    {
      printf("How much change is owed?\n");
      f = GetFloat();
    }
    while(f<0);
    return f;
}


