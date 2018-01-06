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

#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include <SFML/Window/Event.hpp>
#include "../model/DataBase.h"
#include "../../libs/MDC-SFML/src/Text.h"
#include "../model/SettingsModel.h"
#include "../utils/definitions.h"
#include "../utils/AppColor.h"

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * The AppTextManager Class groups app's standalone texts
 * and handles them
 *
 * Text objects branded as "label" are loaded from string files
 * Text objects branded as "Text" are loaded from parsed data
 *
 * @author Arthur
 * @date 02/04/16 - 06/01/18
 */
class AppTextManager
{
    public:
    //=== CTORs / DTORs
    AppTextManager(DataBase *dataBase, unsigned int width, unsigned int height);
    AppTextManager(const AppTextManager& myText) = delete;
    ~AppTextManager();

    //=== OPERATORS
    void operator=(AppTextManager const&) = delete;

    //=== METHODS
    //Text utils
    void handleAboutLinks(sf::Event event, const SettingsModel &settings) const;
    void updateWholeStandaloneTextContent(); //TODO: modularize (divide in modules to reduce time complexity)

    //Text init
    void initMenuLeaderboardText();

    //Text syncing
    void syncSplashScreenText(bool continueVisibility);
    void syncSettingsText(int currentPage);
    void syncMenuLeaderboardText();
    void syncShopText();
    void syncRunningGameText(int bonusTimeout);
    void syncPausedGameText();
    void syncGameOverText(int gameSpeed);

    //Text drawing
    void drawSplashScreenText(sf::RenderWindow *window) const;
    void drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const;
    void drawLeaderboardText(sf::RenderWindow *window) const;
    void drawMenuShopText(sf::RenderWindow *window) const;
    void drawRunningGameText(sf::RenderWindow *window) const;
    void drawPausedGameText(sf::RenderWindow *window) const;
    void drawGameOverText(sf::RenderWindow *window) const;

private:
    //=== ATTRIBUTES
    unsigned int m_width, m_height;
    sf::Font m_regularFont;
    sf::Font m_condensedFont;
    sf::Font m_BoldFont;
    DataBase *m_dataBase;
    std::vector<mdsf::Text*> m_textList;

    //Splash screen label
    mdsf::Text *m_splashScreenContinueLabel;

    //Leaderboard Labels
    mdsf::Text *m_leaderboardTitleLabel;

    //Settings Labels
    mdsf::Text *m_configTitleLabel;
    mdsf::Text *m_configLangTitleLabel;
    mdsf::Text *m_configDifficultyTitleLabel;
    mdsf::Text *m_configCustomTitleLabel;
    mdsf::Text *m_configMusicTitleLabel;
    mdsf::Text *m_statsTitleLabel;
    mdsf::Text *m_statsOverallTitleLabel;
    mdsf::Text *m_statsPerGameTitleLabel;
    mdsf::Text *m_statsTotalDistanceLabel;
    mdsf::Text *m_statsTotalEnemiesLabel;
    mdsf::Text *m_statsTotalCoinsLabel;
    mdsf::Text *m_statsTotalGamesLabel;
    mdsf::Text *m_statsPerGameDistanceLabel;
    mdsf::Text *m_statsPerGameEnemiesLabel;
    mdsf::Text *m_statsPerGameCoinsLabel;
    mdsf::Text *m_aboutTitleLabel;
    mdsf::Text *m_aboutDescriptionLabel;
    mdsf::Text *m_aboutRepositoryLabel;
    mdsf::Text *m_aboutCopyrightLabel;

    //Settings Links
    mdsf::Text *m_aboutRepositoryLink;
    mdsf::Text *m_aboutEmailLink;

    //Game (Main, Pause & End) Labels
    mdsf::Text *m_playerLifeLabel;
    mdsf::Text *m_currentDistanceLabel;
    mdsf::Text *m_coinsCollectedLabel;
    mdsf::Text *m_endTitleLabel;
    mdsf::Text *m_speedMultiplierLabel;
    mdsf::Text *m_flattenedEnemiesLabel;
    mdsf::Text *m_currentScoreLabel;

    //Menu data-texts
    mdsf::Text *m_statsTotalDistanceText;
    mdsf::Text *m_statsTotalEnemiesText;
    mdsf::Text *m_statsTotalGamesText;
    mdsf::Text *m_statsTotalCoinsNbText;
    mdsf::Text *m_statsPerGameDistanceText;
    mdsf::Text *m_statsPerGameEnemiesText;
    mdsf::Text *m_statsPerGameCoinsText;
    mdsf::Text *m_leaderboardContentEasyText;
    mdsf::Text *m_leaderboardContentHardText;
    mdsf::Text *m_walletText;

    //In-Game data-texts
    mdsf::Text *m_currentDistanceText;
    mdsf::Text *m_bonusTimeoutText;
    mdsf::Text *m_currentCoinsNbText;
    mdsf::Text *m_speedMultiplierText;
    mdsf::Text *m_flattenedEnemiesText;
    mdsf::Text *m_currentScoreText;

    //Constants
    const int PAUSE_TEXT_X = 80;
    const int STAT_LABEL_X = 60;
    const int SUBTOTAL_LABEL_X = 220;
    const int SUBTOTAL_VALUE_X = 580;
    const unsigned int DEFAULT_CHAR_SIZE = 24;
    const unsigned int CONTENT_CHAR_SIZE = 20;

    //=== METHODS
    void loadText(); //TODO: Modularize with map instead (like in the past :) ) to only load what's needed
};

#endif
