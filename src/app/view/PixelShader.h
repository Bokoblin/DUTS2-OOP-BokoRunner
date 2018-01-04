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

/* ORIGINAL LICENCE :

SFML
----

SFML - Copyright (C) 2007-2015 Laurent Gomila - laurent@sfml-dev.org

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.



External libraries used by SFML
-------------------------------

* OpenAL-Soft is under the LGPL license
* libjpeg is public domain
* stb_image and stb_image_write are public domain
* freetype is under the FreeType license or the GPL license
* libogg is under the BSD license
* libvorbis is under the BSD license
* libflac is under the BSD license
*/

#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include "../../libs/MDC-SFML/src/Sprite.h"


/**
 * The PixelShader class creates
 * an animated pixelized effect on an image
 *
 * SFML shader example, from official SFML
 * github repository, Effect.cpp and Shader.cpp
 * altered and merged into this class, original
 * licence is included above
 *
 * @author Arthur
 * @date 26/04/16 - 16/04/17
 */
class PixelShader : public sf::Drawable
{
public:
    //=== CTORs / DTORs
    PixelShader();
    ~PixelShader() override;

    //=== METHODS
    void load(const std::string &image);
    void update(float x, float y);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool onLoad(const std::string &image);

private:
    //=== ATTRIBUTES
    bool m_isLoaded;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Shader m_shader;
};

#endif
