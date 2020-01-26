// Finds the shortest edit distance to convert string1 to string2
// Operations allowed are insert, delete or substitute a letter
// Dynamic programming

using namespace std;
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


string string1, string2;

// Passing in the length of the substrings
int sed(int s1, int s2)
{
  int dp[s1+1][s2+1];

  // Initializing dp matrix
  for (int x = 0; x <= s2; x++)
  {
    dp[0][x] = x;
  }

  for (int x = 0; x <= s1; x++)
  {
    dp[x][0] = x;
  }

  for (int a = 1; a <= s1; a++)
  {
    for (int b = 1; b <= s2; b++)
    {
      if (string1[a-1] == string2[b-1])
      {
        dp[a][b] = dp[a-1][b-1];
      }
      else
      {
        dp[a][b] = 1 + min(min(dp[a-1][b], dp[a][b-1]), min(dp[a-1][b], dp[a-1][b-1]));
      }
    }
  }
  return dp[s1][s2];
}

int main()
{
  int minEditDist, length1, length2;
  cin >> string1;
  cin >> string2;
  length1 = string1.length();
  length2 = string2.length();
  minEditDist = sed(length1, length2);
  cout << "Length1: " << length1 << endl;
  cout << "Length2: " << length2 << endl;
  cout << minEditDist << endl;
}
