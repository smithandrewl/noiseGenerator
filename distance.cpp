#include "distance.h"
#include <cmath>

using namespace std;

int euclideanDistance(int x1, int y1, int x2, int y2) {
  int xDiff = x1 - x2;
  int yDiff = y1 - y2;

  return sqrt(
    (xDiff * xDiff) +
    (yDiff * yDiff)
  );
}

int manhattanDistance(int x1, int y1, int x2, int y2) {
  int xDiff = abs(x1 - x2);
  int yDiff = abs(y1 - y2);

  return xDiff + yDiff;
}

int chebyshevDistance(int x1, int y1, int x2, int y2) {
  return std::fmax(
    abs(x1 - x2),
    abs(y1 - y2)
  );
}

int other(int x1, int y1, int x2, int y2) {
  int xDiff = x1 - x2;
  int yDiff = y1 - y2;

  return (xDiff * xDiff) + (yDiff * yDiff);
}

int orthEuclideanDistance(int x1, int y1, int x2, int y2) {
  return 0;
}

int orthManhattanDistance(int x1, int y1, int x2, int y2) {
  return 0;
}

int orthChebyshevDistance(int x1, int y1, int x2, int y2) {
  return 0;
}

int orthOtherDistance(int x1, int y1, int x2, int y2) {
  return 0;
}
