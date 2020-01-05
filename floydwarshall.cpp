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
int dist[301][301];
const int INF = 1000001;
int N;

// Running time: O(N^3) with adjacency matrix

void floydwarshall()
{
  for (int k = 1; k <= N; k++)
  {
    for (int i = 1; i <= N; i++)
    {
      for (int j = 1; j <= N; j++)
      {
        // If the maximum hurdle on the path is less than the current maximum hurdle
        if (dist[i][k] + dist[k][j] < dist[i][j])
        {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

int main()
{
  int start, end, height, M;
  cin >> N;
  // cin >> M;

  // Initializing matrix to 0 and infinity
  for (int a = 1; a <= N; a++)
  {
    for (int b = 1; b <= N; b++)
    {
      if (a == b)
      {
        dist[a][b] = 0;
      }
      else
      {
        dist[a][b] = INF;
      }
    }
  }
  /*// Reading input
  for (int x = 0; x < M; x++)
  {
    cin >> start;
    cin >> end;
    cin >> height;
    dist[start][end] = height;
  }*/

  for (int a = 1; a <= N; a++)
  {
    for (int b = 1; b <= N; b++)
    {
      cin >> dist[a][b];
    }
  }

  floydwarshall();
  for (int a = 1; a <= N; a++)
  {
    for (int b = 1; b <= N; b++)
    {
      cout << dist[a][b] << " ";
    }
    cout << endl;
  }
  cout << dist[1][3] << endl;
}
