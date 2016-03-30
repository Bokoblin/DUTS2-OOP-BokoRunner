/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "../header/Menu.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 25/02 - 27/03
*********************************************/
Menu::Menu(int w, int h, sf::RenderWindow *window): View(w, h, window)
{
    m_window->create( sf::VideoMode(w, h, 32), "Boko Runner", sf::Style::Close );
    m_window->setFramerateLimit(30);
    m_window->setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2, (sf::VideoMode::getDesktopMode().height - m_height)/2 ));

    //=== Images Loading

    loadImages();

    //=== font & text initialization

    m_font = new sf::Font();
    m_font->loadFromFile(FONT);

    loadText();
}


/********************************************
    Destructor
*********************************************
    Arthur : 26/02 - 27/03
*********************************************/
Menu::~Menu()
{
    if(m_font!= NULL)
        delete m_font;
    if(m_farBackground!= NULL)
        delete m_farBackground;
    if(m_nearBackground!= NULL)
        delete m_nearBackground;
    if(m_titleGraphic!= NULL)
        delete m_titleGraphic;
    if(m_playButtonGraphic!= NULL)
        delete m_playButtonGraphic;
    if(m_quitButtonGraphic!= NULL)
        delete m_quitButtonGraphic;
}


/********************************************
    Image Loading
*********************************************
    Arthur : 26/03 - 27/03
*********************************************/
void Menu::loadImages()
{
    if (!m_farBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_2))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_2 << endl;
    else
    {
        m_farBackgroundTexture.setSmooth(true);
        m_farBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_height, 1);
    }

    if (!m_nearBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_1))
        cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_1 << endl;
    else
    {
        m_nearBackgroundTexture.setSmooth(true);
        m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_height, 2);
    }

    if (!m_titleTexture.loadFromFile(TITLE_IMAGE))
    cerr << "ERROR when loading image file: " << TITLE_IMAGE << endl;
    else
    {
        m_titleTexture.setSmooth(true);
        m_titleGraphic = new GraphicElement(m_titleTexture, m_width/2-200, m_height/6, 400, 200);
    }

    if (!m_playButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(151,0,150,80)))
    cerr << "ERROR when loading image file: " << BUTTONS_IMAGE << endl;
    else
    {
        m_playButtonTexture.setSmooth(true);
        m_playButtonGraphic = new GraphicElement(m_playButtonTexture, m_width/2-75, m_height/1.5, 150, 80);
    }

        if (!m_quitButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(151,0,150,80)))
    cerr << "ERROR when loading image file: " << BUTTONS_IMAGE << endl;
    else
    {
        m_quitButtonTexture.setSmooth(true);
        m_quitButtonGraphic = new GraphicElement(m_quitButtonTexture, m_width/2-75, m_height/1.2, 150, 80);
    }
}


/********************************************
    Text Loading
*********************************************
    Arthur : 25/03 - 27/03
*********************************************/
void Menu::loadText()
{
    m_playButtonText.setFont(*m_font);
    m_playButtonText.setPosition(m_width/2-30, m_height/1.42);
    m_playButtonText.setCharacterSize(24);
    m_playButtonText.setColor(sf::Color::White);
    m_playButtonText.setString( "PLAY" );

    m_quitButtonText.setFont(*m_font);
    m_quitButtonText.setPosition(m_width/2-30, m_height/1.15);
    m_quitButtonText.setCharacterSize(24);
    m_quitButtonText.setColor(sf::Color::White);
    m_quitButtonText.setString( "QUIT" );
}


/********************************************
    Synchronization function
*********************************************
    Arthur : 26/03
*********************************************/
void Menu::synchronize()
{
    m_titleGraphic->resize(400,200);
    m_farBackground->sync();
    m_nearBackground->sync();
}


/********************************************
    View Drawing
*********************************************
    Arthur : 26/03 - 27/03
*********************************************/
void Menu::draw()
{
    m_window->clear();

    //=== Graphic Elements drawing
    m_farBackground->draw(*m_window);
    m_nearBackground->draw(*m_window);
    m_window->draw(*m_titleGraphic);
    m_window->draw(*m_playButtonGraphic);
    m_window->draw(*m_quitButtonGraphic);

    //=== Text Drawing
    m_window->draw(m_playButtonText);
    m_window->draw(m_quitButtonText);

    m_window->display();
}


/********************************************
    Events treating
*********************************************
    Arthur : 25/03 - 27/03
*********************************************/
bool Menu::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_model->setMenuState(false);
                m_window->close();
                result = false;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if ( m_playButtonGraphic->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) )
                    {
                        m_playButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(0,0,150,80));
                    }
                    else if ( m_quitButtonGraphic->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) )
                    {
                        m_quitButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(0,0,150,80));
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_playButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(151,0,150,80));
                    m_quitButtonTexture.loadFromFile(BUTTONS_IMAGE, sf::IntRect(151,0,150,80));

                    if ( m_playButtonGraphic->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) )
                    {
                        m_model->setMenuState(false);
                        m_model->setGameState(true);
                    }
                    else if ( m_quitButtonGraphic->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) )
                    {
                        m_window->close();
                        result = false;
                    }
                }
            }
        }

    }
    return result;
}
