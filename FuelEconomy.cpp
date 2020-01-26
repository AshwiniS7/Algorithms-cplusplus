// USACO 2013 US Open, Silver
// Sorting

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
long long int N, G, B, D;
const long long int INF = -1;

struct station
{
  long long int index;
  long long int dist;
  long long int price;
};

bool comp(station a, station b)
{
  return a.dist < b.dist;
}

int main()
{
  long long int minCost = 0;
  stack<station>s;
  cin >> N;
  cin >> G;
  cin >> B;
  cin >> D;
  // Stores dist and price of all fuel stations
  struct station fuelStations[N];
  // Stores the next station with less cost than station i
  struct station nextStations[N];

  for (int x = 0; x < N; x++)
  {
    cin >> fuelStations[x].dist;
    cin >> fuelStations[x].price;
  }
  sort(fuelStations, fuelStations+N, comp);

  for (int y = 0; y < N; y++)
  {
    fuelStations[y].index = y;
  }

  for (int z = 0; z <= N; z++)
  {
    if (z == N)
    {
      while (!s.empty() && s.top().price >= -1)
      {
        // cout << "Top of stack: " << s.top().height << endl;
        nextStations[s.top().index].dist = -1;
        nextStations[s.top().index].price = -1;
        nextStations[s.top().index].index = -1;
        s.pop();
      }
    }
    else
    {
      while (!s.empty() && s.top().price >= fuelStations[z].price)
      {
        // cout << "Top of stack: " << s.top().height << endl;
        nextStations[s.top().index].dist = fuelStations[z].dist;
        nextStations[s.top().index].price = fuelStations[z].price;
        nextStations[s.top().index].index = fuelStations[z].index;
        s.pop();
      }
      s.push(fuelStations[z]);
    }
  }

  int currentGas = B-fuelStations[0].dist;
  int gasRequired;

  for (int s = 0; s < N; s++)
  {
    cout << "Current gas: " << currentGas << endl;
    cout << "Current station: " << s << endl;

    if (currentGas < 0)
    {
      cout << -1 << endl;
      exit(0);
    }
    // If there is no next minimal station, take as much gas you need to finish the trip or fill up the tank
    if (nextStations[s].index == -1)
    {
      gasRequired = min(G,D-fuelStations[s].dist);
    }
    // If there is a minimal station, take as much gas you need to go there or fill up the tank
    else
    {
      gasRequired = min(G,nextStations[s].dist - fuelStations[s].dist);
    }

    // If the gas required exceeds the current gas, then pay for gas
    if (gasRequired > currentGas)
    {
      minCost+=(gasRequired-currentGas) * fuelStations[s].price;
      currentGas = gasRequired;
    }
    // Subtract the distance from this station to the next
    currentGas = currentGas - (fuelStations[s+1].dist - fuelStations[s].dist);
  }
  cout << minCost << endl;
}
