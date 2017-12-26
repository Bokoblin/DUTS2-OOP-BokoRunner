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
#include "../utils/definitions.h"

/**
 * ShopItemCard Class
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
class ShopItemCard : public GraphicElement
{
public:
    //=== CTORs / DTORs
    ShopItemCard(int id, ShopItem *item, TextHandler *textHandler);
    ~ShopItemCard() override;

    //=== GETTERS
    int getId() const;
    Button *getBuyButton() const;
    ShopItem *getItem() const;

    //=== METHODS
    void loadImages();
    void sync(DataBase *dataBase);
    void draw(sf::RenderWindow *window) const override;

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
