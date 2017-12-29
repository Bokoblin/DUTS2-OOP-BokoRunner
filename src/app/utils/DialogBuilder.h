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

#ifndef DIALOG_BUILDER_H
#define DIALOG_BUILDER_H

#include "../model/DataBase.h"
#include "../view/ShopDialog.h"
#include <string>
#include "../../libs/Logger/Logger.h"

namespace sl = Bokoblin::SimpleLogger;

/**
 * The class DialogBuilder matches dialog title,
 * content, cancel button and ok button strings
 * from strings files with dialog context
 *
 * @author Arthur
 * @date 16/04/17
 */
class DialogBuilder
{
public:
    static void retrieveCorrespondingStrings(mdsf::Dialog *dialog, const DataBase& dataBase)
    {
        if (dialog != nullptr)
        {
            std::string utf8_titleString;
            std::string utf8_contentString;
            std::string utf8_cancelString;
            std::string utf8_okString;
            if (dialog->getContext() == "shopAskDialog")
            {
                ShopDialog *shopDialog = dynamic_cast<ShopDialog*>(dialog);
                utf8_titleString = dataBase.loadTextFromIdentifier("shop_dialog_title");
                utf8_contentString = dataBase.loadTextFromIdentifier("shop_dialog_content");
                utf8_contentString.replace(utf8_contentString.find("$NAME"), 5,
                                           shopDialog->getLinkedShopItem()->getName());
                utf8_contentString.replace(utf8_contentString.find("$PRICE"), 6,
                                           std::to_string(shopDialog->getLinkedShopItem()->getPrice()));
                utf8_cancelString = dataBase.loadTextFromIdentifier("dialog_cancel");
                utf8_okString = dataBase.loadTextFromIdentifier("dialog_ok");
            }
            else if (dialog->getContext() == "shopSuccess")
            {
                utf8_titleString = "";
                utf8_contentString = dataBase.loadTextFromIdentifier("shop_dialog_success");
                utf8_cancelString = "";
                utf8_okString = dataBase.loadTextFromIdentifier("dialog_ok");
            }
            else if (dialog->getContext() == "shopFailure")
            {
                utf8_titleString = "";
                utf8_contentString = dataBase.loadTextFromIdentifier("shop_dialog_failure");
                utf8_cancelString = "";
                utf8_okString = dataBase.loadTextFromIdentifier("dialog_ok");
            }
            else if (dialog->getContext() == "confirm")
            {
                utf8_titleString = dataBase.loadTextFromIdentifier("confirm_dialog_title");
                utf8_contentString = dataBase.loadTextFromIdentifier("confirm_dialog_content");
                utf8_cancelString = dataBase.loadTextFromIdentifier("dialog_cancel");
                utf8_okString = dataBase.loadTextFromIdentifier("dialog_ok");
            }
            else
            {
                utf8_titleString = "";
                utf8_contentString = "";
                utf8_cancelString = "";
                utf8_okString = "";
            }
            dialog->setTitleText(sf::String::fromUtf8(utf8_titleString.begin(), utf8_titleString.end()));
            dialog->setContentText(sf::String::fromUtf8(utf8_contentString.begin(), utf8_contentString.end()));
            dialog->setCancelButtonText(sf::String::fromUtf8(utf8_cancelString.begin(), utf8_cancelString.end()));
            dialog->setOkButtonText(sf::String::fromUtf8(utf8_okString.begin(), utf8_okString.end()));
        }
        else
            sl::Logger::printErrorOnConsole("NULL dialog passed in parameter");
    }
};

#endif
