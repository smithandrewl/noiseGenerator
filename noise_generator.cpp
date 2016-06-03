#include "noise_generator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

NoiseGenerator::NoiseGenerator(const sf::Vector2i& topLeft) {
  srand(time(NULL));
  this->colorFunction = Linear;
  this->distanceFunction = Euclidean;

  colorFunc = linearColor;
  distanceFunc = euclideanDistance;

  this->topLeft = topLeft;

  sprite.setPosition(topLeft.x, topLeft.y);
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(texture);

  numberOfPoints = 5;
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
  }
}

int NoiseGenerator::getNumberOfPoints() {
  return numberOfPoints;
}

void NoiseGenerator::setNumberOfPoints(int numberOfPoints) {
  this->numberOfPoints = numberOfPoints;
}

void NoiseGenerator::closestPoint(const sf::Vector2i& pixelLocation, sf::Vector2i& outLocation) {
  sf::Vector2i* closestPoint = &points[0];
  int closestDist = 90000;

  for(int i = 0; i < points.size(); i++) {
    int dist = euclideanDistance(pixelLocation.x, pixelLocation.y, points[i].x, points[i].y);

    if(dist < closestDist) {
      closestDist  = dist;
      closestPoint = &points[i];
    }
  }

  outLocation.x = closestPoint->x;
  outLocation.y = closestPoint->y;
}

void NoiseGenerator::draw(sf::RenderWindow& window) {
  window.draw(sprite);
}

void NoiseGenerator::randomPoints(int count) {
  points.clear();
  points.reserve(count);
  sf::Vector2i point;

  for(int i = 0; i < count; i++) {
    point.x = rand() % WIDTH;
    point.y = rand() % HEIGHT;

    points.push_back(point);
  }
}
void NoiseGenerator::generate() {
  randomPoints(numberOfPoints);
  sf::Vector2i closest;
  sf::Color color;
  sf::Vector2i current;
  int distance;
  int base;

  for(int x = 0; x < WIDTH; x++) {
    for(int y = 0; y < HEIGHT; y++) {
      base = (x + y * WIDTH) * 4;

      current.x = x;
      current.y = y;
      closestPoint(current, closest);

      distance = distanceFunc(x, y, closest.x, closest.y);

      color = colorFunc(distance);

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
