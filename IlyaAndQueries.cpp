// Codeforces Ilya and Queries 313B
// uses prefix sums

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
  string s;
  cin >> s;
  int arr[s.length()];
  for (int i = 0; i < s.length()-1; i++)
  {
    if (s[i] == s[i+1])
    {
      arr[i] = 1;
    }
    else
    {
      arr[i] = 0;
    }
  }
  arr[s.length()-1] = 1;

  /*for (int x = 0; x < s.length(); x++)
  {
    cout << arr[x] << endl;
  }*/

  int prefixsum[s.length()];

  int runningsum = 0;
  for (int i = 0; i < s.length(); i++)
  {
    runningsum+=arr[i];
    prefixsum[i] = runningsum;
  }

  int q, left, right;
  cin >> q;
  int sol[q];
  for (int j = 0; j < q; j++)
  {
    cin >> left >> right;
    if (left == 1)
    {
      sol[j] = prefixsum[right-2];
    }
    else
    {
      sol[j] = prefixsum[right-2]-prefixsum[left-2];
    }
  }

  for (int z = 0; z < q; z++)
  {
    cout << sol[z] << endl;
  }
}
