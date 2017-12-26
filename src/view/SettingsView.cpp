#include "SettingsView.h"
#include "../utils/DialogBuilder.h"

using namespace std;


/**
 * Constructs a Settings view with
 * the window, a text handler and Settings model
 * @author Arthur
 * @date 20/05/16 - 30/01/17
 *
 * @param window the current window which displays a settings view
 * @param textHandler the text handler to display standalone texts
 * @param settingsModel the settings model
 */
SettingsView::SettingsView(sf::RenderWindow *window, TextHandler *textHandler, Settings *settingsModel) :
        AbstractView(window, textHandler),
    m_settings{settingsModel}, m_confirmDialog{nullptr}
{
    loadImages();

    //=== Create Pages Indicator

    for (int i=0; i < Settings::PAGE_NUMBER; i++)
    {
        m_pageIndicators[i] = new RadioButton(0, 580, 15, 15, "indicator");
        m_pageIndicators[i]->setPosition(m_width/2 - 12*Settings::PAGE_NUMBER + 24*i, 550);
        m_pageIndicators[i]->resize(INDICATOR_BUTTONS_SIZE);
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
    m_buttonList.push_back(m_resetRectButton);
    m_buttonList.push_back(m_menuMusicButton);
    m_buttonList.push_back(m_gameMusicButton);

    m_confirmDialog = new Dialog(m_width/2-140, m_height/2-120, 280, 200, *textHandler, "confirm");
    m_confirmDialog->hide();

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

    delete m_logoIUTGraphic;
    delete m_logoSFMLGraphic;
    delete m_confirmDialog;
}


/**
 * Image Loading
 * @author Arthur
 * @date 20/05/16 - 23/12/16
 */
void SettingsView::loadImages()
{
    //=== Initialize RADIOS buttons

    m_englishLangRadio = new RadioButton(RADIOS_MARGIN, 205, 50, 50, "config_lang_english");
    m_frenchLangRadio = new RadioButton(RADIOS_MARGIN, 245, 50, 50, "config_lang_french");
    m_spanishLangRadio = new RadioButton(RADIOS_MARGIN, 285, 50, 50, "config_lang_spanish");
    m_easyModeRadio = new RadioButton(RADIOS_MARGIN, 420, 50, 50, "config_easy_mode");
    m_hardModeRadio = new RadioButton(RADIOS_MARGIN, 460, 50, 50, "config_hard_mode");
    m_defaultBallSkinRadio = new RadioButton(m_width/2+RADIOS_MARGIN, 205, 50, 50, "config_ball_default_skin");
    m_morphBallSkinRadio = new RadioButton(m_width/2+RADIOS_MARGIN, 245, 50, 50, "config_ball_morph_skin");
    m_capsuleBallSkinRadio = new RadioButton(m_width/2+RADIOS_MARGIN, 285, 50, 50, "config_ball_capsule_skin");


    //=== Initialize Music controls

    std::vector<sf::IntRect> clipRect_music;
    clipRect_music.emplace_back(0, 200, 50, 50);
    clipRect_music.emplace_back(50, 200, 50, 50);

    m_menuMusicButton = new Button(m_width/2+RADIOS_MARGIN, 420, 25, 25, "config_music_menu",
                                   GAME_BUTTONS_IMAGE, clipRect_music);
    m_menuMusicButton->resize(25, 25);
    m_menuMusicButton->setLabelPosition(RIGHT);

    m_gameMusicButton = new Button(m_width/2+RADIOS_MARGIN, 460, 25, 25, "config_music_game",
                                   GAME_BUTTONS_IMAGE, clipRect_music);
    m_gameMusicButton->resize(25, 25);
    m_gameMusicButton->setLabelPosition(RIGHT);


    //=== Initialize HOME form button

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.emplace_back(0, 50, 50, 50);
    clipRectHome.emplace_back(51, 50, 50, 50);
    m_homeFormButton = new Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);


    //=== Initialize RESET button

    vector<sf::IntRect> clipRectReset;
    clipRectReset.emplace_back(0, 100, 150, 40);
    clipRectReset.emplace_back(151, 100, 150, 40);
    m_resetRectButton = new Button(m_width/2-75, 450, 150, 40, "stats_app_reset", RECT_BUTTONS_IMAGE, clipRectReset);
    m_resetRectButton->resize(170, 45);


    //=== Initialize Logo sprites

    m_logoIUTGraphic = new GraphicElement(700, 160, 245, 210);
    m_logoIUTGraphic->setTextureFromImage(IUT_LOGO_IMAGE);
    m_logoIUTGraphic->resize(150, 130);

    m_logoSFMLGraphic = new GraphicElement(700, 350, 373, 113);
    m_logoSFMLGraphic->setTextureFromImage(SFML_LOGO_IMAGE);
    m_logoSFMLGraphic->resize(150, 45);

    //=== Initialize link icon

    m_link1Graphic = new GraphicElement(75, 276, 24, 24);
    m_link1Graphic->setTextureFromImage(IMAGE_FOLDER + "ui/ic_link.png");
    m_link2Graphic = new GraphicElement(75, 368, 24, 24);
    m_link2Graphic->setTextureFromImage(IMAGE_FOLDER + "ui/ic_link.png");
}


/**
 * Synchronization function
 * @author Arthur
 * @date 20/05/16 - 23/12/16
 */
void SettingsView::synchronize()
{
    //=== Update Status of Radio buttons

    m_englishLangRadio->setSelected(m_settings->getDataBase()->getLanguage() == ENGLISH);
    m_frenchLangRadio->setSelected(m_settings->getDataBase()->getLanguage() == FRENCH);
    m_spanishLangRadio->setSelected(m_settings->getDataBase()->getLanguage() == SPANISH);
    m_easyModeRadio->setSelected(m_settings->getDataBase()->getDifficulty() == EASY);
    m_hardModeRadio->setSelected(m_settings->getDataBase()->getDifficulty() == HARD);
    m_defaultBallSkinRadio->setSelected(m_settings->getDataBase()->getBallSkin() == "default");
    m_morphBallSkinRadio->setSelected(m_settings->getDataBase()->getBallSkin() == "morphing");
    m_capsuleBallSkinRadio->setSelected(m_settings->getDataBase()->getBallSkin() == "capsule");

    m_morphBallSkinRadio->setEnabled(m_settings->isMorphSkinAvailable());
    m_capsuleBallSkinRadio->setEnabled(m_settings->isCapsuleSkinAvailable());
    m_defaultBallSkinRadio->setEnabled(m_settings->isMorphSkinAvailable()
                                       || m_settings->isCapsuleSkinAvailable());


    //=== Sync buttons

    for (Button *button : m_buttonList)
        button->sync(m_settings->getDataBase());


    DialogBuilder::retrieveCorrespondingStrings(m_confirmDialog, *m_settings->getDataBase());


    //=== Update and sync indicators

    for(auto &it : m_pageIndicators)
    {
        (it.second)->sync();
        it.second->setSelected(it.first == m_settings->getCurrentPage());
    }

    //=== Resize Radio buttons

    m_homeFormButton->resize(FORM_BUTTONS_SIZE);
    m_englishLangRadio->resize(RADIO_BUTTONS_SIZE);
    m_frenchLangRadio->resize(RADIO_BUTTONS_SIZE);
    m_spanishLangRadio->resize(RADIO_BUTTONS_SIZE);
    m_easyModeRadio->resize(RADIO_BUTTONS_SIZE);
    m_hardModeRadio->resize(RADIO_BUTTONS_SIZE);
    m_defaultBallSkinRadio->resize(RADIO_BUTTONS_SIZE);
    m_morphBallSkinRadio->resize(RADIO_BUTTONS_SIZE);
    m_capsuleBallSkinRadio->resize(RADIO_BUTTONS_SIZE);

    //=== TextHandler update

    m_textHandler->syncSettingsText(m_settings->getCurrentPage());
}


/**
 * Settings View Drawing
 * @author Arthur
 * @date 20/05/16 - 25/01/17
 */
void SettingsView::draw() const
{
    m_window->clear(MINE_GREY_COLOR);

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

        m_textHandler->drawMenuSettingsText(m_window, CONFIG);
    }
    else if (m_settings->getCurrentPage() == STATS)
    {
        m_textHandler->drawMenuSettingsText(m_window, STATS);
        m_resetRectButton->draw(m_window);
        m_confirmDialog->draw(m_window);
    }
    else //ABOUT
    {
        m_window->draw(*m_logoIUTGraphic);
        m_window->draw(*m_logoSFMLGraphic);
        m_window->draw(*m_link1Graphic);
        m_window->draw(*m_link2Graphic);
        m_textHandler->drawMenuSettingsText(m_window, ABOUT);
    }

    for(const auto &it : m_pageIndicators)
        it.second->draw(m_window);

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 20/05/16 - 26/12/17
 */
bool SettingsView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_settings->getCurrentPage() == ABOUT)
        {
            m_textHandler->handleAboutLinks(event, *m_settings);
        }

        if (!m_confirmDialog->isVisible())
        {
            for (Button *button : m_buttonList)
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

        for (Button *button : m_buttonList)
            button->setPressed(false);
        for(auto &it : m_pageIndicators)
            it.second->setPressed(false);


        //=== handle mouse up on a button

        if (m_settings->getCurrentPage() == CONFIG)
        {
            if (m_englishLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(ENGLISH);
                m_textHandler->updateWholeText();
            }
            else if (m_frenchLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(FRENCH);
                m_textHandler->updateWholeText();
            }
            else if (m_spanishLangRadio->contains(MOUSE_POSITION))
            {
                m_settings->changeLanguage(SPANISH);
                m_textHandler->updateWholeText();
            }
            else if (m_easyModeRadio->contains(MOUSE_POSITION))
            {
                m_settings->getDataBase()->setDifficulty(EASY);
            }
            else if (m_hardModeRadio->contains(MOUSE_POSITION))
            {
                m_settings->getDataBase()->setDifficulty(HARD);
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
                m_settings->getDataBase()->setMenuMusic(!m_settings->getDataBase()->isMenuMusicEnabled());
                handleMusic();
            }
            else if (m_gameMusicButton->contains(MOUSE_POSITION))
            {
                m_settings->getDataBase()->setGameMusic(!m_settings->getDataBase()->isGameMusicEnabled());
                handleMusic();
            }
        }
        else if (m_settings->getCurrentPage() == STATS)
        {
            if (!m_confirmDialog->isVisible())
            {
                if (m_resetRectButton->contains(MOUSE_POSITION))
                {
                    m_confirmDialog->show();
                }
            }
            else
            {
                if (m_confirmDialog->getOkButtonText().contains(MOUSE_POSITION))
                {
                    m_confirmDialog->hide();
                    m_settings->getDataBase()->clearAppData();
                    m_textHandler->syncSettingsText(m_settings->getCurrentPage());
                    m_settings->checkItemsAvailability();
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
            m_textHandler->handleAboutLinks(event, *m_settings);
        }

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
    }
    return true;
}

/**
 * Handles music settings
 * @author Arthur
 * @date 25/01/17
 */
void SettingsView::handleMusic()
{
    //=== Change menu music volume

    if (m_settings->getDataBase()->isMenuMusicEnabled())
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

    if (m_settings->getDataBase()->isGameMusicEnabled())
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

