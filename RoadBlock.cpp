// USACO 2014 December Contest, Gold
// Dijkstra's algorithm

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
int N, M;
int adjMatrix[101][101];
int distArr[101];
int visited[101];
int parent[101];
const int INF = 100000001;

// First dijkstra called on original path
void dijkstra1()
{
  // Initializing dist array (0 for source and infinity for rest of vertices)
  for (int x = 1; x <= N; x++)
  {
    if (x == 1)
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

  for (int y = 1; y <= N; y++)
  {
    // Finds the node with the minimum distance
    minDist = INF;
    for (int z = 1; z <= N; z++)
    {
      if (visited[z] == false && distArr[z] < minDist)
      {
        minDist = distArr[z];
        currentNode = z;
      }
    }

    // Updates the distances from the current node to all other nodes
    for (int b = 1; b <= N; b++)
    {
      if (visited[b] == false && adjMatrix[currentNode][b] != INF && b != currentNode)
      {
        distArr[b] = min(distArr[b], distArr[currentNode] + adjMatrix[currentNode][b]);
        if (distArr[b] == distArr[currentNode] + adjMatrix[currentNode][b])
        {
          parent[b] = currentNode;
          cout << "Setting parent[" << b << "] = " << currentNode << endl;
        }
      }
    }
    visited[currentNode] = true;
  }
}

// Second dikjstra called whenever an edge length is doubled
void dijkstra2()
{
  // Initializing dist array (0 for source and infinity for rest of vertices)
  for (int x = 1; x <= N; x++)
  {
    if (x == 1)
    {
      distArr[x] = 0;
    }
    else
    {
      distArr[x] = INF;
    }
    // Resetting visited to false for all vertices
    visited[x] = false;
  }

  int minDist;
  int currentNode;

  for (int y = 1; y <= N; y++)
  {
    // Finds the node with the minimum distance
    minDist = INF;
    for (int z = 1; z <= N; z++)
    {
      if (visited[z] == false && distArr[z] < minDist)
      {
        minDist = distArr[z];
        currentNode = z;
      }
    }

    // Updates the distances from the current node to all other nodes
    for (int b = 1; b <= N; b++)
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
  int field1, field2, weight, originalLength, newLength, maxLength, increase;
  cin >> N;
  cin >> M;

  // Initializing the graph
  for (int a = 1; a <= 100; a++)
  {
    for (int b = 1; b <= 100; b++)
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

  // Reading input
  for (int x = 1; x <= M; x++)
  {
    cin >> field1;
    cin >> field2;
    cin >> weight;
    adjMatrix[field1][field2] = weight;
    adjMatrix[field2][field1] = weight;
  }

  cout << "Starting dijkstra on the original path" << endl;
  dijkstra1();
  originalLength = distArr[N];
  cout << "Original Length: " << originalLength << endl;

  maxLength = 0;
  int vertex = N;
  int precedingVertex = parent[N];

  for (int a = 1; a <= N; a++)
  {
    cout << "Parent[" << a << "] = " << parent[a] << endl;
  }

  // Calculating the maximum increase
  while (vertex != 1)
  {
    // cout << "Vertex: " << vertex << " , Preceding vertex: " << precedingVertex;
    // Multiplying edge length by 2
    adjMatrix[precedingVertex][vertex] = 2*adjMatrix[precedingVertex][vertex];
    dijkstra2();
    newLength = distArr[N];
    if (newLength > maxLength)
    {
      maxLength = newLength;
      increase = maxLength - originalLength;
    }
    adjMatrix[precedingVertex][vertex] = adjMatrix[precedingVertex][vertex]/2;
    vertex = precedingVertex;
    precedingVertex = parent[vertex];
  }
  cout << increase << endl;
}
