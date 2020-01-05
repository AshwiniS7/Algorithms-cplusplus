#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>

using namespace std;
int adjMatrix[2501][2501];
int distArr[2501];
bool visited[2501];
int V,E,S;
const int INF = 100000001;

// Running time: O(V^2) with adjacency matrix

void dijkstra()
{
  // Initializing dist array (0 for source and infinity for rest of vertices)
  for (int x = 1; x <= V; x++)
  {
    if (x == S)
    {
      distArr[x] = 0;
    }
    else
    {
      distArr[x] = INF;
    }
  }

  int minDist;
  int currentNode;

  for (int y = 1; y <= V; y++)
  {
    // Finds the node with the minimum distance
    minDist = INF;
    for (int z = 1; z <= V; z++)
    {
      if (visited[z] == false && distArr[z] < minDist)
      {
        minDist = distArr[z];
        currentNode = z;
      }
    }

    // Updates the distances from the current node to all other nodes
    for (int b = 1; b <= V; b++)
    {
      if (visited[b] == false && adjMatrix[currentNode][b] != INF)
      {
        distArr[b] = min(distArr[b], distArr[currentNode] + adjMatrix[currentNode][b]);
      }
    }
    visited[currentNode] = true;
  }
}

int main()
{
  int vertex1, vertex2, weight;
  cin >> V;
  cin >> E;
  cin >> S;

  // Initializing the graph
  for (int a = 1; a <= 2500; a++)
  {
    for (int b = 1; b <= 2500; b++)
    {
      if (a == b)
      {
        adjMatrix[a][b] = 0;
      }
      else
      {
        adjMatrix[a][b] = INF;
      }
    }
  }

  // Reading the edges
  for (int x = 0; x < E; x++)
  {
    cin >> vertex1;
    cin >> vertex2;
    cin >> weight;
    adjMatrix[vertex1][vertex2] = weight;
    adjMatrix[vertex2][vertex1] = weight;
  }

  dijkstra();

  // Printing the distances from source to every other node
  for (int z = 1; z <= V; z++)
  {
    // If there is no path
    if (distArr[z] == INF)
    {
      cout << -1 << endl;
    }
    // If there is a path
    else
    {
      cout << distArr[z] << endl;
    }
  }
}
