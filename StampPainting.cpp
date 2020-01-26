// USACO 2018 January Contest, Gold
// Uses DP to find how many patterns can form when placing M stamps of different color of length K on an N length board
// Simple problem: finding the number of ways to put K consecutive things on an N length board
// Solution: Use complimentary counting (total ways - ways where there are no K consecutive things)
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
#include <math.h>

using namespace std;

int main()
{
  long long int N, M, K;
  cin >> N;
  cin >> M;
  cin >> K;
  long long int dp[N+1];
  long long int totalCombos = 1;
  long long int num = 1;

  // Finding total possible combinations (which is M^N)
  for (int x = 1; x <= N; x++)
  {
    totalCombos = totalCombos*M;
    totalCombos = totalCombos % 1000000007;
  }

  // Finding combinations where there are no K consecutive things

  // Initializing ways for the first K items
  for (int x = 1; x <= K; x++)
  {
    num = num * M;
    num = num % (1000000007);
    if (x != K)
    {
      dp[x] = num % (1000000007);
    }
    else
    {
      dp[x] = (num - M) % (1000000007);
    }
  }

  for (int y = K+1; y <= N; y++)
  {
    dp[y] = (M*dp[y-1] - dp[y-K]*(M-1)) % (1000000007);
  }

  // cout << totalCombos << endl;
  // cout << dp[N] << endl;
  cout << (totalCombos - dp[N]) % (1000000007) << endl;
}
