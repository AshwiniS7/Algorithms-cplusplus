// Dijkstra's shortest path algorithm with graph represented as an adjacency list 

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
// Running time: O(V+E)logV with adjacency list

int V,E,S;
typedef pair <int, int> pii;
vector <list<pii> > adjList(50001);
// Stores true (used) and false (not used) for each vertex
bool usedVertices[50001];
// Stores the distance
int distances[50001];
const long int INF = 100000001;

// Causes the queue's front to be the least element, instead of the max element
struct compareCust
{
   bool operator()(const pii x, const pii y)
   {
      return x.first > y.first;
   }
};

void dijkstra()
{
  // Initializing distances to a very high number except for source
  for (int c = 1; c <= V; c++)
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
  int minWeight, minVertex, addedDist, addedVertex;
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
    }
  }
}

int main()
{
  int vertex1, vertex2, cost;
  pii pair1, pair2;
  cin >> V;
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
    pair2.first = cost;
    pair2.second = vertex1;
    adjList[vertex2].push_back(pair2);
  }
  dijkstra();
  for (int x = 1; x <= V; x++)
  {
    // If there is no path
    if (distances[x] >= INF)
    {
      cout << -1 << endl;
    }
    else
    {
      cout << distances[x] << endl;
    }
  }
}
