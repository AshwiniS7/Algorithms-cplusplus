// Cutting rod problem so the value of the product of the sale amounts is maximum
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
    int dp[N+1];

    // Initializing dp state
    for (int x = 0; x <= N; x++)
    {
      dp[x] = x;
    }

    // For rods of length 2 to N
    for (int i = 2; i <= N; i++)
    {
      int maxval = -1;
      for (int j = 1; j <= i; j++)
      {
        // Taking the maximum of max and the value if a rod with length i were split into j and i-j
        maxval = max(maxval, j * dp[i-j]);
      }
      dp[i] = maxval;
    }
    cout << dp[N] << endl;
    return 0;
}
