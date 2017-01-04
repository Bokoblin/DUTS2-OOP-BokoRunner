#include "Shop.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur  @date 11/05/16 - 16/05/16
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
 * Buy items
 * @author Arthur
 * @date 11/05/16 - 04/01/17
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
 * Fetch Shop Items from file
 * @author Arthur
 * @date 11/05/16 - 04/01/17
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
        string name = getStringFromLangFile(id + "_name");
        string desc = getStringFromLangFile(id + "_desc");
        int price = atoi(shopItem.attribute("price").value());
        string result = shopItem.attribute("bought").value();
        if (result == "true" ) isBought=true;

        //Adds item to array
        m_shopItemsArray.push_back( new ShopItem(name, desc, price, isBought) );
    }
}


/**
 * Get language-adapted name and description
 * from language string file with item
 * @author Arthur
 * @date 04/01/17
 */
string Shop::getStringFromLangFile(string name)
{
    pugi::xml_document doc;
    doc.load_file(m_dataBase->getLanguageFile().c_str());

    pugi::xml_node resources = doc.child("resources");

    for (pugi::xml_node item: resources.children("string")) {
        if (string(item.attribute("name").value()) == name)
        {
            return item.attribute("value").value();
        }
    }
    return "unknown";
}