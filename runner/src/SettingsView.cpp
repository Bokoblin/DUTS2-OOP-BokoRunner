#include "../header/SettingsView.h"

using namespace std;


/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 20/05
*********************************************/
SettingsView::SettingsView(float w, float h, sf::RenderWindow *window, Text * t):
    View(w, h, window, t), m_settings{nullptr}, m_currentIndicator{0},
    m_nbIndicators{2}
{
	    loadImages();

        //=== Create Pages Indicator

        for (int i=0; i < m_nbIndicators; i++)
        {
            m_pageIndicators[i] = new Button(*m_pageIndicatorButton);
            m_pageIndicators[i]->setPosition( m_width/2 - 12*m_nbIndicators + 24*i, 550 );
            m_pageIndicators[i]->resize(22, 22);
        }
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 20/05
*********************************************/
SettingsView::~SettingsView()
{
    //=== Graphic Elements

    delete m_homeFormButton;
    delete m_englishLangRadio;
    delete m_frenchLangRadio;
    delete m_spanishLangRadio;
    delete m_normalModeRadio;
    delete m_masterModeRadio;
    delete m_defaultBallSkinRadio;
    delete m_morphBallSkinRadio;
    delete m_capsuleBallSkinRadio;
    delete m_logoIUTSprite;

    //=== Page Indicators

    delete m_pageIndicatorButton;

    for ( auto it : m_pageIndicators)
        delete it.second;
}


/********************************************
   Setters
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void SettingsView::setSettingsModel(Settings *model)
{
    m_settings = model;
}


/********************************************
    Image Loading
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void SettingsView::loadImages()
{
    //=== Initialize settings radio buttons

    if (!m_radioButtonsTexture.loadFromFile(RADIO_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << RADIO_BUTTONS_IMAGE << endl;
    else
    {
        m_radioButtonsTexture.setSmooth(true);

        vector<sf::IntRect> clip_rects;
        clip_rects.push_back(sf::IntRect( 0, 0, 50, 50) );
        clip_rects.push_back(sf::IntRect( 50, 0, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 50, 50, 50) );
        clip_rects.push_back(sf::IntRect( 50, 50, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 100, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 150, 50, 50) );

        m_englishLangRadio = new Button(clip_rects, m_radioButtonsTexture, 50, 205, 50, 50, true);
        m_frenchLangRadio = new Button(clip_rects, m_radioButtonsTexture, 50, 245, 50, 50, true);
        m_spanishLangRadio = new Button(clip_rects, m_radioButtonsTexture, 50, 285, 50, 50, true);
        m_normalModeRadio = new Button(clip_rects, m_radioButtonsTexture, 50, 420, 50, 50, true);
        m_masterModeRadio = new Button(clip_rects, m_radioButtonsTexture, 50, 460, 50, 50, true);
        m_defaultBallSkinRadio = new Button(clip_rects, m_radioButtonsTexture, m_width/2+50, 205, 50, 50, true);
        m_morphBallSkinRadio = new Button(clip_rects, m_radioButtonsTexture, m_width/2+50, 245, 50, 50, true);
        m_capsuleBallSkinRadio = new Button(clip_rects, m_radioButtonsTexture, m_width/2+50, 285, 50, 50, true);
    }

    //=== Initialize HOME form button

    if (!m_menuButtonTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
    else
    {
        m_menuButtonTexture.setSmooth(true);

        std::vector<sf::IntRect> clip_rects;
        clip_rects.push_back(sf::IntRect( 0, 50, 50, 50));
        clip_rects.push_back(sf::IntRect( 51, 50, 50, 50));
        m_homeFormButton = new Button(clip_rects, m_menuButtonTexture, 10, 10, 50, 50, false);
     }

    //=== Initialize INDICATORS buttons

    if (!m_pageIndicatorTexture.loadFromFile(INDICATOR_IMAGE) )
        cerr << "ERROR when loading image file: " << INDICATOR_IMAGE << endl;
    else
    {
        m_pageIndicatorTexture.setSmooth(true);

        vector<sf::IntRect> clip_rects;
        clip_rects.push_back(sf::IntRect( 0, 0, 50, 50) );
        clip_rects.push_back(sf::IntRect( 50, 0, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 50, 50, 50) );
        clip_rects.push_back(sf::IntRect( 50, 50, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 0, 50, 50) );
        clip_rects.push_back(sf::IntRect( 0, 50, 50, 50) );

        m_pageIndicatorButton = new Button(clip_rects, m_pageIndicatorTexture, 0, 580, 15, 15, true);
    }

    //=== Initialize IUT Logo sprite

    if (!m_logoIUTTexture.loadFromFile(IUT_LOGO_IMAGE) )
        cerr << "ERROR when loading image file: " << IUT_LOGO_IMAGE << endl;
    else
    {
        m_logoIUTTexture.setSmooth(true);
        m_logoIUTSprite = new GraphicElement( m_logoIUTTexture, 700, 350, 250, 210);
        m_logoIUTSprite->resize(150, 110);
    }
}


/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 20/05 - 21/05
*********************************************/
void SettingsView::synchronize()
{
    //=== Update Status of Radio buttons

    m_englishLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "en");
    m_frenchLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "fr");
    m_spanishLangRadio->setActivatedState(m_settings->getDataBase()->getLanguage() == "es");
    m_normalModeRadio->setActivatedState(m_model->getDifficulty() == NORMAL_DIFFICULTY);
    m_masterModeRadio->setActivatedState(m_model->getDifficulty() != NORMAL_DIFFICULTY);
    m_defaultBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "default");
    m_morphBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "morphing");
    m_capsuleBallSkinRadio->setActivatedState(m_settings->getDataBase()->getBallSkin() == "capsule");

    m_morphBallSkinRadio->setDisabledState(!m_settings->getMorphSkinAvailability());
    m_capsuleBallSkinRadio->setDisabledState(!m_settings->getCapsuleSkinAvailability());
    m_defaultBallSkinRadio->setDisabledState( m_settings->getMorphSkinAvailability() == false
                    && m_settings->getCapsuleSkinAvailability() == false  );

    //=== Sync Radio buttons

    m_homeFormButton->sync();
    m_englishLangRadio->sync();
    m_frenchLangRadio->sync();
    m_spanishLangRadio->sync();
    m_normalModeRadio->sync();
    m_masterModeRadio->sync();
    m_defaultBallSkinRadio->sync();
    m_morphBallSkinRadio->sync();
    m_capsuleBallSkinRadio->sync();

    //=== Update and sync indicators

    for( auto it : m_pageIndicators)
    {
         (it.second)->sync();
         it.first == m_currentIndicator ?
         it.second->setActivatedState(true) : it.second->setActivatedState(false);
    }

    //=== Resize Radio buttons

    m_homeFormButton->resize(30, 30);
    m_englishLangRadio->resize(26, 26);
    m_frenchLangRadio->resize(26, 26);
    m_spanishLangRadio->resize(26, 26);
    m_normalModeRadio->resize(26, 26);
    m_masterModeRadio->resize(26, 26);
    m_defaultBallSkinRadio->resize(26, 26);
    m_morphBallSkinRadio->resize(26, 26);
    m_capsuleBallSkinRadio->resize(26, 26);

    //=== Text update

    m_text->syncSettingsText(m_width, m_height);
}


/********************************************
    Menu View Drawing
*********************************************
    @author Arthur  @date 20/05
*********************************************/
void SettingsView::draw() const
{
    m_window->clear(GREY_BG_COLOR);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);

    if ( m_currentIndicator == 0)
    {
        m_window->draw(*m_englishLangRadio);
        m_window->draw(*m_frenchLangRadio);
        m_window->draw(*m_spanishLangRadio);
        m_window->draw(*m_normalModeRadio);
        m_window->draw(*m_masterModeRadio);
        m_window->draw(*m_defaultBallSkinRadio);
        m_window->draw(*m_morphBallSkinRadio);
        m_window->draw(*m_capsuleBallSkinRadio);
    }
    else
    {
        m_window->draw(*m_logoIUTSprite);
    }

    //=== Text Drawing

    m_text->drawMenuSettingsText(m_window, m_currentIndicator);

    for( auto it : m_pageIndicators)
        m_window->draw(*it.second);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 20/05
*********************************************/
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

        else if ( m_normalModeRadio->IS_POINTED )
            m_normalModeRadio->setPressedState(true);

        else if ( m_masterModeRadio->IS_POINTED )
            m_masterModeRadio->setPressedState(true);

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
        m_normalModeRadio->setPressedState(false);
        m_masterModeRadio->setPressedState(false);
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
            m_text->updateWholeText();
        }
        else if ( m_frenchLangRadio->IS_POINTED )
        {
            m_settings->changeLanguage("fr");
            m_text->updateWholeText();
        }
        else if ( m_spanishLangRadio->IS_POINTED )
        {
            m_settings->changeLanguage("es");
            m_text->updateWholeText();
        }
        else if ( m_normalModeRadio->IS_POINTED )
        {
            m_model->setDifficulty(NORMAL_DIFFICULTY);
        }
        else if ( m_masterModeRadio->IS_POINTED )
        {
            m_model->setDifficulty(MASTER_DIFFICULTY);
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
