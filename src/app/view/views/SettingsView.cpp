#include "SettingsView.h"

namespace ModelResources = Bokoblin::BokoRunner::Resources::Model;
namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the settings view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param settingsModel the settings model counterpart
 *
 * @author Arthur
 * @date 20/05/16 - 03/05/2020
 */
SettingsView::SettingsView(sf::RenderWindow* window, AppTextManager* textManager, SettingsModel* settingsModel) :
        AbstractView(window, textManager), m_settings{settingsModel}, m_confirmDialog{nullptr}
{
    SettingsView::loadSprites();

    //=== Create Pages Indicator

    for (int i = 0; i < SettingsModel::PAGE_NUMBER; i++) {
        m_pageIndicators[i] = new mdsf::RadioButton(
                getHalfXPosition() - OFFSET * SettingsModel::PAGE_NUMBER + (INDICATOR_DIAMETER + INDICATOR_PADDING) * i,
                0.92f * m_height, 50, INDICATOR_DIAMETER, "", ViewResources::PAGE_INDICATOR_IMAGE);
    }

    //=== Fill button list

    m_buttonList.push_back(m_homeButton);
    m_buttonList.push_back(m_enLanguageRadio);
    m_buttonList.push_back(m_frLanguageRadio);
    m_buttonList.push_back(m_esLanguageRadio);
    m_buttonList.push_back(m_easyModeRadio);
    m_buttonList.push_back(m_hardModeRadio);
    m_buttonList.push_back(m_playerMoblinSkinRadio);
    m_buttonList.push_back(m_playerMorphingSkinRadio);
    m_buttonList.push_back(m_PlayerPokeballSkinRadio);
    m_buttonList.push_back(m_resetDataButton);
    m_buttonList.push_back(m_menuMusicButton);
    m_buttonList.push_back(m_gameMusicButton);

    //=== Init buttons

    for (mdsf::Button* button : m_buttonList) {
        button->retrieveLabel(LocalizationManager::fetchLocalizedString);
    }

    //=== Init confirm dialog

    m_confirmDialog = new mdsf::Dialog(
            getDialogXPosition(CONFIRM_DIALOG_WIDTH), getDialogYPosition(CONFIRM_DIALOG_HEIGHT),
            CONFIRM_DIALOG_WIDTH, CONFIRM_DIALOG_HEIGHT, "confirm_data_delete");
    m_confirmDialog->hide();
    DialogBuilder::retrieveCorrespondingStrings(m_confirmDialog);
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16 - 24/12/17
 */
SettingsView::~SettingsView()
{
    for (auto& button : m_buttonList) {
        delete button;
    }

    for (auto& it : m_pageIndicators) {
        delete it.second;
    }

    delete m_logoIUT;
    delete m_logoSFML;
    delete m_confirmDialog;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the settings screen
 *
 * @author Arthur
 * @date 20/05/2016 - 03/05/2020
 */
void SettingsView::loadSprites()
{
    //=== Initialize RADIOS buttons

    float C1_POS_X = 0.06f * m_width;
    float C2_POS_X = 0.58f * m_width;
    float C3_POS_X = 0.55f * m_width;
    float G1_POS_Y = 0.34f * m_height;
    float G2_POS_Y = 0.68f * m_height;
    float G3_POS_Y = 0.34f * m_height;
    float G4_POS_Y = 0.71f * m_height;

    m_enLanguageRadio = new mdsf::RadioButton(C1_POS_X, G1_POS_Y, 50, RADIO_DIAMETER, "config_lang_english");
    m_frLanguageRadio = new mdsf::RadioButton(C1_POS_X, G1_POS_Y + RADIO_DIAMETER, 50, RADIO_DIAMETER, "config_lang_french");
    m_esLanguageRadio = new mdsf::RadioButton(C1_POS_X, G1_POS_Y + 2 * RADIO_DIAMETER, 50, RADIO_DIAMETER, "config_lang_spanish");
    m_easyModeRadio = new mdsf::RadioButton(C1_POS_X, G2_POS_Y, 50, RADIO_DIAMETER, "config_easy_mode");
    m_hardModeRadio = new mdsf::RadioButton(C1_POS_X, G2_POS_Y + RADIO_DIAMETER, 50, RADIO_DIAMETER, "config_hard_mode");
    m_playerMoblinSkinRadio = new mdsf::RadioButton(C2_POS_X, G3_POS_Y, 50, RADIO_DIAMETER, "player_skin_moblin");
    m_playerMorphingSkinRadio = new mdsf::RadioButton(C2_POS_X, G3_POS_Y + RADIO_DIAMETER, 50, RADIO_DIAMETER, "player_skin_morphing");
    m_PlayerPokeballSkinRadio = new mdsf::RadioButton(C2_POS_X, G3_POS_Y + 2 * RADIO_DIAMETER, 50, RADIO_DIAMETER, "player_skin_pokeball");

    //=== Initialize Music controls

    m_menuMusicButton = new mdsf::ToggleButton(C3_POS_X, G4_POS_Y, MUTE_BTN_WIDTH, MUTE_BTN_HEIGHT, "config_music_menu");
    m_gameMusicButton = new mdsf::ToggleButton(C3_POS_X, G4_POS_Y + MUTE_BTN_HEIGHT, MUTE_BTN_WIDTH, MUTE_BTN_HEIGHT, "config_music_game");

    //=== Initialize HOME button

    m_homeButton = new mdsf::RaisedButton(10, 10, DEFAULT_HOME_SIZE, DEFAULT_HOME_SIZE, "", ViewResources::HOME_IMAGE);
    m_homeButton->resize(HOME_BTN_SIZE);

    //=== Initialize RESET button

    m_resetDataButton = new mdsf::RaisedButton(getHalfXPosition() - (0.5f * RESET_BTN_WIDTH), 0.75f * m_height,
                                               RESET_BTN_WIDTH, RESET_BTN_HEIGHT, "stats_app_reset");
    m_resetDataButton->setFillColor(mdsf::Color::MaterialRed);


    //=== Initialize Logo sprites

    m_logoIUT = new mdsf::Sprite(0.77f * m_width, 0.267f * m_height,
                                 ORIGINAL_IUT_LOGO_WIDTH, ORIGINAL_IUT_LOGO_HEIGHT, ViewResources::IUT_LOGO_IMAGE);
    m_logoIUT->resize(IUT_LOGO_WIDTH, IUT_LOGO_HEIGHT);

    m_logoSFML = new mdsf::Sprite(0.77f * m_width, 0.58f * m_height,
                                  ORIGINAL_SFML_LOGO_WIDTH, ORIGINAL_SFML_LOGO_HEIGHT, ViewResources::SFML_LOGO_IMAGE);
    m_logoSFML->resize(SFML_LOGO_WIDTH, SFML_LOGO_HEIGHT);

    //=== Initialize link icon

    m_iconRepoLink = new mdsf::Sprite(0.083f * m_width, 0.46f * m_height, HYPERLINK_SIZE, ViewResources::HYPERLINK_IMAGE);
    m_iconEmailLink = new mdsf::Sprite(0.083f * m_width, 0.613f * m_height, HYPERLINK_SIZE, ViewResources::HYPERLINK_IMAGE);
}


/**
 * Synchronizes settings elements
 *
 * @author Arthur
 * @date 20/05/2016 - 02/05/2020
 */
void SettingsView::synchronize()
{
    //=== Update Status of Radio buttons

    m_enLanguageRadio->setSelected(m_settings->getLanguage() == ModelResources::ENGLISH);
    m_frLanguageRadio->setSelected(m_settings->getLanguage() == ModelResources::FRENCH);
    m_esLanguageRadio->setSelected(m_settings->getLanguage() == ModelResources::SPANISH);
    m_easyModeRadio->setSelected(m_settings->getGameDifficulty() == EASY);
    m_hardModeRadio->setSelected(m_settings->getGameDifficulty() == HARD);
    m_playerMoblinSkinRadio->setSelected(m_settings->getPlayerSkin() == "moblin");
    m_playerMorphingSkinRadio->setSelected(m_settings->getPlayerSkin() == "morphing");
    m_PlayerPokeballSkinRadio->setSelected(m_settings->getPlayerSkin() == "pokeball");
    m_menuMusicButton->setToggled(m_settings->isMenuMusicEnabled());
    m_gameMusicButton->setToggled(m_settings->isGameMusicEnabled());

    m_playerMorphingSkinRadio->setEnabled(m_settings->isMorphBallSkinAvailable());
    m_PlayerPokeballSkinRadio->setEnabled(m_settings->isPokeballSkinAvailable());
    m_playerMoblinSkinRadio->setEnabled(m_settings->isMorphBallSkinAvailable() || m_settings->isPokeballSkinAvailable());

    //=== Sync buttons

    for (mdsf::Button* button : m_buttonList) {
        button->sync();
    }

    //=== Update and sync indicators

    for (auto& it : m_pageIndicators) {
        (it.second)->sync();
        (it.second)->setSelected(it.first == m_settings->getCurrentPage());
    }

    //=== Standalone Text update

    m_textManager->syncMenuSettingsText(m_settings->getCurrentPage());
}


/**
 * Draws settings elements on the window
 *
 * @author Arthur
 * @date 20/05/16 - 30/10/18
 */
void SettingsView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    m_homeButton->draw(m_window);

    for (const auto& it : m_pageIndicators) {
        it.second->draw(m_window);
    }

    switch (m_settings->getCurrentPage()) {
        case CONFIG:
            m_enLanguageRadio->draw(m_window);
            m_frLanguageRadio->draw(m_window);
            m_esLanguageRadio->draw(m_window);
            m_easyModeRadio->draw(m_window);
            m_hardModeRadio->draw(m_window);
            m_playerMoblinSkinRadio->draw(m_window);
            m_playerMorphingSkinRadio->draw(m_window);
            m_PlayerPokeballSkinRadio->draw(m_window);
            m_menuMusicButton->draw(m_window);
            m_gameMusicButton->draw(m_window);
            m_textManager->drawMenuSettingsText(m_window, CONFIG);
            break;
        case STATS:
            m_resetDataButton->draw(m_window);
            m_textManager->drawMenuSettingsText(m_window, STATS);
            m_confirmDialog->draw(m_window); //Must be above everything
            break;
        case ABOUT:
            m_logoIUT->draw(m_window);
            m_logoSFML->draw(m_window);
            m_iconRepoLink->draw(m_window);
            m_iconEmailLink->draw(m_window);
            m_textManager->drawMenuSettingsText(m_window, ABOUT);
            break;
        default:
            break;
    }

    m_window->display();
}


/**
 * Updates all text based components
 * or components that uses text (e.g. buttons, dialogs).
 * This function is meant to be used only by some
 * event triggers (those which change language) to minimize disk access.
 *
 * @author Arthur
 * @date 02/01/18
 */
void SettingsView::updateTextBasedComponents() const
{
    //Update standalone text
    m_textManager->updateWholeStandaloneTextContent();

    //Update button text
    for (mdsf::Button* button : m_buttonList) {
        button->retrieveLabel(LocalizationManager::fetchLocalizedString);
    }

    //Update dialog text
    DialogBuilder::retrieveCorrespondingStrings(m_confirmDialog);
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 20/05/16 - 14/01/19
 */
bool SettingsView::handleEvents(sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event) && !m_confirmDialog->isVisible()) {
        for (mdsf::Button* button : m_buttonList) {
            if (EventUtils::isMouseInside(*button, event)) {
                button->setPressed(true);
                break;
            }
        }
    }

    if (EventUtils::wasMouseReleased(event)) {
        for (mdsf::Button* button : m_buttonList) { //Reset all buttons
            button->setPressed(false);
        }

        if (!m_confirmDialog->isVisible() && EventUtils::isMouseInside(*m_homeButton, event)) {
            m_settings->quit();
            return false;
        }
    }

    handlePageIndicatorsEvents(event);

    switch (m_settings->getCurrentPage()) {
        case CONFIG:
            handleConfigEvents(event);
            break;
        case STATS:
            handleStatsEvents(event);
            break;
        case ABOUT:
            handleAboutEvents(event);
            break;
        default:
            break;
    }

    return true;
}


/**
 * Handles the user interaction events for config page
 *
 * @param event sfml event object
 *
 * @author Arthur
 * @date 20/05/16 - 30/10/18
 */
void SettingsView::handleConfigEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseReleased(event)) {
        if (EventUtils::isMouseInside(*m_enLanguageRadio, event)) {
            m_settings->changeLanguage(ModelResources::ENGLISH);
            updateTextBasedComponents();
        } else if (EventUtils::isMouseInside(*m_frLanguageRadio, event)) {
            m_settings->changeLanguage(ModelResources::FRENCH);
            updateTextBasedComponents();
        } else if (EventUtils::isMouseInside(*m_esLanguageRadio, event)) {
            m_settings->changeLanguage(ModelResources::SPANISH);
            updateTextBasedComponents();
        } else if (EventUtils::isMouseInside(*m_easyModeRadio, event)) {
            m_settings->setGameDifficulty(EASY);
        } else if (EventUtils::isMouseInside(*m_hardModeRadio, event)) {
            m_settings->setGameDifficulty(HARD);
        } else if (EventUtils::isMouseInside(*m_playerMoblinSkinRadio, event)) {
            m_settings->changePlayerSkin("moblin");
        } else if (EventUtils::isMouseInside(*m_playerMorphingSkinRadio, event)) {
            m_settings->changePlayerSkin("morphing");
        } else if (EventUtils::isMouseInside(*m_PlayerPokeballSkinRadio, event)) {
            m_settings->changePlayerSkin("pokeball");
        } else if (EventUtils::isMouseInside(*m_menuMusicButton, event)) {
            m_settings->toggleMenuMusic();
        } else if (EventUtils::isMouseInside(*m_gameMusicButton, event)) {
            m_settings->toggleGameMusic();
        }
    }
}


/**
 * Handles the user interaction events for stats page
 *
 * @param event sfml event object
 *
 * @author Arthur
 * @date 20/05/16 - 30/10/18
 */
void SettingsView::handleStatsEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseReleased(event)) {
        if (m_confirmDialog->isVisible()) {
            if (EventUtils::isMouseInside(m_confirmDialog->getOkButtonText(), event)) {
                processClearAppDataConfirmAction();
            } else if (EventUtils::isMouseInside(m_confirmDialog->getCancelButtonText(), event)
                    || !EventUtils::isMouseInside(*m_confirmDialog, event)) {
                m_confirmDialog->hide();
            }
        } else {
            if (EventUtils::isMouseInside(*m_resetDataButton, event)) {
                m_confirmDialog->show();
            }
        }
    }

    if (EventUtils::wasKeyboardEscapePressed(event)) {
        m_confirmDialog->hide();
    }
}


/**
 * Handles the user interaction events for about page
 *
 * @param event sfml event object
 *
 * @author Arthur
 * @date 20/05/16 - 30/10/18
 */
void SettingsView::handleAboutEvents(const sf::Event& event) const
{
    if (EventUtils::wasMouseLeftPressed(event) || EventUtils::wasMouseReleased(event)) {
        m_textManager->handleAboutLinks(event);
    }
}


/**
 * Handles events for the page indicators
 *
 * @param event sfml event object
 *
 * @author Arthur
 * @date 14/01/19
 */
void SettingsView::handlePageIndicatorsEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event) && !m_confirmDialog->isVisible()) {
        for (auto& it : m_pageIndicators) {
            if (EventUtils::isMouseInside(*it.second, event)) {
                it.second->setPressed(true);
                break;
            }
        }
    }

    if (EventUtils::wasMouseReleased(event)) {
        for (auto& it : m_pageIndicators) {
            it.second->setPressed(false);
        }

        if (!m_confirmDialog->isVisible()) {
            for (auto& it : m_pageIndicators) {
                if (EventUtils::isMouseInside(*it.second, event)) {
                    m_settings->setCurrentPage(it.first);
                    break;
                }
            }
        }
    }
}


/**
 * Processes confirm action on clear app data
 *
 * @author Arthur
 * @date 14/10/18 - 02/05/2020
 */
void SettingsView::processClearAppDataConfirmAction()
{
    m_confirmDialog->hide();
    m_settings->clearAppData();
    PersistenceManager::resetPersistence();
    m_textManager->syncMenuSettingsText(m_settings->getCurrentPage());
    m_settings->checkItemsAvailability();
}


/**
 * Get dialog X position from the dialog width
 *
 * @param width the dialog width
 * @return the X position
 *
 * @author Arthur
 * @date 06/09/18 - 16/09/18
 */
float SettingsView::getDialogXPosition(int width) const
{
    return getHalfXPosition() - 0.5f * width;
}


/**
 * Get dialog Y position from the dialog height
 *
 * @param height the dialog height
 * @return the Y position
 *
 * @author Arthur
 * @date 06/09/18 - 16/09/18
 */
float SettingsView::getDialogYPosition(int height) const
{
    return getHalfYPosition() - 0.5f * height;
}
