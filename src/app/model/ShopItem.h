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

#ifndef SHOP_ITEM_H
#define SHOP_ITEM_H

#include <string>

/**
 * The ShopItem class
 * contains information on buyable items from shop.
 * Each item has a name, a description, a price
 * and a state to check if it has already been bought
 * @author Arthur
 * @date 11/05/16 - 04/02/17
 */
class ShopItem
{
public:
    //=== CTORs / DTORs
    ShopItem(const std::string &id, const std::string &name, const std::string &description, int price, bool state);
    ~ShopItem();

    //=== GETTERS
    std::string getId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getPrice() const;
    bool isBought() const;

    //=== SETTERS
    void buy();

private:
    //=== ATTRIBUTES
    std::string m_id;
    std::string m_name;
    std::string m_description;
    int m_price;
    bool m_isBought;
};

#endif
