#include "PixelateEffect.h"

using namespace std;


/**
 * Default Constructor
 * @author Arthur
 * @date 28/04/16
 */
PixelateEffect::PixelateEffect() : m_isLoaded(false)
{ }


/**
 * Destructor
 * @author Arthur
 * @date 28/04/16
 */
PixelateEffect::~PixelateEffect()
{ }


/**
 * Load if shader available
 * @author Arthur
 * @date 28/04/16 - 10/04/17
 */
void PixelateEffect::load(const string &image)
{
    m_isLoaded = sf::Shader::isAvailable() && onLoad(image);
}


/**
 * Action linked to load
 * @author Arthur
 * @date 28/04/16
 */
bool PixelateEffect::onLoad(std::string image)
{
    if (!m_texture.loadFromFile(image))
        return false;
    m_sprite.setTexture(m_texture);

    // Load the shader
    if (!m_shader.loadFromFile("../res/pixelate.frag", sf::Shader::Fragment))
        return false;
    m_shader.setParameter("texture", sf::Shader::CurrentTexture);

    return true;
}


/**
 * Effect update
 * @author Arthur
 * @date 28/04/16
 */
void PixelateEffect::update(float x, float y)
{
    if (m_isLoaded)
        m_shader.setParameter("pixel_threshold", (x + y) / 30);
}


/**
 * Draw function
 * @author Arthur
 * @date 28/04/16
 */
void PixelateEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_isLoaded)
    {
        states.shader = &m_shader;
        target.draw(m_sprite, states);
    }
}
