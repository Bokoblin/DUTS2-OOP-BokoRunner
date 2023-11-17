#include "ClipRectUtils.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

std::vector<sf::IntRect> ClipRectUtils::generate(int xOrigin, int yOrigin, int width, int height, int nbLine, int nbColumn)
{
    std::vector<sf::IntRect> clipRect;

    for (int i = 0; i < nbLine; i++) {
        for (int j = 0; j < nbColumn; j++) {
            clipRect.emplace_back(xOrigin + (j * width), yOrigin + (i * height), width, height);
        }
    }

    return clipRect;
}

unsigned long ClipRectUtils::binaryToDecimal(int n)
{
    return std::bitset<8>(std::to_string(n)).to_ulong();
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

