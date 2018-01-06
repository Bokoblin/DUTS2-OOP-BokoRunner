#include "ShopDialog.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

ShopDialog::ShopDialog() : Dialog(), m_shopItem{nullptr}
{
    hide();
}


/**
 * Constructs a dialog with coordinates, a size
 * a context and a shopItem
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param context the context to make a contextual dialog
 * @param item the shop item to link
 *
 * @author Arthur
 * @date 16/04/17
 */
ShopDialog::ShopDialog(float x, float y, float width, float height,
                       const std::string &context, ShopItem *item) :
        Dialog(x, y, width, height, context), m_shopItem{item}
{}


/**
 * Destructor
 * @author Arthur
 * @date 16/04/17
 */
ShopDialog::~ShopDialog() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

ShopItem *ShopDialog::getLinkedShopItem() const {return m_shopItem; }

