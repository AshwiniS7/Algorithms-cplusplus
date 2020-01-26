// Determine Longest Common Substring given two strings
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

// DP Solution for find the longest common substring

using namespace std;
string string1, string2;
int length1, length2, result;

// Pass in the length of the strings
int lcsubstr(int s1, int s2)
{
  int dp[s1+1][s2+1];
  int maxLength = 0;
  // Initializing dp matrix
  for (int x = 0; x <= s1; x++)
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
        dp[a][b] = dp[a-1][b-1]+1;
        if (dp[a][b] > maxLength)
        {
          maxLength = dp[a][b];
        }
      }
      else
      {
        dp[a][b] = 0;
      }
    }
  }
  return maxLength;
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
  result = lcsubstr(length1, length2);
  cout << result << endl;
}
