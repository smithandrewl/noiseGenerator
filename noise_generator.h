#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <iostream>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "distance.h"
#include "color.h"

#define WIDTH 1680
#define HEIGHT 1050

class NoiseGenerator {
  private:
    bool inverted;
    int numberOfPoints;

    ColorFunction    colorFunction;
    DistanceFunction distanceFunction;

    DistanceFunc distanceFunc;
    ColorFunc          colorFunc;
    std::vector<sf::Vector2i>               points;

    sf::Uint8    pixels[WIDTH * HEIGHT * 4];
    sf::Vector2i topLeft;
    sf::Texture  texture;
    sf::Sprite   sprite;

    int closestPoint(const sf::Vector2i& pixelLocation);

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
    bool getInverted();
    void setInverted(bool invert);
};

#endif

