// Determine the maximum weight edge between two nodes in a tree
// for a set of pairs of nodes (queries)
// Algorithm uses range-minimum-query (RMQ) to find LCA of the two nodes
// RMQ is implemented using a segment tree
// Maximum edge from each node to its LCA is computed using heavy-light decomposition (HLD)

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
// heavy light decomposition (log(n)*log(n))

// maximum length of segment tree
const int MAX_N = 1e6;
// maximum number of vertices in the tree
const int MAX_V = 1e4;
const double INF = 100000001;
// two segment trees
int stree_LCA[MAX_N];
int stree_HLD[MAX_N];
// int arr[MAX_V];
long int E,V,treesize_LCA, treesize_HLD;

int tourindex = 1;
typedef pair <int, int> pii;
// each node has the node it is connected to and the edge
vector <list<pii> > adjList(MAX_V);
// order of nodes in the tour
int eulertour[2*MAX_V-1];
// heights of the nodes in the tour
int heights[2*MAX_V-1];
// first occurrences of nodes in the tour
int firstOcc[MAX_V];
bool visited[MAX_V];
int chainheads[MAX_V];
int totalchains = 1;
int edgecount;

struct node
{
  int parent;
  int depth;
  int subtree_size;
  // position in segment tree
  int pos_segtree;
  // the chain it belongs to
  int chain;
};

struct edge
{
  int weight;
  int deeper_node;
};

// stores info about each node
struct node nodes[MAX_V];
struct edge edges[MAX_V-1];

// initializes things for lca (tour, heights, etc..)
// finds info about node needed for hld
void dfs(int node, int parent, int height)
{
  // cout << "Calling dfs on vertex " << v << endl;
  visited[node] = true;
  eulertour[tourindex] = node;
  heights[tourindex] = height;
  firstOcc[node] = tourindex;

  nodes[node].parent = parent;
  nodes[node].depth = height;
  nodes[node].subtree_size = 1;

  list<pii>::iterator itl;
  // For all its neighbors
  for (itl = (adjList[node]).begin(); itl != (adjList[node]).end(); itl++)
  {
    if (visited[(*itl).first] == false)
    {
      tourindex++;
      edges[(*itl).second].deeper_node = (*itl).first;

      dfs((*itl).first, node, height+1);
      tourindex++;
      eulertour[tourindex] = node;
      heights[tourindex] = height;

      nodes[node].subtree_size+=nodes[(*itl).first].subtree_size;
    }
  }
}

void printEulerTour()
{
  cout << "Euler Tour: ";
  for (int i = 1; i <= 2*V-1; i++)
  {
    cout << eulertour[i] << " ";
  }
  cout << endl;
}

void printHeights()
{
  cout << "Heights: ";
  for (int i = 1; i <= 2*V-1; i++)
  {
    cout << heights[i] << " ";
  }
  cout << endl;
}

void printOcc()
{
  cout << "First Occ: ";
  for (int i = 1; i <= V; i++)
  {
    cout << firstOcc[i] << " ";
  }
  cout << endl;
}

void printNodes()
{
  cout << "Nodes: " << endl;
  for (int i = 1; i <= V; i++)
  {
    cout << "NODE: " << i << endl;
    cout << "Parent: " << nodes[i].parent << endl;
    cout << "Depth: " << nodes[i].depth << endl;
    cout << "Subtree size: " << nodes[i].subtree_size << endl;
    cout << "Position in segment tree: " << nodes[i].pos_segtree << endl;
    cout << "Chain: " << nodes[i].chain << endl;
    cout << endl;
  }
}

void printChainHeads()
{
  cout << "ChainHeads: " << endl;
  for (int i = 1; i <= totalchains; i++)
  {
    cout << "Chain: " << i << endl;
    cout << "Head: " << chainheads[i] << endl;
    cout << endl;
  }
}

void initialize_tree_LCA()
{
  for (int x = 0; x <= ((treesize_LCA+1)/2)-1; x++)
  {
    stree_LCA[x] = 0;
  }

  int ind = 1;
  for (int x = ((treesize_LCA+1)/2); x <= treesize_LCA; x++)
  {
    stree_LCA[x] = ind;
    ind++;
  }
}

void initialize_tree_HLD()
{
  for (int x = 0; x <= treesize_HLD; x++)
  {
    stree_HLD[x] = 0;
  }
}


void add_LCA(int index, int amount)
{
  // arr[index]+=amount;
  int powerOf2 = (treesize_LCA+1)/2;
  int i = index+powerOf2-1;
  // stree[i]+=amount;
  // cout << "Start point: " << i << endl;
  for (int c = i/2; c >= 1; c/=2)
  {
    // cout << "c: " << c << endl;
    if (heights[stree_LCA[2*c]] <= heights[stree_LCA[2*c+1]])
    {
      stree_LCA[c] = stree_LCA[2*c];
    }
    else
    {
      stree_LCA[c] = stree_LCA[2*c+1];
    }
    // cout << "value of stree: " << stree[c] << endl;
  }
}

void add_HLD(int index, int amount)
{
  // arr[index]+=amount;
  int powerOf2 = (treesize_HLD+1)/2;
  int i = index+powerOf2-1;
  stree_HLD[i]+=amount;
  // cout << "Start point: " << i << endl;
  for (int c = i/2; c >= 1; c/=2)
  {
    stree_HLD[c] = max(stree_HLD[2*c],stree_HLD[2*c+1]);
    // cout << "value of stree: " << stree_HLD[c] << endl;
  }
}

void printSegTree_LCA()
{
  cout << "Segment Tree LCA: ";
  for (int i = 1; i <= treesize_LCA; i++)
  {
    cout << stree_LCA[i] << " ";
  }
  cout << endl;
}

void printSegTree_HLD()
{
  cout << "Segment Tree HLD: ";
  for (int i = 1; i <= treesize_HLD; i++)
  {
    cout << stree_HLD[i] << " ";
  }
  cout << endl;
}

// Finds minimum over a range [a,b]
// Recursion finds minimums over disjoint intervals in the larger interval
int RMQ_LCA(int node, int a, int b, int start, int end)
{
  // cout << "Query range: [" << a << "," << b << "]" << endl;
  // cout << "Start/end range: [" << start << "," << end << "]" << endl;
  // If range is outside [a,b]
  if (start > b || end < a)
  {
    return INF;
  }
  // If range is within [a,b]
  else if (start >= a && end <= b)
  {
    // cout << "Returning: " << stree[node] << endl;
    return stree_LCA[node];
  }
  else
  {
    int mid = (start + end)/2;
    int left_child = RMQ_LCA(2*node,a,b,start,mid);
    int right_child = RMQ_LCA(2*node+1,a,b,mid+1,end);
    // if both indices exist
    if (left_child != INF && right_child != INF)
    {
      if (heights[left_child] <= heights[right_child])
      {
        return left_child;
      }
      else
      {
        return right_child;
      }
    }
    else if (left_child != INF)
    {
      return left_child;
    }
    else
    {
      return right_child;
    }
  }
}

// Finds minimum over a range [a,b]
// Recursion finds minimums over disjoint intervals in the larger interval
int RMQ_HLD(int node, int a, int b, int start, int end)
{
  // cout << "Query range: [" << a << "," << b << "]" << endl;
  // cout << "Start/end range: [" << start << "," << end << "]" << endl;
  // If range is outside [a,b]
  if (start > b || end < a)
  {
    return -INF;
  }
  // If range is within [a,b]
  else if (start >= a && end <= b)
  {
    // cout << "Returning: " << stree[node] << endl;
    return stree_HLD[node];
  }
  else
  {
    int mid = (start + end)/2;
    int left_child = RMQ_HLD(2*node,a,b,start,mid);
    int right_child = RMQ_HLD(2*node+1,a,b,mid+1,end);
    // Return max
    return max(left_child, right_child);
  }
}

void buildLCATree()
{
  int x = (int)(ceil(log2(2*V-1)));
  treesize_LCA = 2*(int)pow(2, x) - 1;
  initialize_tree_LCA();
  // cout << "Actual segment tree size: " << treesize << endl;
  for (int i = 1; i <= 2*V-1; i++)
  {
    add_LCA(i, heights[i]);
    // cout << heights[i] << " ";
  }
}


// Returns the lca of two nodes u and v
int LCA(int u, int v)
{
  // printEulerTour();
  // printHeights();
  // printOcc();
  // Constructing the segment tree

  // printSegTree_LCA();

  // If u is after v in the Euler tour, then swap them (range query won't work if they aren't swapped)
  if (firstOcc[u] > firstOcc[v])
  {
    int temp = u;
    u = v;
    v = temp;
  }

  int start = firstOcc[u];
  int end = firstOcc[v];
  int minindex = RMQ_LCA(1,start,end,1,(treesize_LCA+1)/2);
  // cout << "Query start: " << start << endl;
  // cout << "Query end: " << end << endl;
  // cout << "Index: " << minindex << endl;
  return eulertour[minindex];
}

// decomposes tree into chains
void HLD(int node, int edgeId)
{
  // if the head of the chain has not been initialized, then set it
  if (chainheads[totalchains] == 0)
  {
    chainheads[totalchains] = node;
  }
  nodes[node].chain = totalchains;
  nodes[node].pos_segtree = edgecount;
  // segment tree stuff
  add_HLD(edgecount, edges[edgeId].weight);

  edgecount++;
  list<pii>::iterator itl;
  int specialchild = -1;
  int specialedge = -1;
  // For all its neighbors that are not its parent (all children)
  for (itl = (adjList[node]).begin(); itl != (adjList[node]).end(); itl++)
  {
    if ((*itl).first != nodes[node].parent)
    {
      // finds the special child (child with the largest subtree)
      if (specialchild == -1 || nodes[specialchild].subtree_size < nodes[(*itl).first].subtree_size)
      {
        specialchild = (*itl).first;
        specialedge = (*itl).second;
      }
    }
  }

  // If node wasn't a leaf, then continue the chain
  if (specialchild != -1)
  {
    HLD(specialchild, specialedge);
  }

  // for the nonspecial children, start a new chain
  for (itl = (adjList[node]).begin(); itl != (adjList[node]).end(); itl++)
  {
    if ((*itl).first != nodes[node].parent && (*itl).first != specialchild)
    {
      totalchains++;
      HLD((*itl).first, (*itl).second);
    }
  }
}

// function to move from u to a node h above u
int calcMaxUp(int u, int h)
{
  int sol = 0;
  int h_chain = nodes[h].chain;
  cout << "Finding max between nodes " << u << " and " << h << endl;

  while (true)
  {
    int u_chain = nodes[u].chain;
    // two nodes belong to the same chain
    if (u_chain == h_chain)
    {
      if (u != h)
      {
        cout << "Same chain: " << endl;
        sol = max(sol, RMQ_HLD(1,nodes[h].pos_segtree+1, nodes[u].pos_segtree, 1, (treesize_HLD+1)/2));
        cout << "Max on Range: " << nodes[h].pos_segtree+1 << " to " << nodes[u].pos_segtree << " = " << sol << endl;
      }
      break;
    }
    // belong to different chains
    else
    {
      cout << "Different chain: " << endl;
      sol = max(sol, RMQ_HLD(1,nodes[chainheads[u_chain]].pos_segtree, nodes[u].pos_segtree, 1, (treesize_HLD+1)/2));
      cout << "Max on Range: " << nodes[chainheads[u_chain]].pos_segtree << " to " << nodes[u].pos_segtree << " = " << sol << endl;
      u = nodes[chainheads[u_chain]].parent;
    }
  }
  return sol;
}

int maxEdge(int u, int v)
{
  int lca = LCA(u,v);
  // cout << "LCA: " << lca << endl;
  // cout << "first max: " << calcMaxUp(u, lca) << endl;
  // cout << "second max: " << calcMaxUp(v, lca) << endl;
  return max(calcMaxUp(u, lca), calcMaxUp(v, lca));
}

int main()
{
  // Reading tree into adjacency list
  long int v1, v2, w,u, v;
  // E is the number of edges in the tree
  cin >> E;
  V = E+1;
  edges[0].weight = -1;
  edges[0].deeper_node = 1;
  for (long int x = 1; x < V; x++)
  {
    cin >> v1 >> v2 >> w;
    pii p1,p2;
    p1.first = v1;
    p1.second = x;
    p2.first = v2;
    p2.second = x;
    adjList[v1].push_back(p2);
    adjList[v2].push_back(p1);
    edges[x].weight = w;
  }
  // Reading in 2 nodes to find maxedge between
  cin >> u >> v;
  // cout << LCA(u,v) << endl;

  dfs(1,-1,0);
  buildLCATree();
  // edgecount = 1;
  int x = (int)(ceil(log2((E+1))));
  treesize_HLD = 2*(int)pow(2, x) - 1;
  // cout << "Edge count: " << edgecount << endl;
  // cout << "Treesize: " << treesize_HLD << endl;
  initialize_tree_HLD();
  HLD(1, 0);
  cout << maxEdge(u, v) << endl;
  // printNodes();
  // printChainHeads();
  // printSegTree_HLD();
}
