#include "ShopItemCard.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 16/05 - 23/12
 */
ShopItemCard::ShopItemCard(DataBase *dataBase, int num, ShopItem *item, TextHandler *t) :
    m_dataBase{dataBase}, m_id{num}, m_posY{150}, m_shownState{false}, m_item{item}, m_text{t}
{
    if ( num%3 == 0)
        m_posX = 100;
    else if ( num%3 == 1)
        m_posX = 350;
    else if ( num%3 == 2)
        m_posX = 600;

    loadImages();

    m_name.setCharacterSize(20);
    m_name.setFont( *m_text->getCondensedFont() );
    m_name.setColor(sf::Color::White);
    m_name.setString( item->getName() );
    m_name.setPositionSelfCentered( m_posX + m_width/2, m_posY+15);

    m_desc.setCharacterSize(16);
    m_desc.setFont( *m_text->getCondensedFont() );
    m_desc.setColor(sf::Color::White);
    m_desc.setString( item->getDescription() );
    m_desc.setPositionSelfCentered( m_posX + m_width/2, m_posY+200);
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05 - 23/12
 */
ShopItemCard::~ShopItemCard()
{
    m_text = nullptr;
    delete m_cardBackgroundSprite;
    delete m_buyButton;
    delete m_boughtButton;
}


//=== Getters

int ShopItemCard::getId() const { return m_id; }
bool ShopItemCard::getShownState() const { return m_shownState; }
Button *ShopItemCard::getBuyButton() const { return m_buyButton; }
ShopItem *ShopItemCard::getItem() const { return m_item; }


//=== Setters

void ShopItemCard::setShownState(bool state) { m_shownState = state; }


/**
 * Image Loading
 * @author Arthur
 * @date 16/05 - 23/12
 */
void ShopItemCard::loadImages()
{
    //=== Initialize BUY, BOUGHT Buttons

	if (!m_rectButtonsTexture.loadFromFile(RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_rectButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clipRectGreen;
        clipRectGreen.push_back(GREEN_BUTTON_UP);
        clipRectGreen.push_back(GREEN_BUTTON_DOWN);
		m_buyButton = new Button(clipRectGreen, m_rectButtonsTexture, m_posX + m_width/2 - 75,
                                 m_posY+250, 150, 80, "shop_purchasable");

        m_rectButtonsTexture.setSmooth(true);

        vector<sf::IntRect> clipRectRed;
        clipRectRed.push_back(RED_BUTTON_UP);
        clipRectRed.push_back(RED_BUTTON_UP);
        m_boughtButton = new Button(clipRectRed, m_rectButtonsTexture, m_posX + m_width/2 - 75,
                                 m_posY+250, 150, 80, "shop_bought");
        m_boughtButton->setActivated(false);
    }


	//=== Initialize CARD Sprite

	if (!m_cardBackgroundTexture.loadFromFile(CARD_IMAGE) )
        cerr << "ERROR when loading image file: " << CARD_IMAGE << endl;
    else
    {
        m_cardBackgroundTexture.setSmooth(true);
        m_cardBackgroundSprite = new GraphicElement(m_cardBackgroundTexture, m_posX, m_posY, m_width, m_height);
    }
}


/**
 * Sync function
 * @author Arthur
 * @date 16/05 - 23/12
 */
void ShopItemCard::sync()
{
    if (  m_item->getBoughtState() )
    {
        m_buyButton->setVisible(false);
        m_boughtButton->setVisible(true);
        m_boughtButton->sync(m_dataBase);
    }
    else
    {
        m_boughtButton->setVisible(false);
        m_buyButton->setVisible(true);
        m_buyButton->sync(m_dataBase);
    }
}


/**
 * Draw function
 * @author Arthur
 * @date 16/05 - 23/12
 */
void ShopItemCard::draw(sf::RenderWindow *window) const
{
    window->draw(*m_cardBackgroundSprite);
    window->draw(m_name);
    window->draw(m_desc);
    m_buyButton->draw(window);
    m_boughtButton->draw(window);
}
