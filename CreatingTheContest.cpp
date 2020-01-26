// Codeforces 1029B
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

using namespace std;


int main()
{
  int n;
  cin >> n;
  int arr[n];
  int dp[n];
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
    dp[i] = 1;
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = i-1; j >= 0; j--)
    {
      if (arr[i] <= 2 * arr[j])
      {
        dp[i] = max(dp[i], dp[j]+1);
      }
      else
      {
        break;
      }
    }
  }

  int max = -1;
  for (int i = 0; i < n; i++)
  {
    if (dp[i] > max)
    {
      max = dp[i];
    }
  }

  cout << max << endl;

}
