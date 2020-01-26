// Classic knapsack problem - packing max value objects into a given capacity
// Dynamic programming with sliding window to reduce information stored

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
// Number of objects and capacity
int N, C;
int size[10001];
long int value[10001];

long int knapsack()
{
  long int dp[2][C+1];

  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y <= C; y++)
    {
      dp[x][y] = 0;
    }
  }

  for (int item = 1; item <= N; item++)
  {
    for (int cap = 1; cap <= C; cap++)
    {
      if (size[item] > cap)
      {
        dp[1][cap] = dp[0][cap];
      }
      else
      {
        dp[1][cap] = max(dp[0][cap], dp[0][cap-size[item]] + value[item]);
      }
    }
    for (int y = 0; y <= C; y++)
    {
      dp[0][y] = dp[1][y];
    }
  }

  /*for (int x = 0; x <= N; x++)
  {
    for (int y = 0; y <= C; y++)
    {
      cout << dp[x][y] << " ";
    }
    cout << endl;
  }*/
  return dp[0][C];
}

int main()
{
  long int maxValue;
  cin >> N;
  cin >> C;
  for (int x = 1; x <= N; x++)
  {
    cin >> size[x];
    cin >> value[x];
  }

  maxValue = knapsack();
  cout << maxValue << endl;
}
