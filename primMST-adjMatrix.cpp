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

// Running time: O(V^2) with adjacency matrix

using namespace std;
// Stores the graph
int adjMatrix[2501][2501];
// Stores true (used) and false (not used) for each vertex
bool usedVertices[2501];
// Stores the distance
int distances[2501];
int V, E, totalCost;
const long int INF = 100000001;

void prim()
{
  distances[1] = 0;
  usedVertices[1] = false;
  // Initializing distances to a very high number
  for (int c = 2; c <= V; c++)
  {
    distances[c] = INF;
    usedVertices[c] = false;
  }

  int vertexToBeAdded = 0;

  for (int y = 1; y <= V; y++)
  {
    int minDist = INF;
    // Finding the vertex that will create the smallest edge length
    for (int a = 1; a <= V; a++)
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
    for (int b = 1; b <= V; b++)
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

int main()
{
  int vertex1, vertex2, weight;
  cin >> V;
  cin >> E;
  int first_vertex[E+1];
  int second_vertex[E+1];
  int weights[E+1];

  for (int x = 1; x <= E; x++)
  {
    cin >> first_vertex[x];
    cin >> second_vertex[x];
    cin >> weights[x];

  }

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

  for (int y = 1; y <= E; y++)
  {
    vertex1 = first_vertex[y];
    vertex2 = second_vertex[y];
    weight = weights[y];
    adjMatrix[vertex1][vertex2] = weight;
    adjMatrix[vertex2][vertex1] = weight;
  }

  prim();
  cout << totalCost << endl;
}
