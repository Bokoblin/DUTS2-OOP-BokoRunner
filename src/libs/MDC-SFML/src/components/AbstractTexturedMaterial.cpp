#include "AbstractTexturedMaterial.h"

using std::string;
using std::to_string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs with a size and an optional image
 *
 * @param width the width
 * @param height the height
 * @param image the image used for the texture (optional)
 *
 * @author Arthur
 * @date 21/02/2016 - 06/07/2020
 */
AbstractTexturedMaterial::AbstractTexturedMaterial(float width, float height, const string& image) :
        AbstractMaterial(width, height), m_textureFilename{image}
{
    if (!image.empty()) {
        loadAndApplyTextureFromFile(image);
        //AbstractTexturedMaterial::resize(width, height); //This shall work with above func
    }
}

/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur, Florian
 * @date 25/02/2016 - 28/06/2020
 */
AbstractTexturedMaterial::AbstractTexturedMaterial(AbstractTexturedMaterial const& other) :
        AbstractMaterial(other), m_textureFilename{other.m_textureFilename}
{
}

//------------------------------------------------
//          METHODS
//------------------------------------------------
/**
 * Loads a texture from an image file
 * and applies it to the sprite on loading success
 *
 * @param file the source file
 * @param area the image area to use (optional)
 *
 * @author Arthur
 * @date 02/01/2017 - 13/01/2019
 */
void AbstractTexturedMaterial::loadAndApplyTextureFromFile(const string& file, const sf::IntRect& area)
{
    if (m_texture.loadFromFile(file, area)) {
        processTextureLoading(file);
    } else {
        Config::printError("Image loading failed for \"" + file + "\" and the area ("
                + to_string(area.left) + ", " + to_string(area.top) + ", "
                + to_string(area.width) + ", " + to_string(area.height) + ")");
    }
}

/**
 * Applies the texture to the sprite after loading success
 *
 * @param file the source file
 * @param area the image area to use
 *
 * @author Arthur
 * @date 04/01/2018 - 06/07/2020
 */
void AbstractTexturedMaterial::processTextureLoading(const string& file)
{
    m_textureFilename = file;
    m_texture.setSmooth(true);
    m_initialSize = sf::Vector2f(m_texture.getSize());

    m_states[NEED_RESIZE] = m_initialSize != m_size;
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
