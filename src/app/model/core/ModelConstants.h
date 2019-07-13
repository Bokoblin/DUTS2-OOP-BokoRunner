/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#ifndef MODEL_CONSTANTS_H
#define MODEL_CONSTANTS_H

#include <string>

namespace Bokoblin
{
namespace BokoRunner
{
namespace Resources
{

/**
 * @brief Provide constants to model classes
 *
 * @author Arthur
 * @date 23/10/16 - 13/07/2019
 */
namespace Model
{

/**
 * @brief Folder constants
 */
namespace Folder
{
//=== Top-level Folders
//TODO: Use a dotenv configuration to replace environment based config (persistence, folders, screen, title)
//  - try this lib, it may work: https://github.com/adeharo9/cpp-dotenv
//  - see also: std::getenv (from official cpp ref)
extern const std::string RES;
extern const std::string SOURCES;
extern const std::string TESTS;

//=== Second-level Folders
extern const std::string LOCALIZATION;
}

//=== Languages
extern const std::string ENGLISH;
extern const std::string FRENCH;
extern const std::string SPANISH;

//=== Regex
extern const std::string INTEGER_REGEX;
extern const std::string BOOLEAN_REGEX;

//=== Language strings files
extern const std::string ENGLISH_STRINGS;
extern const std::string FRENCH_STRINGS;
extern const std::string SPANISH_STRINGS;

} //namespace Resources
} //namespace View
} //namespace BokoRunner
} //namespace Bokoblin

#endif
