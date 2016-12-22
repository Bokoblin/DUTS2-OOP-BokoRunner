#include "ShopView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 16/05
 */
ShopView::ShopView(float w, float h, sf::RenderWindow *window, TextHandler * text):
	View(w, h, window,text), m_shop{nullptr}, m_currentIndicator{0},
    m_totalIndicator{0}, m_buyDialog{nullptr}
{
	    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05
 */
ShopView::~ShopView()
{
    delete m_coinSprite;
    delete m_homeFormButton;
    delete m_pageIndicatorButton;
    delete m_buyDialog;

    for ( auto c : m_shopItemsCardArray)
        delete c;

    for ( auto it : m_pageIndicators)
        delete it.second;
}


//=== Setters

void ShopView::setShopModel(Shop *model)
{
	m_shop = model;
	createCards();
}


/**
 * Image Loading
 * @author Arthur
 * @date 16/05
 */
void ShopView::loadImages()
{
    //=== Initialize COIN Sprite

    if (!m_coinTexture.loadFromFile(BONUS_IMAGE, sf::IntRect(0,0,50,50)))
        cerr << "ERROR when loading image file: " << BONUS_IMAGE << endl;
    else
    {
        m_coinTexture.setSmooth(true);
        m_coinSprite = new GraphicElement(m_coinTexture, m_width/2-60, 53, 25, 25);
        m_coinSprite->resize(25, 25);
    }

    //=== Initialize HOME form buttons

    if (!m_menuFormButtonsTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
        cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
    else
    {
        m_menuFormButtonsTexture.setSmooth(true);

        std::vector<sf::IntRect> clipRectHome;
        clipRectHome.push_back(sf::IntRect( 0, 50, 50, 50));
        clipRectHome.push_back(sf::IntRect( 51, 50, 50, 50));
        m_homeFormButton = new Button(clipRectHome, m_menuFormButtonsTexture, 10, 10, 50, 50, false);

        //=== Initialize INDICATORS Buttons

        if (!m_pageIndicatorTexture.loadFromFile(INDICATOR_IMAGE) )
            cerr << "ERROR when loading image file: " << INDICATOR_IMAGE << endl;
        else
        {
            m_pageIndicatorTexture.setSmooth(true);

            vector<sf::IntRect> clipRect;
            clipRect.push_back(sf::IntRect(  0,   0, 50, 50) );
            clipRect.push_back(sf::IntRect(50,   0, 50, 50) );
            clipRect.push_back(sf::IntRect(  0, 50, 50, 50) );
            clipRect.push_back(sf::IntRect(50, 50, 50, 50) );
            clipRect.push_back(sf::IntRect( 0, 0, 50, 50) );
            clipRect.push_back(sf::IntRect( 0, 50, 50, 50) );

            m_pageIndicatorButton  = new Button(clipRect, m_pageIndicatorTexture, 0, 580, 15, 15, true);
        }
    }
}

/**
 * Create Cards ans Indicators
 * @author Arthur
 * @date 16/05
 */
void ShopView::createCards()
{
    //=== Create Item Cards
    int i = 0;
    for ( ShopItem *item : m_shop->getShopItemsArray() )
    {
        m_shopItemsCardArray.push_back( new ShopItemCard(i, item, m_textHandler)  );
        i++;
    }

    //=== Create Pages Indicator

    m_totalIndicator = (int) (m_shop->getShopItemsArray().size() / 3);
    if ( m_shop->getShopItemsArray().size()%3 != 0)
        m_totalIndicator++;

    for (int j=0; j < m_totalIndicator; j++)
    {
        m_pageIndicators[j] = new Button(*m_pageIndicatorButton);
        m_pageIndicators[j]->setPosition( m_width/2 - 10*m_totalIndicator + 20*j, 550 );
        m_pageIndicators[j]->resize(22, 22);
    }
}


/**
 * Display current Cards function
 * @author Arthur
 * @date 16/05
 */
void ShopView::displayCards() const
{
    //display only 3 cards linked to the current page indicator
    for( ShopItemCard *card : m_shopItemsCardArray)
        if( card->getId() == 0 + 3*m_currentIndicator
            || card->getId() == 1 + 3*m_currentIndicator
            || card->getId() == 2 + 3*m_currentIndicator )
            {
                card->setShownState(true);
                card->draw(m_window);
            }
            else
                card->setShownState(false);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 16/05
 */
void ShopView::synchronize()
{
    m_homeFormButton->sync();
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);

    m_textHandler->syncShopText();

    for( ShopItemCard *card : m_shopItemsCardArray)
    {
        card->sync();
    }

    for( auto it : m_pageIndicators)
    {
         (it.second)->sync();
         it.first == m_currentIndicator ?
         it.second->setActivatedState(true) : it.second->setActivatedState(false);
    }
}


/**
 * Menu View Drawing
 * @author Arthur
 * @date 16/05
 */
void ShopView::draw() const
{
    m_window->clear(GREY_BG_COLOR);

    //=== Graphic Elements drawing

    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_coinSprite);
    displayCards();

    if ( m_buyDialog != nullptr)
        m_buyDialog->draw(m_window);
    else
    {
        for( auto it : m_pageIndicators)
            m_window->draw(*it.second);
    }

    //=== TextHandler Drawing

    m_textHandler->drawMenuShopText(m_window);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 16/05 - 18/05
 */
bool ShopView::treatEvents() { return false; }
bool ShopView::treatEvents(sf::Event event)
{
    bool stop_shop = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if ( m_homeFormButton->IS_POINTED )
            m_homeFormButton->setPressedState(true);

        for( auto it : m_pageIndicators)
            if ( it.second->IS_POINTED )
                it.second->setPressedState(true);

        for ( auto card : m_shopItemsCardArray )
            if ( card->getBuyButton()->IS_POINTED
                    && card->getShownState() && m_buyDialog == nullptr)
                card->getBuyButton()->setPressedState(true);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressedState(false);
        for( auto it : m_pageIndicators)
            it.second->setPressedState(false);

        for ( auto card : m_shopItemsCardArray )
            card->getBuyButton()->setPressedState(false);

        //=== handle mouse up on a button

        if ( m_homeFormButton->IS_POINTED )
            stop_shop = true;

        for( auto it : m_pageIndicators)
            if ( it.second->IS_POINTED )
                m_currentIndicator = it.first;

        for ( auto card : m_shopItemsCardArray )
            if ( card->getBuyButton()->IS_POINTED && card->getShownState()
                    && !card->getItem()->getBoughtState() && m_buyDialog == nullptr)
            {
                //Get dialog text from file
                string title, content, negative_choice, positive_choice;
                m_textHandler->syncDialogText("askBuying", title, content, negative_choice, positive_choice);
                content.insert(content.find(" : ")+3, card->getItem()->getName() + "\n\n" );
                content.insert(content.find("\n")+11, to_string(card->getItem()->getPrice() ) );

                //create buy dialog
                m_buyDialog = new Dialog((int) (m_width / 2 - 125), (int) (m_height / 2 - 100),
                                         card->getItem(), m_textHandler, title, content, negative_choice, positive_choice);
            }

        //Mouse up on negative button
        if ( m_buyDialog != nullptr && m_buyDialog->getNegativeButton().IS_POINTED )
        {
            delete m_buyDialog;
            m_buyDialog = nullptr;
        }
        //Mouse up on positive button as dialog
        else if ( m_buyDialog != nullptr && m_buyDialog->getPositiveButton().IS_POINTED
                  &&  m_buyDialog->getNegativeButton().getString() != "")
        {
            bool result = m_shop->buyItem(m_buyDialog->getItemLinked() );
            delete m_buyDialog;
            m_buyDialog = nullptr;

            string title, content, negative_choice, positive_choice;
            if ( result)
                m_textHandler->syncDialogText("success", title, content, negative_choice, positive_choice);
            else
                m_textHandler->syncDialogText("failure", title, content, negative_choice, positive_choice);

            m_buyDialog = new Dialog((int) (m_width / 2 - 125), (int) (m_height / 2 - 100),
                                     nullptr, m_textHandler, title, content, negative_choice, positive_choice);
        }

        //Mouse up on positive button as toast
        else if ( m_buyDialog != nullptr && m_buyDialog->getPositiveButton().IS_POINTED
                  &&  m_buyDialog->getNegativeButton().getString() == "")
        {
            delete m_buyDialog;
            m_buyDialog = nullptr;
        }
    }

    return stop_shop;
}
