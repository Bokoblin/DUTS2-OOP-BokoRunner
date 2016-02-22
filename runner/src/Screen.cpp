#include "Screen.h"
#include "../Game.h"

Screen::Screen() :
    m_window {sf::VideoMode {g.getScreenWidth(), m_defaultScreenHeight, SCREEN_BPP}, "Runner", sf::Style::Close}
{
    m_window.setFramerateLimit(30);
}

Screen::~Screen()
{
    //dtor
}

void Screen::run()
{

}
