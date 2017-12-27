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

#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include <SFML/Window/Event.hpp>
#include "../model/DataBase.h"
#include "Text.h"
#include "../model/Settings.h"
#include "../utils/definitions.h"

/**
 * The TextHandler Class groups app's standalone texts
 * and handles them
 *
 * Text objects branded as "label" are loaded from string files
 * Text objects branded as "Text" are loaded from parsed data
 *
 * @author Arthur
 * @date 02/04/16 - 25/01/17
 */
class TextHandler
{
    public:
    //=== CTORs / DTORs
    TextHandler(DataBase *dataBase, float width, float height);
    TextHandler(const TextHandler& myText) = delete;
    ~TextHandler();

    //=== GETTERS
    const sf::Font& getRegularFont() const;
    const sf::Font& getCondensedFont() const;
    const sf::Font& getBoldFont() const;

    //=== METHODS
    void updateWholeText();

    void initMenuLeaderboardText();

    void syncSplashScreenText(bool continueVisibility);
    void syncSettingsText(int currentPage);
    void syncMenuLeaderboardText();
    void syncShopText();
    void syncGameText(int bonusTimeout);
    void syncPauseText();
    void syncGameOverText(int gameSpeed);

    void drawSplashScreenText(sf::RenderWindow *window) const;
    void drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const;
    void drawLeaderboardText(sf::RenderWindow *window) const;
    void drawMenuShopText(sf::RenderWindow *window) const;
    void drawGameText(sf::RenderWindow *window) const;
    void drawPauseText(sf::RenderWindow *window) const;
    void drawGameOverText(sf::RenderWindow *window) const;
    void handleAboutLinks(sf::Event event, const Settings &settings) const;

private:
    //=== ATTRIBUTES
    float m_width, m_height;
    sf::Font m_regularFont;
    sf::Font m_condensedFont;
    sf::Font m_BoldFont;
    DataBase *m_dataBase;
    std::vector<Text*> m_textList;

    //Splash screen label
    Text *m_splashScreenContinueLabel; //FIXME: To keep only until auto dismissing with full-screen

    //Leaderboard Labels
    Text *m_leaderboardTitleLabel;

    //Settings Labels
    Text *m_configTitleLabel;
    Text *m_configLangTitleLabel;
    Text *m_configDifficultyTitleLabel;
    Text *m_configCustomTitleLabel;
    Text *m_configMusicTitleLabel;
    Text *m_statsTitleLabel;
    Text *m_statsOverallTitleLabel;
    Text *m_statsPerGameTitleLabel;
    Text *m_statsTotalDistanceLabel;
    Text *m_statsTotalEnemiesLabel;
    Text *m_statsTotalCoinsLabel;
    Text *m_statsTotalGamesLabel;
    Text *m_statsPerGameDistanceLabel;
    Text *m_statsPerGameEnemiesLabel;
    Text *m_statsPerGameCoinsLabel;
    Text *m_aboutTitleLabel;
    Text *m_aboutDescriptionLabel;
    Text *m_aboutRepositoryLabel;
    Text *m_aboutCopyrightLabel;

    //Settings Links
    Text *m_aboutRepositoryLink;
    Text *m_aboutEmailLink;

    //Game (Main, Pause & End) Labels
    Text *m_playerLifeLabel;
    Text *m_currentDistanceLabel;
    Text *m_coinsCollectedLabel;
    Text *m_endTitleLabel;
    Text *m_speedMultiplierLabel;
    Text *m_flattenedEnemiesLabel;
    Text *m_currentScoreLabel;

    //Menu data-texts
    Text *m_statsTotalDistanceText;
    Text *m_statsTotalEnemiesText;
    Text *m_statsTotalGamesText;
    Text *m_statsTotalCoinsNbText;
    Text *m_statsPerGameDistanceText;
    Text *m_statsPerGameEnemiesText;
    Text *m_statsPerGameCoinsText;
    Text *m_leaderboardContentEasyText;
    Text *m_leaderboardContentHardText;
    Text *m_walletText;

    //In-Game data-texts
    Text *m_currentDistanceText;
    Text *m_bonusTimeoutText;
    Text *m_currentCoinsNbText;
    Text *m_speedMultiplierText;
    Text *m_flattenedEnemiesText;
    Text *m_currentScoreText;

    //Constants
    const int PAUSE_TEXT_X = 80;
    const int STAT_LABEL_X = 60;
    const int SUBTOTAL_LABEL_X = 220;
    const int SUBTOTAL_VALUE_X = 580;
    const unsigned int DEFAULT_CHAR_SIZE = 24;
    const unsigned int CONTENT_CHAR_SIZE = 20;

    //=== METHODS
    void loadText();
};

#endif
