//======================================================================
//Author: James Anthony Ortiz
//File: knapsack.cpp
//Course: COP4531 - Analysis Of Algorithms
//Description: Assignment #3 - Implementation of the 0-1 Knapsack problem.
//This program will also display the weights and values contained 
//in the knapsack.
//Compile: g++ -std=c++11 knapsack.cpp -o knapsack
//=====================================================================


//Libraries used in program:
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <math.h>


using namespace std;

//Function Prototypes:
void printElemnts(int, int *, int *, int, int, int **);
void knapSack(int, int *, int *, int);
void createTestCase(const char*, int, int, int);

/* 
============================================================
   Function: knapSack()
   Description: Returns the optimal value that can be placed 
   in a knapsack of capacity W 
 
   Parameters:
   W   -  Knapsack capacity
   wt  -  array of weights
   val -  array of values
   n   -  number of elements in array

   Returns: Void
============================================================
*/

void knapSack(int W, int *wt, int *val, int n) 
{

  int i, w;
  int **K = new int*[n + 1];
  for (int i = 0; i <= n; i++)
    K[i] = new int[W + 1];

  for (i = 0; i <= n; i++) 
  {

    for (w = 0; w <= W; w++) 
    {
      if (i == 0 || w == 0)
        K[i][w] = 0;
      else if (wt[i - 1] <= w)
        K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
      else
        K[i][w] = K[i - 1][w];
    }
  }
  cout << "Maximum weight W of Knapsack: " << W << endl;
  //cout << K[n][W] << endl;
  printElemnts(W, wt, val, n, K[n][W], K);
  for (int i = 0; i <= n; i++)
    delete K[i];
  delete K;
}

/*
===========================================================================
  Function: printElemnts()
  Displays the maximum value that can be put in a knapsack of capacity W

  Parameters: 
  W   - knapsack capacity
  wt  - array of weights
  val - array of values
  n   - number of elements in array
  K   - table [][] with results. The last index [n][W] contains the answer

  Returns: void
============================================================================
*/

void printElemnts(int W, int *wt, int *val, int n, int result, int **K) 
{
  int w = W, i;
  int *arr = new int[n];
  int count = 0;
  for (i = n; i > 0 && result > 0; i--) {

    if (result == K[i - 1][w])
      continue;
    else {
      arr[count] = i;
      //cout << wt[i - 1] << " ";
      result = result - val[i - 1];
      w = w - wt[i - 1];
      count++;
    }
  }
  cout << "Number of elements : " << count << "\nOptimal Knapsack Value : " << K[n][W] << endl;
  sort(arr, arr + count);
  for (int j = 0; j < count; j++)
    cout << "Index in vector : " << arr[j] << "\nElement: " << val[arr[j] - 1] << endl;
}
 
//=====================================
//---------- Main Driver --------------
//=====================================
int main()
{
 
  //n - Number of Values:
  int n = 100;

  //w - Largest Capacity of Weights:
  int w = 335732;
 
  //Dynamically allocate two arrays 
  //corresponding to the size of n.
  int *val = new int[n];
  int *weights = new int[n];

  //Set all values to 1
  for (int i = 0; i < n; i++)
  {
    val[i] = 1;
  }

  //Calculate all weights, set them to an array.
  for (int i = 0; i < n; i++) 
  {
    weights[i] = round(1000 * pow((i + 1), .5));
  }

  //Call Knapsack DP Algorithm:
  knapSack(w, weights, val, n);

  //Remove Memory Allocation for Arrays
  delete val;
  delete weights;
 
  return 0;
}//End MAIN
