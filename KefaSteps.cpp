// Codeforces 580A
// Determines the maximum length increasing subsequence in an array
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
  int n;
  cin >> n;
  int arr[n];

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  int dp[n];
  dp[0] = 1;
  for (int j = 1; j < n; j++)
  {
    if (arr[j-1] <= arr[j])
    {
      dp[j] = dp[j-1]+1;
    }
    else
    {
      dp[j] = 1;
    }
  }

  sort(dp, dp+n);
  cout << dp[n-1] << endl;
}
