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

#define RES_FOLDER "../res/" //TODO [2.0.x] Move MDC-SFML resources to MDC-SFML/res/

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
 * @date 29/12/17 - 12/10/18
 */
class Config
{
public:
    //=== ATTRIBUTES
    static constexpr const char* DEFAULT_REGULAR_FONT = RES_FOLDER"fonts/Roboto_Regular.ttf";
    static constexpr const char* DEFAULT_CONDENSED_FONT = RES_FOLDER"fonts/Roboto_Condensed.ttf";
    static constexpr const char* DEFAULT_BOLD_FONT = RES_FOLDER"fonts/Roboto_Bold.ttf";
    static constexpr const char* RADIO_BUTTON_IMAGE = RES_FOLDER"images/ui/radio_buttons.png";
    static constexpr const char* RAISED_BUTTON_IMAGE = RES_FOLDER"images/ui/raised_buttons.png";
    static constexpr const char* DIALOG_IMAGE = RES_FOLDER"images/ui/dialog.png";

    //Logger function pointer
    typedef void (*logger_function)(const std::string&);
    static logger_function printError;
    static void defaultPrintErrorFunction(const std::string& message);
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
