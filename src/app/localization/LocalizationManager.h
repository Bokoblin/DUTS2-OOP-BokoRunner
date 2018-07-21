/* Copyright 2018 Jolivet Arthur

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

#ifndef LOCALIZATION_MANAGER_H
#define LOCALIZATION_MANAGER_H

#include "libs/Logger/Logger.h"
#include "libs/XMLHelper/XMLHelper.h"
#include "app/model/core/AppCore.h"
#include "LocalizationException.h"

class AppCore;

//TODO: maybe store config as static document xml instead of loading file each time
//TODO: Especially useful for languages files accessed a dozen times
//TODO: Dynamic language handling (adding a language file adds it to available languages if valid) [post 2.X?]

/**
 * The LocalizationManager class manages the app localization. \n
 * The localization method is abstracted from app's point of view in order to easily change
 * localization system by only changing this file. \n
 * The current localization system uses an xml string file for each supported language.
 *
 * @author Arthur
 * @date 11/02/18 - 21/07/18
 */
class LocalizationManager
{
public:
    //=== METHODS
    static void initContext(AppCore* appCore);
    static void closeContext();
    static void checkContext();
    static std::string fetchLocalizedString(const std::string& label);

private:
    //=== ATTRIBUTES
    static bool m_isInit;
    static AppCore* m_appCore;

    //=== METHODS
    static std::string getLanguageFile();
};

#endif
