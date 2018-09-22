#include "ShopItemCard.h"

using std::string;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a ShopItemCard with a card number and a shop item
 *
 * @param num the card number
 * @param item the item related
 * @param screenWidth the screen width
 * @param screenHeight the screen height
 * @param cardsPerPage the number of cards per page to adjust x position
 *
 * @author Arthur
 * @date 16/05/16 - 17/09/18
 */
ShopItemCard::ShopItemCard(int num, ShopItem* item, float screenWidth, float screenHeight, int cardsPerPage) :
        mdsf::Sprite(0, 0.17f * screenHeight, WIDTH, HEIGHT),
        m_id{num}, m_item{item}, m_title{""}, m_content{""}
{
    //=== Set position following card id

    const float INITIAL_POS_Y = 0.3f * screenHeight;
    const float EDGE_MARGIN = 0.05f * screenWidth;
    const float PAGE_MARGIN = (screenWidth - (cardsPerPage * m_width) - ((cardsPerPage - 1)) * EDGE_MARGIN) / 2;
    setPosition(PAGE_MARGIN + (num % cardsPerPage) * (m_width + EDGE_MARGIN), INITIAL_POS_Y);

    //=== Init title and content

    m_title.applyTextFont(ROBOTO_CONDENSED_FONT, 20, sf::Color::White);
    m_title.setUtf8String(item->getName());
    m_title.setPositionSelfCentered(getX() + m_width / 2, getY() + 0.067f * m_height);

    m_content.applyTextFont(ROBOTO_CONDENSED_FONT, 16, sf::Color::White);
    m_content.setUtf8String(item->getDescription());
    m_content.setPosition(getX() + 0.15f * WIDTH, getY() + 0.633f * m_height);

    //=== Init buy button

    m_buyButton = new mdsf::RaisedButton(getX() + 0.125f * m_width, getY() + 0.83f * m_height, 0.75f * m_width,
                                         0.133f * m_height, "shop_purchasable", RAISED_BUTTON_IMAGE);

    //=== Init background

    loadAndApplyTextureFromImageFile(CARD_IMAGE);
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/16 - 04/01/18
 */
ShopItemCard::~ShopItemCard()
{
    delete m_buyButton;
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

int ShopItemCard::getId() const { return m_id; }
mdsf::RaisedButton* ShopItemCard::getBuyButton() const { return m_buyButton; }
ShopItem* ShopItemCard::getItem() const { return m_item; }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes sprite color and buy button state
 *
 * @author Arthur
 * @date 16/05/16 - 04/01/18
 */
void ShopItemCard::sync()
{
    mdsf::Sprite::sync();

    if (m_item->isBought()) {
        m_buyButton->setEnabled(false);
        m_buyButton->setFillColor(mdsf::Color::MaterialRed);
    } else {
        m_buyButton->setEnabled(true);
        m_buyButton->setFillColor(mdsf::Color::MaterialGreenA700);
    }

    m_buyButton->sync();
}


/**
 * Syncs the card and retrieve content of buttons label
 *
 * @param func the function used to retrieve the string given a label
 *
 * @author Arthur
 * @date 16/05/16 - 23/01/18
 */
void ShopItemCard::syncWithButtonLabelRetrieval(mdsf::Button::label_retrieval_func_t func)
{
    sync();
    m_buyButton->setLabelDescription(m_item->isBought() ? "shop_bought" : "shop_purchasable");
    m_buyButton->retrieveAndSyncLabel(func);
}


/**
 * Draws the ShopItemCard if visible
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 16/05/16 - 04/01/18
 */
void ShopItemCard::draw(sf::RenderWindow* window) const
{
    if (isVisible()) {
        window->draw(*this);
        window->draw(m_title);
        window->draw(m_content);
        m_buyButton->draw(window);
    }
}

