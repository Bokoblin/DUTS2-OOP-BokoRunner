#include "../header/Shop.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 11/05 - 16/05
*********************************************/
Shop::Shop(DataBase *data) :  m_dataBase{data}
{
    m_dataBase->fetchBuyableItemsFromFile(m_shopItemsArray);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 11/05 - 18/05
*********************************************/
Shop::~Shop()
{
    for (ShopItem *si: m_shopItemsArray)
        delete si;
}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 16/05
*********************************************/
vector<ShopItem*> Shop::getShopItemsArray() const { return m_shopItemsArray; }


/********************************************
    Buy items
*********************************************
    @author Arthur  @date 11/05 - 18/05
*********************************************/
bool Shop::buyItem(ShopItem *my_item)
{
    if ( my_item->getBoughtState() == false && my_item->getPrice() <= m_dataBase->getTotalCoinsCollected() )
    {
        m_dataBase->setTotalCoinsCollected( -my_item->getPrice() );
        my_item->setBoughtState(true);
        m_dataBase->getActivatedItemsArray().push_back( my_item->getName() );

        pugi::xml_document doc;
        doc.load_file("Resources/config.xml");

        for (pugi::xml_node item: doc.child("runner").child("shop").children("item") )
        {
            if ( item.attribute("name").value() == my_item->getName()  )
            {
                pugi::xml_attribute state = item.attribute("boughtState");
                state.set_value(true);
                doc.save_file("Resources/config.xml");
                doc.save_file("Resources/.fragment_cache");
            }
        }
        return true;
    }
    else
        return false;
}


/********************************************
    String cast function
*********************************************
    @author Arthur  @date 14/05
*********************************************/
string Shop::toString() const
{
    string result = "== Shop content ==\n";
    result += " There are " + to_string(m_shopItemsArray.size() ) + " items :\n\n";
    for ( ShopItem *bi : m_shopItemsArray )
    {
        result += bi->toString();
    }

    return result;
}
