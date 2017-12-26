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
#include "../utils/definitions.h"

/**
 * The dialog class allows to create dialogs
 * with a title, a content and up to two buttons
 * @author Arthur
 * @date 16/05/16 - 16/04/17
 */
class Dialog : public GraphicElement
{
public:
    //=== CTORs / DTORs
    Dialog();
    Dialog(float x, float y, float w, float h, const TextHandler &textHandler, const std::string &context);
    Dialog(const Dialog& d)=delete;
    ~Dialog() override;

    //=== GETTERS
    const std::string &getContext() const;
    const Text &getCancelButtonText() const;
    const Text &getOkButtonText() const;

    //=== SETTERS
    void setTitleText(const std::string &title);
    void setContentText(const std::string &content);
    void setCancelButtonText(const std::string &cancel);
    void setOkButtonText(const std::string &ok);

    //=== METHODS
    void draw(sf::RenderWindow *window) const override;

protected:
    //=== ATTRIBUTES
    std::string m_context;
    Text m_title;
    Text m_content;
    Text m_cancelButtonText;
    Text m_okButtonText;
};

#endif
