/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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
#include "libs/MDC-SFML/src/RaisedButton.h"
#include "app/model/models/SettingsModel.h"
#include "app/view/utils/DialogBuilder.h"
#include "AbstractView.h"

/**
 * The SettingsView class inherits AbstractView.
 * It is the view counterpart of the class SettingsModel.
 * It handles the settings screen's rendering.
 *
 * @author Arthur
 * @date 20/05/16 - 13/01/19
 */
class SettingsView: public AbstractView
{
public:
    //=== CTORs / DTORs
    SettingsView(sf::RenderWindow* window, AppTextManager* textManager, SettingsModel* settingsModel);
    ~SettingsView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event& event) override;

private:
    //=== ATTRIBUTES
    SettingsModel* m_settings;

    //UI components
    mdsf::RaisedButton* m_homeButton;
    mdsf::RadioButton* m_englishLangRadio;
    mdsf::RadioButton* m_frenchLangRadio;
    mdsf::RadioButton* m_spanishLangRadio;
    mdsf::RadioButton* m_easyModeRadio;
    mdsf::RadioButton* m_hardModeRadio;
    mdsf::RadioButton* m_defaultBallSkinRadio;
    mdsf::RadioButton* m_morphBallSkinRadio;
    mdsf::RadioButton* m_capsuleBallSkinRadio;
    mdsf::RaisedButton* m_resetDataButton;
    mdsf::Button* m_menuMusicButton;
    mdsf::Button* m_gameMusicButton;
    mdsf::Sprite* m_logoIUT;
    mdsf::Sprite* m_logoSFML;
    mdsf::Sprite* m_iconRepoLink;
    mdsf::Sprite* m_iconEmailLink;
    mdsf::Dialog* m_confirmDialog;

    //Containers
    std::map<int, mdsf::RadioButton*> m_pageIndicators;
    std::vector<mdsf::Button*> m_buttonList;

    //Constants
    const int OFFSET = 12;
    const int INDICATOR_PADDING = 2;
    const int CONFIRM_DIALOG_WIDTH = 320;
    const int CONFIRM_DIALOG_HEIGHT = 200;
    const int RESET_BUTTON_WIDTH = 150;
    const int RESET_BUTTON_HEIGHT = 40;
    const int MUTE_BUTTON_SIZE = 25;
    const int ORIGINAL_IUT_LOGO_WIDTH = 245;
    const int ORIGINAL_IUT_LOGO_HEIGHT = 210;
    const int ORIGINAL_SFML_LOGO_WIDTH = 373;
    const int ORIGINAL_SFML_LOGO_HEIGHT = 113;
    const int HOME_BUTTON_SIZE = 30;
    const int IUT_LOGO_WIDTH = 150;
    const int IUT_LOGO_HEIGHT = 130;
    const int SFML_LOGO_WIDTH = 150;
    const int SFML_LOGO_HEIGHT = 45;
    const int HYPERLINK_SIZE = 24;
    const int RADIO_DIAMETER = 25;
    const int INDICATOR_DIAMETER = 22;

    //=== METHODS
    void loadSprites() override;
    void handleMusic();
    void updateTextBasedComponents() const;
    float getDialogXPosition(int width) const;
    float getDialogYPosition(int height) const;
    void processClearAppDataConfirmAction();
    void handleConfigEvents(const sf::Event& event);
    void handleStatsEvents(const sf::Event& event);
    void handleAboutEvents(const sf::Event& event) const;
};


#endif
