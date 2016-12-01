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

#ifndef SHOPITEMCARD_H
#define SHOPITEMCARD_H

#include "ImagesConstants.h"
#include "Button.h"
#include "../Model/ShopItem.h"
#include "Text.h"

#define HALF_WIDTH getGlobalBounds().width/2
#define RED_BUTTON_UP sf::IntRect( 0, 100, 150, 40)
#define GREEN_BUTTON_UP sf::IntRect(0, 178, 150, 43)
#define GREEN_BUTTON_DOWN sf::IntRect(151, 179, 150, 40)


/********************************************
    ShopItemCard Class
*********************************************
    @author Arthur  @date 16/05 - 18/05
*********************************************/
class ShopItemCard
{
    public:
        //=== CTORs / DTORs
        ShopItemCard(int id, ShopItem *item, Text *t);
        ~ShopItemCard();

        //=== GETTERS
        int getId() const;
        bool getShownState() const;
        Button *getBuyButton() const;
        ShopItem *getItem() const;

        //== SETTERS
        void setShownState( bool state);

        //=== METHODS
        void loadImages();
        void sync();
        void draw(sf::RenderWindow *window) const;

    private:
        //=== ATTRIBUTES
        int m_id;
        int m_posX, m_posY;
        int m_width = 200;
        int m_height = 300;
        bool m_shownState;

        ShopItem *m_item;
        Text *m_text;
        sf::Text m_name;
        sf::Text m_desc;
        sf::Text m_buyButtonContent;

        sf::Texture m_cardBackgroundTexture;
        sf::Texture m_rectButtonsTexture;

        GraphicElement *m_cardBackgroundSprite;
        Button *m_buyButton;
};

#endif
