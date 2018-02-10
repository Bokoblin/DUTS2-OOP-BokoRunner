/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include "libs/MDC-SFML/src/Dialog.h"
#include "libs/MDC-SFML/src/RadioButton.h"
#include "app/model/models/SettingsModel.h"
#include "app/view/utils/DialogBuilder.h"
#include "AbstractView.h"

/**
 * The SettingsView class inherits AbstractView.
 * It is the view counterpart of the class SettingsModel.
 * It handles the settings screen's rendering.
 *
 * @author Arthur
 * @date 20/05/16 - 02/01/18
 */
class SettingsView : public AbstractView
{
public:
    //=== CTORs / DTORs
    SettingsView(sf::RenderWindow *window, AppTextManager *textManager, SettingsModel *settingsModel);
    ~SettingsView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    SettingsModel *m_settings;

    //UI components
    mdsf::Button *m_homeFormButton;
    mdsf::RadioButton *m_englishLangRadio;
    mdsf::RadioButton *m_frenchLangRadio;
    mdsf::RadioButton *m_spanishLangRadio;
    mdsf::RadioButton *m_easyModeRadio;
    mdsf::RadioButton *m_hardModeRadio;
    mdsf::RadioButton *m_defaultBallSkinRadio;
    mdsf::RadioButton *m_morphBallSkinRadio;
    mdsf::RadioButton *m_capsuleBallSkinRadio;
    mdsf::Button *m_resetDataRaisedButton;
    mdsf::Button *m_menuMusicButton;
    mdsf::Button *m_gameMusicButton;
    mdsf::Sprite *m_logoIUT;
    mdsf::Sprite *m_logoSFML;
    mdsf::Sprite *m_iconRepoLink;
    mdsf::Sprite *m_iconEmailLink;
    mdsf::Dialog *m_confirmDialog;

    //Containers
    std::map<int, mdsf::RadioButton *> m_pageIndicators;
    std::vector<mdsf::Button*> m_buttonList;

    //=== METHODS
    void loadSprites() override;
    void handleMusic();
    void updateTextBasedComponents() const;
};


#endif
