#include "Shop.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur  @date 11/05 - 16/05
 */
Shop::Shop(DataBase *data) :  m_dataBase{data}
{
    fetchBuyableItemsFromFile();
}


/**
 * Destructor
 * @author Arthur
 * @date 11/05 - 18/05
 */
Shop::~Shop()
{
    for (ShopItem *si: m_shopItemsArray)
        delete si;
}


//=== Getters

vector<ShopItem*> Shop::getShopItemsArray() const { return m_shopItemsArray; }


/**
 * Buy items
 * @author Arthur
 * @date 11/05 - 24/10
 */
bool Shop::buyItem(ShopItem *my_item)
{
    if ( !my_item->getBoughtState() && my_item->getPrice() <= m_dataBase->getTotalCoinsNumber() )
    {
        //=== update objects

        m_dataBase->setTotalCoinsCollected( -my_item->getPrice() );
        my_item->setBoughtState(true);

        //=== update config files

        pugi::xml_document doc;
        doc.load_file(CONFIG_FILE.c_str());

        pugi::xml_node runner = doc.child("runner");
        pugi::xml_node shop = runner.child("shop");

        for (pugi::xml_node shopItem: shop.children("shopItem"))
        {
            if ( string(shopItem.attribute("name").value()) == my_item->getName()  )
            {
                pugi::xml_attribute state = shopItem.attribute("boughtState");
                state.set_value(true);
                doc.save_file(CONFIG_FILE.c_str());
            }
        }
        return true;
    }
    else
        return false;
}


/**
 * String cast function
 * @author Arthur
 * @date 14/05
 */
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

/**
 * Fetch Shop Items from file
 * @author Arthur  @date 11/05 - 24/10
 */
void Shop::fetchBuyableItemsFromFile() {
    string result_value = "";
    string name = "";
    string desc = "";
    int price = 0;

    //open file with pugi library and init nodes
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node shop = doc.child("runner").child("shop");

    for (pugi::xml_node shopItem: shop.children("shopItem"))
    {
        //update item's attributes
        bool state = false;
        std::stringstream ss;
        name = shopItem.attribute("name").value();
        desc = shopItem.attribute("description").value();
        result_value = shopItem.attribute("price").value();
        ss << result_value;
        ss >> price;
        result_value = shopItem.attribute("boughtState").value();
        if (result_value == "true" ) state=true;

        //add item to array
        m_shopItemsArray.push_back( new ShopItem(name, desc, price, state) );
    }
}
