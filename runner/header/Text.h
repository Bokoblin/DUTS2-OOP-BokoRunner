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
#include "MenuModel.h"
#include "Leaderboard.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <fstream>


/********************************************
    Constant Variables
********************************************/
const std::string ROBOTO_FONT = "Resources/Roboto_Condensed.ttf";
const std::string ENGLISH_STRINGS = "Resources/english.xml";
const std::string FRENCH_STRINGS = "Resources/french.xml";
const std::string SPANISH_STRINGS = "Resources/spanish.xml";


/********************************************
    Text Class
*********************************************
    @author Arthur  @date 02/04 - 06/05
*********************************************/
class Text
{
    public:
    //=== CTORs / DTORs
    Text(DataModel *data);
    Text(const Text& myText) = delete;
    ~Text();

    //=== GETTERS
    sf::Text *getResumeText() const;
    sf::Text *getRestartText() const;
    sf::Text *getHomeText() const;

    //=== METHODS
    void loadText();
    void updateWholeText();
    void updateString(std::string file, sf::Text *currentText, std::string currentName);

    void syncMenuHomeText(int width, int height);
    void syncMenuSettingsText(MenuModel *gameModel, int width, int height);
    void syncMenuLeaderboardText(int w, int h, Leaderboard *lb);
    void syncGameText(GameModel *gameModel);
    void syncPauseText(GameModel *gameModel);
    void syncEndText(GameModel *gameModel);

    void drawMenuHomeText(sf::RenderWindow *window);
    void drawMenuSettingsText(sf::RenderWindow *window);
    void drawMenuLeaderboardText(sf::RenderWindow *window);
    void drawGameText(sf::RenderWindow *window);
    void drawPauseText(sf::RenderWindow *window);
    void drawEndText(sf::RenderWindow *window);

private:
    //=== ATTRIBUTES
    sf::Font *m_font;
    DataModel *m_dataModel;
    std::map<sf::Text*, std::string> m_textMap;

    //Menu, Settings and Leaderboard Labels
    // ( loaded from file)
    sf::Text *m_playButtonLabel;
    sf::Text *m_quitButtonLabel;
    sf::Text *m_clearButtonLabel;
    sf::Text *m_configTitleLabel;
    sf::Text *m_configLangTitleLabel;
    sf::Text *m_configLangEngLabel;
    sf::Text *m_configLangFraLabel;
    sf::Text *m_configLangEspLabel;
    sf::Text *m_configDifficultyLabel;
    sf::Text *m_configDifficultyNormalLabel;
    sf::Text *m_configDifficultyMasterLabel;
    sf::Text *m_statisticsTitleLabel;
    sf::Text *m_totalDistanceLabel;
    sf::Text *m_totalFlattenedEnemiesLabel;
    sf::Text *m_totalGamesPlayedLabel;
    sf::Text *m_leaderboardTitleLabel;

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

    //Menu, Settings and Leaderboard DataText
    // ( loaded from parsed data)
    sf::Text *m_totalDistanceText;
    sf::Text *m_totalFlattenedEnemiesText;
    sf::Text *m_totalGamesPlayedText;
    sf::Text *m_leaderboardContentText;

    //Game (Main, Pause & End) DataText
    sf::Text *m_currentDistanceText;
    sf::Text *m_bonusTimeoutText;
    sf::Text *m_saveButtonText;
    sf::Text *m_totalCoinsCollectedText;
    sf::Text *m_currentCoinsCollectedText;
    sf::Text *m_speedMultiplierText;
    sf::Text *m_flattenedEnemiesText;
    sf::Text *m_currentScoreText;
};

#endif // TEXT_H
