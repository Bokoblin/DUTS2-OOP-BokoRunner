#include "ShopItem.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 11/05
*********************************************/
ShopItem::ShopItem(string name, string description, int price, bool state) :
    m_name{name}, m_description{description}, m_price{price}, m_isBought{state}
{ }


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 11/05
*********************************************/
ShopItem::~ShopItem()
{ }


/********************************************
    Getters
*********************************************
    @author Arthur  @date 13/05
*********************************************/
string ShopItem::getName() const { return m_name; }
string ShopItem::getDescription() const { return m_description; }
int ShopItem::getPrice() const { return m_price; }
bool ShopItem::getBoughtState() const { return m_isBought; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 13/05
*********************************************/
void ShopItem::setBoughtState(bool state) { m_isBought = state; }


/********************************************
    String cast function
*********************************************
    @author Arthur  @date 13/05 - 15/05
*********************************************/
string ShopItem::toString() const
{
    string result = "=== " + m_name + " ===\n";
    result += "Description : " + m_description + "\n";
    result += "Price : " + to_string(m_price) + "\n";
    if ( m_isBought == true)
        result += "Already bought ? YES\n";
    else
        result += "Already bought ? NO\n";

    return result;
}
