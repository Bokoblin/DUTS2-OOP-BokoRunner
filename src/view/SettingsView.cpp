#include "SettingsView.h"

using namespace std;


/**
 * Parameterized Constructor
 * @author Arthur
 * @date 20/05/16 - 25/01/17
 */
SettingsView::SettingsView(float w, float h, sf::RenderWindow *window, TextHandler * t):
        View(w, h, window, t), m_settings{nullptr}, m_confirmDialog{nullptr}
{
    loadImages();

    //=== Create Pages Indicator

    for (int i=0; i < Settings::PAGE_NUMBER; i++)
    {
        m_pageIndicators[i] = new RadioButton(0, 580, 15, 15, "indicator");
        m_pageIndicators[i]->setPosition( m_width/2 - 12*Settings::PAGE_NUMBER + 24*i, 550 );
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

    m_confirmDialog = new Dialog(m_width/2-140, m_height/2-120, 280, 200, t, "confirm");
    m_confirmDialog->hide();
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16 - 24/01/17
 */
SettingsView::~SettingsView()
{
    for ( auto button : m_buttonList)
        delete button;

    for ( auto it : m_pageIndicators)
        delete it.second;

    delete m_logoIUTSprite;
    delete m_logoSFMLSprite;
    delete m_confirmDialog;
}


//=== Setters

void SettingsView::setSettingsModel(Settings *model)
{
    m_settings = model;
    handleMusic();
}


/**
 * Image Loading
 * @author Arthur
 * @date 20/05/16 - 23/12/16
 */
void SettingsView::loadImages()
{
    //=== Initialize RADIOS buttons

    m_englishLangRadio = new RadioButton(RADIO_BUTTONS_MARGIN, 205, 50, 50, "config_lang_english");
    m_frenchLangRadio = new RadioButton(RADIO_BUTTONS_MARGIN, 245, 50, 50, "config_lang_french");
    m_spanishLangRadio = new RadioButton(RADIO_BUTTONS_MARGIN, 285, 50, 50, "config_lang_spanish");
    m_easyModeRadio = new RadioButton(RADIO_BUTTONS_MARGIN, 420, 50, 50, "config_easy_mode");
    m_hardModeRadio = new RadioButton(RADIO_BUTTONS_MARGIN, 460, 50, 50, "config_hard_mode");
    m_defaultBallSkinRadio = new RadioButton(m_width/2+RADIO_BUTTONS_MARGIN, 205, 50, 50, "config_ball_default_skin");
    m_morphBallSkinRadio = new RadioButton(m_width/2+RADIO_BUTTONS_MARGIN, 245, 50, 50, "config_ball_morph_skin");
    m_capsuleBallSkinRadio = new RadioButton(m_width/2+RADIO_BUTTONS_MARGIN, 285, 50, 50, "config_ball_capsule_skin");


    //=== Initialize Music controls

    std::vector<sf::IntRect> clipRect_music;
    clipRect_music.emplace_back(0, 200, 50, 50);
    clipRect_music.emplace_back(50, 200, 50, 50);

    m_menuMusicButton = new Button(m_width/2+RADIO_BUTTONS_MARGIN, 420, 25, 25, "config_music_menu",
                                   GAME_BUTTONS_IMAGE, clipRect_music);
    m_menuMusicButton->resize(25, 25);
    m_menuMusicButton->setLabelPosition(RIGHT);

    m_gameMusicButton = new Button(m_width/2+RADIO_BUTTONS_MARGIN, 460, 25, 25, "config_music_game",
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

    m_logoIUTSprite = new GraphicElement(700, 160, 245, 210);
    m_logoIUTSprite->setTextureFromImage(IUT_LOGO_IMAGE);
    m_logoIUTSprite->resize(150, 130);

    m_logoSFMLSprite = new GraphicElement(700, 350, 373, 113);
    m_logoSFMLSprite->setTextureFromImage(SFML_LOGO_IMAGE);
    m_logoSFMLSprite->resize(150, 45);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 20/05/16 - 23/12/16
 */
void SettingsView::synchronize()
{
    //=== Update Status of Radio buttons

    m_englishLangRadio->setActivated(m_settings->getDataBase()->getLanguage() == "en");
    m_frenchLangRadio->setActivated(m_settings->getDataBase()->getLanguage() == "fr");
    m_spanishLangRadio->setActivated(m_settings->getDataBase()->getLanguage() == "es");
    m_easyModeRadio->setActivated(m_model->getDataBase()->getDifficulty() == EASY);
    m_hardModeRadio->setActivated(m_model->getDataBase()->getDifficulty() == HARD);
    m_defaultBallSkinRadio->setActivated(m_settings->getDataBase()->getBallSkin() == "default");
    m_morphBallSkinRadio->setActivated(m_settings->getDataBase()->getBallSkin() == "morphing");
    m_capsuleBallSkinRadio->setActivated(m_settings->getDataBase()->getBallSkin() == "capsule");

    m_morphBallSkinRadio->setDisabled(!m_settings->getMorphSkinAvailability());
    m_capsuleBallSkinRadio->setDisabled(!m_settings->getCapsuleSkinAvailability());
    m_defaultBallSkinRadio->setDisabled(!m_settings->getMorphSkinAvailability()
                                        && !m_settings->getCapsuleSkinAvailability());


    //=== Sync buttons

    for ( Button *button : m_buttonList)
        button->sync(m_settings->getDataBase());


    m_confirmDialog->sync(m_settings->getDataBase());


    //=== Update and sync indicators

    for( auto it : m_pageIndicators)
    {
        (it.second)->sync();
        it.second->setActivated(it.first == m_settings->getCurrentPage());
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

    if ( m_settings->getCurrentPage() == Settings::CONFIG)
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

        m_textHandler->drawMenuSettingsText(m_window, Settings::CONFIG);
    }
    else if ( m_settings->getCurrentPage() == Settings::STATS)
    {
        m_textHandler->drawMenuSettingsText(m_window, Settings::STATS);
        m_resetRectButton->draw(m_window);
        m_confirmDialog->draw(m_window);
    }
    else //ABOUT
    {
        m_window->draw(*m_logoIUTSprite);
        m_window->draw(*m_logoSFMLSprite);
        m_textHandler->drawMenuSettingsText(m_window, Settings::ABOUT);
    }

    for( auto it : m_pageIndicators)
        it.second->draw(m_window);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 20/05/16 - 24/01/17
 */
bool SettingsView::treatEvents() { return false; }
bool SettingsView::treatEvents(sf::Event event)
{
    bool stop_settings = false;

    if (!m_confirmDialog->isShowing() )
    {
        if (MOUSE_LEFT_PRESSED_EVENT) {
            for (Button *button : m_buttonList) {
                if (button->contains(MOUSE_POSITION)) {
                    button->setPressed(true);
                    break;
                }
            }

            for (auto it : m_pageIndicators) {
                if (it.second->contains(MOUSE_POSITION)) {
                    it.second->setPressed(true);
                    break;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        for ( Button *button : m_buttonList)
            button->setPressed(false);
        for( auto it : m_pageIndicators)
            it.second->setPressed(false);


        //=== handle mouse up on a button

        if ( m_settings->getCurrentPage() == Settings::CONFIG)
        {
            if (m_englishLangRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeLanguage("en");
                m_textHandler->updateWholeText();
            }
            else if (m_frenchLangRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeLanguage("fr");
                m_textHandler->updateWholeText();
            }
            else if (m_spanishLangRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeLanguage("es");
                m_textHandler->updateWholeText();
            }
            else if (m_easyModeRadio->contains(MOUSE_POSITION) )
            {
                m_model->getDataBase()->setDifficulty(EASY);
            }
            else if (m_hardModeRadio->contains(MOUSE_POSITION) )
            {
                m_model->getDataBase()->setDifficulty(HARD);
            }
            else if (m_defaultBallSkinRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeBallSkin("default");
            }
            else if (m_morphBallSkinRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeBallSkin("morphing");
            }
            else if (m_capsuleBallSkinRadio->contains(MOUSE_POSITION) )
            {
                m_settings->changeBallSkin("capsule");
            }
            else if (m_menuMusicButton->contains(MOUSE_POSITION) )
            {
                m_settings->getDataBase()->setMenuMusic(!m_settings->getDataBase()->isMenuMusicEnabled());
                handleMusic();
            }
            else if (m_gameMusicButton->contains(MOUSE_POSITION) )
            {
                m_settings->getDataBase()->setGameMusic(!m_settings->getDataBase()->isGameMusicEnabled());
                handleMusic();
            }
        }
        else
        {
            if (!m_confirmDialog->isShowing() )
            {
                if (m_resetRectButton->contains(MOUSE_POSITION) )
                {
                    m_confirmDialog->show();
                }
            }
            else
            {
                if ( m_confirmDialog->getOkButtonText().contains(MOUSE_POSITION) )
                {
                    m_confirmDialog->hide();
                    m_settings->getDataBase()->clearAppData();
                    m_textHandler->syncSettingsText(m_settings->getCurrentPage());
                    m_settings->checkItemsAvailability();
                }
                else if ( m_confirmDialog->getCancelButtonText().contains(MOUSE_POSITION)
                     || !m_confirmDialog->contains(MOUSE_POSITION))
                {
                    m_confirmDialog->hide();
                }
            }
        }

        if (!m_confirmDialog->isShowing() )
        {
            if (m_homeFormButton->contains(MOUSE_POSITION) )
                stop_settings = true;

            for (auto it : m_pageIndicators)
                if (it.second->contains(MOUSE_POSITION))
                    m_settings->setCurrentPage(it.first);
        }
    }
    return stop_settings;
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
