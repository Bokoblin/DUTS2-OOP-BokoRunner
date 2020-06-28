/* Copyright 2017-2020 Jolivet Arthur

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

#ifndef MDC_SFML_COLOR_H
#define MDC_SFML_COLOR_H

#include <SFML/Graphics/Color.hpp>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Color class inherits sf::Color.
 * It defines the official 2014 Material colors.
 * It also defines custom colors and provide a color modifier enum
 *
 * @author Arthur
 * @date 29/12/17 - 28/06/2020
 *
 * @see sf::Color
 * @see https://m2.material.io/design/color/the-color-system.html#tools-for-picking-colors:~:text=2014%20Material%20Design%20color%20palettes
 */
class Color: public sf::Color
{
public:
    //=== ENUMS
    enum Modifier
    {
        REPL,   //Replace
        INCR,   //Increment
        DECR,   //Decrement
        MULT    //Multiply
    };

    //=== ATTRIBUTES

    //Special colors
    static const sf::Color Black;
    static const sf::Color White;
    static const sf::Color Transparent;


    //Main colors
    static const sf::Color MaterialRed;
    static const sf::Color MaterialPink;
    static const sf::Color MaterialPurple;
    static const sf::Color MaterialDeepPurple;
    static const sf::Color MaterialIndigo;
    static const sf::Color MaterialBlue;
    static const sf::Color MaterialLightBlue;
    static const sf::Color MaterialCyan;
    static const sf::Color MaterialTeal;
    static const sf::Color MaterialGreen;
    static const sf::Color MaterialLightGreen;
    static const sf::Color MaterialLime;
    static const sf::Color MaterialYellow;
    static const sf::Color MaterialAmber;
    static const sf::Color MaterialOrange;
    static const sf::Color MaterialDeepOrange;
    static const sf::Color MaterialBrown;
    static const sf::Color MaterialGrey;
    static const sf::Color MaterialBlueGrey;

    //Additional red colors
    static const sf::Color MaterialRed50;
    static const sf::Color MaterialRed100;
    static const sf::Color MaterialRed200;
    static const sf::Color MaterialRed300;
    static const sf::Color MaterialRed400;
    static const sf::Color MaterialRed500;
    static const sf::Color MaterialRed600;
    static const sf::Color MaterialRed700;
    static const sf::Color MaterialRed800;
    static const sf::Color MaterialRed900;
    static const sf::Color MaterialRedA100;
    static const sf::Color MaterialRedA200;
    static const sf::Color MaterialRedA400;
    static const sf::Color MaterialRedA700;

    //Additional pink colors
    static const sf::Color MaterialPink50;
    static const sf::Color MaterialPink100;
    static const sf::Color MaterialPink200;
    static const sf::Color MaterialPink300;
    static const sf::Color MaterialPink400;
    static const sf::Color MaterialPink500;
    static const sf::Color MaterialPink600;
    static const sf::Color MaterialPink700;
    static const sf::Color MaterialPink800;
    static const sf::Color MaterialPink900;
    static const sf::Color MaterialPinkA100;
    static const sf::Color MaterialPinkA200;
    static const sf::Color MaterialPinkA400;
    static const sf::Color MaterialPinkA700;
    static const sf::Color MaterialPurple50;

    //Additional purple colors
    static const sf::Color MaterialPurple100;
    static const sf::Color MaterialPurple200;
    static const sf::Color MaterialPurple300;
    static const sf::Color MaterialPurple400;
    static const sf::Color MaterialPurple500;
    static const sf::Color MaterialPurple600;
    static const sf::Color MaterialPurple700;
    static const sf::Color MaterialPurple800;
    static const sf::Color MaterialPurple900;
    static const sf::Color MaterialPurpleA100;
    static const sf::Color MaterialPurpleA200;
    static const sf::Color MaterialPurpleA400;
    static const sf::Color MaterialPurpleA700;

    //Additional indigo colors
    static const sf::Color MaterialIndigo50;
    static const sf::Color MaterialIndigo100;
    static const sf::Color MaterialIndigo200;
    static const sf::Color MaterialIndigo300;
    static const sf::Color MaterialIndigo400;
    static const sf::Color MaterialIndigo500;
    static const sf::Color MaterialIndigo600;
    static const sf::Color MaterialIndigo700;
    static const sf::Color MaterialIndigo800;
    static const sf::Color MaterialIndigo900;
    static const sf::Color MaterialIndigoA100;
    static const sf::Color MaterialIndigoA200;
    static const sf::Color MaterialIndigoA400;
    static const sf::Color MaterialIndigoA700;

    //Additional blue colors
    static const sf::Color MaterialBlue50;
    static const sf::Color MaterialBlue100;
    static const sf::Color MaterialBlue200;
    static const sf::Color MaterialBlue300;
    static const sf::Color MaterialBlue400;
    static const sf::Color MaterialBlue500;
    static const sf::Color MaterialBlue600;
    static const sf::Color MaterialBlue700;
    static const sf::Color MaterialBlue800;
    static const sf::Color MaterialBlue900;
    static const sf::Color MaterialBlueA100;
    static const sf::Color MaterialBlueA200;
    static const sf::Color MaterialBlueA400;
    static const sf::Color MaterialBlueA700;

    //Additional light blue colors
    static const sf::Color MaterialLightBlue50;
    static const sf::Color MaterialLightBlue100;
    static const sf::Color MaterialLightBlue200;
    static const sf::Color MaterialLightBlue300;
    static const sf::Color MaterialLightBlue400;
    static const sf::Color MaterialLightBlue500;
    static const sf::Color MaterialLightBlue600;
    static const sf::Color MaterialLightBlue700;
    static const sf::Color MaterialLightBlue800;
    static const sf::Color MaterialLightBlue900;
    static const sf::Color MaterialLightBlueA100;
    static const sf::Color MaterialLightBlueA200;
    static const sf::Color MaterialLightBlueA400;
    static const sf::Color MaterialLightBlueA700;

    //Additional cyan colors
    static const sf::Color MaterialCyan50;
    static const sf::Color MaterialCyan100;
    static const sf::Color MaterialCyan200;
    static const sf::Color MaterialCyan300;
    static const sf::Color MaterialCyan400;
    static const sf::Color MaterialCyan500;
    static const sf::Color MaterialCyan600;
    static const sf::Color MaterialCyan700;
    static const sf::Color MaterialCyan800;
    static const sf::Color MaterialCyan900;
    static const sf::Color MaterialCyanA100;
    static const sf::Color MaterialCyanA200;
    static const sf::Color MaterialCyanA400;
    static const sf::Color MaterialCyanA700;

    //Additional teal colors
    static const sf::Color MaterialTeal50;
    static const sf::Color MaterialTeal100;
    static const sf::Color MaterialTeal200;
    static const sf::Color MaterialTeal300;
    static const sf::Color MaterialTeal400;
    static const sf::Color MaterialTeal500;
    static const sf::Color MaterialTeal600;
    static const sf::Color MaterialTeal700;
    static const sf::Color MaterialTeal800;
    static const sf::Color MaterialTeal900;
    static const sf::Color MaterialTealA100;
    static const sf::Color MaterialTealA200;
    static const sf::Color MaterialTealA400;
    static const sf::Color MaterialTealA700;

    //Additional green colors
    static const sf::Color MaterialGreen50;
    static const sf::Color MaterialGreen100;
    static const sf::Color MaterialGreen200;
    static const sf::Color MaterialGreen300;
    static const sf::Color MaterialGreen400;
    static const sf::Color MaterialGreen500;
    static const sf::Color MaterialGreen600;
    static const sf::Color MaterialGreen700;
    static const sf::Color MaterialGreen800;
    static const sf::Color MaterialGreen900;
    static const sf::Color MaterialGreenA100;
    static const sf::Color MaterialGreenA200;
    static const sf::Color MaterialGreenA400;
    static const sf::Color MaterialGreenA700;

    //Additional light green colors
    static const sf::Color MaterialLightGreen50;
    static const sf::Color MaterialLightGreen100;
    static const sf::Color MaterialLightGreen200;
    static const sf::Color MaterialLightGreen300;
    static const sf::Color MaterialLightGreen400;
    static const sf::Color MaterialLightGreen500;
    static const sf::Color MaterialLightGreen600;
    static const sf::Color MaterialLightGreen700;
    static const sf::Color MaterialLightGreen800;
    static const sf::Color MaterialLightGreen900;
    static const sf::Color MaterialLightGreenA100;
    static const sf::Color MaterialLightGreenA200;
    static const sf::Color MaterialLightGreenA400;
    static const sf::Color MaterialLightGreenA700;

    //Additional lime colors
    static const sf::Color MaterialLime50;
    static const sf::Color MaterialLime100;
    static const sf::Color MaterialLime200;
    static const sf::Color MaterialLime300;
    static const sf::Color MaterialLime400;
    static const sf::Color MaterialLime500;
    static const sf::Color MaterialLime600;
    static const sf::Color MaterialLime700;
    static const sf::Color MaterialLime800;
    static const sf::Color MaterialLime900;
    static const sf::Color MaterialLimeA100;
    static const sf::Color MaterialLimeA200;
    static const sf::Color MaterialLimeA400;
    static const sf::Color MaterialLimeA700;

    //Additional yellow colors
    static const sf::Color MaterialYellow50;
    static const sf::Color MaterialYellow100;
    static const sf::Color MaterialYellow200;
    static const sf::Color MaterialYellow300;
    static const sf::Color MaterialYellow400;
    static const sf::Color MaterialYellow500;
    static const sf::Color MaterialYellow600;
    static const sf::Color MaterialYellow700;
    static const sf::Color MaterialYellow800;
    static const sf::Color MaterialYellow900;
    static const sf::Color MaterialYellowA100;
    static const sf::Color MaterialYellowA200;
    static const sf::Color MaterialYellowA400;
    static const sf::Color MaterialYellowA700;

    //Additional amber colors
    static const sf::Color MaterialAmber50;
    static const sf::Color MaterialAmber100;
    static const sf::Color MaterialAmber200;
    static const sf::Color MaterialAmber300;
    static const sf::Color MaterialAmber400;
    static const sf::Color MaterialAmber500;
    static const sf::Color MaterialAmber600;
    static const sf::Color MaterialAmber700;
    static const sf::Color MaterialAmber800;
    static const sf::Color MaterialAmber900;
    static const sf::Color MaterialAmberA100;
    static const sf::Color MaterialAmberA200;
    static const sf::Color MaterialAmberA400;
    static const sf::Color MaterialAmberA700;

    //Additional orange colors
    static const sf::Color MaterialOrange50;
    static const sf::Color MaterialOrange100;
    static const sf::Color MaterialOrange200;
    static const sf::Color MaterialOrange300;
    static const sf::Color MaterialOrange400;
    static const sf::Color MaterialOrange500;
    static const sf::Color MaterialOrange600;
    static const sf::Color MaterialOrange700;
    static const sf::Color MaterialOrange800;
    static const sf::Color MaterialOrange900;
    static const sf::Color MaterialOrangeA100;
    static const sf::Color MaterialOrangeA200;
    static const sf::Color MaterialOrangeA400;
    static const sf::Color MaterialOrangeA700;

    //Additional deep orange colors
    static const sf::Color MaterialDeepOrange50;
    static const sf::Color MaterialDeepOrange100;
    static const sf::Color MaterialDeepOrange200;
    static const sf::Color MaterialDeepOrange300;
    static const sf::Color MaterialDeepOrange400;
    static const sf::Color MaterialDeepOrange500;
    static const sf::Color MaterialDeepOrange600;
    static const sf::Color MaterialDeepOrange700;
    static const sf::Color MaterialDeepOrange800;
    static const sf::Color MaterialDeepOrange900;
    static const sf::Color MaterialDeepOrangeA100;
    static const sf::Color MaterialDeepOrangeA200;
    static const sf::Color MaterialDeepOrangeA400;
    static const sf::Color MaterialDeepOrangeA700;

    //Additional brown colors
    static const sf::Color MaterialBrown50;
    static const sf::Color MaterialBrown100;
    static const sf::Color MaterialBrown200;
    static const sf::Color MaterialBrown300;
    static const sf::Color MaterialBrown400;
    static const sf::Color MaterialBrown500;
    static const sf::Color MaterialBrown600;
    static const sf::Color MaterialBrown700;
    static const sf::Color MaterialBrown800;
    static const sf::Color MaterialBrown900;

    //Additional gray colors
    static const sf::Color MaterialGray50;
    static const sf::Color MaterialGray100;
    static const sf::Color MaterialGray200;
    static const sf::Color MaterialGray300;
    static const sf::Color MaterialGray400;
    static const sf::Color MaterialGray500;
    static const sf::Color MaterialGray600;
    static const sf::Color MaterialGray700;
    static const sf::Color MaterialGray800;
    static const sf::Color MaterialGray900;

    //Additional blue grey colors
    static const sf::Color MaterialBlueGray50;
    static const sf::Color MaterialBlueGray100;
    static const sf::Color MaterialBlueGray200;
    static const sf::Color MaterialBlueGray300;
    static const sf::Color MaterialBlueGray400;
    static const sf::Color MaterialBlueGray500;
    static const sf::Color MaterialBlueGray600;
    static const sf::Color MaterialBlueGray700;
    static const sf::Color MaterialBlueGray800;
    static const sf::Color MaterialBlueGray900;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
