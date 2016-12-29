#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>

typedef std::function<sf::Color (int)> ColorFunc;

enum ColorFunction {
  Linear,
  Xor,
  Mod,
  And,
  Sin,
  Tan,
  Minty
};

sf::Color linearColor(int value);
sf::Color xorColor(int value);
sf::Color modColor(int value);
sf::Color andColor(int value);
sf::Color sinColor(int value);
sf::Color tanColor(int value);
sf::Color mintyColor(int value);

#endif
