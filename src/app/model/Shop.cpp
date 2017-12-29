#include "Shop.h"

using std::string;
using std::stoi;
using std::vector;

/**
 * Constructs a Settings model with database
 * @author Arthur
 * @date 11/05/16 - 29/01/16
 *
 * @param dataBase the common app's dataBase
 */
Shop::Shop(DataBase *dataBase) :  AbstractModel(dataBase)
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
    if (!item->isBought() && item->getPrice() <= m_dataBase->getWallet())
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
            if (string(shopItem.attribute("id").value()) == item->getId())
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
 * @date 11/05/16 - 24/12/17
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
        string id = shopItem.attribute("id").value();
        string name = m_dataBase->loadTextFromIdentifier(id + "_name");
        string desc = m_dataBase->loadTextFromIdentifier(id + "_desc");
        int price = stoi(shopItem.attribute("price").value());
        bool isBought = ((string)shopItem.attribute("bought").value()) == "true";

        //Adds item to array
        m_shopItemsArray.push_back(new ShopItem(name, desc, price, isBought));
    }
}

/**
 * Next Step
 * @author Arthur
 * @date 29/01/17
 */
void Shop::nextStep()
{}


/**
 * Quits shop by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void Shop::quit()
{
    m_dataBase->pushConfigurationToFile();
}

