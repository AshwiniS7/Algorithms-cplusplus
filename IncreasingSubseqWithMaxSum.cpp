// Determine increasing subsequence in an array that has the maximum sum
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

using namespace std;

int main()
{
  int N;
  cin >> N;
  int arr[N];
  int dp[N];
  int tracker[N];


  for (int i = 0; i < N; i++)
  {
    cin >> arr[i];
    dp[i] = arr[i];
    tracker[i] = -1;
  }

  // tracker[0] = -1;
  int maxSum = 0;
  int maxIndex = 0;

  for (int i = 1; i < N; i++)
  {
    for (int j = i; j >= 0; j--)
    {
      if (arr[j] < arr[i])
      {
        if (dp[j]+arr[i] > dp[i])
        {
            dp[i] = dp[j]+arr[i];
            tracker[i] = j;
        }
        // dp[i] = max(dp[j]+arr[i], dp[i]);
        // stores max sum and updates it continually
        if (dp[i] > maxSum)
        {
          maxSum = dp[i];
          maxIndex = i;
        }
        // maxSum = max(maxSum, dp[i]);
      }
    }
  }

  int a = tracker[maxIndex];
  cout << arr[maxIndex] << " ";
  while (a >= 0)
  {
    // cout << "a: " << a << endl;
    cout << arr[a] << " ";
    a = tracker[a];
  }
  cout << maxSum << endl;
}
