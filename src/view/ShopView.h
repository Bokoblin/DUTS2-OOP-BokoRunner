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

#ifndef SHOP_VIEW_H
#define SHOP_VIEW_H

#include "View.h"
#include "../model/Shop.h"
#include "ShopItemCard.h"
#include "Dialog.h"
#include "RadioButton.h"


/**
 * ShopView Class
 * @author Arthur
 * @date 11/05/16 - 02/01/17
 */
class ShopView : public View
{
public:
    //=== CTORs / DTORs
    ShopView(float w, float h, sf::RenderWindow *window, TextHandler *textHandler);
    ~ShopView() override;

    //=== SETTERS
    void setShopModel(Shop *model);

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    void loadImages() override;
    bool treatEvents() override;
    bool treatEvents( sf::Event event );
    void syncCards() const;
    void createCards();

private:
    //=== ATTRIBUTES
    Shop *m_shop;
    int m_currentIndicator;
    int m_totalIndicator;

    //Graphic Elements
    GraphicElement *m_coinSprite;
    Button *m_homeFormButton;
    Dialog *m_buyDialog;

    //Containers
    std::vector<ShopItemCard *> m_shopItemCardsArray;
    std::map<int, RadioButton *> m_pageIndicators;
};


#endif