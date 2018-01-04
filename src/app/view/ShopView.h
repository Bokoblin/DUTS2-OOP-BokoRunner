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

#ifndef SHOP_VIEW_H
#define SHOP_VIEW_H

#include "AbstractView.h"
#include "../model/ShopModel.h"
#include "ShopItemCard.h"
#include "ShopDialog.h"
#include "../utils/DialogBuilder.h"
#include "../../libs/MDC-SFML/src/RadioButton.h"

/**
 * The ShopView class inherits AbstractView.
 * It is the view counterpart of the class ShopModel.
 * It handles the shop screen's rendering.
 *
 * @author Arthur
 * @date 11/05/16 - 29/12/17
 */
class ShopView : public AbstractView
{
public:
    //=== CTORs / DTORs
    ShopView(sf::RenderWindow *window, TextHandler *textHandler, ShopModel *shopModel);
    ~ShopView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    ShopModel *m_shop;
    int m_currentIndicator;
    int m_totalIndicator;

    //Graphic Elements
    mdsf::Sprite *m_coinSprite;
    mdsf::Button *m_homeFormButton;
    ShopDialog *m_buyDialog;

    //Containers
    std::vector<ShopItemCard *> m_shopItemCardsArray;
    std::map<int, mdsf::RadioButton *> m_pageIndicators;

    //=== METHODS
    void loadImages() override;
    void syncCards();
    void createCards();
};


#endif
