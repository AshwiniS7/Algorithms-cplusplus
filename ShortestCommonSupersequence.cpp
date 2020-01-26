// Determine the shortest common supersequence given two strings
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

using namespace std;
string s1, s2;
const long int INF = 100000001;

int superseq()
{
  int dp[s1.length()][s2.length()];
  int maxLength = 0;

  // Initializing dp matrix
  for (int x = 0; x <= s1.length(); x++)
  {
    for (int y = 0; y <= s2.length(); y++)
    {
      dp[x][y] = INF;
    }
  }

  if (s1[0] == s2[0])
  {
    dp[0][0] = 1;
  }
  else
  {
    dp[0][0] = 2;
  }

  if (s1.length() > 1)
  {
    if (s1[1] == s2[0])
    {
        dp[1][0] = 2;
    }
    else
    {
      dp[1][0] = dp[0][0]+1;
    }
  }

  if (s2.length() > 1)
  {
    if (s1[0] == s2[1])
    {
        dp[0][1] = 2;
    }
    else
    {
      dp[0][1] = dp[0][0]+1;
    }
  }

  for (int a = 1; a <= s1.length(); a++)
  {
    for (int b = 1; b <= s2.length(); b++)
    {
      if (s1[a] == s2[b])
      {
        dp[a][b] = dp[a-1][b-1]+1;
      }
      else
      {
        dp[a][b] = min(dp[a-1][b], dp[a][b-1])+1;
      }
    }
  }

  return dp[s1.length()-1][s2.length()-1];
}

int main()
{
  cin >> s1 >> s2;
  cout << superseq() << endl;
}
