#include "distance.h"
#include <cmath>

using namespace std;

int other1(int x1, int y1, int x2, int y2) {
  int dist = chebyshevDistance(x1, y1, x2, y2) - manhattanDistance(x1, y1, x2, y2) ;

  if(dist == 0) return 255;

  return dist;


}

int other2(int x1, int y1, int x2, int y2) {
  return (manhattanDistance(x1, y1, x2, y2) - chebyshevDistance(x1, y1, x2, y2));
}

int other3(int x1, int y1, int x2, int y2) {

    sqrt(manhattanDistance(x1, y1, x2, y2) * manhattanDistance(x1, y1, x2, y2) -
    chebyshevDistance(x1, y1, x2, y2) * chebyshevDistance(x1, y1, x2, y2));
}
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

int orth(int x1, int y1, int x2, int y2, DistanceFunc f) {
  int xDiff = abs(x1 - x2);
  int yDiff = abs(y1 - y2);

  if(yDiff > xDiff) {
    return (0.41 * xDiff) + (0.941246 * yDiff);
  } else {
    return f(x1, y1, x2, y2);
  }
}

int orthEuclideanDistance(int x1, int y1, int x2, int y2) {
  return orth(x1, y1, x2, y2, euclideanDistance);
}
int orthManhattanDistance(int x1, int y1, int x2, int y2) {
  return orth(x1, y1, x2, y2, manhattanDistance);
}

int orthChebyshevDistance(int x1, int y1, int x2, int y2) {
  return orth(x1, y1, x2, y2, chebyshevDistance);
}

int orthOtherDistance(int x1, int y1, int x2, int y2) {
  return orth(x1, y1, x2, y2, other);
}
