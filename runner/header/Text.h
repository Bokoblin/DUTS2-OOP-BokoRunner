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


/********************************************
    Constant Variables
********************************************/
const std::string OLIVE_FONT = "Fonts/Antique_Olive.ttf";
const std::string ROBOTO_FONT = "Fonts/Roboto_Condensed.ttf";

/********************************************
    Text Class
*********************************************
    @author Arthur  @date 02/04
*********************************************/
class Text
{
    public:
    //=== CTORs / DTORs
    Text();
    ~Text();

    //=== GETTERS
    sf::Text getPauseResumeText();
    sf::Text getRestartText();
    sf::Text getHomeText();

    //=== METHODS
    void loadText();
    void syncMenuText(int width, int height);
    void syncGameText(GameModel *gameModel);
    void syncPauseText(GameModel *gameModel);
    void syncEndText(GameModel *gameModel);
    void drawMenuText(sf::RenderWindow *window);
    void drawGameText(sf::RenderWindow *window);
    void drawPauseText(sf::RenderWindow *window);
    void drawEndText(sf::RenderWindow *window);

private:
    //=== ATTRIBUTES
    sf::Font *m_font;

    //Menu Text
    sf::Text m_playButtonText;
    sf::Text m_quitButtonText;
    //Game Text
    sf::Text m_distanceText;
    sf::Text m_playerLifeLabel;
    //Pause Text
    sf::Text m_pauseResumeLabel;
    sf::Text m_restartLabel;
    sf::Text m_homeLabel;
    sf::Text m_CoinsCollectedNumberText;
    //End Text
    sf::Text m_endTitleLabel;
    sf::Text m_gameSpeedmultiplicatorLabel;
    sf::Text m_gameSpeedmultiplicatorText;
    sf::Text m_distanceLabel;
    sf::Text m_CoinsCollectedNumberLabel;
    sf::Text m_scoreLabel;
    sf::Text m_scoreText;
};

#endif // TEXT_H
