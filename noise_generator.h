#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include "distance.h"
#include "color.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <functional>

class NoiseGenerator {
  private:
    std::function<int (int, int, int, int)> distanceFunc;
    std::function<sf::Color (int)> colorFunc;

    sf::Uint8 pixels[1420 * 650 * 4];
    ColorFunction colorFunction;
    DistanceFunction distanceFunction;
    int numberOfPoints;
    std::vector<sf::Vector2i> points;
    sf::Vector2i closestPoint(sf::Vector2i& pixelLocation);
    sf::Vector2i topLeft;
    sf::Texture texture;
    sf::Sprite sprite;
  public:
    void randomPoints(int count);
    NoiseGenerator(sf::Vector2i& topLeft);
    sf::Vector2i getTopLeft();
    void setTopLeft(sf::Vector2i& topLeft);
    ColorFunction getColorFunction();
    void setColorFunction(ColorFunction& colorFunction);
    DistanceFunction getDistanceFunction();
    void setDistanceFunction(DistanceFunction& distanceFunction);
    int getNumberOfPoints();
    void setNumberOfPoints(int numberOfPoints);
    void draw(sf::RenderWindow& window);
    void generate();
    void save(std::ostream& stream);
};

#endif

