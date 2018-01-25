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

#include <string>
#include "libs/Logger/Logger.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * TODO : Temporary \n
 * The Config class currently implements a temporary config for MDC-SFML for stdout and stderr. \n
 * Moving forward it shall use values defined in an XML that user can change
 *
 * @author Arthur
 * @date 29/12/17
 */
class Config
{
public:
    //=== ATTRIBUTES
    static constexpr const char* DEFAULT_REGULAR_FONT = "../res/fonts/Roboto_Regular.ttf";
    static constexpr const char* DEFAULT_CONDENSED_FONT = "../res/fonts/Roboto_Condensed.ttf";
    static constexpr const char* DEFAULT_BOLD_FONT = "../res/fonts/Roboto_Bold.ttf";
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
