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
 *
 * @author Arthur
 * @date 16/05/16 - 05/09/18
 */
ShopItemCard::ShopItemCard(int num, ShopItem* item) :
        mdsf::Sprite(INITIAL_POS_X, INITIAL_POS_Y, WIDTH, HEIGHT),
        m_id{num}, m_item{item}, m_title{""}, m_content{""}
{
    //=== Set position following card id

    if (num % 3 == 0) {
        setPosition(EDGE_MARGIN, INITIAL_POS_Y);
    } else if (num % 3 == 1) {
        setPosition((SCREEN_WIDTH / 2) - (m_width / 2), INITIAL_POS_Y);
    } else if (num % 3 == 2) {
        setPosition(SCREEN_WIDTH - m_width - EDGE_MARGIN, INITIAL_POS_Y);
    }

    //=== Init title and content

    m_title.applyTextFont(ROBOTO_CONDENSED_FONT, 20, sf::Color::White);
    m_title.setUtf8String(item->getName());
    m_title.setPositionSelfCentered(getX() + m_width / 2, getY() + 20);

    m_content.applyTextFont(ROBOTO_CONDENSED_FONT, 16, sf::Color::White);
    m_content.setUtf8String(item->getDescription());
    m_content.setPosition(getX() + 30, getY() + 190);

    //=== Init buy button

    std::vector<sf::IntRect> flatButtonClipRect;
    flatButtonClipRect.emplace_back(RAISED_BUTTON_DEFAULT);
    flatButtonClipRect.emplace_back(RAISED_BUTTON_PRESSED);
    m_buyButton = new mdsf::Button(getX() + m_width / 2 - 75, getY() + 250, static_cast<float>(0.75 * WIDTH),
                                   BUTTON_HEIGHT, RECT_BUTTONS_IMAGE, flatButtonClipRect);

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
mdsf::Button *ShopItemCard::getBuyButton() const { return m_buyButton; }
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
        m_buyButton->setColor(mdsf::Color::MaterialRed);
    } else {
        m_buyButton->setEnabled(true);
        m_buyButton->setColor(mdsf::Color::MaterialGreenA700);
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

