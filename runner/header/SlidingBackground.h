#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H

#include "GraphicElement.h"


/********************************************
    SlidingBackground Class
*********************************************
    Arthur : 3/03 - 3/03
    Florian: 3/03 - 3/03
*********************************************/
class SlidingBackground
{
public:
    //CTORS
    SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed);

    //METHODS
    void syncAndDraw(sf::RenderWindow &window);

    //SETTERS
    void setSpeed(unsigned int speed);


private:
    GraphicElement *m_left, *m_right;
    int m_width, m_height;
    unsigned int m_speed;

};

#endif // SLIDINGBACKGROUND_H
