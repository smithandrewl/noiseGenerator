#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "distance.h"
#include "color.h"

#define WIDTH  1680
#define HEIGHT 1050

class NoiseGenerator {
  private:
    
    std::map<std::string, std::function<sf::Color (int)> > colorFunctions;
    std::map<std::string, std::function<int (int, int, int, int)> > distanceFunctions; 

    bool inverted;
    bool invertColors;

    int numberOfPoints;

    DistanceFunc distanceFunc;
    ColorFunc    colorFunc;

    std::vector<sf::Vector2i>               points;

    sf::Uint8    pixels[WIDTH * HEIGHT * 4];
    sf::Vector2i topLeft;
    sf::Texture  texture;
    sf::Sprite   sprite;

    int closestPoint(const sf::Vector2i& pixelLocation);
  
  public:
    NoiseGenerator(const sf::Vector2i& topLeft, int numPoints);

    sf::Vector2i     getTopLeft();

    int  getNumberOfPoints();
    void setColorFunction(const std::string& colorFunction);
    void setDistanceFunction(const std::string& distanceFunction);
    void setTopLeft(const sf::Vector2i& topLeft);
    void randomPoints(int count);
    void setNumberOfPoints(int numberOfPoints);
    void draw(sf::RenderWindow& window);
    void generate();
    void save(std::string path);
    bool getInverted();
    void setInverted(bool invert);

    bool getInvertColors();
    void setInvertColors(bool invert);

    std::vector<std::string> getColorFunctions();
    std::vector<std::string> getDistanceFunctions();
};

#endif
