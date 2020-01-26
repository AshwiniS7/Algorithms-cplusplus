// USACO 2019 December Contest, Gold
// Depth-first search

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

// Gold Dec 2019 - calculating the existence of a node in a tree in a subpath
using namespace std;
typedef pair <int, int> pii;
const int MAX_N = 100002;
int N, M;
// stores cow types
int types[MAX_N];
bool visited[MAX_N];
// stores tree graph
vector <list<int> > adjList(MAX_N);
// for each type of cow, it stores the cows found and the depth of each cow
vector <list<pii> > typeList(MAX_N);
vector<int> nodeList;
// Stores the times when the node is visited and lefted
pii prepost[MAX_N];
long long int timestamp = 1;

// Query struct
struct Query
{
  int start;
  int end;
  int cowtype;
};

struct Query queries[MAX_N];
// vector maps vertices to a list of queries
vector <list<int> > vertexq (MAX_N);
int sol[MAX_N];

// determines whether node u is an ancestor of node v
bool isAnc(int v, int u)
{
  if (prepost[v].first >= prepost[u].first && prepost[v].second <= prepost[u].second)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void dfs1(int node)
{
  // cout << "Calling dfs on node " << node << endl;
  visited[node] = true;

  prepost[node].first = timestamp;
  list<int>::iterator itl;

  // For all its neighbors
  for (itl = (adjList[node]).begin(); itl != (adjList[node]).end(); itl++)
  {
    if (visited[(*itl)] == false)
    {
      // cout << "Visiting neighbor: " << *itl << endl;
      timestamp++;
      dfs1(*itl);
    }
  }
  timestamp++;
  prepost[node].second = timestamp;
}

void dfs2(int node, int depth)
{
  // cout << "Currently at node " << node << endl;
  visited[node] = true;
  pii p1;
  p1.first = node;
  p1.second = depth;
  // Stores the cows of each type that have been encountered
  typeList[types[node]].push_back(p1);
  nodeList.push_back(node);

  // Checks through all queries relevant to node
  list<int>::iterator itl1;
  for (itl1 = (vertexq[node]).begin(); itl1 != (vertexq[node]).end(); itl1++)
  {
    // cout << "Working on query " << *itl1 << endl;
    // gets the type that we are looking for (specific to the query)
    int type = queries[*itl1].cowtype;
    // gets the other endpoint in the Query
    int othernode = queries[*itl1].start + queries[*itl1].end - node;
    // if the node is the preferred type of cow
    if (types[node] == type)
    {
      sol[*itl1] = 1;
    }
    else if (typeList[type].size() > 0)
    {
      // finds last cow encountered that had the same cow type
      int cow = typeList[type].back().first;
      // cout << "Last encountered cow with preferred type " << type << " is " << cow << endl;
      // cout << "Other node in query: " << othernode << endl;

      // Checks whether the cow found is an ancestor of the other node
      if (!isAnc(othernode, cow))
      {
        // cout << cow << " is not an ancestor of " << othernode << endl;
        // that means the cow lies between the lca and node
        sol[*itl1] = 1;
      }
      else
      {
        // Test whether the cow found is the lca of node and othernode
        // Figure out the cow directly below the cow with the preferred type

        if (nodeList.size() > typeList[type].back().second)
        {
          int cowbelow = nodeList[typeList[type].back().second];

          // cout << "Cow below: " << cowbelow << " at depth " << typeList[type].back().second << endl;
          // If this lower cow is not an ancestor of othernode, then the cow is the lca

          /*for (vector<int>::iterator nit = nodeList.begin(); nit != nodeList.end(); nit++)
          {
            cout << *nit << endl;
          }*/
          if (!isAnc(othernode, cowbelow))
          {
            // cout << "Cow below: " << cowbelow << " is not an ancestor of other node: " << othernode << endl;
            sol[*itl1] = 1;
          }
        }
      }
    }
  }

  // Calls dfs on all neighbors
  list<int>::iterator itl2;
  for (itl2 = (adjList[node]).begin(); itl2 != (adjList[node]).end(); itl2++)
  {
    if (visited[(*itl2)] == false)
    {
      dfs2(*itl2, depth+1);
    }
  }
  // Pops elements from the stacks
  typeList[types[node]].pop_back();
  nodeList.pop_back();
}

void resetVisited()
{
  for (int i = 0; i <= MAX_N; i++)
  {
    visited[i] = false;
  }
}

int main()
{
  ofstream fout ("milkvisits.out");
  ifstream fin ("milkvisits.in");
  int f1, f2;
  fin >> N >> M;

  // cout << "Before reading the types" << endl;
  for (int i = 1; i <= N; i++)
  {
    fin >> types[i];
  }
  // cout << "After reading the types" << endl;
  for (int i = 1; i <= N-1; i++)
  {
    fin >> f1 >> f2;
    adjList[f1].push_back(f2);
    adjList[f2].push_back(f1);
  }

  // cout << "Before first DFS" << endl;
  dfs1(1);
  // cout << "After first DFS" << endl;
  /*for (int i = 1; i <= N; i++)
  {
    cout << "timestamp[" << i << "] = " << prepost[i].first << " " << prepost[i].second << endl;
  }*/

  // Reads queries
  for (int i = 1; i <= M; i++)
  {
    fin >> queries[i].start >> queries[i].end >> queries[i].cowtype;
    vertexq[queries[i].start].push_back(i);
    vertexq[queries[i].end].push_back(i);
  }
  resetVisited();
  /*for (vector<int>::iterator nit = nodeList.begin(); nit != nodeList.end(); nit++)
  {
    cout << *nit << endl;
  }*/

  // cout << "Before second DFS" << endl;
  dfs2(1,1);
  // cout << "After second DFS" << endl;

  for (int s = 1; s <= M; s++)
  {
    // sol[s] = 100;
    fout << sol[s];
  }
}
