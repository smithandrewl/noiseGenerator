#include "color.h"

sf::Color linearColor(int distance) {
  int value = std::min(255, distance);
 return sf::Color(value, value, value, 255);
}
