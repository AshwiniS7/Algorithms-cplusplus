// Determine the least number of coins that add up to a certain amount
// given coin denomiations
// Uses Dynamic programming

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
const long int INF = 100000001;
// Calculates least amount of coins to pay a certain amount of money given coin denominations

int main() {
    int n, amount;
    cin >> n;
    int coinArr[n];
    for (int x = 0; x < n; x++)
    {
      cin >> coinArr[x];
    }
    cin >> amount;
    int dp[amount+1];
    dp[0] = 0;
    for (int x = 1; x <= amount; x++)
    {
      dp[x] = INF;
      for (int c = 0; c < n; c++)
      {
        if (x-coinArr[c] >= 0)
        {
          dp[x] = min(dp[x], dp[x-coinArr[c]]+1);
        }
      }
    }

    cout << "Min coins needed: " << dp[amount] << endl;
    return 0;
}
