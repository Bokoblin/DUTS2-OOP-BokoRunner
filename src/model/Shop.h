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

#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include "ShopItem.h"
#include "AbstractModel.h"

/**
 * The Shop class is the model of ShopView class
 * It fetches the list of available to buy items
 * @author Arthur
 * @date 11/05/16 - 03/11/17
 */
class Shop : public AbstractModel
{
public:
    //=== CTORs / DTORs
    Shop(DataBase *dataBase);
    virtual ~Shop() override;

    //=== GETTERS
    std::vector<ShopItem*> getShopItemsArray() const;

    //=== METHODS
    bool buyItem(ShopItem *item);
    virtual void nextStep() override;
    void quit();

private:
    //=== ATTRIBUTES
    std::vector<ShopItem*> m_shopItemsArray;

    //=== METHODS
    void fetchBuyableItemsFromFile();
};

#endif
