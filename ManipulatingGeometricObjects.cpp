// Library of functions to perform operations on geometric objects
// in a 2D plane


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
const double EPS = 0.01;

struct Point
{
  double x;
  double y;
  Point() { x = y = 0.0; }
  Point(double _x, double _y) : x(_x), y(_y) {}
  bool operator == (Point other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
};

struct Line
{
  double a,b,c;
};

struct Vec
{
  double x;
  double y;
};

bool comp(Point a, Point b)
{
    if (abs(a.x - b.x) > EPS)
    {
      return a.x < b.x;
    }
    else
    {
      return a.y < b.y;
    }
}

int N = 10;
struct Point PointColl[10];

void sortPoints()
{
  sort(PointColl, PointColl+N, comp);
}

bool isEqual(Point a, Point b)
{
  if ((abs(a.x - b.x) < EPS) && (abs(a.y - b.y) < EPS))
  {
    return true;
  }
  else
  {
    return false;
  }
}

double dist(Point a, Point b)
{
  double distance = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
  distance = sqrt(distance);
  return distance;
}

// rotates counterclockwise
Point rotate(Point a, double theta)
{
  Point p;
  double angle = (theta*22/7)/180;
  p.x = a.x*cos(angle) - a.y*sin(angle);
  p.y = a.x*sin(angle) - a.y*cos(angle);
  return p;
}

Line pointsToLine(Point a, Point b)
{
  Line l;
  if (abs(a.x - b.x) < EPS)
  {
    l.a = 1;
    l.b = 0;
    l.c = -a.x;
  }
  else
  {
    l.a = -(a.y-b.y)/(a.x-b.x);
    l.b = 1;
    l.c = -(l.a)*(a.x)-a.y;
  }
  return l;
}

bool areParallel(Line l1, Line l2)
{
  if (abs(l1.a-l2.a) < EPS && abs(l1.b-l2.b) < EPS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool areSame(Line l1, Line l2)
{
  if (areParallel(l1,l2) && abs(l1.c-l2.c) < EPS)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool areIntersect(Line l1, Line l2, Point &p)
{
  if (areParallel(l1,l2))
  {
    return false;
  }
  else
  {
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // cout << "X: " << p.x << endl;
    if (abs(l1.b) > EPS)
    {
      p.y = -(l1.a * p.x + l1.c);
    }
    else
    {
      p.y = -(l2.a * p.x + l2.c);
    }
    return true;
  }
}

// vector a->b
Vec toVec(Point a, Point b)
{
  Vec v;
  v.x = b.x-a.x;
  v.y = b.y-a.y;
  return v;
}

Vec scale(Vec v, double s)
{
  Vec scaled;
  scaled.x = v.x*s;
  scaled.y = v.y*s;
  return scaled;
}

Point translate(Point p, Vec v)
{
  Point trans;
  trans.x = p.x + v.x;
  trans.y = p.y + v.y;
  return trans;
}

double dot(Vec a, Vec b)
{
  return a.x * b.x + a.y * b.y;
}

double mag_sq(Vec v)
{
  return v.x * v.x + v.y * v.y;
}

// returns distance from p to line defined by Points a and b
// closest point is stored in c
double distToLine(Point p, Point a, Point b, Point &c)
{
  Vec ap = toVec(a,p);
  Vec ab = toVec(a,b);
  double u = dot(ap,ab) / mag_sq(ab);
  c = translate(a, scale(ab,u));
  return dist(p,c);
}

double distToLineSegment(Point p, Point a, Point b, Point &c)
{
  Vec ap = toVec(a,p);
  Vec ab = toVec(a,b);
  double u = dot(ap,ab) / mag_sq(ab);
  if (u < 0.0)
  {
    c.x = a.x;
    c.y = a.y;
    return dist(p,a);
  }
  if (u > 1.0)
  {
    c.x = b.x;
    c.y = b.y;
    return dist(p,b);
  }
  return distToLine(p,a,b,c);
}

// computes angle aob
double angle (Point a, Point o, Point b)
{
  Vec oa = toVec(o,a);
  Vec ob = toVec(o,b);
  return acos(dot(oa,ob) / sqrt(mag_sq(oa) * mag_sq(ob)));
}


double cross(Vec a, Vec b)
{
  return a.x * b.y - a.y * b.x;
}

// return true if point r is on left side of line pq
bool ccw(Point p, Point q, Point r)
{
  return cross(toVec(p,q), toVec(p,r)) > 0;
}

double perim(const vector<Point> &P)
{
  double result = 0.0;
  for (int i = 0; i < P.size()-1; i++)
  {
    result += dist(P[i], P[i+1]);
  }
  return result;
}

// uses shoelace theorem
double area (const vector<Point> &P)
{
  double result = 0.0, x1,y1,x2,y2;
  for (int i = 0; i < P.size()-1; i++)
  {
    x1 = P[i].x; x2 = P[i+1].x;
    y1 = P[i].y; y2 = P[i+1].y;
    result += (x1*y2 - x2*y1);
  }
  return abs(result)/2.0;
}

bool isConvex(const vector<Point> &P)
{
  int sz = P.size();
  if (sz <= 3)
  {
    return false;
  }
  bool isLeft = ccw(P[0], P[1], P[2]);
  for (int i = 1; i < sz-1; i++)
  {
    if (i+2 == sz)
    {
      if (ccw(P[i], P[i+1], P[1]) != isLeft)
      {
        return false;
      }
    }
    else
    {
      if (ccw(P[i], P[i+1], P[i+2]) != isLeft)
      {
        return false;
      }
    }
  }
  return true;
}

// winding number algorithm
bool inPolygon(Point pt, const vector<Point> &P)
{
  if (P.size() == 0)
  {
    return false;
  }
  double sum = 0;
  for (int i = 0; i < P.size()-1; i++)
  {
    if (ccw(pt, P[i], P[i+1]))
    {
      sum += angle(P[i], pt, P[i+1]);
    }
    else
    {
      sum -= angle(P[i], pt, P[i+1]);
    }
  }

  cout << "Sum: " << sum << endl;
  cout << "2PI: " << 22.0*2/7.0 << endl;
  return abs(abs(sum)-(2*22.0/7.0)) < EPS;
}

// intersection of line segment p-q with line A-B
Point lineIntersectSeg(Point p, Point q, Point A, Point B)
{
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x*A.y - A.x*B.y;
  double u = abs(a * p.x + b * p.y + c);
  double v = abs(a * q.x + b * q.y + c);
  return Point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

// cuts polygon Q along line formed by points a and b
// (in returned polygon, first point is the last point)
vector<Point> cutPolygon(Point a, Point b, const vector<Point> &Q)
{
  cout << "Starting cut polygon method" << endl;
  vector<Point> P;
  for (int i = 0; i < (int)Q.size(); i++)
  {
    double left1 = cross(toVec(a,b), toVec(a, Q[i]));
    double left2 = 0;
    cout << "Left1: " << left1 << endl;

    if (i != Q.size()-1)
    {
      left2 = cross(toVec(a,b), toVec(a, Q[i+1]));
    }
    cout << "Left2: " << left << endl;
    if (left1 > -EPS)
    {
      P.push_back(Q[i]);
    }

    if (left1 * left2 < -EPS)
    {
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a,b));
    }
  }

  if (!P.empty() && !(P.back() == P.front()))
  {
    P.push_back(P.front());
  }
  return P;
}

bool collinear(Point a, Point b, Point c)
{
  return (abs(cross(toVec(a,b), toVec(a,c))) < EPS);

}
Point pivot(0,0);
// Graham's scan algorithm for convex hull

// Compares angles with respect to a pivot Point
// Return true if angle a is less degrees (polar-wise with the pivot as the pole)
bool angleCmp(Point a, Point b)
{
  if (collinear(pivot,a,b))
  {
    return dist(pivot, a) < dist(pivot, b);
  }

  double d1x = a.x - pivot.x;
  double d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x;
  double d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

// Finds the convex hull of a set of points
vector<Point> CH(vector<Point> P)
{
  int i, j , n = P.size();
  // If there are only 3 or less points
  if (n <= 3)
  {
    if (!(P[0] == P[n-1]))
    {
      P.push_back(P[0]);
    }
    return P;
  }

  // Finds the bottommost point
  // If two points tie, then finds the rightmost
  int PO = 0;
  for (int i = 1; i < n; i++)
  {
    if (P[i].y < P[PO].y || (P[i].y == P[PO].y && P[i].x > P[PO].x))
    {
      PO = i;
    }
  }

  // Sets the pivot to the bottommost point and sorts the other points based on polar degree
  Point temp = P[0];
  P[0] = P[PO];
  P[PO] = temp;
  pivot = P[0];
  sort(++P.begin(), P.end(), angleCmp);
  vector<Point> S;
  S.push_back(P[n-1]);
  S.push_back(P[0]);
  S.push_back(P[1]);
  i = 2;
  // ccw tests
  while (i < n)
  {
    j = S.size()-1;
    if (ccw(S[j-1], S[j], P[i]))
    {
      S.push_back(P[i++]);
    }
    else
    {
      S.pop_back();
    }

  }

  return S;
}

int main()
{
  for (int p = 0; p < N; p++)
  {
    PointColl[p].x = N-p;
    PointColl[p].y = p;
  }
  sortPoints();
  for (int p = 0; p < N; p++)
  {
    cout << "(" << PointColl[p].x << "," << PointColl[p].y << ")" << endl;
    if (p != N-1)
    {
      cout << "Distance to next point: " << dist(PointColl[p], PointColl[p+1]) << endl;
    }
  }
  Point rotated = rotate(PointColl[0], 180);
  cout << "The 180 counterclockwise rotation of " << PointColl[0].x << "," << PointColl[0].y << " is " << rotated.x << "," << rotated.y << endl;
  Line l1 = pointsToLine(PointColl[0], PointColl[1]);
  Line l2 = pointsToLine(PointColl[1], PointColl[1]);
  cout << "Line is: " << l1.a << "x + " << l1.b << "y + " << l1.c << " = 0" << endl;
  cout << "Parallel: " << areParallel(l1,l2) << endl;
  cout << "Same: " << areSame(l1,l2) << endl;
  Line l3, l4;
  l3.a = 1; l3.b = 1; l3.c = -10;
  l4.a = -4; l4.b = 1; l4.c = 10;
  Point p1;
  cout << "Line intersection: " << areIntersect(l3,l4,p1) << " at " << p1.x << "," << p1.y << endl;
  Vec v = toVec(PointColl[0], PointColl[1]);
  v = scale(v, 0.5);
  cout << "Vector: " << v.x << " " << v.y << endl;
  Point p2,p3,p4,p5;
  p2.x = 1; p2.y = 2;
  p3.x = 1; p3.y = 1; p4.x = 2; p4.y = 2;
  cout << "Distance to Line: " << distToLine(p2, p3, p4, p5)  << " at " << p5.x << "," << p5.y << endl;
  cout << "Angle between vectors: " << angle(PointColl[0], PointColl[1],PointColl[2]) << endl;

  // 6 points, entered in counter clockwise order (polygon)
  // last point has to equal first point
  vector<Point> P;
  P.push_back(Point(1,1));
  P.push_back(Point(3,3));
  P.push_back(Point(9,1));
  P.push_back(Point(12,4));
  P.push_back(Point(9,7));
  P.push_back(Point(1,7));
  P.push_back(P[0]);
  cout << "Polygon perim: " << perim(P) << endl;
  cout << "Is convex: " << isConvex(P) << endl;
  cout << "Is (3,4) inside polygon?: " << inPolygon(Point(3,4), P) << endl;

  vector<Point> P2;
  P2.push_back(Point(1,1));
  P2.push_back(Point(9,1));
  P2.push_back(Point(4,4));
  // P2.push_back(Point(12,4));
  P2.push_back(Point(9,7));
  P2.push_back(Point(1,7));
  P2.push_back(P2[0]);

  vector<Point> cut = cutPolygon(Point(7,4), Point(9,7), P2);
  cout << "Subset of vertices from cut: " << cut.size() << endl;
  for (int i = 0; i < cut.size(); i++)
  {
    cout << cut[i].x << "," << cut[i].y << endl;
  }

  vector<Point> hull = CH(P2);
  cout << "Vertices in the convex hull: " << endl;
  for (int i = 0; i < hull.size(); i++)
  {
    cout << hull[i].x << "," << hull[i].y << endl;
  }


}
