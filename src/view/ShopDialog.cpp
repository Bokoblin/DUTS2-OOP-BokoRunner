#include "ShopDialog.h"


ShopDialog::ShopDialog() : Dialog(), m_shopItem{nullptr}
{
    hide();
}


/**
 * Constructs a dialog with x and y coordinates,
 * a textHandler and a description
 * @author Arthur
 * @date 16/04/17
 */
ShopDialog::ShopDialog(float x, float y, float width, float height, const TextHandler &textHandler,
                       const std::string &context) :
        Dialog(x, y, width, height, textHandler, context), m_shopItem{nullptr}
{ }

/**
 * Constructs a dialog with x and y coordinates,
 * a shopItem, a textHandler and a description
 * @author Arthur
 * @date 16/04/17
 */
ShopDialog::ShopDialog(float x, float y, float width, float height, const TextHandler &textHandler,
                       const std::string &context, ShopItem *item) :
        Dialog(x, y, width, height, textHandler, context), m_shopItem{item}
{ }


/**
 * Destructor
 * @author Arthur
 * @date 16/04/17
 */
ShopDialog::~ShopDialog()
{}


//=== Getters
ShopItem *ShopDialog::getLinkedShopItem() const {return m_shopItem; }

