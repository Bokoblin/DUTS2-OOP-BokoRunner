/* Copyright 2020 Jolivet Arthur

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef MDC_SFML_CLIP_RECT_UTILS_H
#define MDC_SFML_CLIP_RECT_UTILS_H

#include <bitset>
#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * Utility methods to manipulate sprite clip rectangles
 *
 * @author Arthur
 * @date 28/04/2020 - 02/05/2020
 */
class ClipRectUtils
{
public:
    //=== METHODS
    static std::vector<sf::IntRect> generate(int xOrigin, int yOrigin, int width, int height, int nbLine, int nbColumn);
    static unsigned long binaryToDecimal(int n);
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
