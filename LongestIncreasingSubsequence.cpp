// Determine longest increasing subsequence in an array of integers
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

using namespace std;
int N, num;
int dp[20001];
int arr[20001];

int lis(int n)
{
  /*for (int x = 0; x < n; x++)
  {
    cin >> arr[x];
  }*/

  for (int y = 0; y < n; y++)
  {
    dp[y] = 1;
  }

  for (int i = 0; i < n; i++)
  {
    // Compute lis[i]
    for (int j = i-1; j >= 0; j--)
    {
      if (arr[j] < arr[i])
      {
        dp[i] = max(dp[i], dp[j]+1);
        // cout << "lis[" << i << "] = " << max(lis[i], lis[j]+1) << endl;
      }
    }
  }
  sort(dp, dp+n);
  /*for (int y = 0; y < n; y++)
  {
    cout << dp[y] << " ";
  }
  cout << endl;*/
  return dp[n-1];
}

int main()
{
  int result;
  cin >> N;
  int sol[N];
  for (int x = 0; x < N; x++)
  {
    cin >> num;
    // cout << "NUM: " << num << endl;
    for (int y = 0; y < num; y++)
    {
      cin >> arr[y];
    }
    sol[x] = lis(num);
  }

  for (int a = 0; a < N; a++)
  {
    cout << sol[a] << endl;
  }
  // cout << "N: " << N << endl;
  // Stores the longest increasing subsequence up to i
}
