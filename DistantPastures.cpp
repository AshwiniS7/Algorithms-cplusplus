// USACO 2012 November Contest, Silver
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
#include <set>

using namespace std;
// Running time: O(V+E)logV = O(ElogV) with adjacency list

long long int N, A, B;
typedef pair <long long int, int> pii;
vector <list<pii> > adjList(50001);
// Stores true (used) and false (not used) for each vertex
bool usedVertices[50001];
// Stores the distance
long long int distances[50001];
const long int INF = 100000001;

// Causes the queue's front to be the least element, instead of the max element
struct compareCust
{
   bool operator()(const pii x, const pii y)
   {
      return x.first > y.first;
   }
};

// Single-source shortest path function
long long int dijkstra(int S)
{
  long long int max = 0;
  // Initializing distances to a very high number except for source
  for (int c = 0; c < N*N; c++)
  {
    if (c == S)
    {
      distances[c] = 0;
    }
    else
    {
      distances[c] = INF;
    }
    usedVertices[c] = false;
  }

  // Uses priority queue to find the smallest weight node
  priority_queue<pii, vector<pii>, compareCust> pq;
  pii pair2, pair3, minPair;
  long long int minWeight, minVertex, addedDist, addedVertex;
  pair2.first = distances[S];
  pair2.second = S;

  // Pushes source in the priority queue
  pq.push(pair2);

  // While the priority queue is not empty
  while (!pq.empty())
  {
    minPair = pq.top();
    minWeight = minPair.first;
    minVertex = minPair.second;
    cout << "Top of queue: (" << minWeight << "," << minVertex << ")" << endl;
    pq.pop();

    // If the minimum vertex has not been visited
    if (usedVertices[minVertex] == false)
    {
      usedVertices[minVertex] = true;

      list<pii>::iterator itl;

      // Loops through all neighbors in adjacency list
      for (itl = (adjList[minVertex]).begin(); itl != (adjList[minVertex]).end(); itl++)
      {
        // If its neighbor v has not been visited and its distance can be updated
        if (usedVertices[(*itl).second] == false && distances[(*itl).second] > distances[minVertex] + (*itl).first)
        {
          // Update the distance
          distances[(*itl).second] = distances[minVertex] + (*itl).first;
          pair3.first = distances[(*itl).second];
          pair3.second = (*itl).second;
          cout << "Adding (" << pair3.first << "," << pair3.second << ") to queue" << endl;
          // Push it into the queue
          pq.push(pair3);
        }
      }

      if (minWeight > max)
      {
        max = minWeight;
      }
    }
  }
  // Returns the max distance from the source
  return max;
}

// Converts row and column to a single number
int convertToCellId(int r, int c)
{
  int cellId = N*r + c;
  return cellId;
}

int main()
{
  cin >> N >> A >> B;
  char matrix[N][N];
  pii pair1;

  // Reading input
  for (int x = 0; x < N; x++)
  {
    for (int y = 0; y < N; y++)
    {
      cin >> matrix[x][y];
    }
  }

  // Creating the graph
  long long int cost;
  for (int r = 0; r < N; r++)
  {
    for (int c = 0; c < N; c++)
    {
      // Creating edge between current cell and cell below it
      if (r+1 < N)
      {
        if (matrix[r+1][c] == matrix[r][c])
        {
          cost = A;
        }
        else
        {
          cost = B;
        }
        pair1.first = cost;
        pair1.second = convertToCellId(r+1, c);
        adjList[convertToCellId(r,c)].push_back(pair1);
      }
      // Creating edge between current cell and cell to the right
      if (c+1 < N)
      {
        if (matrix[r][c+1] == matrix[r][c])
        {
          cost = A;
        }
        else
        {
          cost = B;
        }
        pair1.first = cost;
        pair1.second = convertToCellId(r, c+1);
        adjList[convertToCellId(r,c)].push_back(pair1);
      }
      // Creating edge between current cell and cell above
      if (r-1 >= 0)
      {
        if (matrix[r-1][c] == matrix[r][c])
        {
          cost = A;
        }
        else
        {
          cost = B;
        }
        pair1.first = cost;
        pair1.second = convertToCellId(r-1, c);
        adjList[convertToCellId(r,c)].push_back(pair1);
      }
      // Creating ege between current cell and cell to the left
      if (c-1 >= 0)
      {
        if (matrix[r][c-1] == matrix[r][c])
        {
          cost = A;
        }
        else
        {
          cost = B;
        }
        pair1.first = cost;
        pair1.second = convertToCellId(r, c-1);
        adjList[convertToCellId(r,c)].push_back(pair1);
      }
    }
  }

  long long int maxLength = 0;
  long long int localMax;
  // Calls dijkstra n^2 times to find all pairs shortest path (floyd warshall is too slow)
  for (int m = 0; m < N; m++)
  {
    for (int n = 0; n < N; n++)
    {
      localMax = dijkstra(convertToCellId(m,n));
      // cout << "Local max (from matrix[" << m << "]" << "[" << n << "]) = " << localMax << endl;
      if (localMax > maxLength)
      {
        maxLength = localMax;
      }
    }
  }

  // Prints out the longest shortest path
  cout << maxLength << endl;
}
