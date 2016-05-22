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

#ifndef SHOPVIEW_H
#define SHOPVIEW_H

#include "View.h"
#include "Shop.h"
#include "ShopItemCard.h"
#include "Dialog.h"


/********************************************
    ShopView Class
*********************************************
    @author Arthur  @date 11/05 - 18/05
*********************************************/
class ShopView : public View
{
public:
    //=== CTORs / DTORs
    ShopView(float w, float h, sf::RenderWindow *window, Text * text);
    virtual ~ShopView();

    //=== GETTERS
    ShopItem* getCardItem( GraphicElement *elem) const;

    //=== SETTERS
    void setShopModel(Shop *model);

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;
    bool treatEvents( sf::Event event );
    void displayCards() const;
    void createCards();

private:
    //=== ATTRIBUTES
    Shop *m_shop;
    int m_currentIndicator;
    int m_totalIndicator;

    //Textures
    sf::Texture m_menuFormButtonsTexture;
    sf::Texture m_coinTexture;
    sf::Texture m_pageIndicatorTexture;

    //Graphic Elements
    GraphicElement *m_coinSprite;
    Button *m_homeFormButton;
    Button *m_pageIndicatorButton;
    Dialog *m_buyDialog;

    std::vector<ShopItemCard *> m_shopItemsCardArray;
    std::map<int, Button *> m_pageIndicators;
};


#endif
