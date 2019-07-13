#include "Bonus.h"

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 *
 * @author Arthur
 * @date 11/04/2016
 */
Bonus::Bonus(float x, float y, float w, float h, float mvX, float mvY) :
        MovableElement(x, y, w, h, mvX, mvY)
{
    chooseBonusType();
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 11/04/2016
 */
Bonus::~Bonus() = default;

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Execute the move routine
 *
 * @author Arthur
 * @date 11/04/2016 - 11/07/2019
 */
void Bonus::move()
{
    m_posX -= 1;
}

/**
 * @brief Select the bonus type following probabilities
 * @details Here are the probabilities: \n
 *  1-30 : PV+    ~30% \n
 * 31-50 : MEGA   ~20% \n
 * 51-65 : FLY    ~15% \n
 * 66-75 : SLOW   ~10% \n
 * 76-100: SHIELD ~25%
 *
 * @author Arthur
 * @date 11/04/2016 - 10/02/2018
 */
void Bonus::chooseBonusType()
{
    int result = RandomUtils::getUniformRandomNumber(1, 100);

    if (result <= 30) {
        m_elementType = PV_PLUS_BONUS;
    } else if (result <= 50) {
        m_elementType = MEGA_BONUS;
    } else if (result <= 65) {
        m_elementType = FLY_BONUS;
    } else if (result <= 75) {
        m_elementType = SLOW_SPEED_BONUS;
    } else {
        m_elementType = SHIELD_BONUS;
    }
}

