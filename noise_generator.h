#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include "distance.h"
#include "color.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <functional>

#define WIDTH 1420
#define HEIGHT 650

class NoiseGenerator {
  private:
    std::function<int (int, int, int, int)> distanceFunc;
    std::function<sf::Color (int)> colorFunc;

    sf::Uint8 pixels[WIDTH * HEIGHT * 4];
    ColorFunction colorFunction;
    DistanceFunction distanceFunction;
    int numberOfPoints;
    std::vector<sf::Vector2i> points;
    void closestPoint(const sf::Vector2i& pixelLocation, sf::Vector2i& outLocation);
    sf::Vector2i topLeft;
    sf::Texture texture;
    sf::Sprite sprite;
  public:
    void randomPoints(int count);
    NoiseGenerator(const sf::Vector2i& topLeft);
    sf::Vector2i getTopLeft();
    void setTopLeft(const sf::Vector2i& topLeft);
    ColorFunction getColorFunction();
    void setColorFunction(const ColorFunction& colorFunction);
    DistanceFunction getDistanceFunction();
    void setDistanceFunction(const DistanceFunction& distanceFunction);
    int getNumberOfPoints();
    void setNumberOfPoints(int numberOfPoints);
    void draw(sf::RenderWindow& window);
    void generate();
    void save(std::ostream& stream);
};

#endif

