// Finds the number of paths in a DAG graph using topological sort
// Runs in O(V+E)

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
int V,E,source, destination;
// inDegree vector
int inDeg[500001];
int topSort[500001];
// Finds the sums
int sum[500001];
vector <list<int> > predecessor(500001);
// vector <int> partialSum(V);
// Adjacency list (nodes each having a list of their neighbors)
vector <list<int> > adjList(500001);

// Causes the queue's front to be the least element, instead of the max element
struct compareCust
{
   bool operator()(const int x, const int y)
   {
      return x > y;
   }
};

void top_sort()
{
  for (int x = 1; x <= V; x++)
  {
    for (auto p: adjList[x])
    {
      predecessor[p].push_back(x);
      inDeg[p]++;
    }
  }
  priority_queue<int, vector<int>, compareCust> pq;
  // Pushing vertice with indegree 0 into the queue
  for (int x = 1; x <= V; x++)
  {
    if (inDeg[x] == 0)
    {
      pq.push(x);
    }
  }

  for (int x = 1; x <= V; x++)
  {
    int top = pq.top();
    pq.pop();
    topSort[x] = top;
    // Loop through its neighbors/children
    list<int>::iterator itl;
    for (itl = (adjList[top]).begin(); itl != (adjList[top]).end(); itl++)
    {
      // Decrement the number of neighbors each of its children has
      inDeg[*itl]--;
      if (inDeg[*itl] == 0)
      {
        pq.push(*itl);
      }
    }
  }
}

int count_paths()
{
  bool flag = false;
  for (int x = 1; x <= V; x++)
  {
    if (topSort[x] == source)
    {
      sum[topSort[x]] = 1;
      flag = true;
    }
    else if (flag)
    {
      for (auto p: predecessor[topSort[x]])
      {
        sum[topSort[x]]+=sum[p];
        cout << "Setting sum of vertex " << topSort[x] << " to " << sum[topSort[x]] << endl;
      }
    }
  }

  return sum[destination];
}

int main()
{
    int firstv, secondv;
    bool flag = false;

    // Reading in number of vertices and edges
    cin >> V >> E;

    // Reading the first vertex and another vertex to which it points to
    for (int x = 0; x < E; x++)
    {
      cin >> firstv >> secondv;
      adjList[firstv].push_back(secondv);
    }
    cin >> source >> destination;
    top_sort();
    cout << "Actual Topological Sort" << endl;
    for (int x = 1; x <= V; x++)
    {
      cout << topSort[x] << " ";
    }
    cout << endl;
    cout << count_paths() << endl;
    return 0;
}
