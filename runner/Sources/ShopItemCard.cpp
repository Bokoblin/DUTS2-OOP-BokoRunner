#include "ShopItemCard.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 16/05 - 19/05
*********************************************/
ShopItemCard::ShopItemCard(int num, ShopItem *item, Text *t) :
    m_id{num}, m_posY{150}, m_shownState{false}, m_item{item}, m_text{t}
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
    m_name.setPosition( m_posX + m_width/2
                    - (int)m_name.HALF_WIDTH, m_posY+15);

    m_desc.setCharacterSize(16);
    m_desc.setFont( *m_text->getCondensedFont() );
    m_desc.setColor(sf::Color::White);
    m_desc.setString( item->getDescription() );
    m_desc.setPosition( m_posX + m_width/2
                    - (int)m_desc.HALF_WIDTH, m_posY+200);

    m_buyButtonContent.setCharacterSize(20);
    m_buyButtonContent.setFont( *m_text->getCondensedFont() );
    m_buyButtonContent.setColor(sf::Color::White);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 16/05 - 18/05
*********************************************/
ShopItemCard::~ShopItemCard()
{
    m_text = nullptr;
    delete m_cardBackgroundSprite;
    delete m_buyButton;
}


/********************************************
   Getters
*********************************************
    @author Arthur  @date 16/05 - 17/05
*********************************************/
int ShopItemCard::getId() const { return m_id; }
bool ShopItemCard::getShownState() const { return m_shownState; }
Button *ShopItemCard::getBuyButton() const { return m_buyButton; }
ShopItem *ShopItemCard::getItem() const { return m_item; }


/********************************************
   Setters
*********************************************
    @author Arthur  @date 16/05
*********************************************/
void ShopItemCard::setShownState(bool state) { m_shownState = state; }


/********************************************
    Image Loading
*********************************************
    @author Arthur  @date 16/05 - 17/05
*********************************************/
void ShopItemCard::loadImages()
{
    //=== Initialize BUY, BOUGHT Buttons

	if (!m_rectButtonsTexture.loadFromFile(RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_rectButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clip_rects;
		clip_rects.push_back(RED_BUTTON_UP);
		clip_rects.push_back(RED_BUTTON_UP);
		clip_rects.push_back(GREEN_BUTTON_UP);
		clip_rects.push_back(GREEN_BUTTON_DOWN);
		m_buyButton = new Button(clip_rects, m_rectButtonsTexture, m_posX
                           + m_width/2 - 75, m_posY+250, 150, 80, true);
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


/********************************************
    Sync function
*********************************************
    @author Arthur  @date 16/05 - 19/05
*********************************************/
void ShopItemCard::sync()
{
    if (  m_item->getBoughtState() )
    {
        m_buyButton->setActivatedState(true);
        m_buyButtonContent.setString( "Bought" );
    }
    else
    {
        m_buyButton->setActivatedState(false);
        m_buyButtonContent.setString( "Buy" );
    }
    m_buyButtonContent.setPosition( m_posX + m_width/2
                    - (int)m_buyButtonContent.HALF_WIDTH, m_posY+258);
    m_buyButton->sync();
}


/********************************************
    Draw function
*********************************************
    @author Arthur  @date 16/05 - 19/05
*********************************************/
void ShopItemCard::draw(sf::RenderWindow *window) const
{
    window->draw(*m_cardBackgroundSprite);
    window->draw(m_name);
    window->draw(m_desc);
    window->draw(*m_buyButton);
    window->draw(m_buyButtonContent);
}
