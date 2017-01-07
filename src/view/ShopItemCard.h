/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef SHOP_ITEM_CARD_H
#define SHOP_ITEM_CARD_H

#include "../model/ShopItem.h"
#include "Button.h"
#include "TextHandler.h"

#define RED_BUTTON_UP sf::IntRect( 0, 100, 150, 40)
#define GREEN_BUTTON_UP sf::IntRect(0, 178, 150, 43)
#define GREEN_BUTTON_DOWN sf::IntRect(151, 179, 150, 40)


/**
 * ShopItemCard Class
 * @author Arthur
 * @date 16/05 - 02/01/17
 */
class ShopItemCard : public GraphicElement
{
    public:
        //=== CTORs / DTORs
        ShopItemCard(int id, ShopItem *item, TextHandler *textHandler);
        ~ShopItemCard();

        //=== GETTERS
        int getId() const;
        Button *getBuyButton() const;
        ShopItem *getItem() const;

        //=== METHODS
        void loadImages();
        void sync(DataBase *dataBase);
        void draw(sf::RenderWindow *window) const;

    private:
        //=== ATTRIBUTES
        int m_id;
        ShopItem *m_item;
        Text m_title;
        Text m_content;
        Button *m_buyButton;
        Button *m_boughtButton;
};

#endif
