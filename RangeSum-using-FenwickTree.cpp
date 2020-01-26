// Determine the sum of numbers within a certain given range in an array
// using Fenwick tree (or binary indexed tree)

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>

// For an array of N numbers, fenwick tree stores N elements
using namespace std;
int N;
int ftree[50001];

void initialize_tree()
{
  for (int x = 0; x < 50001; x++)
  {
    ftree[x] = 0;
  }
}

int sum(int n)
{
  int result = 0;
  int i = n;
  while (i >= 1)
  {
    result += ftree[i];
    i-=i & -i;
  }
  return result;
}

void add(int index, int amount)
{
  int i = index;

  while (i <= N)
  {
    // cout << "Index i: " << i << endl;
    ftree[i]+=amount;
    // cout << "Updating fenwick[" << i << "] to "<< fenwick_tree[i] << endl;
    i += i&-i;
  }
}

int range_query(int a, int b)
{
  return sum(b) - sum(a-1);
}

int main()
{
    int num;
    cin >> N;
    initialize_tree();
    // Creating the tree
    for (int x = 1; x <= N; x++)
    {
      cin >> num;
      add(x,num);
    }

    for (int x = 1; x <= N; x++)
    {
      cout << sum(x) << " ";
    }
    cout << endl;
    return 0;
}
