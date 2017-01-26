/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef SETTINGS_H
#define SETTINGS_H

#include "DataBase.h"

/**
 * The Settings class is the model of SettingsView class
 * It controls page changing and checks item's availability for config changing
 * @author Arthur
 * @date 20/05/16 - 21/05/16
 */
class Settings
{
public:
    //=== CTORs / DTORs
    Settings(DataBase *dataBase);
    ~Settings();

    //=== GETTERS
    DataBase *getDataBase() const;
    bool getMorphSkinAvailability() const;
    bool getCapsuleSkinAvailability() const;
    int getCurrentPage() const;

    //=== SETTERS
    void setCurrentPage(int page);

    //=== METHODS
    void changeLanguage(std::string lang);
    void changeBallSkin(std::string skin);
    void checkItemsAvailability();

    //=== ATTRIBUTES
    static const int PAGE_NUMBER = 3;

    enum Page {
        CONFIG = 0,
        STATS = 1,
        ABOUT = 2
    };

private:
    //=== ATTRIBUTES
    DataBase *m_dataBase; //to not delete in dtor
    int m_currentPage;
    bool m_morphSkinIsAvailable;
    bool m_capsuleSkinIsAvailable;
};

#endif
