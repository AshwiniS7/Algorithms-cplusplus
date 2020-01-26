// GeeksForGeeks Problem DP-13
// Cut a rod of a given length into pieces to maximize sale given value of
// pieces of different lengths
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

int main() {
    int N;
    cin >> N;
    int arr[N+1];
    // Reading array of price for each length of rod from 1..N
    for (int x = 1; x <= N; x++)
    {
      cin >> arr[x];
    }

    int dp[N+1];
    dp[0] = 0;
    // For each length rod
    for (int i = 1; i <= N; i++)
    {
      int maxval = -1;
      // Find the max if the rod of length i were split into a rod of length j and i-j
      for (int j = 0; j < i; j++)
      {
        maxval = max(maxval, dp[j] + arr[i-j]);
      }
      dp[i] = maxval;
    }
    cout << dp[N] << endl;
    return 0;
}
