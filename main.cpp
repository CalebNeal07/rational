// Program to find the nth element 
// of Stern's Diatomic Series
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
// function to find nth stern'
// diatomic series
long int findSDSFunc(long int n)
{
    // Initializing the DP array
    long int DP[n+1];
 
    // SET the Base case
    DP[0] = 0;
    DP[1] = 1;
 
    // Traversing the array from 
    // 2nd Element to nth Element
    for (long int i = 2; i <= n; i++) {
         
        // Case 1: for even n
        if (i % 2 == 0)
            DP[i] = DP[i / 2];
         
        // Case 2: for odd n
        else
            DP[i] = DP[(i - 1) / 2] +
                        DP[(i + 1) / 2];
    }
    return DP[n];
}
 
// Driver program
int main()
{
    long int n = 23483497723467;    
    cout << findSDSFunc(n) << endl;    
    return 0;
}