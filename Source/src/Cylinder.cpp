#include "cylinder.h"

Cylinder::Cylinder(Point center, float height, float radius)
{
  this -> center = center;
  ApproxLine.push_back(Line(Point(0, height), Point(radius, height)));
  ApproxLine.push_back(Line(Point(radius, height), Point(radius, 0)));
  ApproxLine.push_back(Line(Point(radius, 0), Point(0, 0)));
}