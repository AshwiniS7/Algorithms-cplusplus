// Determine the minimum value of numbers within a given range in an array
// This range-minimum-query (RMQ) is implemented using a Segment tree

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <math.h>

// stores min values in the segment tree
using namespace std;
// maximum length of segment tree
const int MAX_N = 1e6;
// maximum number of vertices in the tree
const int MAX_V = 1e4;
const double INF = 100000001;
int stree[MAX_N];
long int V,treesize;

void initialize_tree()
{
  for (int x = 0; x <= treesize; x++)
  {
    stree[x] = 0;
  }
}

void add(int index, int amount)
{
  int powerOf2 = (treesize+1)/2;
  int i = index+powerOf2-1;
  stree[i]+=amount;
  // cout << "i: " << i << endl;
  for (int c = i/2; c >= 1; c/=2)
  {
    // cout << "c: " << c << endl;
    stree[c] = min(stree[2*c],stree[2*c+1]);
    // cout << "value: " << stree[c] << endl;
  }
}

void printSegTree()
{
  cout << "Segment Tree: ";
  for (int i = 1; i <= treesize; i++)
  {
    cout << stree[i] << " ";
  }
  cout << endl;
}

// Finds minimum over a range [a,b]
// Recursion finds minimums over disjoint intervals in the larger interval
int RMQ(int node, int a, int b, int start, int end)
{
  // cout << "Query range: [" << a << "," << b << "]" << endl;
  // cout << "Start/end range: [" << start << "," << end << "]" << endl;
  // If range is outside [a,b]
  if (start > b || end < a)
  {
    return INF;
  }
  // If range is within [a,b]
  else if (start >= a && end <= b)
  {
    // cout << "Returning: " << stree[node] << endl;
    return stree[node];
  }
  else
  {
    int mid = (start + end)/2;
    int left_child = RMQ(2*node,a,b,start,mid);
    int right_child = RMQ(2*node+1,a,b,mid+1,end);
    return min(left_child, right_child);
  }
}

int main()
{
    cin >> V;
    int num;
    // Constructing the segment tree
    int x = (int)(ceil(log2(V)));
    treesize = 2*(int)pow(2, x) - 1;
    initialize_tree();
    // Creating the tree
    for (int x = 1; x <= V; x++)
    {
      cin >> num;
      add(x,num);
      /*for (int x = 1; x <= 2*N-1; x++)
      {
        cout << stree_min[x] << " ";
      }
      cout << endl;*/
    }
    printSegTree();
    // remember that starting node is 1
    cout << RMQ(1,6,9,1,(treesize+1)/2) << endl;
    return 0;
}
