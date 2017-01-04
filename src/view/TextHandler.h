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

#include "../Model/DataBase.h"
#include "Text.h"
#include "../model/Settings.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#define TITLE_TEXT_X m_height/12
#define GOLD_COLOR sf::Color(255,204,0,255)
#define ENEMY_BLUE_COLOR sf::Color(0,232,209,255)
#define END_GREY_COLOR sf::Color(86,103,97,255)

/********************************************
    Constant Variables
********************************************/
const std::string ROBOTO_REGULAR_FONT = RESOURCES_FOLDER + "Roboto_Regular.ttf";
const std::string ROBOTO_CONDENSED_FONT = RESOURCES_FOLDER + "Roboto_Condensed.ttf";
const std::string ROBOTO_BOLD_FONT = RESOURCES_FOLDER + "Roboto_Bold.ttf";

const int PAUSE_TEXT_X = 80;
const int RADIO_TEXT_X = 100;
const int SUBTOTAL_LABEL_X = 220;
const int SUBTOTAL_VALUE_X = 580;
const int DEFAULT_CHAR_SIZE = 24;
const int CONTENT_CHAR_SIZE = 20;

/**
 * The TextHandler Class groups app's standalone texts
 * and handles them
 *
 * Text objects branded as "label" are loaded from string files
 * Text objects branded as "Text" are loaded from parsed data
 *
 * @author Arthur
 * @date 02/04/16 - 04/01/17
 */
class TextHandler
{
    public:
    //=== CTORs / DTORs
    TextHandler(DataBase *dataBase, const int width, const int height);
    TextHandler(const TextHandler& myText) = delete;
    ~TextHandler();

    //=== GETTERS
    sf::Font *getRegularFont() const;
    sf::Font *getCondensedFont() const;
    sf::Font *getBoldFont() const;

    //=== METHODS
    void loadText();
    void updateWholeText();
    void updateString(Text *currentText);

    void syncMenuHomeText();
    void syncSettingsText(int currentPage);
    void syncMenuLeaderboardText();
    void syncShopText();
    void syncGameText(int bonusTimeout);
    void syncPauseText();
    void syncEndText(int gameSpeed);
    void drawMenuSettingsText(sf::RenderWindow *window, int currentPage) const;
    void drawLeaderboardText(sf::RenderWindow *window) const;
    void drawMenuShopText(sf::RenderWindow *window) const;
    void drawGameText(sf::RenderWindow *window) const;
    void drawPauseText(sf::RenderWindow *window) const;
    void drawEndText(sf::RenderWindow *window) const;

private:
    //=== ATTRIBUTES
    const int m_width, m_height;
    sf::Font *m_regularFont;
    sf::Font *m_condensedFont;
    sf::Font *m_BoldFont;
    DataBase *m_dataBase;
    std::vector<Text*> m_textList;

    //Leaderboard Labels
    Text *m_leaderboardTitleLabel;

    //Shop Labels
    Text *m_walletText;

    //Settings Labels
    Text *m_configTitleLabel;
    Text *m_configLangTitleLabel;
    Text *m_configDifficultyTitleLabel;
    Text *m_configCustomTitleLabel;
    Text *m_statsTitleLabel;
    Text *m_statsTotalDistanceLabel;
    Text *m_statsTotalEnemiesLabel;
    Text *m_statsTotalGamesLabel;
    Text *m_statsTotalCoinsLabel;
    Text *m_statsTotalCoinsNbText;
    Text *m_aboutTitleLabel;
    Text *m_aboutDescriptionLabel;
    Text *m_aboutRepositoryLabel;
    Text *m_aboutEmailLabel;
    Text *m_aboutCopyrightLabel;

    //Game (Main, Pause & End) Labels
    Text *m_playerLifeLabel;
    Text *m_currentDistanceLabel;
    Text *m_coinsCollectedLabel;
    Text *m_endTitleLabel;
    Text *m_speedMultiplierLabel;
    Text *m_flattenedEnemiesLabel;
    Text *m_currentScoreLabel;

    //Settings and Leaderboard DataText
    Text *m_statsTotalDistanceText;
    Text *m_statsTotalEnemiesText;
    Text *m_statsTotalGamesText;
    Text *m_leaderboardContentText;

    //Game (Main, Pause & End) DataText
    Text *m_currentDistanceText;
    Text *m_bonusTimeoutText;
    Text *m_currentCoinsNbText;
    Text *m_speedMultiplierText;
    Text *m_flattenedEnemiesText;
    Text *m_currentScoreText;
};

#endif