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

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "View.h"

/********************************************
    Constant Variables
********************************************/
const std::string TITLE_IMAGE = "Images/title.png";
const std::string RECT_BUTTONS_IMAGE = "Images/rect_buttons.png";
const std::string FORM_BUTTONS_IMAGE = "Images/menu_buttons.png";
const std::string RADIO_BUTTONS_IMAGE = "Images/radio_buttons.png";


/********************************************
    MenuView Class
*********************************************
    @author Arthur  @date 26/03 - 20/04
*********************************************/
class MenuView : public View
{
public:
    //=== CTORs / DTORs
    MenuView(float w, float h, sf::RenderWindow *window, Text * text);
    virtual ~MenuView();

    //=== SETTERS
	void setMenuModel(MenuModel *model);

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES
    MenuModel *m_menuModel;

    //Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleImageTexture;
    sf::Texture m_menuRectButtonsTexture;
    sf::Texture m_menuFormButtonsTexture;
    sf::Texture m_menuRadioButtonsTexture;

    //Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    Button *m_playRectButton;
    Button *m_quitRectButton;
    Button *m_clearLbRectButton;
    Button *m_settingsFormButton;
    Button *m_leaderboardFormButton;
    Button *m_homeFormButton;
    Button *m_englishLangRadioButton;
    Button *m_frenchLangRadioButton;
    Button *m_spanishLangRadioButton;
    Button *m_normalQuestRadioButton;
    Button *m_masterQuestRadioButton;
};

#endif // MENUVIEW_H
