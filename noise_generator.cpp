#include "noise_generator.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <omp.h>

NoiseGenerator::NoiseGenerator(const sf::Vector2i& topLeft, int numPoints) {

  colorFunctions.insert(std::make_pair(std::string("Linear"), linearColor));
  colorFunctions.insert(std::make_pair(std::string("Xor"),    xorColor));
  colorFunctions.insert(std::make_pair(std::string("Mod"),    modColor));
  colorFunctions.insert(std::make_pair(std::string("And"),    andColor));
  colorFunctions.insert(std::make_pair(std::string("Sin"),    sinColor));
  colorFunctions.insert(std::make_pair(std::string("Tan"),    tanColor));
  colorFunctions.insert(std::make_pair(std::string("Minty"),  mintyColor));

  distanceFunctions.insert(std::make_pair(std::string("Euclidean"),     euclideanDistance));
  distanceFunctions.insert(std::make_pair(std::string("Manhattan"),     manhattanDistance));
  distanceFunctions.insert(std::make_pair(std::string("Chebyshev"),     chebyshevDistance));
  distanceFunctions.insert(std::make_pair(std::string("Other"),         other));
  distanceFunctions.insert(std::make_pair(std::string("Other1"),        other1));
  distanceFunctions.insert(std::make_pair(std::string("Other2"),        other2));
  distanceFunctions.insert(std::make_pair(std::string("Other3"),        other3));
  distanceFunctions.insert(std::make_pair(std::string("OrthEuclidean"), orthEuclideanDistance));
  distanceFunctions.insert(std::make_pair(std::string("OrthManhattan"), orthManhattanDistance));
  distanceFunctions.insert(std::make_pair(std::string("OrthChebyshev"), orthChebyshevDistance));
  distanceFunctions.insert(std::make_pair(std::string("OrthOther"),     orthOtherDistance));

  srand(time(NULL));

  colorFunc    = mintyColor;
  distanceFunc = euclideanDistance;

  numberOfPoints = numPoints;

  this->topLeft = topLeft;

  sprite.setPosition(topLeft.x, topLeft.y);
  texture.create(WIDTH, HEIGHT);
  sprite.setTexture(texture);

  generate();
}

std::vector<std::string> NoiseGenerator::getColorFunctions() {
  std::vector<std::string> names;

  for(auto pair : colorFunctions) {
    names.push_back(pair.first);
  }

  return names;
}

std::vector<std::string> NoiseGenerator::getDistanceFunctions() {
  std::vector<std::string> names;

  for(auto pair: distanceFunctions) {
    names.push_back(pair.first);
  }

  return names;
}

void NoiseGenerator::setColorFunction(const std::string& colorFunction) {
  colorFunc = colorFunctions[colorFunction];
}

void NoiseGenerator::setDistanceFunction(const std::string& distanceFunction) {
  distanceFunc = distanceFunctions[distanceFunction];
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

void NoiseGenerator::save(std::string path) {

  texture.copyToImage().saveToFile(path);
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


