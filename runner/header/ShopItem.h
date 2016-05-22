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

#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <string>

/********************************************
    ShopItem Class
*********************************************
    @author Arthur  @date 11/05
*********************************************/
class ShopItem
{
    public:
        //=== CTORs / DTORs
        ShopItem(std::string name, std::string description, int price, bool state);
        ~ShopItem();

        //=== GETTERS
        std::string getName() const;
        std::string getDescription() const;
        int getPrice() const;
        bool getBoughtState() const;

        //=== SETTERS
        void setBoughtState(bool state);

        //=== METHODS
        std::string toString() const;

    private:
        //=== ATTRIBUTES
        std::string m_name;
        std::string m_description;
        int m_price;
        bool m_isBought;
};

#endif
