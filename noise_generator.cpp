#include "noise_generator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <omp.h>

NoiseGenerator::NoiseGenerator(const sf::Vector2i& topLeft, int numPoints) {
  srand(time(NULL));

  colorFunction    = Linear;
  distanceFunction = Euclidean;

  colorFunc    = linearColor;
  distanceFunc = euclideanDistance;

  numberOfPoints = numPoints;

  this->topLeft = topLeft;

  sprite.setPosition(topLeft.x, topLeft.y);
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(texture);

  generate();
}

ColorFunction NoiseGenerator::getColorFunction() {
  return colorFunction;
}

void NoiseGenerator::setColorFunction(const ColorFunction& colorFunction) {
  this->colorFunction = colorFunction;

  switch(colorFunction) {
    case Linear:
      colorFunc = linearColor;
      break;
    case Xor:
      colorFunc = xorColor;
      break;
    case Mod:
      colorFunc = modColor;
      break;
    case And:
      colorFunc = andColor;
      break;
    case Sin:
      colorFunc = sinColor;
      break;
    case Tan:
      colorFunc = tanColor;
      break;
  }
}

DistanceFunction NoiseGenerator::getDistanceFunction() {
  return distanceFunction;
}

void NoiseGenerator::setDistanceFunction(const DistanceFunction& distanceFunction) {
  this->distanceFunction = distanceFunction;

  switch(distanceFunction) {
    case Euclidean:
      this->distanceFunc = euclideanDistance;
      break;
    case Manhattan:
      this->distanceFunc = manhattanDistance;
      break;
    case Chebyshev:
      this->distanceFunc = chebyshevDistance;
      break;
    case Other:
      this->distanceFunc = other;
      break;
    case OrthEuclidean:
      this->distanceFunc = orthEuclideanDistance;
      break;
    case OrthManhattan:
      this->distanceFunc = orthManhattanDistance;
      break;
    case OrthChebyshev:
      this->distanceFunc = orthChebyshevDistance;
      break;
    case OrthOther:
      this->distanceFunc = orthOtherDistance;
      break;
  }
}

int NoiseGenerator::getNumberOfPoints() {
  return numberOfPoints;
}

void NoiseGenerator::setNumberOfPoints(int numberOfPoints) {
  this->numberOfPoints = numberOfPoints;
}

int NoiseGenerator::closestPoint(const sf::Vector2i& pixelLocation) {

  int closestDist = 255;

  for(int i = 0; i < points.size(); i++) {

    int xDiff = pixelLocation.x - points[i].x;
    int yDiff = pixelLocation.y - points[i].y;

    bool inRange = (xDiff * xDiff) + (yDiff * yDiff) < (255 * 255);

    if(inRange) {
      int dist = distanceFunc(
        pixelLocation.x,
        pixelLocation.y,
        points[i].x,
        points[i].y
      );

      if(dist < closestDist) {
        closestDist  = dist;
      }
    }
  }

  return closestDist;
}

void NoiseGenerator::draw(sf::RenderWindow& window) {
  window.draw(sprite);
}

void NoiseGenerator::randomPoints(int count) {
  sf::Vector2i point;

  points.clear();
  points.reserve(count);

  for(int i = 0; i < count; i++) {
    point.x = rand() % WIDTH;
    point.y = rand() % HEIGHT;

    points.push_back(point);
  }
}

void NoiseGenerator::generate() {
  int distance;
  int base;

  sf::Color    color;
  sf::Vector2i closest;
  sf::Vector2i current;

  randomPoints(numberOfPoints);

  #pragma omp parallel private(current, closest, distance, color, base)
  #pragma omp for
  for(int x = 0; x < WIDTH; x++) {
    for(int y = 0; y < HEIGHT; y++) {
      base = (x + y * WIDTH) * 4;

      current.x = x;
      current.y = y;

      distance = closestPoint(current);

      if(inverted) {
        color = colorFunc(255 - distance);
      } else {
        color = colorFunc(distance);
      }

      if(getInvertColors()) {
        color.r = 255 - color.r;
        color.g = 255 - color.g;
        color.b = 255 - color.b;
      }

      pixels[base + 0] = color.r;
      pixels[base + 1] = color.g;
      pixels[base + 2] = color.b;
      pixels[base + 3] = color.a;

    }
  }

  texture.update(pixels);

}

void save(std::ostream& stream) {

}

sf::Vector2i NoiseGenerator::getTopLeft() {
  return topLeft;
}

void NoiseGenerator::setTopLeft(const sf::Vector2i& topLeft){
  this->topLeft = topLeft;
}

bool NoiseGenerator::getInverted() {
  return inverted;
}

void NoiseGenerator::setInverted(bool inverted) {
  this->inverted = inverted;
}

bool NoiseGenerator::getInvertColors() {
  return invertColors;
}

void NoiseGenerator::setInvertColors(bool invert) {
  this->invertColors = invert;
}


