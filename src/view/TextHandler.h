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

#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include "../Model/DataBase.h"
#include "Text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#define TITLE_TEXT_ROW m_height/12
#define GOLD_COLOR sf::Color(255,204,0,255)
#define ENEMY_BLUE_COLOR sf::Color(0,232,209,255)
#define END_GREY_COLOR sf::Color(86,103,97,255)

/********************************************
    Constant Variables
********************************************/
const std::string RESOURCES_FOLDER = "../res/";
const std::string ROBOTO_REGULAR_FONT = RESOURCES_FOLDER + "Roboto_Regular.ttf";
const std::string ROBOTO_CONDENSED_FONT = RESOURCES_FOLDER + "Roboto_Condensed.ttf";
const std::string ROBOTO_BOLD_FONT = RESOURCES_FOLDER + "Roboto_Bold.ttf";
const std::string ENGLISH_STRINGS = RESOURCES_FOLDER + "english.xml";
const std::string FRENCH_STRINGS = RESOURCES_FOLDER + "french.xml";
const std::string SPANISH_STRINGS = RESOURCES_FOLDER + "spanish.xml";

const int PAUSE_TEXT_X = 80;
const int RADIO_TEXT_X = 100;
const int SUBTOTAL_LABEL_X = 220;
const int SUBTOTAL_VALUE_X = 580;
const int DEFAULT_CHARACTER_SIZE = 24;
const int CONTENT_CHARACTER_SIZE = 20;

/**
 * Text Class
 * @author Arthur
 * @date 02/04 - 22/12
 */
class TextHandler
{
    public:
    //=== CTORs / DTORs
    TextHandler(DataBase *data, const int width, const int height);
    TextHandler(const TextHandler& myText) = delete;
    ~TextHandler();

    //=== GETTERS
    sf::Font *getRegularFont() const;
    sf::Font *getCondensedFont() const;
    sf::Font *getBoldFont() const;
    Text *getResumeText() const;
    Text *getRestartText() const;
    Text *getHomeText() const;

    //=== METHODS
    void loadText();
    void updateWholeText();
    void updateString(std::string file, Text *currentText);

    void syncMenuHomeText();
    void syncSettingsText();
    void syncMenuLeaderboardText();
    void syncShopText();
    void syncDialogText(std::string context, std::string &title, std::string &content,
                                     std::string &neg_choice, std::string &pos_choices);
    void syncGameText(int bonusTimeout);
    void syncPauseText();
    void syncEndText(bool saveStatus, int gameSpeed);

    void drawMenuHomeText(sf::RenderWindow *window) const;
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

    //Menu and Leaderboard Labels -- loaded from file
    Text *m_playButtonLabel;
    Text *m_quitButtonLabel;
    Text *m_clearButtonLabel;
    Text *m_leaderboardTitleLabel;

    //Settings Labels
    Text *m_configTitleLabel;
    Text *m_configLangTitleLabel;
    Text *m_configLangEngLabel;
    Text *m_configLangFraLabel;
    Text *m_configLangEspLabel;
    Text *m_configDifficultyTitleLabel;
    Text *m_configEasyModeLabel;
    Text *m_configHardModeLabel;
    Text *m_configCustomTitleLabel;
    Text *m_configDefaultBallSkinLabel;
    Text *m_configMorphBallSkinLabel;
    Text *m_configCapsuleBallSkinLabel;
    Text *m_statisticsTitleLabel;
    Text *m_totalDistanceLabel;
    Text *m_totalFlattenedEnemiesLabel;
    Text *m_totalGamesPlayedLabel;
    Text *m_creditsTitleLabel;
    Text *m_creditsContentLabel;
    Text *m_copyrightLabel;

    //Shop Labels
    Text *m_shopDialogTitleLabel;
    Text *m_shopDialogContentLabel;
    Text *m_shopDialogNegativeLabel;
    Text *m_shopDialogPositiveLabel;
    Text *m_buySuccessContentLabel;
    Text *m_buyFailureContentLabel;

    //Game (Main, Pause & End) Labels
    Text *m_playerLifeLabel;
    Text *m_currentDistanceLabel;
    Text *m_coinsCollectedLabel;
    Text *m_pauseResumeLabel;
    Text *m_pauseRestartLabel;
    Text *m_pauseGoToHomeLabel;
    Text *m_endTitleLabel;
    Text *m_speedMultiplierLabel;
    Text *m_flattenedEnemiesLabel;
    Text *m_currentScoreLabel;

    //Settings and Leaderboard DataText -- loaded from parsed data
    Text *m_totalDistanceText;
    Text *m_totalFlattenedEnemiesText;
    Text *m_totalGamesPlayedText;
    Text *m_leaderboardContentText;

    //Game (Main, Pause & End) DataText
    Text *m_currentDistanceText;
    Text *m_bonusTimeoutText;
    Text *m_saveButtonText;
    Text *m_totalCoinsNbText;
    Text *m_currentCoinsNbText;
    Text *m_speedMultiplierText;
    Text *m_flattenedEnemiesText;
    Text *m_currentScoreText;
};

#endif