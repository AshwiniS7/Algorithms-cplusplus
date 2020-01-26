// USACO 2016 December Contest, Gold
// Dynamic programming

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
#include <math.h>

using namespace std;
const long int INF = 1000000001;

int calcEnergy(int x1, int y1, int x2, int y2)
{
  // cout << endl;
  // cout << "x2 - x1 = " << x2 - x1 << " | y2 - y1 = " << y2 - y1 << endl;
  int energy = pow(x2-x1, 2) + pow(y2-y1, 2);
  return energy;
}

int main()
{
  int H, G;
  cin >> H;
  cin >> G;
  int xCoordH[H+1];
  int yCoordH[H+1];
  int xCoordG[G+1];
  int yCoordG[G+1];
  // Represents the min amount of energy to cover Holsteins 1..i and Guernesys 1..j
  int dp[H+1][G+1][2];
  int energy1, energy2;

  for (int a = 1; a <= H; a++)
  {
    cin >> xCoordH[a];
    cin >> yCoordH[a];
  }

  for (int b = 1; b <= G; b++)
  {
    cin >> xCoordG[b];
    cin >> yCoordG[b];
  }

  for (int c = 0; c <= H; c++)
  {
    for (int d = 0; d <= G; d++)
    {
      dp[c][d][0] = INF;
      dp[c][d][1] = INF;
    }
  }

  dp[1][0][0] = 0;

  dp[1][1][1] = calcEnergy(xCoordH[1], yCoordH[1], xCoordG[1], yCoordG[1]);

  for (int e = 2; e <= H; e++)
  {
    dp[e][0][0] = dp[e-1][0][0] + calcEnergy(xCoordH[e-1], yCoordH[e-1], xCoordH[e], yCoordH[e]);
  }

  int minEnergy;
  int currentEnergy;
  for (int i = 2; i <= H; i++)
  {
    minEnergy = INF;
    for (int j = 1; j < i; j++)
    {
      currentEnergy = dp[i][0][0] - calcEnergy(xCoordH[j], yCoordH[j], xCoordH[j+1], yCoordH[j+1]) + calcEnergy(xCoordH[j], yCoordH[j], xCoordG[1], yCoordG[1]) + calcEnergy(xCoordG[1], yCoordG[1], xCoordH[j+1], yCoordH[j+1]);
      if (currentEnergy < minEnergy)
      {
        minEnergy = currentEnergy;
      }
    }
    dp[i][1][0] = minEnergy;
    cout << "Setting dp[" << i << "][1][0] = " << dp[i][1][0] << endl;
  }

  for (int i = 1; i <= H; i++)
  {
    for (int j = 1; j <= G; j++)
    {
      for (int k = 0; k <= 1; k++)
      {
        if (k == 0 && i == 1)
        {
          continue;
        }
        if (i == 1 && k == 1 && j == 1)
        {
          continue;
        }
        if (j == 1 && k == 0)
        {
          continue;
        }

        if (k == 0)
        {
          cout << "dp[" << i-1 << "][" << j << "][0] = " << dp[i-1][j][0] << endl;
          // Energy from i-1 to i
          if (dp[i-1][j][0] == INF)
          {
             energy1 = INF;
          }
          else
          {
            energy1 = calcEnergy(xCoordH[i-1], yCoordH[i-1], xCoordH[i], yCoordH[i]);
          }
          cout << "Energy from Holstein " << i-1 << ": (" << xCoordH[i-1] << "," << yCoordH[i-1] << ") to Holstein " << i << ": (" << xCoordH[i] << "," << yCoordH[i] << ") = " << energy1 << endl;


          cout << "dp[" << i-1 << "][" << j << "][1] = " << dp[i-1][j][1] << endl;
          // Energy from j to i
          if (dp[i-1][j][1] == INF)
          {
            energy2 = INF;
          }
          else
          {
            energy2 = calcEnergy(xCoordG[j], yCoordG[j], xCoordH[i], yCoordH[i]);
          }
          cout << "Energy from Guernesy " << j << ": (" << xCoordG[j] << "," << yCoordG[j] << ") to Holstein " << i << ": (" << xCoordH[i] << "," << yCoordH[i] << ") = " << energy2 << endl;

          dp[i][j][0] = min(dp[i-1][j][0] + energy1, dp[i-1][j][1] + energy2);
          cout << "Setting dp[" << i << "][" << j << "][0] to min(" << dp[i-1][j][0] + energy1 << "," << dp[i-1][j][1] + energy2 << ") = " << dp[i][j][0] << endl;
        }
        else
        {
          // Energy from i to j
          cout << "dp[" << i << "][" << j-1 << "][0] = " << dp[i][j-1][0] << endl;
          if (dp[i][j-1][0] == INF)
          {
            energy1 = INF;
          }
          else
          {
            energy1 = calcEnergy(xCoordH[i], yCoordH[i], xCoordG[j], yCoordG[j]);
          }

          cout << "Energy from Holstein " << i << ": (" << xCoordH[i] << "," << yCoordH[i] << ") to Guernesy " << j << ": (" << xCoordG[j] << "," << yCoordG[j] << ") = " << energy1 << endl;

          cout << "dp[" << i << "][" << j-1 << "][1] = " << dp[i][j-1][1] << endl;

          if (dp[i][j-1][1] == INF)
          {
            energy2 = INF;
          }
          else
          {
            // Energy from j-1 to j
            energy2 = calcEnergy(xCoordG[j-1], yCoordG[j-1], xCoordG[j], yCoordG[j]);
          }
          cout << "Energy from Guernesy " << j-1 << ": (" << xCoordG[j-1] << "," << yCoordG[j-1] << ") to Guernesy " << j << ": (" << xCoordG[j] << "," << yCoordG[j] << ") = " << energy2 << endl;
          dp[i][j][1] = min(dp[i][j-1][0] + energy1, dp[i][j-1][1] + energy2);
          cout << "Setting dp[" << i << "][" << j << "][1] to min(" << dp[i][j-1][0] + energy1 << "," << dp[i][j-1][1] + energy2 << ") = " << dp[i][j][1] <<  endl;
        }

        cout << endl;
      }

    }
  }

  cout << dp[H][G][0] << endl;

}
