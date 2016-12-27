/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#include "AbstractModel.h"

/**
 * Settings Class
 * @author Arthur
 * @date 20/05 - 27/12
 */
class Settings : public AbstractModel
{
public:
    //=== CTORs / DTORs
    Settings(DataBase *dataBase);
    ~Settings();

    //=== GETTERS
    bool getMorphSkinAvailability() const;
    bool getCapsuleSkinAvailability() const;

    //=== METHODS
    void changeLanguage(std::string lang);
    void changeBallSkin(std::string skin);
    void checkItemsAvailability();
    virtual void nextStep() override;

private:
    //=== ATTRIBUTES
    bool m_morphSkinIsAvailable;
    bool m_capsuleSkinIsAvailable;
};

#endif
