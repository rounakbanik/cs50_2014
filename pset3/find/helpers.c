/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int low=0, mid, high=n-1;
    bool check= false;
    
    while(low<=high)
    {
      mid=(low+high)/2;
      
      if(values[mid]==value)
      {
        check= true;
        break;
      }
      
      else if(values[mid]> value)
        high= mid-1;
      else
        low= mid+1;                   
    }
    return check;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int i=0; i<n; i++)
    {
      for(int j=0; j<n-1-i; j++)
        if(values[j]>values[j+1])
        {
          int temp= values[j];
          values[j] = values[j+1];
          values[j+1]= temp;
        }
    }    
    return;
}
