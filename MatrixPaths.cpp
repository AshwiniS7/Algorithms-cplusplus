// Determine shortest path in a matrix with weighted edges
// Can only go right or down
// Dynamic programming

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <deque>
#include <set>

// Uses DP to find the shortest path from left top corner of matrix to bottom right corner of matrix

using namespace std;

int main()
{
  int M,N;
  cin >> M;
  cin >> N;
  int matrix[M][N];
  int dp[M][N];

  for (int a = 0; a < M; a++)
  {
    for (int b = 0; b < N; b++)
    {
      cin >> matrix[a][b];
    }
  }


  dp[0][0] = matrix[0][0];
  for (int c = 0; c < M; c++)
  {
    for (int d = 0; d < N; d++)
    {
      if (c == 0 && d == 0)
      {
      }
      else if (c == 0)
      {
        dp[c][d] = dp[c][d-1] + matrix[c][d];
      }
      else if (d == 0)
      {
        dp[c][d] = dp[c-1][d] + matrix[c][d];
      }
      else
      {
        dp[c][d] = min(dp[c-1][d], dp[c][d-1]) + matrix[c][d];
      }
    }
  }
  cout << dp[M-1][N-1] << endl;
}
