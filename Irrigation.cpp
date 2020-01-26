// USACO 2014 March Contest, Silver
// Prim's MST algorithm

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
#include <math.h>

// Running time: O(V^2) with adjacency matrix

using namespace std;
// Stores the graph
long long int adjMatrix[2001][2001];
// Stores true (used) and false (not used) for each vertex
bool usedVertices[2001];
// Stores the distance
long long int distances[2001];
long long int N,C, totalCost;
const long long int INF = 10000000001;

void prim()
{
  distances[1] = 0;
  usedVertices[1] = false;
  // Initializing distances to a very high number
  for (int c = 2; c <= N; c++)
  {
    distances[c] = INF;
    usedVertices[c] = false;
  }

  int vertexToBeAdded = 0;

  for (int y = 1; y <= N; y++)
  {
    int minDist = INF;
    // Finding the vertex that will create the smallest edge length
    for (int a = 1; a <= N; a++)
    {
      // cout << "Dist[" << a << "] = " << distances[a] << endl;
      // Make sure it has not been added to the mst yet
      if (usedVertices[a] == false && distances[a] < minDist)
      {
        minDist = distances[a];
        vertexToBeAdded = a;
      }
    }
    // cout << "Vertex " << vertexToBeAdded << " has not been added yet with distance of " << minDist << endl;

    // Set the vertex to used
    usedVertices[vertexToBeAdded] = true;
    // Add to the total cost of the MST
    totalCost+=minDist;

    // Update the distances
    for (int b = 1; b <= N; b++)
    {
      // cout << "B: " << b << endl;
      // If the vertex has not been used and is connected to the last added vertex
      if (usedVertices[b] == false && adjMatrix[vertexToBeAdded][b] != INF)
      {
        // cout << "Setting distance[" << b << "] to " << min(distances[b], adjMatrix[vertexToBeAdded][b]) << endl;
        // Stores its current distance or the one from the last added vertex (whichever is smaller)
        distances[b] = min(distances[b], adjMatrix[vertexToBeAdded][b]);
      }
    }
  }
}

int calcCost(int x1, int y1, int x2, int y2)
{
  int cost = pow(x2-x1,2) + pow(y2-y1,2);
  return cost;
}

int main()
{
  cin >> N;
  cin >> C;
  int xCoord[N+1];
  int yCoord[N+1];

  for (int a = 1; a <= N; a++)
  {
    cin >> xCoord[a];
    cin >> yCoord[a];
  }

  // Initializing the graph
  for (int a = 1; a <= 2000; a++)
  {
    for (int b = 1; b <= 2000; b++)
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

  // Creating the graph by setting distances between every two nodes
  for (int b = 1; b <= N-1; b++)
  {
    for (int c = b+1; c <= N; c++)
    {
      if (calcCost(xCoord[b], yCoord[b], xCoord[c], yCoord[c]) < C)
      {
        adjMatrix[b][c] = INF;
        adjMatrix[c][b] = INF;
      }
      else
      {
        adjMatrix[b][c] = calcCost(xCoord[b], yCoord[b], xCoord[c], yCoord[c]);
        adjMatrix[c][b] = calcCost(xCoord[b], yCoord[b], xCoord[c], yCoord[c]);
      }
      cout << "Setting distance between (" << b << "," << c << ") to " << adjMatrix[b][c] << endl;
    }
  }
  prim();
  if (totalCost >= INF)
  {
    cout << -1 << endl;
  }
  else
  {
    cout << totalCost << endl;
  }
}
