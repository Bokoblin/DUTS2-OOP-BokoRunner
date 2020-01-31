/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#include "libs/MDC-SFML/src/RadioButton.h"
#include "libs/MDC-SFML/src/RaisedButton.h"
#include "app/model/models/ShopModel.h"
#include "app/view/ui-components/ShopDialog.h"
#include "app/view/ui-components/ShopItemCard.h"
#include "app/view/utils/DialogBuilder.h"
#include "AbstractView.h"

/**
 * The ShopView class inherits AbstractView.
 * It is the view counterpart of the class ShopModel.
 * It handles the shop screen's rendering.
 *
 * @author Arthur
 * @date 11/05/16 - 13/01/19
 */
class ShopView: public AbstractView
{
public:
    //=== CTORs / DTORs
    ShopView(sf::RenderWindow* window, AppTextManager* textManager, ShopModel* shopModel);
    ~ShopView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event& event) override;

private:
    //=== ATTRIBUTES
    ShopModel* m_shop;
    int m_currentIndicator;

    //Graphic Elements
    mdsf::Sprite* m_coinSprite;
    mdsf::RaisedButton* m_homeButton;
    mdsf::Dialog* m_buyDialog; //TODO [MDC-CPP] to delete with drawableList

    //Containers
    std::vector<ShopItemCard*> m_shopItemCardsArray;
    std::map<int, mdsf::RadioButton*> m_pageIndicators;

    //=== METHODS
    void loadSprites() override;
    void syncCards();
    void createCards();
    void processBuyItemConfirmAction();
    float getDialogXPosition(int width) const;
    float getDialogYPosition(int height) const;

    //=== CONSTANTS
    const int CARDS_PER_PAGE = 3; //NOTE: Current screen ratio supports values from 1 to 3 (0 forbidden)
    const int ITEM_DIALOG_WIDTH = 250;
    const int ITEM_DIALOG_HEIGHT = 200;
    const int CONFIRM_DIALOG_WIDTH = 250;
    const int CONFIRM_DIALOG_HEIGHT = 100;
    const int COIN_SIZE = 25;
    const int HALF_POSITION_OFFSET = 10;
    const int INDICATOR_PADDING = 2;
    const int INDICATOR_DIAMETER = 22;
    const int HOME_BUTTON_SIZE = 30;
};

#endif
