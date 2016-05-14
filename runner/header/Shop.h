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

#ifndef _SHOP_H
#define _SHOP_H

#include "ShopItem.h"
#include "DataModel.h"

/********************************************
    Shop Class
*********************************************
    @author Arthur  @date 11/05 - 14/05
*********************************************/
class Shop
{
public:
    //=== CTORs / DTORs
    Shop(DataModel *data);
    ~Shop();

    //=== METHODS
    bool buyItem(ShopItem *item);
    std::string toString() const;

private:
    //=== ATTRIBUTES
    DataModel *m_dataModel;

    std::set<ShopItem*> m_shopItemsArray;
};

#endif
