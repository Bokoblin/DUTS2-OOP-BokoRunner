#include "../header/Shop.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 11/05 - 14/05
*********************************************/
Shop::Shop(DataModel *data) :  m_dataModel{data}
{
    m_dataModel->fetchBuyableItemsFromFile(m_shopItemsArray);

    //Model Example - to remove with working view :

    cout << this->toString() << endl;
    cout << endl << "===================================" << endl << endl;

    if ( buyItem(*m_shopItemsArray.begin() ) == false)
        cout << "Item can't be bought ! (Not enough money or already bought item)" << endl;
    else
    {
        cout << "Item has been bought !" << endl;
    }
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 11/05
*********************************************/
Shop::~Shop()
{

}


/********************************************
    Buy items
*********************************************
    @author Arthur  @date 11/05 - 15/05
*********************************************/
bool Shop::buyItem(ShopItem *my_item)
{
    if ( my_item->getBoughtState() == false && my_item->getPrice() <= m_dataModel->getTotalCoinsCollected() )
    {
        m_dataModel->setTotalCoinsCollected( -my_item->getPrice() );
        my_item->setBoughtState(true);
        m_dataModel->getActivatedItemsArray().push_back( my_item->getName() );

        pugi::xml_document doc;
        doc.load_file("Resources/config.xml");

        for (pugi::xml_node item: doc.child("runner").child("shop").children("item") )
        {
            string name = my_item->getName();
            for (unsigned int i=0; i < name.size(); i++)
                if (name[i] == ' ') name[i] = '_';

            if ( item.attribute("name").value() == name  )
            {
                cout << "done" << endl;
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
