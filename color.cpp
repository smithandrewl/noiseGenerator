#include "color.h"

using namespace std;  

sf::Color linearColor(int value) {
  return sf::Color(value, value, value, 255);
}

sf::Color xorColor(int value) {
  return sf::Color(
    value ^ 64,
    value ^ 32,
    value ^ 16,
    255
  );
}

sf::Color modColor(int value) {
  return sf::Color(
    value %  70,
    value %   8,
    value % 255,
    255
  );
}

sf::Color andColor(int value) {
  return sf::Color(
    value &   3,
    value &  80,
    value & 150,
    255
  );
}

sf::Color sinColor(int value) {
  int gammaAdj  = 40.0;

  float redPart   = 20.5;
  float greenPart =  5.9;
  float bluePart  =  3.9;

  return sf::Color(
    (sin(value * redPart)   * 10.0) - gammaAdj,
    (sin(value * greenPart) * 10.0) + gammaAdj,
    (sin(value * bluePart)  * 10.0) - gammaAdj,
    255
  );
}

sf::Color tanColor(int value) {
  return sf::Color(
    tan(value * 3.00) *  10.0,
    tan(value * 3.00) * 100.0,
    tan(value * 4.07) *  10.0,
    255
  );
}


sf::Color mintyColor(int distance) {
    int value = distance * 2;
    sf::Color oct1 = sinColor(value);
    
    sf::Color oct2 = modColor(value * 3);

    sf::Color oct3 = xorColor(value);


    sf::Color fin = sf::Color((oct1.r  + oct2.r + oct3.r) / 3, (oct1.g  + oct2.g + oct3.g) / 3, + (oct1.b   + oct2.b + oct3.b) / 3, 255);

    fin = sf::Color( max(0, 255 - fin.r), max(0, 255 - fin.g), max(0, 255 - fin.b), 255);
    return fin;
}

