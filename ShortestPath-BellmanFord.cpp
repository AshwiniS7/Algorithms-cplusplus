// Determine shortest paths from a given source to all vertices
// in a directed graph with positive, zero or negative edge weights
// Bellman Ford Algorithm

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

// Code for bellman ford in O(VE)
using namespace std;
typedef pair <int, int> pii;
const int INF = 1000001;
const int MAX_N = 10001;
int dist[MAX_N];
// number of vertices, edges, source
int N,E,S;
vector <list<pii> > adjList(MAX_N);

void initializeDist()
{
  for (int i = 1; i <= N; i++)
  {
    if (i == S)
    {
      dist[i] = 0;
    }
    else
    {
      dist[i] = INF;
    }
  }
}

// returns true if there is shortest path
// returns false if there is a negative weight cycle
bool bellmanford()
{
  for (int i = 1; i <= N-1; i++)
  {
    // For each edge
    // cout << "adj list size: " << adjList.size() << endl;
    for (int vertex = 1; vertex <= N; vertex++)
    {
      list<pii>::iterator itl1;
      for (itl1 = (adjList[vertex]).begin(); itl1 != (adjList[vertex]).end(); itl1++)
      {
        int u = vertex;
        int v = (*itl1).second;
        int weight = (*itl1).first;

        // cout << "U: " << u << endl;
        // cout << "V: " << v << endl;
        // cout << "Weight: " << weight << endl;
        if (dist[u] != INF && dist[v] > dist[u]+weight)
        {
          dist[v] = dist[u]+weight;
          // cout << "Updating dist[" << v << "] to " << dist[v] << endl;
        }
      }
    }
  }

  // cout << "Finished first part of bf" << endl;

  list<pii>::iterator itl2;
  // For each edge
  for (int vertex = 1; vertex <= N; vertex++)
  {
    for (itl2 = (adjList[vertex]).begin(); itl2 != (adjList[vertex]).end(); itl2++)
    {
      int u = vertex;
      int v = (*itl2).second;
      int weight = (*itl2).first;
      if (dist[v] > dist[u]+weight)
      {
        return false;
      }
    }
  }
  return true;
}

void printDist()
{
  for (int i = 1; i <= N; i++)
  {
    cout << "Dist of vertex " << i << " from source " << S << " is " << dist[i] << endl;
  }
}

int main()
{
  int vertex1, vertex2, cost;
  pii pair1, pair2;
  cin >> N;
  cin >> E;
  cin >> S;

  for (int x = 1; x <= E; x++)
  {
    cin >> vertex1;
    cin >> vertex2;
    cin >> cost;
    pair1.first = cost;
    pair1.second = vertex2;
    adjList[vertex1].push_back(pair1);
  }

  initializeDist();
  // cout << "initialized distances" << endl;
  bool result = bellmanford();
  if (result)
  {
    printDist();
  }
  else
  {
    // printDist();
    cout << "Negative edge weight cycle" << endl;
  }
}
