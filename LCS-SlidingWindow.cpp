// Determine longest common subsequence (LCS) between two given strings
// Dynamic programming - using sliding window to reduce information stored

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

// DP Solution for find the longest common subsequence but with sliding window technique (storing only two rows)
using namespace std;
string string1, string2;
int length1, length2, result;

// Pass in the length of the strings
int lcs(int s1, int s2)
{
  int dp[2][s2+1];
  // Initializing dp matrix
  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y <= s2; y++)
    {
      dp[x][y] = 0;
    }
  }

  for (int a = 1; a <= s1; a++)
  {
    for (int b = 1; b <= s2; b++)
    {
      if (string1[a-1] == string2[b-1])
      {
        dp[1][b] = dp[0][b-1]+1;
      }
      else
      {
        dp[1][b] = max(dp[0][b], dp[1][b-1]);
      }
    }
    for (int y = 0; y <= s2; y++)
    {
      dp[0][y] = dp[1][y];
    }
  }
  return dp[0][s2];
}

int main()
{
  cin >> string1;
  cin >> string2;
  cout << "String1: " << string1 << endl;
  cout << "String2: " << string2 << endl;
  length1 = string1.length();
  length2 = string2.length();
  cout << "Length1: " << length1 << endl;
  cout << "Length2: " << length2 << endl;
  result = lcs(length1, length2);
  cout << result << endl;
}
