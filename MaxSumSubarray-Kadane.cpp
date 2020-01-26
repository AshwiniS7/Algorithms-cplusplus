// Determine the maximum sum subarray (both 1D and 2D arrays)
// Uses Kadane's algorithm
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
#include <math.h>
#include <set>
// Running time: O(R*C*C)

// finds max subarray using kadanes
using namespace std;
int R,C;
int arr[1001];
int matrix[1001][1001];
int dp[1001];
const int NEG_INF = -100000001;

int maxLeft, maxRight, maxTop, maxBottom;
int maxSum = NEG_INF;

int tempTop;
int tempBottom;

// for 1d array of length R
int kadane()
{
  dp[0] = 0;
  int result = arr[0];

  for (int x = 1; x <= R; x++)
  {
    dp[x] = max(dp[x-1], 0) + arr[x];
    if (dp[x] == arr[x])
    {
      tempTop = x;
    }

    if (dp[x] > result)
    {
      result = dp[x];
      tempBottom = x;
    }
  }
  return result;
}

// for 2d array RxC
void kadane2D()
{
  for (int left = 1; left <= C; left++)
  {
    // Resetting array to 0 when left bound is changed
    for (int i = 1; i <= R; i++)
    {
      arr[i] = 0;
    }

    for (int right = left; right <= C; right++)
    {
      // Stores the column
      for (int i = 1; i <= R; i++)
      {
        arr[i]+=matrix[i][right];
      }

      int sum = kadane();
      if (sum > maxSum)
      {
        maxSum = sum;
        maxLeft = left;
        maxRight = right;
        maxBottom = tempBottom;
        maxTop = tempTop;
      }
    }
  }
}



int main()
{
  /*cin >> N;
  for (int x = 1; x <= N; x++)
  {
    cin >> arr[x];
  }
  int max = kadane();*/
  // ofstream fout ("kad.out");
  ifstream fin ("kad.in");

  fin >> R >> C;
  for (int r = 1; r <= R; r++)
  {
    for (int c = 1; c <= C; c++)
    {
      fin >> matrix[r][c];
    }
  }

  kadane2D();
  cout << "Max Sum: " << maxSum << endl;
  cout << "Rectangle: (" << maxTop << "," << maxLeft << ") and (" << maxBottom << "," << maxRight << ")" << endl;
}
