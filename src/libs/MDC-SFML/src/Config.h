/* Copyright 2017-2018 Jolivet Arthur

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

#ifndef MDC_SFML_CONFIG_H
#define MDC_SFML_CONFIG_H

#ifdef MDSF_RES_ROOT
#define FONT_FOLDER MDSF_RES_ROOT"/fonts/"
#define IMG_FOLDER MDSF_RES_ROOT"/images/"
#endif

#include <string>
#include <iostream>

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Config class is designed to define needed resources locations,
 * and store function pointers for the logger. \n
 * Moving forward it shall allow user configuration by using definitions
 *
 * @author Arthur
 * @date 29/12/17 - 28/04/20
 */
class Config
{
public:
    //=== ATTRIBUTES
    static constexpr const char* DEFAULT_REGULAR_FONT = FONT_FOLDER"Roboto_Regular.ttf";
    static constexpr const char* DEFAULT_CONDENSED_FONT = FONT_FOLDER"Roboto_Condensed.ttf";
    static constexpr const char* DEFAULT_BOLD_FONT = FONT_FOLDER"Roboto_Bold.ttf";
    static constexpr const char* RADIO_BUTTON_IMAGE = IMG_FOLDER"radio_button.png";
    static constexpr const char* RAISED_BUTTON_IMAGE = IMG_FOLDER"raised_button.png";
    static constexpr const char* TOGGLE_BUTTON_IMAGE = IMG_FOLDER"toggle_button.png";
    static constexpr const char* DIALOG_IMAGE = IMG_FOLDER"dialog_background.png";

    //Logger function pointer
    typedef void (* logger_function)(const std::string&);
    static logger_function printError;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
