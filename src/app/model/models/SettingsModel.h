/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include "app/model/enums/SettingsPage.h"
#include "app/view/utils/ViewDefinitions.h"
#include "AbstractModel.h"

/**
 * The SettingsModel class inherits AbstractModel.
 * It is the model counterpart of the class SettingsView.
 * It handles the settings screen's logic :
 * controlling current active page and checking item's availability
 *
 * @author Arthur
 * @date 20/05/16 - 30/10/18
 */
class SettingsModel: public AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit SettingsModel(AppCore* appCore);
    ~SettingsModel() override;

    //=== GETTERS
    int getCurrentPage() const;
    const std::string getLanguage() const;
    int getGameDifficulty() const;
    const std::string getPlayerSkin() const;
    bool isMenuMusicEnabled() const;
    bool isGameMusicEnabled() const;
    bool isMorphSkinAvailable() const;
    bool isCapsuleSkinAvailable() const;

    //=== SETTERS
    void setCurrentPage(int page);
    void setGameDifficulty(Difficulty difficulty);
    void toggleMenuMusic();
    void toggleGameMusic();

    //=== METHODS
    void changeLanguage(const std::string& language);
    void changeBallSkin(const std::string& skin);
    void checkItemsAvailability();
    void nextStep() override;
    void quit();
    void clearAppData();

    //=== ATTRIBUTES
    static const int PAGE_NUMBER = 3;

private:
    //=== ATTRIBUTES
    int m_currentPage;
    bool m_morphSkinIsAvailable;
    bool m_capsuleSkinIsAvailable;
};

#endif
