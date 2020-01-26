// Determine least common ancestor (LCA) of two nodes
// in a tree using binary lifting algorithm

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

using namespace std;
// maximum number of vertices in the tree
const long int MAX_V = 1e4;
// Base 2 of MAX_V
const long int MAX_LOG = 14;
long int E,V,LOG_V;
vector <list<long int> > adjList(MAX_V);
long int anc[MAX_V][MAX_LOG];
long int height[MAX_V];

void dfs(long int node, long int parent)
{
  // Initializing anc values
  anc[node][0] = parent;
  for (int i = 1; i <= LOG_V; i++)
  {
    anc[node][i] = anc[anc[node][i-1]][i-1];
  }

  list<long int>::iterator itl;
  // For all its neighbors
  for (itl = (adjList[node]).begin(); itl != (adjList[node]).end(); itl++)
  {
    // Making sure we are only considering children
    if (*itl != parent)
    {
      height[*itl] = height[node]+1;
      dfs(*itl, node);
    }
  }
}

void printHeights()
{
  cout << "Heights: ";
  for (int i = 1; i <= V; i++)
  {
    cout << height[i] << " ";
  }
  cout << endl;
}

int lca(long int u, long int v)
{
  // Makes u the farthest one down the tree
  if (height[u] < height[v])
  {
    int temp = v;
    v = u;
    u = temp;
  }

  // brings u up to the same height as v
  for (int j = LOG_V; j >= 0; j--)
  {
    if ((height[u]-pow(2,j)) >= height[v])
    {
      u = anc[u][j];
    }
  }

  // if u and v are the same, then u is the lca
  if (u == v)
  {
    return u;
  }

  // walking up the tree together
  for (int j = LOG_V; j >= 0; j--)
  {
    if (anc[u][j] != anc[v][j])
    {
      u = anc[u][j];
      v = anc[v][j];
    }
  }

  // Return one above u
  return anc[u][0];
}

int main()
{
  // Reading tree into adjacency list
  long int v1, v2, u, v;
  // E is the number of edges in the tree
  cin >> E;
  V = E+1;
  LOG_V = (long int)(ceil(log2(V)));

  for (long int x = 0; x < E; x++)
  {
    cin >> v1 >> v2;
    adjList[v1].push_back(v2);
    adjList[v2].push_back(v1);
  }
  // Reading in 2 nodes to find LCA of
  cin >> u >> v;
  dfs(1,1);
  printHeights();
  cout << lca(u,v) << endl;
}
