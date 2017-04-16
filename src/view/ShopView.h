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

#include "AbstractView.h"
#include "../model/Shop.h"
#include "ShopItemCard.h"
#include "ShopDialog.h"
#include "RadioButton.h"


/**
 * ShopView Class
 * @author Arthur
 * @date 11/05/16 - 02/01/17
 */
class ShopView : public AbstractView
{
public:
    //=== CTORs / DTORs
    ShopView(sf::RenderWindow *window, TextHandler *textHandler, Shop *shopModel);
    virtual ~ShopView();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents(sf::Event event) override;
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
    ShopDialog *m_buyDialog;

    //Containers
    std::vector<ShopItemCard *> m_shopItemCardsArray;
    std::map<int, RadioButton *> m_pageIndicators;
};


#endif
