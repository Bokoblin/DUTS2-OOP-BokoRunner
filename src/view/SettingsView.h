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

#ifndef SETTINGS_VIEW_H
#define SETTINGS_VIEW_H

#include "AbstractView.h"
#include "../model/Settings.h"
#include "RadioButton.h"
#include "Dialog.h"

/**
 * SettingsView Class
 * @author Arthur
 * @date 20/05/16 - 02/11/17
 */
class SettingsView : public AbstractView
{
public:
    //=== CTORs / DTORs
    SettingsView(sf::RenderWindow *window, TextHandler *textHandler, Settings *settingsModel);
    ~SettingsView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    Settings *m_settings;
    Dialog *m_confirmDialog;

    //Graphic Elements
    Button *m_homeFormButton;
    Button *m_englishLangRadio;
    Button *m_frenchLangRadio;
    Button *m_spanishLangRadio;
    Button *m_easyModeRadio;
    Button *m_hardModeRadio;
    Button *m_defaultBallSkinRadio;
    Button *m_morphBallSkinRadio;
    Button *m_capsuleBallSkinRadio;
    Button *m_resetRectButton;
    Button *m_menuMusicButton;
    Button *m_gameMusicButton;
    GraphicElement *m_logoIUTGraphic;
    GraphicElement *m_logoSFMLGraphic;
    GraphicElement *m_link1Graphic;
    GraphicElement *m_link2Graphic;

    //Containers
    std::map<int, RadioButton *> m_pageIndicators;
    std::vector<Button*> m_buttonList;

    //=== METHODS
    void loadImages() override;
    void handleMusic();
};


#endif
