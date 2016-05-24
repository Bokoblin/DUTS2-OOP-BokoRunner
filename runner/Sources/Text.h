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

#ifndef TEXT_H
#define TEXT_H

#include "GameModel.h"
#include "SFML/Graphics.hpp"
#include <map>

#define HALF_WIDTH getGlobalBounds().width/2
#define TITLE_TEXT_ROW h/12
#define GOLD_COLOR sf::Color(255,204,0,255)
#define ENEMY_BLUE_COLOR sf::Color(0,232,209,255)
#define END_GREY_COLOR sf::Color(86,103,97,255)

/********************************************
    Constant Variables
********************************************/
const std::string ROBOTO_REGULAR_FONT = "Resources/Roboto_Regular.ttf";
const std::string ROBOTO_CONDENSED_FONT = "Resources/Roboto_Condensed.ttf";
const std::string ROBOTO_BOLD_FONT = "Resources/Roboto_Bold.ttf";
const std::string ENGLISH_STRINGS = "Resources/english.xml";
const std::string FRENCH_STRINGS = "Resources/french.xml";
const std::string SPANISH_STRINGS = "Resources/spanish.xml";

const int PAUSE_TEXT_X = 80;
const int RADIO_TEXT_X = 100;
const int SUBTOTAL_LABEL_X = 220;
const int SUBTOTAL_VALUE_X = 580;
const int DEFAULT_CHARACTER_SIZE = 24;
const int CONTENT_CHARACTER_SIZE = 20;

/********************************************
    Text Class
*********************************************
    @author Arthur  @date 02/04 - 24/05
*********************************************/
class Text
{
    public:
    //=== CTORs / DTORs
    Text(DataBase *data);
    Text(const Text& myText) = delete;
    ~Text();

    //=== GETTERS
    sf::Font *getRegularFont() const;
    sf::Font *getCondensedFont() const;
    sf::Font *getBoldFont() const;
    sf::Text *getResumeText() const;
    sf::Text *getRestartText() const;
    sf::Text *getHomeText() const;

    //=== METHODS
    void loadText();
    void updateWholeText();
    void updateString(std::string file, sf::Text *currentText, std::string currentName);

    void syncMenuHomeText(int w, int h);
    void syncSettingsText( int w, int h);
    void syncMenuLeaderboardText(int w, int h, Leaderboard *lb);
    void syncShopText(int w, int h);
    void syncDialogText(std::string context, std::string &title, std::string &content,
                                     std::string &neg_choice, std::string &pos_choices);
    void syncGameText(GameModel *gameModel);
    void syncPauseText();
    void syncEndText(GameModel *gameModel, int w, int h);

    void drawMenuHomeText(sf::RenderWindow *window);
    void drawMenuSettingsText(sf::RenderWindow *window, int currentPage);
    void drawLeaderboardText(sf::RenderWindow *window);
    void drawMenuShopText(sf::RenderWindow *window);
    void drawGameText(sf::RenderWindow *window);
    void drawPauseText(sf::RenderWindow *window);
    void drawEndText(sf::RenderWindow *window);

private:
    //=== ATTRIBUTES
    sf::Font *m_regularFont;
    sf::Font *m_condensedFont;
    sf::Font *m_BoldFont;
    DataBase *m_dataBase;
    std::map<sf::Text*, std::string> m_textMap;

    //Menu and Leaderboard Labels -- loaded from file
    sf::Text *m_playButtonLabel;
    sf::Text *m_quitButtonLabel;
    sf::Text *m_clearButtonLabel;
    sf::Text *m_leaderboardTitleLabel;

    //Settings Labels
    sf::Text *m_configTitleLabel;
    sf::Text *m_configLangTitleLabel;
    sf::Text *m_configLangEngLabel;
    sf::Text *m_configLangFraLabel;
    sf::Text *m_configLangEspLabel;
    sf::Text *m_configDifficultyTitleLabel;
    sf::Text *m_configDifficultyNormalLabel;
    sf::Text *m_configDifficultyMasterLabel;
    sf::Text *m_configCustomTitleLabel;
    sf::Text *m_configDefaultBallskinLabel;
    sf::Text *m_configMorphBallskinLabel;
    sf::Text *m_configCapsuleBallskinLabel;
    sf::Text *m_statisticsTitleLabel;
    sf::Text *m_totalDistanceLabel;
    sf::Text *m_totalFlattenedEnemiesLabel;
    sf::Text *m_totalGamesPlayedLabel;
    sf::Text *m_creditsTitleLabel;
    sf::Text *m_creditsContentLabel;
    sf::Text *m_copyrightLabel;

    //Shop Labels
    sf::Text *m_shopDialogTitleLabel;
    sf::Text *m_shopDialogContentLabel;
    sf::Text *m_shopDialogNegativeLabel;
    sf::Text *m_shopDialogPositiveLabel;
    sf::Text *m_buySuccessContentLabel;
    sf::Text *m_buyFailureContentLabel;

    //Game (Main, Pause & End) Labels
    sf::Text *m_playerLifeLabel;
    sf::Text *m_currentDistanceLabel;
    sf::Text *m_coinsCollectedLabel;
    sf::Text *m_pauseResumeLabel;
    sf::Text *m_pauseRestartLabel;
    sf::Text *m_pauseGoToHomeLabel;
    sf::Text *m_endTitleLabel;
    sf::Text *m_speedMultiplierLabel;
    sf::Text *m_flattenedEnemiesLabel;
    sf::Text *m_currentScoreLabel;

    //Seetings and Leaderboard DataText -- loaded from parsed data
    sf::Text *m_totalDistanceText;
    sf::Text *m_totalFlattenedEnemiesText;
    sf::Text *m_totalGamesPlayedText;
    sf::Text *m_leaderboardContentText;

    //Game (Main, Pause & End) DataText
    sf::Text *m_currentDistanceText;
    sf::Text *m_bonusTimeoutText;
    sf::Text *m_saveButtonText;
    sf::Text *m_totalCoinsNbText;
    sf::Text *m_currentCoinsNbText;
    sf::Text *m_speedMultiplierText;
    sf::Text *m_flattenedEnemiesText;
    sf::Text *m_currentScoreText;
};

#endif // TEXT_H
