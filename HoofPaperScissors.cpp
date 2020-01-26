// USACO 2017 January Contest, Gold
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

using namespace std;
int fjMoves[100001];
int N, K;
// 1 for hoof, 2 for paper, 3 for scissors

// Dp array stores the maximum number of wins Bessie can get in game g with s swaps and some move
int dpfunct()
{
  int dp[3][K+1][4];
  // Option1 is if Bessie plays the same gesture
  // Option2 is if Bessie changes to another gesture
  // Option3 is if Bessie changes to another gesture
  int option1, option2, option3;

  for (int n = 0; n < 3; n++)
  {
    for (int k = 0; k <= K; k++)
    {
      for (int c = 0; c <= 3; c++)
      {
        dp[n][k][c] = 0;
      }
    }
  }

  // First move is hoof
  if (fjMoves[1] == 1)
  {
    dp[1][0][1] = 0;
    dp[1][0][2] = 1;
    dp[1][0][3] = 0;
  }
  // First move is paper
  else if (fjMoves[1] == 2)
  {
    dp[1][0][1] = 0;
    dp[1][0][2] = 0;
    dp[1][0][3] = 1;
  }
  // First move is scissor
  else
  {
    dp[1][0][1] = 1;
    dp[1][0][2] = 0;
    dp[1][0][3] = 0;
  }

  for (int game = 2; game <= N; game++)
  {
    for (int swaps = 0; swaps <= K; swaps++)
    {
      for (int current = 1; current <= 3; current++)
      {
        option1 = 0;
        option2 = 0;
        option3 = 0;
        cout << "FJ's Move: " << fjMoves[game] << endl;
        cout << "Bessie's current move: " << current << endl;
        // If farmer john plays a hoof
        if (fjMoves[game] == 1)
        {
          // Bessie also plays a hoof and ties the game
          if (current == 1)
          {
            // She had played hoof in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played paper in the last game
              option2 = dp[1][swaps-1][2];
              // She had played scissor in the last game
              option3 = dp[1][swaps-1][3];
            }
            cout << "dp[" << 1  << "][" << swaps-1 << "][" << 3 << "] = " << option3 << endl;
          }
          // Bessie plays paper and beats FJ
          else if (current == 2)
          {
            // She had played paper in the last game
            option1 = dp[1][swaps][current]+1;

            if (swaps != 0)
            {
              // She had played hoof in the last game
              option2 = dp[1][swaps-1][1]+1;
              // She had played scissor in the last game
              option3 = dp[1][swaps-1][3]+1;
            }
          }
          // Bessie plays scissors and loses
          else
          {
            // She had played scissors in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played hoof in the last game
              option2 = dp[1][swaps-1][1];
              // She had played paper in the last game
              option3 = dp[1][swaps-1][2];
            }
          }
        }
        else if (fjMoves[game] == 2)
        {
          // Bessie also plays paper and ties the game
          if (current == 2)
          {
            // She had played paper in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played hoof in the last game
              option2 = dp[1][swaps-1][1];
              // She had played scissor in the last game
              option3 = dp[1][swaps-1][3];
            }
          }
          // Bessie plays scissors and beats FJ
          else if (current == 3)
          {
            // She had played scissors in the last game
            option1 = dp[1][swaps][current]+1;
            if (swaps != 0)
            {
              // She had played hoof in the last game
              option2 = dp[1][swaps-1][1]+1;
              // She had played paper in the last game
              option3 = dp[1][swaps-1][2]+1;
            }
          }
          // Bessie plays hoof and loses
          else
          {
            // She had played hoof in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played scissors in the last game
              option2 = dp[1][swaps-1][3];
              // She had played paper in the last game
              option3 = dp[1][swaps-1][2];
            }
          }
        }
        else
        {
          // Bessie also plays scissors and ties the game
          if (current == 3)
          {
            // She had played scissors in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played paper in the last game
              option2 = dp[1][swaps-1][2];
              // She had played hoof in the last game
              option3 = dp[1][swaps-1][1];
            }
          }
          // Bessie plays hoof and beats FJ
          else if (current == 1)
          {
            // She had played hoof in the last game
            option1 = dp[1][swaps][current]+1;
            if (swaps != 0)
            {
              // She had played paper in the last game
              option2 = dp[1][swaps-1][2]+1;
              // She had played scissor in the last game
              option3 = dp[1][swaps-1][3]+1;
            }

          }
          // Bessie plays paper and loses
          else
          {
            // She had played papers in the last game
            option1 = dp[1][swaps][current];
            if (swaps != 0)
            {
              // She had played hoof in the last game
              option2 = dp[1][swaps-1][1];
              // She had played scissors in the last game
              option3 = dp[1][swaps-1][3];
            }
          }
        }
        dp[2][swaps][current] = max(max(option1, option2), max(option2, option3));
        cout << "Option1: " << option1 << " Option2: " << option2 << " Option3: " << option3 << endl;
        cout << "Setting dp[" << 2 << "][" << swaps << "][" << current << "] to " << dp[2][swaps][current] << endl;
      }
    }

    for (int y = 0; y <= K; y++)
    {
      for (int z = 1; z <= 3; z++)
      {
        dp[1][y][z] = dp[2][y][z];
      }
    }
  }
  return max(max(dp[1][K][1], dp[1][K][2]), max(dp[1][K][1], dp[1][K][3]));
}

int main()
{
  char ch;
  int maxWins;
  cin >> N;
  cin >> K;
  for (int x = 1; x <= N; x++)
  {
    cin >> ch;
    if (ch == 'H')
    {
      fjMoves[x] = 1;
    }
    else if (ch == 'P')
    {
      fjMoves[x] = 2;
    }
    else
    {
      fjMoves[x] = 3;
    }
  }
  maxWins = dpfunct();
  cout << maxWins << endl;
}
