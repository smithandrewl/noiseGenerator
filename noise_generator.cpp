#include "noise_generator.h"

NoiseGenerator::NoiseGenerator(sf::Vector2i topLeft) {

  this->topLeft = topLeft;

  sprite.setPosition(topLeft.x, topLeft.y);
  texture.create(1420, 650);
  sprite.setTexture(texture);

  for(int i = 0; i < 1420 * 650 * 4; i+=4) {
    pixels[i + 0] = 15;
    pixels[i + 1] = 13;
    pixels[i + 2] = 13;
    pixels[i + 3] = 255;
  }

  texture.update(pixels);
}

ColorFunction NoiseGenerator::getColorFunction() {
  return colorFunction;
}

void NoiseGenerator::setColorFunction(ColorFunction colorFunction) {
  this->colorFunction = colorFunction;
}

DistanceFunction NoiseGenerator::getDistanceFunction() {
  return distanceFunction;
}

void NoiseGenerator::setDistanceFunction(DistanceFunction distanceFunction) {
  this->distanceFunction = distanceFunction;
}

int NoiseGenerator::getNumberOfPoints() {
  return numberOfPoints;
}

void NoiseGenerator::setNumberOfPoints(int numberOfPoints) {
  this->numberOfPoints = numberOfPoints;
}

sf::Vector2i NoiseGenerator::closestPoint(sf::Vector2i pixelLocation) {
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

void NoiseGenerator::generate() {

}

void save(std::ostream& stream) {

}

sf::Vector2i NoiseGenerator::getTopLeft() {
  return topLeft;
}

void NoiseGenerator::setTopLeft(sf::Vector2i topLeft){
this->topLeft = topLeft;
}
