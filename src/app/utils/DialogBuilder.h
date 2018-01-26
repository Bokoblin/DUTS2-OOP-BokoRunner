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

#ifndef DIALOG_BUILDER_H
#define DIALOG_BUILDER_H

#include <string>
#include "libs/Logger/Logger.h"
#include "app/view/ShopDialog.h"

namespace sl = Bokoblin::SimpleLogger;

/**
 * The class DialogBuilder matches dialog title,
 * content, cancel button and ok button strings
 * from strings files with dialog context
 *
 * @author Arthur
 * @date 16/04/17 - 26/01/18
 */
class DialogBuilder
{
public:
    /**
     * Retrieves dialog content following context and localization
     *
     * @param dialog the concerned dialog
     * @param stringsFilename the strings filename for localization
     *
     * @author Arthur
     * @date 16/04/17 - 26/01/18
     */
    static void retrieveCorrespondingStrings(mdsf::Dialog *dialog, const std::string &stringsFilename)
    {
        if (dialog != nullptr)
        {
            std::string utf8_titleString;
            std::string utf8_contentString;
            std::string utf8_cancelString;
            std::string utf8_okString;

            if (dialog->getContext() == "shop_item_details")
            {
                ShopDialog *shopDialog = dynamic_cast<ShopDialog*>(dialog);
                utf8_titleString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "shop_dialog_title");
                utf8_contentString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "shop_dialog_content");
                utf8_contentString.replace(utf8_contentString.find("$NAME"), 5,
                                           shopDialog->getLinkedShopItem()->getName());
                utf8_contentString.replace(utf8_contentString.find("$PRICE"), 6,
                                           std::to_string(shopDialog->getLinkedShopItem()->getPrice()));
                utf8_cancelString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_cancel");
                utf8_okString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_ok");
            }
            else if (dialog->getContext() == "shop_buying_success")
            {
                utf8_contentString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "shop_dialog_success");
                utf8_okString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_ok");
            }
            else if (dialog->getContext() == "shop_buying_failure")
            {
                utf8_contentString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "shop_dialog_failure");
                utf8_okString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_ok");
            }
            else if (dialog->getContext() == "confirm_data_delete")
            {
                utf8_titleString = XMLPersistenceHelper::loadLabeledString(
                        stringsFilename, "confirm_data_delete_dialog_title");
                utf8_contentString = XMLPersistenceHelper::loadLabeledString(
                        stringsFilename, "confirm_data_delete_dialog_content");
                utf8_cancelString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_cancel");
                utf8_okString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_ok");
            }
            else if (dialog->getContext() == "confirm_leaderboard_delete")
            {
                utf8_titleString = XMLPersistenceHelper::loadLabeledString(
                        stringsFilename, "confirm_leaderboard_delete_dialog_title");
                utf8_contentString = XMLPersistenceHelper::loadLabeledString(
                        stringsFilename, "confirm_leaderboard_delete_dialog_content");
                utf8_cancelString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_cancel");
                utf8_okString = XMLPersistenceHelper::loadLabeledString(stringsFilename, "dialog_ok");
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
