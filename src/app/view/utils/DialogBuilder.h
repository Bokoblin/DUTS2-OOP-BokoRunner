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
#include "app/view/ui-components/ShopDialog.h"

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
     * Retrieves dialog content following context
     *
     * @param dialog the concerned dialog
     *
     * @author Arthur
     * @date 16/04/17 - 11/02/18
     */
    static void retrieveCorrespondingStrings(mdsf::Dialog *dialog)
    {
        if (dialog != nullptr)
        {
            std::string utf8_dialog_title;
            std::string utf8_dialog_content;
            std::string utf8_dialog_cancel;
            std::string utf8_dialog_ok;

            if (dialog->getContext() == "shop_item_details")
            {
                ShopDialog *shopDialog = dynamic_cast<ShopDialog*>(dialog);
                utf8_dialog_title = PersistenceManager::fetchLocalizedString("shop_dialog_title");
                utf8_dialog_content = PersistenceManager::fetchLocalizedString("shop_dialog_content");
                utf8_dialog_content.replace(utf8_dialog_content.find("$NAME"), 5,
                                            shopDialog->getLinkedShopItem()->getName());
                utf8_dialog_content.replace(utf8_dialog_content.find("$PRICE"), 6,
                                            std::to_string(shopDialog->getLinkedShopItem()->getPrice()));
                utf8_dialog_cancel = PersistenceManager::fetchLocalizedString("dialog_cancel");
                utf8_dialog_ok = PersistenceManager::fetchLocalizedString("dialog_ok");
            }
            else if (dialog->getContext() == "shop_buying_success")
            {
                utf8_dialog_content = PersistenceManager::fetchLocalizedString("shop_dialog_success");
                utf8_dialog_ok = PersistenceManager::fetchLocalizedString("dialog_ok");
            }
            else if (dialog->getContext() == "shop_buying_failure")
            {
                utf8_dialog_content = PersistenceManager::fetchLocalizedString("shop_dialog_failure");
                utf8_dialog_ok = PersistenceManager::fetchLocalizedString("dialog_ok");
            }
            else if (dialog->getContext() == "confirm_data_delete")
            {
                utf8_dialog_title = PersistenceManager::fetchLocalizedString("confirm_data_delete_dialog_title");
                utf8_dialog_content = PersistenceManager::fetchLocalizedString("confirm_data_delete_dialog_content");
                utf8_dialog_cancel = PersistenceManager::fetchLocalizedString("dialog_cancel");
                utf8_dialog_ok = PersistenceManager::fetchLocalizedString("dialog_ok");
            }
            else if (dialog->getContext() == "confirm_leaderboard_delete")
            {
                utf8_dialog_title = PersistenceManager::fetchLocalizedString("confirm_leaderboard_delete_dialog_title");
                utf8_dialog_content = PersistenceManager::fetchLocalizedString("confirm_leaderboard_delete_dialog_content");
                utf8_dialog_cancel = PersistenceManager::fetchLocalizedString("dialog_cancel");
                utf8_dialog_ok = PersistenceManager::fetchLocalizedString("dialog_ok");
            }

            dialog->setTitleText(sf::String::fromUtf8(utf8_dialog_title.begin(), utf8_dialog_title.end()));
            dialog->setContentText(sf::String::fromUtf8(utf8_dialog_content.begin(), utf8_dialog_content.end()));
            dialog->setCancelButtonText(sf::String::fromUtf8(utf8_dialog_cancel.begin(), utf8_dialog_cancel.end()));
            dialog->setOkButtonText(sf::String::fromUtf8(utf8_dialog_ok.begin(), utf8_dialog_ok.end()));
        }
        else
            sl::Logger::printErrorOnConsole("NULL dialog passed in parameter");
    }
};

#endif
