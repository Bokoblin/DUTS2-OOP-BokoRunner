#include "Dialog.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 16/05 - 24/05
*********************************************/
Dialog::Dialog(int x, int y, ShopItem *item, Text *t, string title, string content, string negAnswer, string posAnswer):
    m_posX{x}, m_posY{y}, m_itemLinked{item}, m_text{t}
{
    //=== Initialize Dialog Sprite

	if (!m_dialogTexture.loadFromFile(DIALOG_IMAGE) )
        cerr << "ERROR when loading image file: " << DIALOG_IMAGE << endl;
    else
    {
        m_dialogTexture.setSmooth(true);
        m_dialogSprite = new GraphicElement(m_dialogTexture, m_posX, m_posY, m_width, m_height);
    }

    m_dialogTitleLabel.setCharacterSize(19);
    m_dialogTitleLabel.setFont(*m_text->getBoldFont());
    m_dialogTitleLabel.setColor(sf::Color::Black);
    m_dialogTitleLabel.setString( title );
    m_dialogTitleLabel.setPosition( m_posX + 24, m_posY + 24);

    m_dialogContent.setCharacterSize(15);
    m_dialogContent.setFont(*m_text->getRegularFont());
    m_dialogContent.setColor(sf::Color::Black);
    m_dialogContent.setString( content );
    m_dialogContent.setPosition( m_posX + 24, m_posY + 75);

    m_negativeButton.setCharacterSize(14);
    m_negativeButton.setFont(*m_text->getBoldFont());
    m_negativeButton.setColor(MATERIAL_TEAL_COLOR);
    m_negativeButton.setString( negAnswer );
    m_negativeButton.setPosition( m_posX + 0.5*m_width, m_posY + 0.83*m_height);

    m_positiveButton.setCharacterSize(14);
    m_positiveButton.setFont(*m_text->getBoldFont());
    m_positiveButton.setColor(MATERIAL_TEAL_COLOR);
    m_positiveButton.setString( posAnswer );
    m_positiveButton.setPosition( m_posX + 0.8*m_width, m_posY + 0.83*m_height);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 16/05 - 20/05
*********************************************/
Dialog::~Dialog()
{
    m_text = nullptr;
    delete m_dialogSprite;
}


/********************************************
   Getters
*********************************************
    @author Arthur  @date 16/05
*********************************************/
const sf::Text& Dialog::getNegativeButton() const { return m_negativeButton; }
const sf::Text& Dialog::getPositiveButton() const { return m_positiveButton; }
ShopItem *Dialog::getItemLinked() const {return m_itemLinked; }


/********************************************
    Draw function
*********************************************
    @author Arthur  @date 16/05
*********************************************/
void Dialog::draw(sf::RenderWindow *window) const
{
    window->draw(*m_dialogSprite);
    window->draw(m_dialogTitleLabel);
    window->draw(m_dialogContent);
    window->draw(m_negativeButton);
    window->draw(m_positiveButton);
}
