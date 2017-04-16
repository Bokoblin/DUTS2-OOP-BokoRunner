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

#ifndef SHOP_DIALOG_H
#define SHOP_DIALOG_H

#include "Dialog.h"
#include "../model/ShopItem.h"


/**
 * The ShopDialog class adds a shop item to the dialog
 * @author Arthur
 * @date 16/04/17
 */
class ShopDialog : public Dialog
{
public:
    //=== CTORs / DTORs
    ShopDialog();
    ShopDialog(float x, float y, float width, float height, const TextHandler &textHandler, const std::string &context);
    ShopDialog(float x, float y, float width, float height, const TextHandler &textHandler,
               const std::string &context, ShopItem *item);

    ShopDialog(const Dialog& d)=delete;

    ~ShopDialog();

    //=== GETTERS
    ShopItem *getLinkedShopItem() const;

private:
    //=== ATTRIBUTES
    ShopItem *m_shopItem;
};

#endif
