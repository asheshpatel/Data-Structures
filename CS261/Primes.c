/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    June 23, 2016
 * Filename:        Primes.c
 *
 * Overview:
 * This program will read in a number that sets an upper
 * limit, then print all prime numbers starting at 2 that
 * lead up to the upper limit.
 *
 * Input:
 * The input of this program will be an integer that sets 
 * an upper limit to the primes that will be printed out.
 *
 * Output:
 * The output of this program will be the prime integers 
 * leading up to the upper limit set by the user.
 ************************************************************/

#include <stdio.h>

int main()
{
  int n, i= 2, count, c;     //input, integers, counter variables
    
  printf("Enter the upper limit of prime numbers:\n");     //retrieve upper limit
  scanf("%d",&n);
    
  if (n >= 2)     //check that upper limit is high enough
  {
    printf("Prime numbers smaller or equal to %d are:\n", n);
  }
    
  //only continue if number is under upper limit
  for (count = 1; count < n; count++)
  {
    for (c = 2; c <= i - 1; c++)    //check that int i is not divisible
    {                               //by any ints leading up to itself
      if (i % c == 0)
        break;
    }
    
      if (c == i)                 //if loop was only stopped by int i, being divisble by self, i is prime
        printf("%d\n",i);
    i++;     //check next int
  }
  
  return 0;
}
