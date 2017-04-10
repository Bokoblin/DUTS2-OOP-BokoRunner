#include "ShopItemCard.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 16/05/16 - 10/04/17
 */
ShopItemCard::ShopItemCard(int id, ShopItem *item, TextHandler *textHandler) :
        GraphicElement(0, 150, 200, 300), m_id{id}, m_item{item}, m_title{""}, m_content{""}
{
    if ( id%3 == 0)
        setPosition(100, 150);
    else if ( id%3 == 1)
        setPosition(350, 150);
    else if ( id%3 == 2)
        setPosition(600, 150);

    loadImages();

    m_title.setTextFont( textHandler->getCondensedFont(), 20, sf::Color::White );
    std::string utf8_string = item->getName();
    m_title.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    m_title.setPositionSelfCentered( getPosition().x + m_width/2, getPosition().y + 20);

    m_content.setTextFont( textHandler->getCondensedFont(), 16, sf::Color::White );
    utf8_string = item->getDescription();
    m_content.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    m_content.setPosition( getPosition().x + 30, getPosition().y + 190);

    hide();
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 */
ShopItemCard::~ShopItemCard()
{
    delete m_buyButton;
    delete m_boughtButton;
}


//=== Getters

int ShopItemCard::getId() const { return m_id; }
Button *ShopItemCard::getBuyButton() const { return m_buyButton; }
ShopItem *ShopItemCard::getItem() const { return m_item; }


/**
 * Image Loading
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopItemCard::loadImages()
{
    //=== Initialize BUY, BOUGHT Buttons

    vector<sf::IntRect> clipRectGreen;
    clipRectGreen.push_back(GREEN_BUTTON_UP);
    clipRectGreen.push_back(GREEN_BUTTON_DOWN);
    m_buyButton = new Button(getPosition().x + m_width/2-75, getPosition().y + 250, 150, 80, "shop_purchasable",
                             RECT_BUTTONS_IMAGE, clipRectGreen);

    vector<sf::IntRect> clipRectRed;
    clipRectRed.push_back(RED_BUTTON_UP);
    clipRectRed.push_back(RED_BUTTON_UP);
    m_boughtButton = new Button(getPosition().x + m_width/2-75, getPosition().y + 250, 150, 80, "shop_bought",
                                RECT_BUTTONS_IMAGE, clipRectRed);
    m_boughtButton->setDisabled(true);

    setTextureFromImage(CARD_IMAGE);
}


/**
 * Sync function
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 */
void ShopItemCard::sync(DataBase *dataBase)
{
    if (m_item->isBought() )
    {
        m_buyButton->hide();
        m_boughtButton->show();
        m_boughtButton->sync(dataBase);
    }
    else
    {
        m_boughtButton->hide();
        m_buyButton->show();
        m_buyButton->sync(dataBase);
    }
}


/**
 * Draw function
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopItemCard::draw(sf::RenderWindow *window) const
{
    if (isShowing())
    {
        window->draw(*this);
        window->draw(m_title);
        window->draw(m_content);
        m_buyButton->draw(window);
        m_boughtButton->draw(window);
    }
}
