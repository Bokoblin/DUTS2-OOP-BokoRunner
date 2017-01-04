#include "ShopItem.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 11/05/16
 */
ShopItem::ShopItem(string name, string description, int price, bool state) :
    m_name{name}, m_description{description}, m_price{price}, m_isBought{state}
{ }


/**
 * Destructor
 * @author Arthur
 * @date 11/05/16
 */
ShopItem::~ShopItem()
{ }


//=== Getters

string ShopItem::getId() const { return m_id; }
string ShopItem::getName() const { return m_name; }
string ShopItem::getDescription() const { return m_description; }
int ShopItem::getPrice() const { return m_price; }
bool ShopItem::isBought() const { return m_isBought; }


//=== Setters

void ShopItem::buy() { m_isBought = true; }