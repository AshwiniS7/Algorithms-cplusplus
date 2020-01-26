// Determine if an undirected path is bipartite using coloring method

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <set>

using namespace std;
// Checks if undirected graph is bipartite using coloring method

int V,E;
// typedef pair <int, int> pii;
vector <list<int> > adjList(50001);
// Stores true (used) and false (not visited) for each vertex
bool visited[50001];
int color[50001];
bool isBipartite = true;

void dfs(int v, int col)
{
  visited[v] = true;
  color[v] = col;
  cout << "Inside dfs of vertex " << v << " with color " << col << endl;

  list<int>::iterator itl;
  for (itl = (adjList[v]).begin(); itl != (adjList[v]).end(); itl++)
  {
    cout << "Processing child " << (*itl) << endl;
    if (color[(*itl)] == col)
    {
      cout << "Child has same color" << endl;
      isBipartite = false;
      return;
    }
    if (!visited[(*itl)])
    {
      cout << "Visiting child " << (*itl) << endl;
      dfs((*itl), 3-col);
      cout << "Done with child " << (*itl) << endl;

    }
  }

}


int main()
{
  ifstream fin ("bip.in");
  int vertex1, vertex2, cost;
  // pii pair1, pair2;
  fin >> V;
  fin >> E;

  for (int x = 1; x <= E; x++)
  {
    fin >> vertex1;
    fin >> vertex2;
    // pair1.first = cost;
    // pair1.second = vertex2;
    adjList[vertex1].push_back(vertex2);
    // pair2.first = cost;
    // pair2.second = vertex1;
    adjList[vertex2].push_back(vertex1);
  }
  dfs(1,1);

  cout << "isBipartite: " << isBipartite << endl;

}
