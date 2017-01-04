#include "ShopView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 16/05/16
 */
ShopView::ShopView(float w, float h, sf::RenderWindow *window, TextHandler * text):
        View(w, h, window,text), m_shop{nullptr}, m_currentIndicator{0},
        m_totalIndicator{0}, m_buyDialog{nullptr}
{
    loadImages();

    m_buyDialog = new Dialog();
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
ShopView::~ShopView()
{
    delete m_coinSprite;
    delete m_homeFormButton;
    delete m_buyDialog;

    for ( auto shopItemCard : m_shopItemCardsArray)
        delete shopItemCard;

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
 * @date 16/05/16 - 02/01/17
 */
void ShopView::loadImages()
{
    //=== Initialize COIN Sprite

    m_coinSprite = new GraphicElement(m_width/2-60, 53, 25, 25);
    m_coinSprite->setTextureFromImage(BONUS_IMAGE, sf::IntRect(0,0,50,50));
    m_coinSprite->resize(25, 25);

    //=== Initialize HOME form buttons

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.push_back(sf::IntRect( 0, 50, 50, 50));
    clipRectHome.push_back(sf::IntRect( 51, 50, 50, 50));
    m_homeFormButton = new Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);
}

/**
 * Create Cards ans Indicators
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopView::createCards()
{
    //=== Create Item Cards
    int i = 0;
    for ( ShopItem *item : m_shop->getShopItemsArray() )
    {
        m_shopItemCardsArray.push_back(new ShopItemCard(i, item, m_textHandler));
        i++;
    }

    //=== Create Pages Indicator

    m_totalIndicator = (int) (m_shop->getShopItemsArray().size() / 3);
    if ( m_shop->getShopItemsArray().size()%3 != 0)
        m_totalIndicator++;

    for (int j=0; j < m_totalIndicator; j++)
    {
        m_pageIndicators[j] = new RadioButton(0, 580, 15, 15, "indicator");
        m_pageIndicators[j]->setPosition( m_width/2 - 10*m_totalIndicator + 20*j, 550 );
        m_pageIndicators[j]->resize(22, 22);
    }
}


/**
 * sync cards and Shows/hides them
 * depending on the current page
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopView::syncCards() const
{
    //display only 3 cards linked to the current page indicator
    for( ShopItemCard *card : m_shopItemCardsArray)
    {
        card->sync(m_shop->getDataBase());
        if( card->getId() == 0 + 3*m_currentIndicator
            || card->getId() == 1 + 3*m_currentIndicator
            || card->getId() == 2 + 3*m_currentIndicator )
        {
            card->show();
        }
        else
            card->hide();
    }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopView::synchronize()
{
    m_homeFormButton->sync();
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);

    m_textHandler->syncShopText();

    syncCards();

    for( auto it : m_pageIndicators)
    {
        (it.second)->sync();
        it.first == m_currentIndicator ?
        it.second->setActivated(true) : it.second->setActivated(false);
    }
}


/**
 * Menu View Drawing
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopView::draw() const
{
    m_window->clear(MINE_GREY_COLOR);

    //=== Graphic Elements drawing

    for( ShopItemCard *card : m_shopItemCardsArray)
        card->draw(m_window);

    if ( !m_buyDialog->isShowing())
    {
        for( auto it : m_pageIndicators)
            m_window->draw(*it.second);
    }
    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_coinSprite);
    m_buyDialog->draw(m_window);

    //=== TextHandler Drawing

    m_textHandler->drawMenuShopText(m_window);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 16/05/16 - 18/05/16
 */
bool ShopView::treatEvents() { return false; }
bool ShopView::treatEvents(sf::Event event)
{
    bool stop_shop = false;

    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if ( m_homeFormButton->contains(MOUSE_POSITION) )
            m_homeFormButton->setPressed(true);

        for( auto it : m_pageIndicators)
            if ( it.second->contains(MOUSE_POSITION) )
                it.second->setPressed(true);

        for ( auto card : m_shopItemCardsArray )
            if ( card->getBuyButton()->contains(MOUSE_POSITION)
                 && card->isShowing() && !m_buyDialog->isShowing())
                card->getBuyButton()->setPressed(true);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressed(false);
        for( auto it : m_pageIndicators)
            it.second->setPressed(false);

        for ( auto card : m_shopItemCardsArray )
            card->getBuyButton()->setPressed(false);

        //=== handle mouse up on a button

        if ( m_homeFormButton->contains(MOUSE_POSITION) )
            stop_shop = true;

        for( auto it : m_pageIndicators)
            if ( it.second->contains(MOUSE_POSITION) )
                m_currentIndicator = it.first;

        for ( auto card : m_shopItemCardsArray )
            if ( card->getBuyButton()->contains(MOUSE_POSITION) && card->isShowing()
                 && !card->getItem()->isBought() && !m_buyDialog->isShowing() )
            {
                delete m_buyDialog;
                m_buyDialog = new Dialog(m_width/2-125, m_height/2-100, 250, 200,  card->getItem(), m_textHandler, "shopAskDialog");
                m_buyDialog->sync(m_shop->getDataBase());
                m_buyDialog->show();
            }

        if ( m_buyDialog->isShowing() && m_buyDialog->getCancelButtonText().contains(MOUSE_POSITION) )
        {
            m_buyDialog->hide();
        }
        else if ( m_buyDialog->isShowing() && m_buyDialog->getOkButtonText().contains(MOUSE_POSITION) )
        {
            if (m_buyDialog->getId() == "shopAskDialog" )
            {
                if (m_shop->buyItem(m_buyDialog->getLinkedShopItem() ))
                {
                    delete m_buyDialog;
                    m_buyDialog = new Dialog(m_width/2-125, m_height/2-50, 250, 100, m_textHandler, "shopSuccess");
                    m_buyDialog->sync(m_shop->getDataBase());
                }
                else
                {
                    delete m_buyDialog;
                    m_buyDialog = new Dialog(m_width/2-125, m_height/2-50, 250, 100, m_textHandler, "shopFailure");
                    m_buyDialog->sync(m_shop->getDataBase());
                }
            }
            else
                m_buyDialog->hide();
        }
    }

    return stop_shop;
}
