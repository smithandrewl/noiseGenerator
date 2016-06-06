#ifndef DISTANCE_H
#define DISTANCE_H

#include<functional>

typedef std::function<int (int, int, int, int)> DistanceFunc;

enum DistanceFunction {
  Euclidean,
  Manhattan,
  Chebyshev,
  Other,
  OrthEuclidean,
  OrthManhattan,
  OrthChebyshev,
  OrthOther
};

int orth(int x1, int y1, int x2, int y2, DistanceFunc f);
int euclideanDistance(int x1, int y1, int x2, int y2);
int manhattanDistance(int x1, int y1, int x2, int y2);
int chebyshevDistance(int x1, int y1, int x2, int y2);
int other(int x1, int y1, int x2, int y2);
int orthEuclideanDistance(int x1, int y1, int x2, int y2);
int orthManhattanDistance(int x1, int y1, int x2, int y2);
int orthChebyshevDistance(int x1, int y1, int x2, int y2);
int orthOtherDistance(int x1, int y1, int x2, int y2);

#endif
