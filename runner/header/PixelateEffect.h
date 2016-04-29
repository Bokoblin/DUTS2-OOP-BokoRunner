/* Copyright 2016 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef PIXELATEEFFECT_H
#define PIXELATEEFFECT_H

#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>


/********************************************
    GameView Class
*********************************************
    Inspired by an SFML shader example from
    official SFML github repository
*********************************************
    @author Arthur  @date 21/02 - 19/04
    @author Florian @date 21/02 - 3/03
*********************************************/
class Pixelate : public sf::Drawable
{
    public:

        Pixelate();
        ~Pixelate();

        void load(std::string image);
        void update(float time, float x, float y);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool onLoad(std::string image);

    private:
        bool m_isLoaded;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Shader m_shader;
};
#endif // PIXELATEEFFECT_H
