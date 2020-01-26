// USACO 2016 US Open Contest, Gold
// Union-Find algorithm

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

using namespace std;
int N,M;
vector <list<long int> > adjList(200001);
long int parent[200001];
bool added[200001];
long long int size[200001];
// long int rootCount[200001];
map<long int, long int> countR;

// Gets the root
long int root(long int u)
{
  while (u != parent[u])
  {
    parent[u] = parent[parent[u]];
    u = parent[u];
  }
  return u;
}

// Finds if u and v are in the same component
bool find(long int u, long int v)
{
  return (root(u) == root(v));
}

// Merges u and v into the same component
void merge(long int u, long int v)
{
  long int root1 = root(u);
  long int root2 = root(v);
  // If they are already in the same component, return
  if (root1 == root2)
  {
    return;
  }
  else
  {
    if (size[root1] >= size[root2])
    {
      parent[root2] = root1;
      size[root1]+=size[root2];
    }
    else
    {
      parent[root1] = root2;
      size[root2]+=size[root1];
    }
  }
}

int main()
{
  long int v1, v2, addedVertex, v3, v4, diffRoots;
  bool flag;

  ofstream fout ("closing.out");
  ifstream fin ("closing.in");
  fin >> N >> M;
  list<long int>::iterator itl;

  long int order[N+1];
  string outputArr[N+1];

  for (long int x = 0; x < M; x++)
  {
    fin >> v1 >> v2;
    adjList[v1].push_back(v2);
    adjList[v2].push_back(v1);
  }

  for (long int a = 1; a <= N; a++)
  {
    fin >> order[a];
    parent[a] = a;
    size[a] = 1;
  }

  // int count = 0;
  long int partitions = 0;
  // Adding barns to an empty field, one by one
  for (long int b = N; b >= 1; b--)
  {
    /*if (count == 6)
    {
      exit(0);
    }*/
    diffRoots = 0;

    /*for (int a = 0; a <= 200001; a++)
    {
      rootCount[a] = 0;
    }*/

    countR.clear();
    // memset(rootCount, 0, 200001);
    // flag = false;
    addedVertex = order[b];
    // cout << "Added Barn: " << addedVertex << endl;
    added[addedVertex] = true;
    // count++;

    if (b != N)
    {
      // cout << "Merging the new vertex: " << addedVertex << endl;
      for (itl = (adjList[addedVertex]).begin(); itl != (adjList[addedVertex]).end(); itl++)
      {
        // cout << "rootCount[" << root(*itl) << "] = " << rootCount[root(*itl)] << endl;
        if (added[*itl] == true)
        {
          // cout << "Added neighbor: " << *itl << " with root " << root(*itl) << endl;
          /*if (rootCount[root(*itl)] == 0)
          {
            // cout << "Encountering new root from vertex " << *itl  << " with root " << root(*itl) << endl;
            diffRoots++;
            rootCount[root(*itl)]++;
            cout << "Setting rootCount[" << root(*itl) << "] to " << rootCount[root(*itl)] << endl;
          }*/

          if (countR[root(*itl)] == 0)
          {
            diffRoots++;
            countR[root(*itl)]++;
          }
          merge(*itl, addedVertex);
        }
      }
      // cout << "Merging done" << endl;
      v3 = order[b];
      v4 = order[b+1];

      if (outputArr[b+1] == "YES")
      {
        // cout << "Previous graph was connected" << endl;
        if (find(v3,v4) == true)
        {
          outputArr[b] = "YES";
          // cout << "Vertex " << v3 << " and Vertex " << v4 << " have same root" << endl;
          // cout << "OUPUT: YES" << endl;
        }
        else
        {
          outputArr[b] = "NO";
          partitions++;
          // cout << "Vertex " << v3 << " and Vertex " << v4 << " do not have same root" << endl;
          // cout << "OUPUT: NO" << endl;
        }
      }
      else
      {
        // cout << "Previous graph was not connected" << endl;
        if (diffRoots == 0)
        {
          outputArr[b] = "NO";
          partitions++;
          // cout << "New Vertex " << v3 << "is not connected " << endl;
          // cout << "OUPUT: NO" << endl;
        }
        else
        {
          partitions = partitions-diffRoots+1;
          // cout << "diffRoots: " << diffRoots << endl;
          if (partitions == 1)
          {
            outputArr[b] = "YES";
            // cout << "OUPUT: YES" << endl;
          }
          else
          {
            outputArr[b] = "NO";
            // cout << "OUPUT: NO" << endl;
          }
          /*for (int c = b; c < N; c++)
          {
            v3 = order[c];
            v4 = order[c+1];

            if (root(v3) != root(v4))
            {
              outputArr[b] = "NO";
              flag = true;
              break;
            }
          }

          if (flag == false)
          {
            outputArr[b] = "YES";
          }*/
        }
      }
    }
    else
    {
      outputArr[b] = "YES";
      partitions++;
      // cout << "OUPUT: YES" << endl;
    }

    // cout << "Partitions: " << partitions << endl;
    // cout << endl;


    /*for (int c = b; c < N; c++)
    {
      // cout << "b: " << b << endl;
      // cout << "c: " << c << endl;
      v3 = order[c];
      v4 = order[c+1];
      // cout << "V3:" << v3 << " root: " << root(v3) << endl;
      // cout << "V4:" << v4 << " root: " << root(v4) << endl;
      if (root(v3) != root(v4))
      {
        // cout << "Vertex " << v3 << " and Vertex " << v4 << " do not have same root" << endl;
        outputArr[b] = "NO";
        flag = true;
        break;
      }
    }

    if (flag == false)
    {
      outputArr[b] = "YES";
    }*/
  }

  for (long int x = 1; x <= N; x++)
  {
    fout << outputArr[x] << endl;
  }
}
