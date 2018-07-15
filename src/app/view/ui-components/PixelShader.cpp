#include "PixelShader.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Default Constructor
 * @author Arthur
 * @date 28/04/16
 */
PixelShader::PixelShader() : m_isLoaded(false)
{}


/**
 * Destructor
 * @author Arthur
 * @date 28/04/16
 */
PixelShader::~PixelShader() = default;


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Load if shader available
 *
 * @param image the image to apply effects on
 *
 * @author Arthur
 * @date 28/04/16
 */
void PixelShader::load(const std::string &image)
{
    m_isLoaded = sf::Shader::isAvailable() && onLoad(image);
}


/**
 * Action linked to load
 *
 * @author Arthur
 * @date 28/04/16 - 27/10/17
 */
bool PixelShader::onLoad(const std::string &image)
{
    if (!m_texture.loadFromFile(image))
        return false;
    m_sprite.setTexture(m_texture);

    // Load the shader
    if (!m_shader.loadFromFile("../res/shaders/pixel_shader.frag", sf::Shader::Fragment))
        return false;
    m_shader.setUniform("texture", sf::Shader::CurrentTexture);

    return true;
}


/**
 * Updates the effect
 *
 * @param x the x-axis intensity
 * @param y the y-axis intensity
 *
 * @author Arthur
 * @date 28/04/16 - 27/10/17
 */
void PixelShader::update(float x, float y)
{
    if (m_isLoaded)
    {
        m_shader.setUniform("pixel_threshold", (x + y) / 30);
    }
}


/**
 * Draws the effect on the rendering target
 *
 * @param target the rendering target
 * @param states current render states
 *
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
