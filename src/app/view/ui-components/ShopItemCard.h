/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include "libs/MDC-SFML/src/Button.h"
#include "libs/MDC-SFML/src/Color.h"
#include "app/model/menu-components/ShopItem.h"
#include "app/view/utils/ViewDefinitions.h"
#include "app/view/AppTextManager.h"

/**
 * The ShopItemCard class inherits mdsf::Sprite.
 * It defines a card for buying purpose.
 * This card has item title and content and a buy button
 * which action triggers a buying confirm dialog.
 *
 * @author Arthur
 * @date 16/05/16 - 04/01/18
 */
class ShopItemCard : public mdsf::Sprite
{
public:
    //=== CTORs / DTORs
    ShopItemCard(int id, ShopItem *item);
    ~ShopItemCard() override;

    //=== GETTERS
    int getId() const;
    mdsf::Button *getBuyButton() const;
    ShopItem *getItem() const;

    void sync() override;
    void syncWithButtonLabelRetrieval(mdsf::Button::label_retrieval_func_t func);
    void draw(sf::RenderWindow *window) const override;

private:
    //=== ATTRIBUTES
    int m_id;
    ShopItem *m_item;
    mdsf::Text m_title;
    mdsf::Text m_content;
    mdsf::Button *m_buyButton;
};

#endif
