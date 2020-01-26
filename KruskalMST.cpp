// Given an undirected, connected, weighted graph
// Uses Kruskal's algorithm to generate a minimum spanning tree

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

// Struct edge containing start, end, and weight
struct Edge
{
    int start;
    int end;
    int weight;
};

int *parent;
// int *vis;
int *size;
int V,E;
// int roottemp;
int rt1, rt2;

// Sorting from smallest to greatest
bool comp(Edge a, Edge b)
{
  return a.weight < b.weight;
}

// Find the set that the vertex is in
int findSet(int v)
{
  cout << "findset called with vertex " << v << endl;
  if (v == parent[v])
  {
    return v;
  }
  // parent[v] = findSet(parent[v]);
  // cout << "parent[" << v << "] set to " << parent[v] << endl;
  // return parent[v];
  return findSet(parent[v]);
}

// When an edge is given, it combines the sets of both edges
// void unionSet(int v1, int v2)
void unionSet(int root1, int root2)
{
  // Finds the root of both vertices
  // int root1 = findSet(v1);
  // int root2 = findSet(v2);
  cout << "Union of roots (" << root1 << "," << root2 << ")" << endl;

  // If first tree is larger than second one, then attach the second to the first
  if (size[root1] > size[root2])
  {
    cout << "size[" << root1 << "]:" << size[root1] << " > " << "size[" << root2 << "]:" << size[root2] << endl;
    parent[root2] = root1;
    cout << "Assigning " << root1 << " to parent[" << root2 << "]" << endl;
    size[root1]+=size[root2];
    cout << "Updating size[" << root1 << "] to " << size[root1] << endl;
  }
  else
  {
    cout << "size[" << root1 << "]:" << size[root1] << " <= " << "size[" << root2 << "]:" << size[root2] << endl;
    parent[root1] = root2;
    cout << "Assigning " << root2 << " to parent[" << root1 << "]" << endl;
    size[root2]+=size[root1];
    cout << "Updating size[" << root2 << "] to " << size[root2] << endl;
  }

  cout << endl;
}

int main() {
    ofstream fout ("kruskal.out");
    ifstream fin ("kruskal.in");

    fin >> V;
    fin >> E;

    struct Edge edgeList[E];
    struct Edge edgeListMST[V-1];

    parent = new int[V];
    size = new int[V];
    for (int a = 0; a < V; a++)
    {
      parent[a] = a;
      size[a] = 1;
    }

    // Reading in list of edges with start, end, and weight
    for (int x = 0; x < E; x++)
    {
      fin >> edgeList[x].start;
      fin >> edgeList[x].end;
      fin >> edgeList[x].weight;
    }

    // Sorting the edges based on distance
    sort(edgeList,edgeList+E,comp);

    for (int x = 0; x < E; x++)
    {
      cout << edgeList[x].start << " " << edgeList[x].end << " " << edgeList[x].weight << endl;
      // edgeList[x].visited = false;
    }

    // Keep adding V-1 edges until a cycle is detected
    int edgeCount = 0;
    int c = 0;
    int totalWeightMST = 0;

    // While the MST has less than V-1 edges
    while (edgeCount < V-1)
    {
      // Goes through the edges in the list one by one
      int v1 = edgeList[c].start;
      int v2 = edgeList[c].end;
      int weight = edgeList[c].weight;

      // cout << "v1: " << v1 << " v2: " << v2 << endl;
      // If both of vertices of the edge are already in the same set, then a cycle has been found
      cout << c << ": Processing edge: (" << v1 << "," << v2 << ")" << endl;
      rt1 = findSet(v1);
      parent[v1] = rt1;
      rt2 = findSet(v2);
      parent[v2] = rt2;

      cout << "Root[" << v1 << "]=" << rt1 << ", size[" << rt1 << "]=" << size[rt1] << endl;
      cout << "Root[" << v2 << "]=" << rt2 << ", size[" << rt2 << "]=" << size[rt2] << endl;
      if (rt1 != rt2) // roots of both vertices are not the same - no cycle
      {
        unionSet(rt1, rt2);

        // Add the edge to the MST
        edgeListMST[edgeCount].start = v1;
        edgeListMST[edgeCount].end = v2;
        edgeListMST[edgeCount].weight = weight;
        edgeCount++;
        totalWeightMST+=weight;
      }
      else
      {
        // Cycle found
      }

      /*for (int a = 0; a < V; a++)
      {
        cout << "Parent of " << a << " = " << parent[a] << endl;
      }
      cout << endl;*/
      c++;
    }

    // Printing out edges in MST
    fout << "MST: " << endl;
    fout << "Total weight: " << totalWeightMST << endl;
    for (int x = 0; x < V-1; x++)
    {
      fout << edgeListMST[x].start << " " << edgeListMST[x].end << " " << edgeListMST[x].weight << endl;
    }
    return 0;
}
