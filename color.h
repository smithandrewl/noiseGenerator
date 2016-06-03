#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics.hpp>
enum ColorFunction {
  Linear,
  Xor,
  Mod,
  And,
  Sin,
  Tan
};

sf::Color linearColor(int distance);
sf::Color xorColor(int distance);
sf::Color modColor(int distance);
sf::Color andColor(int distance);
sf::Color sinColor(int distance);
sf::Color tanColor(int distance);
#endif
