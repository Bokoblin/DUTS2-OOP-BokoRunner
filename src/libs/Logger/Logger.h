/* Copyright 2017 Jolivet Arthur

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

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

/**
 * TODO : Temporary \n
 * The Logger class currently implements a temporary logger for stdout and stderr. \n
 * Moving forward to Boko Runner 2.0.x release, it should implement
 * a more complexe logger than just writing in program console
 *
 * @author Arthur
 * @date 28/12/17
 */
class Logger
{
public:
    static void printWarningOnConsole(const std::string &message)
    {
        std::cout << "[WARNING] " << message << std::endl;
    }

    static void printErrorOnConsole(const std::string &message)
    {
        std::cerr << "[ERROR] " << message << std::endl;
    }
};

#endif
