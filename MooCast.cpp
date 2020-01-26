// USACO 2016 December Contest, Silver
// Uses Union-Find to find the minimum integer value such that a broadcast from any cow will reach every other cow
// Sort distances between pairs of cows and keep unioning them until all cows are used

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <math.h>

using namespace std;
int parent[1001];
long long int size[1001];

// Gets the root
int root(int u)
{
  while (u != parent[u])
  {
    parent[u] = parent[parent[u]];
    u = parent[u];
  }
  return u;
}

// Finds if u and v are in the same component
bool find(int u, int v)
{
  return (root(u) == root(v));
}

// Merges u and v into the same component
void merge(int u, int v)
{
  int root1 = root(u);
  int root2 = root(v);
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

struct dist
{
  int cow1;
  int cow2;
  long long int distance;
};

long long int calcDist(int x1, int y1, int x2, int y2)
{
  long long int distance = pow(x2-x1,2) + pow(y2-y1,2);
  return distance;
}

bool comp(dist a, dist b)
{
  return a.distance < b.distance;
}

int main()
{
  int N, firstCow, secondCow;
  long long int dist1;
  cin >> N;
  int xCoord[N];
  int yCoord[N];
  struct dist distances[(N*(N-1))/2];

  // Reading input
  // Initializing parent and size arrays
  for (int x = 0; x < N; x++)
  {
    cin >> xCoord[x];
    cin >> yCoord[x];
    parent[x] = x;
    size[x] = 1;
  }

  // Calculating distances between every two cows
  long long int count = 0;
  for (int x = 0; x < N-1; x++)
  {
    for (int y = x+1; y < N; y++)
    {
      dist1 = calcDist(xCoord[x], yCoord[x], xCoord[y], yCoord[y]);
      distances[count].distance = dist1;
      distances[count].cow1 = x;
      distances[count].cow2 = y;
      count++;
    }
  }

  // Sorting the edges by distance
  sort(distances, distances+count, comp);

  /*for (int z = 0; z < count; z++)
  {
    cout << "z: " << z << endl;
    cout << "Cows (" << distances[z].cow1 << "," << distances[z].cow2 << ") = " << distances[z].distance << endl;
  }*/

  cout << "Finished printing" << endl;
  cout << "Count: " << count << endl;

  bool flag = false;
  int a;

  // Going through each edge (from least to greatest)
  for (a = 0; a < count; a++)
  {
    flag = false;
    firstCow = distances[a].cow1;
    secondCow = distances[a].cow2;
    // Merging the two cows
    merge(firstCow, secondCow);

    // Check if all the cows are in the same set
    for (int b = 0; b < N; b++)
    {
      // If they are not in the same set, then set a flag
      if (find(b,b+1) != true)
      {
        flag = true;
      }
    }

    if (flag == false)
    {
      break;
    }
  }
  // Output
  cout << distances[a].distance << endl;
}
