// USACO 2013 December Contest, Gold
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
#include <deque>
#include <set>

using namespace std;

// Calculates the shortest path from node 1 to node N if the path has to go through at least 1 hub

long int adjMatrix[201][201];
long int distArr[201];
bool visited[201];
int N;
const int INF = 100000001;

void dijkstra(int source)
{
  // Initializing dist array (0 for source and infinity for rest of vertices)
  for (int x = 1; x <= N; x++)
  {
    if (x == source)
    {
      distArr[x] = 0;
    }
    else
    {
      distArr[x] = INF;
    }
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
  int M,K,Q;
  long int dollars, farm3, farm4, numOfTrips, costSum, minCost, farm1, farm2, dist1, dist2;
  cin >> N;
  cin >> M;
  cin >> K;
  cin >> Q;

  long int nodeToHub[N+1][K+1];
  long int hubToNode[K+1][N+1];

  // Initializing the graph
  for (int a = 1; a <= 201; a++)
  {
    for (int b = 1; b <= 201; b++)
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

  for (int c = 1; c <= M; c++)
  {
    cin >> farm1;
    cin >> farm2;
    cin >> dollars;
    adjMatrix[farm1][farm2] = dollars;
  }

  // Keeping the node as the source
  for (int f = 1; f <= N; f++)
  {
    dijkstra(f);
    for (int g = 1; g <= K; g++)
    {
      nodeToHub[f][g] = distArr[g];
    }
  }

  // Keeping the hub as the source
  for (int h = 1; h <= K; h++)
  {
    dijkstra(h);
    for (int i = 1; i <= N; i++)
    {
      hubToNode[h][i] = distArr[i];
    }
  }

  minCost = INF;
  costSum = 0;
  numOfTrips = 0;
  for (int d = 1; d <= Q; d++)
  {
    cin >> farm3;
    cin >> farm4;
    // cout << "Setting minCost to " << INF << endl;
    minCost = INF;
    for (int e = 1; e <= K; e++)
    {
      // dijkstra(farm3);
      dist1 = nodeToHub[farm3][e];
      // dijkstra(e);
      dist2 = hubToNode[e][farm4];
      // cout << "Distance from Farm " << farm3 << " to Hub" << e << " is " << distArr[farm3] << endl;
      // cout << "Distance from Farm " << farm4 << " to Hub" << e << " is " << distArr[farm4] << endl;
      if (dist1 != INF && dist2 != INF && dist1 + dist2 < minCost)
      {
        minCost = dist1 + dist2;
      }
    }
    if (minCost != INF)
    {
      // cout << "Incrementing cost sum by " << minCost << endl;
      costSum+=minCost;
      numOfTrips++;
    }
  }

  cout << numOfTrips << endl;
  cout << costSum << endl;
}
