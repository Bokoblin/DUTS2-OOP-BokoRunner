#include "SettingsView.h"

using std::string;

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
 * @date 20/05/16 - 02/01/18
 */
SettingsView::SettingsView(sf::RenderWindow *window, AppTextManager *textManager, SettingsModel *settingsModel) :
        AbstractView(window, textManager), m_settings{settingsModel}, m_confirmDialog{nullptr}
{
    loadSprites();

    //=== Create Pages Indicator

    for (int i=0; i < SettingsModel::PAGE_NUMBER; i++)
    {
        m_pageIndicators[i] = new mdsf::RadioButton(0, 580, INDICATOR_DIAMETER, "indicator");
        m_pageIndicators[i]->setPosition(m_width/2 - 12*SettingsModel::PAGE_NUMBER + 24*i, 550);
    }

    //=== Fill button list

    m_buttonList.push_back(m_homeFormButton);
    m_buttonList.push_back(m_englishLangRadio);
    m_buttonList.push_back(m_frenchLangRadio);
    m_buttonList.push_back(m_spanishLangRadio);
    m_buttonList.push_back(m_easyModeRadio);
    m_buttonList.push_back(m_hardModeRadio);
    m_buttonList.push_back(m_defaultBallSkinRadio);
    m_buttonList.push_back(m_morphBallSkinRadio);
    m_buttonList.push_back(m_capsuleBallSkinRadio);
    m_buttonList.push_back(m_resetDataRaisedButton);
    m_buttonList.push_back(m_menuMusicButton);
    m_buttonList.push_back(m_gameMusicButton);

    //=== Init buttons

    for (mdsf::Button *button : m_buttonList)
        button->retrieveAndSyncLabel(LocalizationManager::getLanguageFile());

    //=== Init confirm dialog

    m_confirmDialog = new mdsf::Dialog(m_width/2-140, m_height/2-120, 280, 200, "confirm_data_delete");
    m_confirmDialog->hide();
    DialogBuilder::retrieveCorrespondingStrings(m_confirmDialog);

    //=== Init music

    handleMusic();
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16 - 24/12/17
 */
SettingsView::~SettingsView()
{
    for (auto &button : m_buttonList)
        delete button;

    for (auto &it : m_pageIndicators)
        delete it.second;

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
 * @date 20/05/16 - 04/01/18
 */
void SettingsView::loadSprites()
{
    //=== Initialize RADIOS buttons

    const int POS_COL_1 = 50; //Column 1 starting x-axis
    const int POS_COL_2 = POS_COL_1 + (int)(m_width/2); //Column 2 starting x-axis

    m_englishLangRadio = new mdsf::RadioButton(POS_COL_1, 205, RADIO_DIAMETER, "config_lang_english");
    m_frenchLangRadio = new mdsf::RadioButton(POS_COL_1, 245, RADIO_DIAMETER, "config_lang_french");
    m_spanishLangRadio = new mdsf::RadioButton(POS_COL_1, 285, RADIO_DIAMETER, "config_lang_spanish");
    m_easyModeRadio = new mdsf::RadioButton(POS_COL_1, 420, RADIO_DIAMETER, "config_easy_mode");
    m_hardModeRadio = new mdsf::RadioButton(POS_COL_1, 460, RADIO_DIAMETER, "config_hard_mode");
    m_defaultBallSkinRadio = new mdsf::RadioButton(POS_COL_2, 205, RADIO_DIAMETER, "config_ball_default_skin");
    m_morphBallSkinRadio = new mdsf::RadioButton(POS_COL_2, 245, RADIO_DIAMETER, "config_ball_morph_skin");
    m_capsuleBallSkinRadio = new mdsf::RadioButton(POS_COL_2, 285, RADIO_DIAMETER, "config_ball_capsule_skin");


    //=== Initialize Music controls

    std::vector<sf::IntRect> clipRect_music;
    clipRect_music.emplace_back(0, 200, 50, 50);
    clipRect_music.emplace_back(50, 200, 50, 50);

    m_menuMusicButton = new mdsf::Button(POS_COL_2, 420, 25, 25, "config_music_menu",
                                         GAME_BUTTONS_IMAGE, clipRect_music);
    //TODO: fix the resize explicit call (hint: correct size in ctor and resize in self.sync())
    //Resize should only be used by user of the lib when s.he actually want to change the size
    m_menuMusicButton->resize(25, 25);
    m_menuMusicButton->setLabelPosition(mdsf::LabelPosition::RIGHT);

    m_gameMusicButton = new mdsf::Button(POS_COL_2, 460, 25, 25, "config_music_game",
                                         GAME_BUTTONS_IMAGE, clipRect_music);
    m_gameMusicButton->resize(25, 25);
    m_gameMusicButton->setLabelPosition(mdsf::LabelPosition::RIGHT);


    //=== Initialize HOME form button

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.emplace_back(0, 50, 50, 50);
    clipRectHome.emplace_back(51, 50, 50, 50);
    m_homeFormButton = new mdsf::Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);


    //=== Initialize RESET button

    std::vector<sf::IntRect> clipRectReset;
    clipRectReset.emplace_back(RAISED_BUTTON_DEFAULT);
    clipRectReset.emplace_back(RAISED_BUTTON_PRESSED);
    m_resetDataRaisedButton = new mdsf::Button(m_width/2 - 75, 450, 150, 36, "stats_app_reset",
                                               RECT_BUTTONS_IMAGE, clipRectReset);
    m_resetDataRaisedButton->setColor(mdsf::Color::MaterialRed);


    //=== Initialize Logo sprites

    m_logoIUT = new mdsf::Sprite(700, 160, 245, 210);
    m_logoIUT->loadAndApplyTextureFromImageFile(IUT_LOGO_IMAGE);
    m_logoIUT->resize(150, 130);

    m_logoSFML = new mdsf::Sprite(700, 350, 373, 113);
    m_logoSFML->loadAndApplyTextureFromImageFile(SFML_LOGO_IMAGE);
    m_logoSFML->resize(150, 45);

    //=== Initialize link icon

    m_iconRepoLink = new mdsf::Sprite(75, 276, 24, 24);
    m_iconRepoLink->loadAndApplyTextureFromImageFile(IMAGE_FOLDER + "ui/ic_link.png");
    m_iconEmailLink = new mdsf::Sprite(75, 368, 24, 24);
    m_iconEmailLink->loadAndApplyTextureFromImageFile(IMAGE_FOLDER + "ui/ic_link.png");
}


/**
 * Synchronizes settings elements
 *
 * @author Arthur
 * @date 20/05/16 - 02/01/18
 */
void SettingsView::synchronize()
{
    //=== Update Status of Radio buttons

    m_englishLangRadio->setSelected(m_settings->getAppCore()->getLanguage() == ENGLISH);
    m_frenchLangRadio->setSelected(m_settings->getAppCore()->getLanguage() == FRENCH);
    m_spanishLangRadio->setSelected(m_settings->getAppCore()->getLanguage() == SPANISH);
    m_easyModeRadio->setSelected(m_settings->getAppCore()->getDifficulty() == EASY);
    m_hardModeRadio->setSelected(m_settings->getAppCore()->getDifficulty() == HARD);
    m_defaultBallSkinRadio->setSelected(m_settings->getAppCore()->getBallSkin() == "default");
    m_morphBallSkinRadio->setSelected(m_settings->getAppCore()->getBallSkin() == "morphing");
    m_capsuleBallSkinRadio->setSelected(m_settings->getAppCore()->getBallSkin() == "capsule");

    m_morphBallSkinRadio->setEnabled(m_settings->isMorphSkinAvailable());
    m_capsuleBallSkinRadio->setEnabled(m_settings->isCapsuleSkinAvailable());
    m_defaultBallSkinRadio->setEnabled(m_settings->isMorphSkinAvailable()
                                               || m_settings->isCapsuleSkinAvailable());


    //=== Sync buttons

    for (mdsf::Button *button : m_buttonList)
        button->sync();


    //=== Update and sync indicators

    for(auto &it : m_pageIndicators)
    {
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
 * @date 20/05/16 - 25/01/17
 */
void SettingsView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);

    if (m_settings->getCurrentPage() == CONFIG)
    {
        m_englishLangRadio->draw(m_window);
        m_frenchLangRadio->draw(m_window);
        m_spanishLangRadio->draw(m_window);
        m_easyModeRadio->draw(m_window);
        m_hardModeRadio->draw(m_window);
        m_defaultBallSkinRadio->draw(m_window);
        m_morphBallSkinRadio->draw(m_window);
        m_capsuleBallSkinRadio->draw(m_window);
        m_menuMusicButton->draw(m_window);
        m_gameMusicButton->draw(m_window);

        m_textManager->drawMenuSettingsText(m_window, CONFIG);
    }
    else if (m_settings->getCurrentPage() == STATS)
    {
        m_textManager->drawMenuSettingsText(m_window, STATS);
        m_resetDataRaisedButton->draw(m_window);
        m_confirmDialog->draw(m_window);
    }
    else //ABOUT
    {
        m_window->draw(*m_logoIUT);
        m_window->draw(*m_logoSFML);
        m_window->draw(*m_iconRepoLink);
        m_window->draw(*m_iconEmailLink);
        m_textManager->drawMenuSettingsText(m_window, ABOUT);
    }

    for(const auto &it : m_pageIndicators)
        it.second->draw(m_window);

    m_window->display();
}


/**
 * Handles music settings
 *
 * @author Arthur
 * @date 25/01/17
 */
void SettingsView::handleMusic()
{
    //=== Change menu music volume

    if (m_settings->getAppCore()->isMenuMusicEnabled())
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 200, 50, 50);
        clipRect.emplace_back(50, 200, 50, 50);
        m_menuMusicButton->setClipRectArray(clipRect);
    }
    else
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 250, 50, 50);
        clipRect.emplace_back(50, 250, 50, 50);
        m_menuMusicButton->setClipRectArray(clipRect);
    }

    //=== Change game music volume

    if (m_settings->getAppCore()->isGameMusicEnabled())
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 200, 50, 50);
        clipRect.emplace_back(50, 200, 50, 50);
        m_gameMusicButton->setClipRectArray(clipRect);
    }
    else
    {
        std::vector<sf::IntRect> clipRect;
        clipRect.emplace_back(0, 250, 50, 50);
        clipRect.emplace_back(50, 250, 50, 50);
        m_gameMusicButton->setClipRectArray(clipRect);
    }
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
    for (mdsf::Button *button : m_buttonList)
        button->retrieveAndSyncLabel(LocalizationManager::getLanguageFile());

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
 * @date 20/05/16 - 04/02/18
 */
bool SettingsView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_settings->getCurrentPage() == ABOUT)
        {
            m_textManager->handleAboutLinks(event, *m_settings);
        }

        if (!m_confirmDialog->isVisible())
        {
            for (mdsf::Button *button : m_buttonList)
            {
                if (button->contains(MOUSE_POSITION))
                {
                    button->setPressed(true);
                    break;
                }
            }

            for (auto &it : m_pageIndicators)
            {
                if (it.second->contains(MOUSE_POSITION))
                {
                    it.second->setPressed(true);
                    break;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        for (mdsf::Button *button : m_buttonList)
            button->setPressed(false);
        for(auto &it : m_pageIndicators)
            it.second->setPressed(false);


        //=== handle mouse up on a button

        if (!m_confirmDialog->isVisible())
        {
            if (m_homeFormButton->contains(MOUSE_POSITION))
            {
                m_settings->quit();
                return false;
            }

            for (auto &it : m_pageIndicators)
                if (it.second->contains(MOUSE_POSITION))
                    m_settings->setCurrentPage(it.first);
        }

        if (m_settings->getCurrentPage() == CONFIG)
        {
            if (m_englishLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(ENGLISH);
                updateTextBasedComponents();
            }
            else if (m_frenchLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(FRENCH);
                updateTextBasedComponents();
            }
            else if (m_spanishLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(SPANISH);
                updateTextBasedComponents();
            }
            else if (m_easyModeRadio->contains(MOUSE_POSITION))
            {
                m_settings->getAppCore()->setDifficulty(EASY);
            }
            else if (m_hardModeRadio->contains(MOUSE_POSITION))
            {
                m_settings->getAppCore()->setDifficulty(HARD);
            }
            else if (m_defaultBallSkinRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeBallSkin("default");
            }
            else if (m_morphBallSkinRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeBallSkin("morphing");
            }
            else if (m_capsuleBallSkinRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeBallSkin("capsule");
            }
            else if (m_menuMusicButton->contains(MOUSE_POSITION))
            {
                m_settings->getAppCore()->toggleMenuMusic();
                handleMusic();
            }
            else if (m_gameMusicButton->contains(MOUSE_POSITION))
            {
                m_settings->getAppCore()->toggleGameMusic();
                handleMusic();
            }
        }
        else if (m_settings->getCurrentPage() == STATS)
        {
            if (!m_confirmDialog->isVisible())
            {
                if (m_resetDataRaisedButton->contains(MOUSE_POSITION))
                {
                    m_confirmDialog->show();
                }
            }
            else
            {
                if (m_confirmDialog->getOkButtonText().contains(MOUSE_POSITION))
                {
                    m_confirmDialog->hide();
                    m_settings->getAppCore()->clearAppData();
                    PersistenceManager::deletePersistence();
                    PersistenceManager::initPersistence();
                    m_textManager->syncMenuSettingsText(m_settings->getCurrentPage());
                    m_settings->checkItemsAvailability();
                    handleMusic();
                }
                else if (m_confirmDialog->getCancelButtonText().contains(MOUSE_POSITION)
                        || !m_confirmDialog->contains(MOUSE_POSITION))
                {
                    m_confirmDialog->hide();
                }
            }
        }
        else
        {
            m_textManager->handleAboutLinks(event, *m_settings);
        }
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        m_confirmDialog->hide();
    }

    return true;
}

