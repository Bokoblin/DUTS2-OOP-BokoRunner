#include "PixelShader.h"

using namespace std;


/**
 * Default Constructor
 * @author Arthur
 * @date 28/04/16
 */
PixelShader::PixelShader() : m_isLoaded(false)
{ }


/**
 * Destructor
 * @author Arthur
 * @date 28/04/16
 */
PixelShader::~PixelShader()
{ }


/**
 * Load if shader available
 * @author Arthur
 * @date 28/04/16
 */
void PixelShader::load(const string &image)
{
    m_isLoaded = sf::Shader::isAvailable() && onLoad(image);
}


/**
 * Action linked to load
 * @author Arthur
 * @date 28/04/16
 */
bool PixelShader::onLoad(const string &image)
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
void PixelShader::update(float x, float y)
{
    if (m_isLoaded)
        m_shader.setParameter("pixel_threshold", (x + y) / 30);
}


/**
 * Draw function
 * @author Arthur
 * @date 28/04/16
 */
void PixelShader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_isLoaded)
    {
        states.shader = &m_shader;
        target.draw(m_sprite, states);
    }
}
