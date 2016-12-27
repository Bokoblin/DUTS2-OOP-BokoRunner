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

#ifndef SETTINGS_VIEW_H
#define SETTINGS_VIEW_H

#include "AbstractView.h"
#include "../Model/Settings.h"

#define RADIO_BUTTONS_SIZE 26,26
#define INDICATOR_BUTTONS_SIZE 22,22

/**
 * SettingsView Class
 * @author Arthur
 * @date 20/05
 */
class SettingsView : public AbstractView
{
public:
    //=== CTORs / DTORs
    SettingsView(float w, float h, sf::RenderWindow *window, TextHandler * text);
    virtual ~SettingsView();

    //=== SETTERS
    void setSettingsModel(Settings *model);

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;
    bool treatEvents( sf::Event event );

private:
    //=== ATTRIBUTES
    Settings *m_settings;
    int m_currentIndicator;
    int m_nbIndicators;

    //Textures
    sf::Texture m_menuButtonTexture;
    sf::Texture m_radioButtonsTexture;
    sf::Texture m_pageIndicatorTexture;
    sf::Texture m_logoIUTTexture;

    //Graphic Elements
    Button *m_homeFormButton;
    Button *m_pageIndicatorButton;
    Button *m_englishLangRadio;
    Button *m_frenchLangRadio;
    Button *m_spanishLangRadio;
    Button *m_easyModeRadio;
    Button *m_hardModeRadio;
    Button *m_defaultBallSkinRadio;
    Button *m_morphBallSkinRadio;
    Button *m_capsuleBallSkinRadio;
    GraphicElement *m_logoIUTSprite;

    std::map<int, Button *> m_pageIndicators;
};


#endif
