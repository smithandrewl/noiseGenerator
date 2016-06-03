#include "color.h"

sf::Color linearColor(int distance) {
  int value = std::min(255, distance);

  return sf::Color(value, value, value, 255);
}

sf::Color xorColor(int distance) {
  int value = std::min(255, distance);

  return sf::Color(
    value ^ 64,
    value ^ 32,
    value ^ 16,
    255
  );
}

sf::Color modColor(int distance) {
  int value = std::min(255, distance);

  return sf::Color(
    value %  70,
    value %   8,
    value % 255,
    255
  );
}

sf::Color andColor(int distance) {
  int value = std::min(255, distance);

  return sf::Color(
    value &   3,
    value &  80,
    value & 150,
    255
  );
}

sf::Color sinColor(int distance) {
  int value     = std::min(255, distance);
  int gammaAdj  = 70;

  float redPart   = 10.9;
  float greenPart =  5.9;
  float bluePart  = 20.5;

  return sf::Color(
    (sin(value * redPart)   * 100) + gammaAdj,
    (sin(value * greenPart) * 100) - gammaAdj,
    (sin(value * bluePart)  * 100) + gammaAdj,
    255
  );
}

sf::Color tanColor(int distance) {
  int value = std::min(255, distance);

  return sf::Color(
    tan(value * 30.00) * 100,
    tan(value * 25.00) * 100,
    tan(value * 30.07) * 100,
    255
  );
}

/*
sf::Color tanModSinColor(value) {
    int value = std::min(255, distance);
    var oct1 = tanColor(value);
    var oct1 = [oct1[0] * 0.125, oct1[1] * 0.125, oct1[2] * 0.125];
    var oct2 = modColor(value);
    var oct3 = sinColor(value);
    var oct3 = [oct3[0] * 0.25, oct3[1] * 0.25, oct3[2] * 0.25];

    var fin = [(oct1[0] + oct2[0] + oct3[0]) / 3, (oct1[1] + oct2[1] + oct3[1]) / 3, + (oct1[2] + oct2[2] + oct3[2]) / 3, 255];

    return fin;
}*/
