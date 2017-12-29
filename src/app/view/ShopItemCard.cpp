#include "ShopItemCard.h"

using std::string;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 16/05/16 - 25/01/17
 */
ShopItemCard::ShopItemCard(int num, ShopItem *item) :
        mdsf::Sprite(0, 150, 200, 300), m_id{num}, m_item{item}, m_title{""}, m_content{""}
{
    if (num%3 == 0)
        setPosition(100, 150);
    else if (num%3 == 1)
        setPosition(350, 150);
    else if (num%3 == 2)
        setPosition(600, 150);

    loadImages();

    m_title.applyTextFont(ROBOTO_CONDENSED_FONT, 20, sf::Color::White);
    string utf8_string = item->getName();
    m_title.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    m_title.setPositionSelfCentered(getPosition().x + m_width/2, getPosition().y + 20);

    m_content.applyTextFont(ROBOTO_CONDENSED_FONT, 16, sf::Color::White);
    utf8_string = item->getDescription();
    m_content.setString(sf::String::fromUtf8(utf8_string.begin(), utf8_string.end()));
    m_content.setPosition(getPosition().x + 30, getPosition().y + 190);

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
mdsf::Button *ShopItemCard::getBuyButton() const { return m_buyButton; }
ShopItem *ShopItemCard::getItem() const { return m_item; }


/**
 * Image Loading
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopItemCard::loadImages()
{
    //=== Initialize BUY, BOUGHT Buttons

    std::vector<sf::IntRect> clipRectGreen;
    clipRectGreen.emplace_back(GREEN_BUTTON_UP);
    clipRectGreen.emplace_back(GREEN_BUTTON_DOWN);
    m_buyButton = new mdsf::Button(getPosition().x + m_width/2 - 75, getPosition().y + 250, 150, 80,
                                   "shop_purchasable", RECT_BUTTONS_IMAGE, clipRectGreen);

    std::vector<sf::IntRect> clipRectRed;
    clipRectRed.emplace_back(RED_BUTTON_UP);
    clipRectRed.emplace_back(RED_BUTTON_UP);
    m_boughtButton = new mdsf::Button(getPosition().x + m_width/2 - 75, getPosition().y + 250, 150, 80,
                                      "shop_bought", RECT_BUTTONS_IMAGE, clipRectRed);
    m_boughtButton->setEnabled(false);

    setTextureFromImage(CARD_IMAGE);
}


/**
 * Sync function
 * @author Arthur
 * @date 16/05/16 - 27/12/17
 */
void ShopItemCard::sync()
{
    mdsf::Sprite::sync();

    if (m_item->isBought())
    {
        m_buyButton->hide();
        m_boughtButton->applyColor();
        m_boughtButton->show();
        m_boughtButton->sync();
    }
    else
    {
        m_boughtButton->hide();
        m_buyButton->applyColor();
        m_buyButton->show();
        m_buyButton->sync();
    }
}


/**
 * Syncs the card and retrieve content of buttons label
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 *
 * @param dataBase the database for retrieval
 */
void ShopItemCard::syncWithButtonLabelRetrieval(const DataBase &dataBase)
{
    if (m_item->isBought())
    {
        m_buyButton->hide();
        m_boughtButton->applyColor();
        m_boughtButton->show();
        m_boughtButton->sync();
        m_boughtButton->retrieveAndSyncLabel(dataBase);
    }
    else
    {
        m_boughtButton->hide();
        m_buyButton->applyColor();
        m_buyButton->show();
        m_buyButton->sync();
        m_buyButton->retrieveAndSyncLabel(dataBase);
    }
}


/**
 * Draw function
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopItemCard::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
        window->draw(m_title);
        window->draw(m_content);
        m_buyButton->draw(window);
        m_boughtButton->draw(window);
    }
}

