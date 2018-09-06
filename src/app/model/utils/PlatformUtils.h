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

#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include <string>

#if defined _WIN32

#include <rpc.h>

#endif


/**
 * The PlatformUtils class provides utils functions used to access system features
 *
 * @author Arthur
 * @date 06/09/18
 */
class PlatformUtils
{
public:
/**
 * Opens an URL in default browser
 * @author Arthur
 * @date 02/11/17
 */
    static void openURLinBrowser(const std::string& url)
    {
#if defined __linux__ || __unix__ || defined(_POSIX_VERSION)
        std::string command = "x-www-browser " + url;
        system(command.c_str());
#elif _WIN32
        ShellExecute(nullptr, nullptr, url.c_str(), nullptr, nullptr, SW_SHOW);
#elif __APPLE__
        std::string command = "open " + url;
        system(command.c_str());
#else
#error Operation not supported on your platform
#endif
    }
};

#endif
