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

#ifndef DIALOG_H
#define DIALOG_H

#include "GraphicElement.h"
#include <iostream>
#include "ShopItem.h"

#define HALF_WIDTH getGlobalBounds().width/2
#define MATERIAL_TEAL_COLOR sf::Color(0, 150, 136, 255)


/********************************************
    Constant Variables
********************************************/
const std::string REGULAR_FONT = "Resources/Roboto_Regular.ttf";
const std::string BOLD_FONT = "Resources/Roboto_Bold.ttf";
const std::string DIALOG_IMAGE = "Images/dialog.png";


/********************************************
    Dialog Class
*********************************************
    @author Arthur  @date 16/05 - 18/05
*********************************************/
class Dialog
{
    public:
        //=== CTORs / DTORs
        Dialog(int posX, int posY, ShopItem *item, std::string title, std::string content, std::string negAnswer, std::string posAnswer);
        Dialog(const Dialog& d)=delete;
        ~Dialog();

        //=== GETTERS
        const sf::Text& getNegativeButton() const;
        const sf::Text& getPositiveButton() const;
        ShopItem *getItemLinked() const;
        bool getOverridingState() const;

        //=== METHODS
        void draw(sf::RenderWindow *window) const;

    private:
        //=== ATTRIBUTES
        int m_posX, m_posY;
        int m_width = 250;
        int m_height = 200;
        ShopItem *m_itemLinked;

        sf::Texture m_dialogTexture;
        GraphicElement *m_dialogSprite;

        sf::Font *m_regularFont;
        sf::Font *m_boldFont;
        sf::Text m_dialogTitleLabel;
        sf::Text m_dialogContent;
        sf::Text m_negativeButton;
        sf::Text m_positiveButton;
};

#endif
