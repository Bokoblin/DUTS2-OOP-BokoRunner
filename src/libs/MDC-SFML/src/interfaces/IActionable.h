/* Copyright 2020 Jolivet Arthur

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

#ifndef MDC_SFML_ACTIONABLE_H
#define MDC_SFML_ACTIONABLE_H

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * @interface IActionable
 * @details Defines actionable methods linked to mouse events
 *
 * @author Arthur
 * @date 28/06/2020 - 05/07/2020
 */
class IActionable
{
public:
    //=== DTOR
    virtual ~IActionable() = default;

    //=== GETTERS
    virtual bool isClicked() const = 0;
    virtual bool isEnabled() const = 0;
    virtual bool isHovered() const = 0;
    virtual bool isPressed() const = 0;

    //=== SETTERS
    virtual void setClicked(bool value = true) = 0;
    virtual void setEnabled(bool value = true) = 0;
    virtual void setHovered(bool value = true) = 0;
    virtual void setPressed(bool value = true) = 0;
    //TODO 5/07: Replace setHover by onHover ...
    //  The new function shall set the state but also if supported do a specific treatment
    //  This is needed by components that hold sub-components (such as the dialog and cards having buttons)

    //=== STATES
    const unsigned int CLICKED = 2798430122;
    const unsigned int ENABLED = 2794916800;
    const unsigned int HOVERED = 2806580354;
    const unsigned int PRESSED = 2807347427;
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
