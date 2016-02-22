#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>


class Screen
{
    public:
        Screen();
        ~Screen();

        void run();
        void handleEvents();
        void draw();

    protected:

    private:
        sf::RenderWindow m_window;
};

#endif // SCREEN_H
