#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <iostream>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "distance.h"
#include "color.h"

#define WIDTH 1420
#define HEIGHT 650

class NoiseGenerator {
  private:
    int numberOfPoints;

    ColorFunction    colorFunction;
    DistanceFunction distanceFunction;

    std::function<int (int, int, int, int)> distanceFunc;
    std::function<sf::Color (int)>          colorFunc;
    std::vector<sf::Vector2i>               points;

    sf::Uint8    pixels[WIDTH * HEIGHT * 4];
    sf::Vector2i topLeft;
    sf::Texture  texture;
    sf::Sprite   sprite;

    void closestPoint(const sf::Vector2i& pixelLocation, sf::Vector2i& outLocation);

  public:
    NoiseGenerator(const sf::Vector2i& topLeft, int numPoints);

    sf::Vector2i     getTopLeft();
    ColorFunction    getColorFunction();
    DistanceFunction getDistanceFunction();

    int  getNumberOfPoints();
    void setDistanceFunction(const DistanceFunction& distanceFunction);
    void setColorFunction(const ColorFunction& colorFunction);
    void setTopLeft(const sf::Vector2i& topLeft);
    void randomPoints(int count);
    void setNumberOfPoints(int numberOfPoints);
    void draw(sf::RenderWindow& window);
    void generate();
    void save(std::ostream& stream);
};

#endif

