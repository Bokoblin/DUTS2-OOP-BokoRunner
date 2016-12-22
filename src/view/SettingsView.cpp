#include "SettingsView.h"

using namespace std;


/**
 * Parameterized Constructor
 * @author Arthur
 * @date 20/05
 */
SettingsView::SettingsView(float w, float h, sf::RenderWindow *window, TextHandler * t):
    View(w, h, window, t), m_settings{nullptr}, m_currentIndicator{CONFIG}, m_nbIndicators{3}
{
	    loadImages();

        //=== Create Pages Indicator

        for (int i=0; i < m_nbIndicators; i++)
        {
            m_pageIndicators[i] = new Button(*m_pageIndicatorButton);
            m_pageIndicators[i]->setPosition( m_width/2 - 12*m_nbIndicators + 24*i, 550 );
            m_pageIndicators[i]->resize(INDICATOR_BUTTONS_SIZE);
        }
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05 - 22/12
 */
SettingsView::~SettingsView()
{
    //=== Graphic Elements

    delete m_homeFormButton;
    delete m_englishLangRadio;
    delete m_frenchLangRadio;
    delete m_spanishLangRadio;
    delete m_easyModeRadio;
    delete m_hardModeRadio;
    delete m_defaultBallSkinRadio;
    delete m_morphBallSkinRadio;
    delete m_capsuleBallSkinRadio;
    delete m_logoIUTSprite;
    delete m_logoSFMLSprite;

    //=== Page Indicators

    delete m_pageIndicatorButton;

    for ( auto it : m_pageIndicators)
        delete it.second;
}


//=== Setters

void SettingsView::setSettingsModel(Settings *model)
{
    m_settings = model;
}


/**
 * Image Loading
 * @author Arthur
 * @date 20/05 - 22/12
 */
void SettingsView::loadImages()
{
    //=== Initialize settings radio buttons

    if (!m_radioButtonsTexture.loadFromFile(RADIO_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << RADIO_BUTTONS_IMAGE << endl;
    else
    {
        m_radioButtonsTexture.setSmooth(true);

        vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect( 0, 0, 50, 50) );
        clipRect.push_back(sf::IntRect( 50, 0, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 50, 50, 50) );
        clipRect.push_back(sf::IntRect( 50, 50, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 100, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 150, 50, 50) );

        m_englishLangRadio = new Button(clipRect, m_radioButtonsTexture, 50, 205, 50, 50, true);
        m_frenchLangRadio = new Button(clipRect, m_radioButtonsTexture, 50, 245, 50, 50, true);
        m_spanishLangRadio = new Button(clipRect, m_radioButtonsTexture, 50, 285, 50, 50, true);
        m_easyModeRadio = new Button(clipRect, m_radioButtonsTexture, 50, 420, 50, 50, true);
        m_hardModeRadio = new Button(clipRect, m_radioButtonsTexture, 50, 460, 50, 50, true);
        m_defaultBallSkinRadio = new Button(clipRect, m_radioButtonsTexture, m_width/2+50, 205, 50, 50, true);
        m_morphBallSkinRadio = new Button(clipRect, m_radioButtonsTexture, m_width/2+50, 245, 50, 50, true);
        m_capsuleBallSkinRadio = new Button(clipRect, m_radioButtonsTexture, m_width/2+50, 285, 50, 50, true);
    }

    //=== Initialize HOME form button

    if (!m_menuButtonTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
    else
    {
        m_menuButtonTexture.setSmooth(true);

        std::vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect( 0, 50, 50, 50));
        clipRect.push_back(sf::IntRect( 51, 50, 50, 50));
        m_homeFormButton = new Button(clipRect, m_menuButtonTexture, 10, 10, 50, 50, false);
     }

    //=== Initialize INDICATORS buttons

    if (!m_pageIndicatorTexture.loadFromFile(INDICATOR_IMAGE) )
        cerr << "ERROR when loading image file: " << INDICATOR_IMAGE << endl;
    else
    {
        m_pageIndicatorTexture.setSmooth(true);

        vector<sf::IntRect> clipRect;
        clipRect.push_back(sf::IntRect( 0, 0, 50, 50) );
        clipRect.push_back(sf::IntRect( 50, 0, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 50, 50, 50) );
        clipRect.push_back(sf::IntRect( 50, 50, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 0, 50, 50) );
        clipRect.push_back(sf::IntRect( 0, 50, 50, 50) );

        m_pageIndicatorButton = new Button(clipRect, m_pageIndicatorTexture, 0, 580, 15, 15, true);
    }

    //=== Initialize Logo sprites

    if (!m_logoIUTTexture.loadFromFile(IUT_LOGO_IMAGE) )
        cerr << "ERROR when loading image file: " << IUT_LOGO_IMAGE << endl;
    else
    {
        m_logoIUTTexture.setSmooth(true);
        m_logoIUTSprite = new GraphicElement( m_logoIUTTexture, 700, 160, 245, 210);
        m_logoIUTSprite->resize(150, 130);
    }

    if (!m_logoSFMLTexture.loadFromFile(SFML_LOGO_IMAGE) )
        cerr << "ERROR when loading image file: " << IUT_LOGO_IMAGE << endl;
    else
    {
        m_logoSFMLTexture.setSmooth(true);
        m_logoSFMLSprite = new GraphicElement( m_logoSFMLTexture, 700, 350, 373, 113);
        m_logoSFMLSprite->resize(150, 45);
    }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 20/05
 */
void SettingsView::synchronize()
{
    //TODO : Add RESET APP

    //=== Update Status of Radio buttons

    m_englishLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "en");
    m_frenchLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "fr");
    m_spanishLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "es");
    m_easyModeRadio->setActivatedState(m_model->getDataBase()->getDifficulty() == EASY);
    m_hardModeRadio->setActivatedState(m_model->getDataBase()->getDifficulty() == HARD);
    m_defaultBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "default");
    m_morphBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "morphing");
    m_capsuleBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "capsule");

    m_morphBallSkinRadio->setDisabledState(!m_settings->getMorphSkinAvailability());
    m_capsuleBallSkinRadio->setDisabledState(!m_settings->getCapsuleSkinAvailability());
    m_defaultBallSkinRadio->setDisabledState(!m_settings->getMorphSkinAvailability()
                                             && !m_settings->getCapsuleSkinAvailability());

    //=== Sync Radio buttons

    m_homeFormButton->sync();
    m_englishLangRadio->sync();
    m_frenchLangRadio->sync();
    m_spanishLangRadio->sync();
    m_easyModeRadio->sync();
    m_hardModeRadio->sync();
    m_defaultBallSkinRadio->sync();
    m_morphBallSkinRadio->sync();
    m_capsuleBallSkinRadio->sync();

    //=== Update and sync indicators

    for( auto it : m_pageIndicators)
    {
         (it.second)->sync();
         it.second->setActivatedState(it.first == m_currentIndicator);
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

    m_textHandler->syncSettingsText(m_currentIndicator);
}


/**
 * Settings View Drawing
 * @author Arthur
 * @date 20/05 - 22/12
 */
void SettingsView::draw() const
{
    m_window->clear(GREY_BG_COLOR);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);

    if ( m_currentIndicator == CONFIG)
    {
        m_window->draw(*m_englishLangRadio);
        m_window->draw(*m_frenchLangRadio);
        m_window->draw(*m_spanishLangRadio);
        m_window->draw(*m_easyModeRadio);
        m_window->draw(*m_hardModeRadio);
        m_window->draw(*m_defaultBallSkinRadio);
        m_window->draw(*m_morphBallSkinRadio);
        m_window->draw(*m_capsuleBallSkinRadio);

        m_textHandler->drawMenuSettingsText(m_window, CONFIG);
    }
    else if ( m_currentIndicator == STATS)
    {
        m_textHandler->drawMenuSettingsText(m_window, STATS);
    }
    else //ABOUT
    {
        m_window->draw(*m_logoIUTSprite);
        m_window->draw(*m_logoSFMLSprite);
        m_textHandler->drawMenuSettingsText(m_window, ABOUT);
    }

    for( auto it : m_pageIndicators)
        m_window->draw(*it.second);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 20/05
 */
bool SettingsView::treatEvents() { return false; }
bool SettingsView::treatEvents(sf::Event event)
{
    bool stop_settings = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if ( m_homeFormButton->IS_POINTED )
            m_homeFormButton->setPressedState(true);

        else if ( m_englishLangRadio->IS_POINTED )
            m_englishLangRadio->setPressedState(true);

        else if ( m_frenchLangRadio->IS_POINTED )
            m_frenchLangRadio->setPressedState(true);

        else if ( m_spanishLangRadio->IS_POINTED )
            m_spanishLangRadio->setPressedState(true);

        else if ( m_easyModeRadio->IS_POINTED )
            m_easyModeRadio->setPressedState(true);

        else if ( m_hardModeRadio->IS_POINTED )
            m_hardModeRadio->setPressedState(true);

        else if ( m_defaultBallSkinRadio->IS_POINTED
                 && !m_defaultBallSkinRadio->getDisabledState() )
            m_defaultBallSkinRadio->setPressedState(true);

        else if ( m_morphBallSkinRadio->IS_POINTED
                 && !m_morphBallSkinRadio->getDisabledState() )
            m_morphBallSkinRadio->setPressedState(true);

        else if ( m_capsuleBallSkinRadio->IS_POINTED
                 && !m_capsuleBallSkinRadio->getDisabledState() )
            m_capsuleBallSkinRadio->setPressedState(true);

        for( auto it : m_pageIndicators)
            if ( it.second->IS_POINTED )
                it.second->setPressedState(true);

    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressedState(false);
        m_englishLangRadio->setPressedState(false);
        m_frenchLangRadio->setPressedState(false);
        m_spanishLangRadio->setPressedState(false);
        m_easyModeRadio->setPressedState(false);
        m_hardModeRadio->setPressedState(false);
        m_defaultBallSkinRadio->setPressedState(false);
        m_morphBallSkinRadio->setPressedState(false);
        m_capsuleBallSkinRadio->setPressedState(false);
        for( auto it : m_pageIndicators)
            it.second->setPressedState(false);


        //=== handle mouse up on a button

        if ( m_homeFormButton->IS_POINTED )
            stop_settings = true;
        else if ( m_englishLangRadio->IS_POINTED )
        {
            m_settings->changeLanguage("en");
            m_textHandler->updateWholeText();
        }
        else if ( m_frenchLangRadio->IS_POINTED )
        {
            m_settings->changeLanguage("fr");
            m_textHandler->updateWholeText();
        }
        else if ( m_spanishLangRadio->IS_POINTED )
        {
            m_settings->changeLanguage("es");
            m_textHandler->updateWholeText();
        }
        else if ( m_easyModeRadio->IS_POINTED )
        {
            m_model->getDataBase()->setDifficulty(EASY);
        }
        else if ( m_hardModeRadio->IS_POINTED )
        {
            m_model->getDataBase()->setDifficulty(HARD);
        }
        else if ( m_defaultBallSkinRadio->IS_POINTED
                 && !m_defaultBallSkinRadio->getDisabledState() )
        {
            m_settings->changeBallSkin("default");
        }
        else if ( m_morphBallSkinRadio->IS_POINTED
                 && !m_morphBallSkinRadio->getDisabledState() )
        {
            m_settings->changeBallSkin("morphing");
        }
        else if ( m_capsuleBallSkinRadio->IS_POINTED
                 && !m_capsuleBallSkinRadio->getDisabledState() )
        {
            m_settings->changeBallSkin("capsule");
        }

        for( auto it : m_pageIndicators)
            if ( it.second->IS_POINTED )
                m_currentIndicator = it.first;
    }
    return stop_settings;
}
