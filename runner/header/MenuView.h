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
#include "MenuModel.h"

/********************************************
    Constant Variables
********************************************/
const std::string TITLE_IMAGE = "Images/title.png";
const std::string BUTTONS_IMAGE = "Images/buttons.png";
const std::string SETTINGS_BUTTONS_IMAGE = "Images/menu_buttons.png";
const std::string RADIOS_IMAGE = "Images/radios.png";


/********************************************
    MenuView Class
*********************************************
    @author Arthur  @date 26/03 - 19/04
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

    //Menu Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleTexture;
    sf::Texture m_playButtonTexture;
    sf::Texture m_quitButtonTexture;
    sf::Texture m_settingsButtonTexture;
    sf::Texture m_leaderboardButtonTexture;
    sf::Texture m_homeButtonTexture;

    //Settings Texture
    sf::Texture m_radioTexture;

    //Menu Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    Button *m_playButtonGraphic;
    Button *m_quitButtonGraphic;
    Button *m_settingsButtonGraphic;
    Button *m_leaderboardButtonGraphic;
    Button *m_homeButtonGraphic;

    //Settings Graphic Elements
    Button *m_langEnRadioGraphic;
    Button *m_langFrRadioGraphic;
    Button *m_langEsRadioGraphic;
    Button *m_difNormalRadioGraphic;
    Button *m_difMasterRadioGraphic;
};

#endif // MENUVIEW_H
