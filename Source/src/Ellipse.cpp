#include "geometry.h"

Ellipse::Ellipse(Point center, int major, int minor)
{
  DrawByMidPoint(center, major, minor);
}

void Ellipse::Add4SymetricPoint(int x, int y, int index)
{
  for (int i = 0; i < 4; ++i)
  {
    int x_ = x * sym_x[i];
    int y_ = y * sym_y[i];
    PointSet[index + i] = Point(x_, y_);
  }
}

void Ellipse::DrawByMidPoint(Point center, int major, int minor)
{
  float major2 = pow(major, 2);
  float minor2 = pow(minor, 2);
  int P = (pow(minor, 2)) - (pow(major, 2) * minor) + (pow(major, 2) / 4);
  int X = 0;
  int Y = minor;
  // n_points = (floor(1.0 * major/sqrt(2)) + floor(1.0 * minor/sqrt(2)) + 1) * 4;
  float boundx = major2 / sqrt(major2 + minor2);
  float boundy = minor2 / sqrt(major2 + minor2);
  n_points = (ceil(boundx) + floor(boundy)) * 4;
  PointSet = new Point[n_points];
  PointSet[0] = Point(0,  minor);
  PointSet[1] = Point(0, -minor);
  PointSet[2] = Point( major, 0);
  PointSet[3] = Point(-major, 0);
  int i = 4;
  for (; i < ceil(boundx) * 4; i += 4)
  {
    X++;
    if (P >= 0)
    {
      Y--;
      P -= 2 * pow(major, 2) * Y;
    }
    P += pow(minor, 2) * (2 * X + 1);
    Add4SymetricPoint(X, Y, i);
  }
  P = pow(minor, 2) * pow((X + 1.0 / 2), 2) + pow(major, 2) * pow(Y - 1, 2) - pow(major, 2) * pow(minor, 2);
  for (; i < n_points; i += 4)
  {
    Y--;
    if (P <= 0)
    {
      X++;
      P += 2 * pow(minor, 2) * X;
    }
    P -= pow(major, 2) * (2 * Y - 1);
    Add4SymetricPoint(X, Y, i);
  }
  // move to center
  for (int i = 0; i < n_points; ++i)
  {
    PointSet[i].x += center.x;
    PointSet[i].y += center.y;
  }
}