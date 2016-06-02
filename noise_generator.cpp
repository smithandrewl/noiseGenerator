#include "noise_generator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
NoiseGenerator::NoiseGenerator(sf::Vector2i& topLeft) {
  srand(time(NULL));
  this->colorFunction = Linear;
  this->distanceFunction = Euclidean;

  colorFunc = linearColor;
  distanceFunc = euclideanDistance;

  this->topLeft = topLeft;

  sprite.setPosition(topLeft.x, topLeft.y);
  texture.create(1420, 650);
  sprite.setTexture(texture);

  int base;
  for(int x = 0; x < 1420; x++) {
    for(int y = 0; y < 650; y++) {
      base = (x + y * 1420) *4;

      pixels[base + 0] = 255;
      pixels[base + 1] = 255;
      pixels[base + 2] = 255;
      pixels[base + 3] = 255;
    }
  }

  texture.update(pixels);
}

ColorFunction NoiseGenerator::getColorFunction() {
  return colorFunction;
}

void NoiseGenerator::setColorFunction(ColorFunction& colorFunction) {
  this->colorFunction = colorFunction;
}

DistanceFunction NoiseGenerator::getDistanceFunction() {
  return distanceFunction;
}

void NoiseGenerator::setDistanceFunction(DistanceFunction& distanceFunction) {
  this->distanceFunction = distanceFunction;
}

int NoiseGenerator::getNumberOfPoints() {
  return numberOfPoints;
}

void NoiseGenerator::setNumberOfPoints(int numberOfPoints) {
  this->numberOfPoints = numberOfPoints;
}

sf::Vector2i NoiseGenerator::closestPoint(sf::Vector2i& pixelLocation) {
  sf::Vector2i closestPoint = points[0];
  int closestDist = 90000;

  for(int i = 0; i < points.size(); i++) {
    int dist = euclideanDistance(pixelLocation.x, pixelLocation.y, points[i].x, points[i].y);

    if(dist < closestDist) {
      closestDist  = dist;
      closestPoint = points[i];
    }
  }

  return closestPoint;
}

void NoiseGenerator::draw(sf::RenderWindow& window) {
  window.draw(sprite);
}

void NoiseGenerator::randomPoints(int count) {
  points.clear();

  int x;
  int y;
  Vector2i point;
  for(int i = 0; i < count; i++) {
    x = rand() % 1420;
    y = rand() % 640;
    point.x = x;
    point.y = y;

    points.push_back(point);
  }
}
void NoiseGenerator::generate() {
  randomPoints(30);
  sf::Vector2i closest;
  sf::Color color;
  int distance;
  int base;

  for(int x = 0; x < 1420; x++) {
    for(int y = 0; y < 650; y++) {
      base = (x + y * 1420) *4;

      closest = closestPoint({x, y});

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

void NoiseGenerator::setTopLeft(sf::Vector2i& topLeft){
this->topLeft = topLeft;
}
