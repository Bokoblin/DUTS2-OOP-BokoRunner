#include "Shop.h"

using namespace std;

/**
 * Constructs a Settings model with database
 * @author Arthur
 * @date 11/05/16 - 16/05/16
 *
 * @param dataBase the common app's dataBase
 */
Shop::Shop(DataBase *dataBase) :  m_dataBase{dataBase}
{
    fetchBuyableItemsFromFile();
}


/**
 * Destructor
 * @author Arthur
 * @date 11/05/16 - 18/05/16
 */
Shop::~Shop()
{
    for (ShopItem *shopItem: m_shopItemsArray)
        delete shopItem;
}


//=== Getters
DataBase* Shop::getDataBase() const { return m_dataBase; }
vector<ShopItem*> Shop::getShopItemsArray() const { return m_shopItemsArray; }


/**
 * Buys items
 * @author Arthur
 * @date 11/05/16 - 04/01/17
 *
 * @param item the item to buy
 */
bool Shop::buyItem(ShopItem *item)
{
    if ( !item->isBought() && item->getPrice() <= m_dataBase->getWallet() )
    {
        //=== update objects

        m_dataBase->decreaseWallet(item->getPrice());
        item->buy();

        //=== update config files

        pugi::xml_document doc;
        doc.load_file(CONFIG_FILE.c_str());

        pugi::xml_node runner = doc.child("runner");
        pugi::xml_node shop = runner.child("shop");

        for (pugi::xml_node shopItem: shop.children("shopItem"))
        {
            if ( string(shopItem.attribute("id").value()) == item->getId()  )
            {
                shopItem.attribute("bought").set_value(true);
                doc.save_file(CONFIG_FILE.c_str());
            }
        }
        return true;
    }
    else
        return false;
}


/**
 * Fetches Shop Items from file
 * @author Arthur
 * @date 11/05/16 - 07/01/17
 */
void Shop::fetchBuyableItemsFromFile()
{
    //Opens config file with pugiXML library
    pugi::xml_document doc;
    doc.load_file(CONFIG_FILE.c_str());

    pugi::xml_node shop = doc.child("runner").child("shop");

    for (pugi::xml_node shopItem: shop.children("shopItem"))
    {
        //Updates item's attributes
        bool isBought = false;
        string id = shopItem.attribute("id").value();
        string name = m_dataBase->getTextValueFromStringsFile(id + "_name");
        string desc = m_dataBase->getTextValueFromStringsFile(id + "_desc");
        int price = atoi(shopItem.attribute("price").value());
        string result = shopItem.attribute("bought").value();
        if (result == "true" ) isBought=true;

        //Adds item to array
        m_shopItemsArray.push_back( new ShopItem(name, desc, price, isBought) );
    }
}