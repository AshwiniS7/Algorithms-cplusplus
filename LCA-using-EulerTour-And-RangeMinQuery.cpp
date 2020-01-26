// Determine least common ancestor (LCA) of two nodes in a tree
// using Euler Tour & Range Minimum Query

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

// Performs Euler tour and segment tree rmq on the heights array
using namespace std;
// maximum length of segment tree
const int MAX_N = 1e6;
// maximum number of vertices in the tree
const int MAX_V = 1e4;
const double INF = 100000001;
int stree[MAX_N];
// int arr[MAX_V];
long int E,V, treesize;
int tourindex = 1;

vector <list<long int> > adjList(MAX_V);
// order of nodes in the tour
int eulertour[2*MAX_V-1];
// heights of the nodes in the tour
int heights[2*MAX_V-1];
// first occurrences of nodes in the tour
int firstOcc[MAX_V];
bool visited[MAX_V];

void dfs(int v, int height)
{
  // cout << "Calling dfs on vertex " << v << endl;
  visited[v] = true;
  eulertour[tourindex] = v;
  heights[tourindex] = height;
  firstOcc[v] = tourindex;
  list<long int>::iterator itl;
  // For all its neighbors
  for (itl = (adjList[v]).begin(); itl != (adjList[v]).end(); itl++)
  {
    if (visited[(*itl)] == false)
    {
      tourindex++;
      dfs(*itl, height+1);
      tourindex++;
      eulertour[tourindex] = v;
      heights[tourindex] = height;
    }
  }
}

void printEulerTour()
{
  cout << "Euler Tour: ";
  for (int i = 1; i <= 2*V-1; i++)
  {
    cout << eulertour[i] << " ";
  }
  cout << endl;
}

void printHeights()
{
  cout << "Heights: ";
  for (int i = 1; i <= 2*V-1; i++)
  {
    cout << heights[i] << " ";
  }
  cout << endl;
}

void printOcc()
{
  cout << "First Occ: ";
  for (int i = 1; i <= V; i++)
  {
    cout << firstOcc[i] << " ";
  }
  cout << endl;
}

void initialize_tree()
{
  for (int x = 0; x <= ((treesize+1)/2)-1; x++)
  {
    stree[x] = 0;
  }

  int ind = 1;
  for (int x = ((treesize+1)/2); x <= treesize; x++)
  {
    stree[x] = ind;
    ind++;
  }
}


void add(int index, int amount)
{
  // arr[index]+=amount;
  int powerOf2 = (treesize+1)/2;
  int i = index+powerOf2-1;
  // stree[i]+=amount;
  cout << "Start point: " << i << endl;
  for (int c = i/2; c >= 1; c/=2)
  {
    cout << "c: " << c << endl;
    if (heights[stree[2*c]] <= heights[stree[2*c+1]])
    {
      stree[c] = stree[2*c];
    }
    else
    {
      stree[c] = stree[2*c+1];
    }
    cout << "value of stree: " << stree[c] << endl;
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
    // if both indices exist
    if (left_child != INF && right_child != INF)
    {
      if (heights[left_child] <= heights[right_child])
      {
        return left_child;
      }
      else
      {
        return right_child;
      }
    }
    else if (left_child != INF)
    {
      return left_child;
    }
    else
    {
      return right_child;
    }
  }
}

// Returns the lca of two nodes u and v
int lca(int u, int v)
{
  dfs(1,1);
  printEulerTour();
  printHeights();
  printOcc();

  // Constructing the segment tree
  int x = (int)(ceil(log2(2*V-1)));
  treesize = 2*(int)pow(2, x) - 1;
  initialize_tree();
  cout << "Actual segment tree size: " << treesize << endl;
  for (int i = 1; i <= 2*V-1; i++)
  {
    add(i, heights[i]);
    // cout << heights[i] << " ";
  }
  printSegTree();

  // If u is after v in the Euler tour, then swap them (range query won't work if they aren't swapped)
  if (firstOcc[u] > firstOcc[v])
  {
    int temp = u;
    u = v;
    v = temp;
  }

  int start = firstOcc[u];
  int end = firstOcc[v];
  int minindex = RMQ(1,start,end,1,(treesize+1)/2);
  cout << "Query start: " << start << endl;
  cout << "Query end: " << end << endl;
  cout << "Index: " << minindex << endl;
  return eulertour[minindex];
}

int main()
{
  // Reading tree into adjacency list
  long int v1, v2, u, v;
  // E is the number of edges in the tree
  cin >> E;
  V = E+1;
  for (long int x = 0; x < E; x++)
  {
    cin >> v1 >> v2;
    adjList[v1].push_back(v2);
    adjList[v2].push_back(v1);
  }
  // Reading in 2 nodes to find LCA of
  cin >> u >> v;
  cout << lca(u,v) << endl;
}
