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

#ifndef DIALOG_H
#define DIALOG_H

#include "GraphicElement.h"
#include "TextHandler.h"
#include "../Model/ShopItem.h"
#include "../model/ShopItem.h"

#define MATERIAL_TEAL_COLOR sf::Color(0, 150, 136, 255)


/**
 * The dialog class allows to create dialogs
 * with a title, a content and up to two buttons
 * @author Arthur
 * @date 16/05/16 - 04/01/17
 */
class Dialog : public GraphicElement
{
public:
    //=== CTORs / DTORs
    Dialog();
    Dialog(float x, float y, float w, float h, ShopItem *item, TextHandler *textHandler, std::string description);
    Dialog(float x, float y, float w, float h, TextHandler *textHandler, std::string id);
    Dialog(const Dialog& d)=delete;
    ~Dialog();

    //=== GETTERS
    std::string getId() const;
    const Text& getCancelButtonText() const;
    const Text& getOkButtonText() const;
    ShopItem *getLinkedShopItem() const;

    //=== METHODS
    void sync(DataBase *dataBase);
    void draw(sf::RenderWindow *window) const;

private:
    //=== ATTRIBUTES
    std::string m_id;
    Text m_title;
    Text m_content;
    Text m_cancelButtonText;
    Text m_okButtonText;
    ShopItem *m_shopItem;
};

#endif
