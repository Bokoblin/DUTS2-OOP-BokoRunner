#include "ShopView.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the shop view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param shopModel the shop model counterpart
 *
 * @author Arthur
 * @date 16/05/16 - 29/01/17
 */
ShopView::ShopView(sf::RenderWindow *window, AppTextManager *textManager, ShopModel *shopModel) :
        AbstractView(window, textManager),
    m_shop{shopModel}, m_currentIndicator{0}, m_totalIndicator{0}, m_buyDialog{nullptr}
{
    loadSprites();
    createCards();
    m_buyDialog = new ShopDialog();
}


/**
 * Destructor
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
ShopView::~ShopView()
{
    delete m_coinSprite;
    delete m_homeFormButton;
    delete m_buyDialog;

    for (auto &shopItemCard : m_shopItemCardsArray)
        delete shopItemCard;

    for (auto &it : m_pageIndicators)
        delete it.second;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the shop screen
 * @author Arthur
 * @date 16/05/16 - 26/01/17
 */
void ShopView::loadSprites()
{
    //=== Initialize COIN Sprite

    m_coinSprite = new mdsf::Sprite(m_width/2-60, 53, 25, 25);
    m_coinSprite->loadAndApplyTextureFromImageFile(BONUS_IMAGE, sf::IntRect(0, 0, 50, 50));
    m_coinSprite->resize(25, 25);

    //=== Initialize HOME form buttons

    std::vector<sf::IntRect> clipRectHome;
    clipRectHome.emplace_back(0, 50, 50, 50);
    clipRectHome.emplace_back(51, 50, 50, 50);
    m_homeFormButton = new mdsf::Button(10, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectHome);
    m_homeFormButton->resize(FORM_BUTTONS_SIZE);
}

/**
 * Create Cards ans Indicators
 *
 * @author Arthur
 * @date 16/05/16 - 02/01/18
 */
void ShopView::createCards()
{
    //=== Create Item Cards
    int i = 0;
    for (ShopItem *item : m_shop->getShopItemsArray())
    {
        ShopItemCard *card = new ShopItemCard(i, item);
        card->syncWithButtonLabelRetrieval(m_shop->getAppCore()->getLanguageFile());
        card->hide(); //to display by pages
        m_shopItemCardsArray.push_back(card);
        i++;
    }

    //=== Create Pages Indicator

    m_totalIndicator = (int) (m_shop->getShopItemsArray().size() / 3);
    if (m_shop->getShopItemsArray().size()%3 != 0)
        m_totalIndicator++;

    for (int j=0; j < m_totalIndicator; j++)
    {
        m_pageIndicators[j] = new mdsf::RadioButton(0, 580, INDICATOR_DIAMETER, "indicator");
        m_pageIndicators[j]->setPosition(m_width/2 - 10*m_totalIndicator + 24*j, 550);
    }
}


/**
 * Syncs cards and Shows/hides them
 * depending on the current page
 *
 * @author Arthur
 * @date 16/05/16 - 02/01/17
 */
void ShopView::syncCards()
{
    //display only 3 cards linked to the current page indicator
    for (ShopItemCard *card : m_shopItemCardsArray)
    {
        card->sync();
        if(card->getId() == 0 + 3 * m_currentIndicator
            || card->getId() == 1 + 3 * m_currentIndicator
            || card->getId() == 2 + 3 * m_currentIndicator)
        {
            card->show();
        }
        else
            card->hide();
    }
}


/**
 * Synchronizes shop elements
 *
 * @author Arthur
 * @date 16/05/16 - 02/01/18
 */
void ShopView::synchronize()
{
    m_homeFormButton->sync();

    m_textManager->syncMenuShopText();

    syncCards();

    for (auto &it : m_pageIndicators)
    {
        (it.second)->sync();
        (it.second)->setSelected(it.first == m_currentIndicator);
    }
}


/**
 * Draws shop elements on the window
 *
 * @author Arthur
 * @date 16/05/16 - 24/01/17
 */
void ShopView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    for (ShopItemCard *card : m_shopItemCardsArray)
        card->draw(m_window);

    for (const auto &it : m_pageIndicators)
            m_window->draw(*it.second);
    m_window->draw(*m_homeFormButton);
    m_window->draw(*m_coinSprite);
    m_buyDialog->draw(m_window);

    //=== Standalone Text Drawing

    m_textManager->drawMenuShopText(m_window);

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 16/05/16 - 26/12/17
 */
bool ShopView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (!m_buyDialog->isVisible())
        {
            if (m_homeFormButton->contains(MOUSE_POSITION))
                m_homeFormButton->setPressed(true);

            for (auto &it : m_pageIndicators)
                if (it.second->contains(MOUSE_POSITION))
                    it.second->setPressed(true);

            for (auto &card : m_shopItemCardsArray)
                if (card->getBuyButton()->contains(MOUSE_POSITION)
                    && card->isVisible() && !m_buyDialog->isVisible())
                    card->getBuyButton()->setPressed(true);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        //=== Reset buttons

        m_homeFormButton->setPressed(false);
        for (auto &card : m_shopItemCardsArray)
            card->getBuyButton()->setPressed(false);
        for (auto &it : m_pageIndicators)
            it.second->setPressed(false);

        //=== handle mouse up on a button

        if (!m_buyDialog->isVisible())
        {
            if (m_homeFormButton->contains(MOUSE_POSITION))
            {
                m_shop->quit();
                return false;
            }

            for (auto &it : m_pageIndicators)
                if (it.second->contains(MOUSE_POSITION))
                    m_currentIndicator = it.first;

            for (auto &card : m_shopItemCardsArray)
                if (card->getBuyButton()->contains(MOUSE_POSITION)
                     && card->isVisible() && !card->getItem()->isBought())
                {
                    delete m_buyDialog;
                    m_buyDialog = new ShopDialog(m_width/2 - 125, m_height/2 - 100, 250, 200,
                                                 "shop_item_details", card->getItem());
                    DialogBuilder::retrieveCorrespondingStrings(m_buyDialog, m_shop->getAppCore()->getLanguageFile());
                    m_buyDialog->show();
                }
        }
        else
        {
            if (m_buyDialog->getOkButtonText().contains(MOUSE_POSITION))
            {
                if (m_buyDialog->getContext() == "shop_item_details")
                {
                    ShopItem *shopItem = dynamic_cast<ShopDialog *>(m_buyDialog)->getLinkedShopItem();

                    delete m_buyDialog; //TODO-1: As items are allocated with new we can allocate then in code
                    // TODO-2: and add them to a drawable item list to draw them instead of keeping a pointer from ctor

                    const std::string operationResult = m_shop->buyItem(shopItem)
                            ? "shop_buying_success" : "shop_buying_failure";
                    m_buyDialog = new mdsf::Dialog(m_width/2 - 125, m_height/2 - 50, 250, 100, operationResult);
                    DialogBuilder::retrieveCorrespondingStrings(m_buyDialog, m_shop->getAppCore()->getLanguageFile());

                    if (operationResult == "shop_buying_success")
                    {
                        for (auto &card : m_shopItemCardsArray)
                            if (card->getItem() == shopItem)
                                card->syncWithButtonLabelRetrieval(m_shop->getAppCore()->getLanguageFile());
                    }
                }
                else
                    m_buyDialog->hide();
            }
            else if (m_buyDialog->getCancelButtonText().contains(MOUSE_POSITION)
                 || !m_buyDialog->contains(MOUSE_POSITION))
            {
                m_buyDialog->hide();
            }
        }
    }

    return true;
}
