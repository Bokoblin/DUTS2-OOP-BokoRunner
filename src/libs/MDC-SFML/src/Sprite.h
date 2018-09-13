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

#ifndef MDC_SFML_SPRITE_H
#define MDC_SFML_SPRITE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Config.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{

/**
 * The Sprite class inherits sf::Sprite.
 * It adds visibility, alpha and light control to a sprite. \n
 * It keeps the texture (and its filename) used to set sprite texture
 * for sync purpose in inherited classes.
 * Finally, it allows resize and position containing check.
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 11/09/18
 *
 * @see sf::Sprite
 */
class Sprite : public sf::Sprite
{
public:
    //=== CTORs / DTORs
    Sprite(float width, float height);
    Sprite(float x, float y, float width, float height);
    Sprite(float x, float y, float width, float height, const std::string &image);
    explicit Sprite(float size);
    Sprite(float x, float y, float size);
    Sprite(float x, float y, float size, const std::string &image);
    Sprite(Sprite const& other);
    ~Sprite() override;

    //=== GETTERS
    virtual float getX() const;
    virtual float getY() const;
    virtual float getWidth() const;
    virtual float getHeight() const;
    bool isVisible() const;
    int getAlpha() const;
    int getLight() const;
    std::string getTextureFileName() const;

    //=== SETTERS
    void setVisible(bool visible);
    void show();
    void hide();
    virtual void setAlpha(int alpha);
    virtual void setLight(int light);
    virtual void increaseAlpha(int alphaLevel);
    virtual void decreaseAlpha(int alphaLevel);
    virtual void increaseLight(int lightLevel);
    virtual void decreaseLight(int lightLevel);

    //=== METHODS
    virtual void sync();
    virtual void draw(sf::RenderWindow *window) const;

    virtual void resize(float width, float height);
    virtual void resize(float size);
    virtual bool contains(float x, float y) const;
    virtual void applyColor();

    virtual void loadAndApplyTextureFromImageFile(const std::string &imageFile);
    virtual void loadAndApplyTextureFromImageFile(const std::string &imageFile, sf::IntRect area);

protected:
    //=== ATTRIBUTES
    float m_width;
    float m_height;
    bool m_isVisible;
    sf::Uint8 m_alpha;
    sf::Uint8 m_light;
    sf::Texture m_texture;
    std::string m_textureFilename;

private:
    void processTextureLoading(const std::string &imageFile);
};

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin

#endif
