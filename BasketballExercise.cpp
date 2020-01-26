// Codeforces Basketball Exercise 1195C
// Uses dynamic programming

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
  long long int mat[2][n];
  long long int dp[2][n];

  for (int i = 0; i <= 1; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> mat[i][j];
      dp[i][j] = mat[i][j];
    }
  }

  long long int sol = max(dp[0][0], dp[1][0]);
  long long int toprowmax = 0;
  long long int botrowmax = 0;

  for (int j = 0; j < n; j++)
  {

    /*for (int a = 0; a < j; a++)
    {
      dp[0][j] = max(dp[0][j], dp[1][a]+mat[0][j]);
      dp[1][j] = max(dp[1][j], dp[0][a]+mat[1][j]);
      sol = max(max(sol, dp[0][j]), max(sol, dp[1][j]));
      // cout << "Sol: " << sol << endl;
    }*/

    dp[0][j] = max(dp[0][j], botrowmax+mat[0][j]);
    dp[1][j] = max(dp[1][j], toprowmax+mat[1][j]);
    sol = max(max(sol, dp[0][j]), max(sol, dp[1][j]));

    toprowmax = max(toprowmax, dp[0][j]);
    botrowmax = max(botrowmax, dp[1][j]);
  }

  /*for (int i = 0; i <= 1; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }*/

  cout << sol << endl;
}
