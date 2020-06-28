/* Copyright 2016-2018 Jolivet Arthur

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

#ifndef MDC_SFML_DIALOG_H
#define MDC_SFML_DIALOG_H

#include "utils/Color.h"
#include "Sprite.h"
#include "Text.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Dialog class inherits Sprite.
 * It allows to create modal dialogs
 * containing a title, a content and up to two buttons.
 *
 * @author Arthur
 * @date 16/05/16 - 26/09/18
 *
 * @see Sprite
 * @see Text
 */
class Dialog : public Sprite
{
public:
    //=== CTORs / DTORs
    Dialog();
    Dialog(float x, float y, float width, float height, const std::string &context);
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

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
