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

#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include "ShopItem.h"
#include "AbstractModel.h"

/**
 * The ShopModel class inherits AbstractModel.
 * It is the model counterpart of the class ShopView.
 * It handles the shop screen's logic.
 * It fetches the list of selling-available items.
 *
 * @author Arthur
 * @date 11/05/16 - 29/12/17
 */
class ShopModel : public AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit ShopModel(AppCore *appCore);
    ~ShopModel() override;

    //=== GETTERS
    std::vector<ShopItem*> getShopItemsArray() const;

    //=== METHODS
    bool buyItem(ShopItem *item);
    void nextStep() override;
    void quit();

private:
    //=== ATTRIBUTES
    std::vector<ShopItem*> m_shopItemsArray;

    //=== METHODS
    void fetchBuyableItemsFromFile();
};

#endif
