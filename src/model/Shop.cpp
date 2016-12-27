#include "Shop.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 11/05 - 27/12
 */
Shop::Shop(DataBase *dataBase) :  AbstractModel(dataBase)
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
 * Fetch Shop Items from file
 * @author Arthur
 * @date 11/05 - 24/10
 */
void Shop::fetchBuyableItemsFromFile()
{
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

/**
 * Next Step
 * @author Arthur
 * @date 27/12
 */
void Shop::nextStep()
{}