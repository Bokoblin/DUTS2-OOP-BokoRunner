#include "ShopView.h"
#include <math.h>

using Bokoblin::SimpleLogger::Logger;

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
ShopView::ShopView(sf::RenderWindow* window, AppTextManager* textManager, ShopModel* shopModel) :
        AbstractView(window, textManager), m_shop{shopModel}, m_currentIndicator{0}, m_buyDialog{nullptr}
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
    delete m_homeButton;
    delete m_buyDialog;

    for (auto& shopItemCard : m_shopItemCardsArray)
        delete shopItemCard;

    for (auto& it : m_pageIndicators)
        delete it.second;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the shop screen
 * @author Arthur
 * @date 16/05/16 - 17/09/18
 */
void ShopView::loadSprites()
{
    //=== Initialize COIN Sprite

    m_coinSprite = new mdsf::Sprite(0.45f * m_width, 0.2f * m_height, COIN_SIZE);
    m_coinSprite->loadAndApplyTextureFromImageFile(BONUS_IMAGE, sf::IntRect(0, 0, 50, 50));
    m_coinSprite->resize(COIN_SIZE, COIN_SIZE);

    //=== Initialize HOME buttons

    m_homeButton = new mdsf::RaisedButton(10, 10, DEFAULT_HOME_SIZE, DEFAULT_HOME_SIZE, HOME_IMAGE);
    m_homeButton->resize(HOME_BUTTON_SIZE, HOME_BUTTON_SIZE);
}

/**
 * Create Cards ans Indicators
 *
 * @author Arthur
 * @date 16/05/16 - 06/09/18
 */
void ShopView::createCards()
{
    //=== Create Item Cards
    int i = 0;
    for (ShopItem* item : m_shop->getShopItemsArray()) {
        ShopItemCard* card = new ShopItemCard(i, item, m_width, m_height, CARDS_PER_PAGE);
        card->syncWithButtonLabelRetrieval(LocalizationManager::fetchLocalizedString);
        card->hide(); //to display by pages
        m_shopItemCardsArray.push_back(card);
        i++;
    }

    //=== Create Pages Indicator

    unsigned int pageNumber = (unsigned int) (ceil(1.0 * m_shop->getShopItemsArray().size() / CARDS_PER_PAGE));

    for (unsigned int j = 0; j < pageNumber; j++) {
        m_pageIndicators[j] = new mdsf::RadioButton(
                getHalfXPosition() - (HALF_POSITION_OFFSET * pageNumber) + (INDICATOR_DIAMETER + INDICATOR_PADDING) * j,
                0.92f * m_height, INDICATOR_DIAMETER, "", PAGE_INDICATOR_IMAGE);
    }
}


/**
 * Syncs cards and Shows/hides them
 * depending on the current page
 *
 * @author Arthur
 * @date 16/05/16 - 06/09/18
 */
void ShopView::syncCards()
{
    //display only cards linked to the current page indicator
    for (ShopItemCard* card : m_shopItemCardsArray) {
        card->sync();
        if (card->getId() / CARDS_PER_PAGE == m_currentIndicator) {
            card->show();
        } else {
            card->hide();
        }
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
    m_homeButton->sync();
    m_textManager->syncMenuShopText();
    syncCards();

    for (auto& it : m_pageIndicators) {
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

    for (ShopItemCard* card : m_shopItemCardsArray)
        card->draw(m_window);

    for (const auto& it : m_pageIndicators)
        m_window->draw(*it.second);

    m_homeButton->draw(m_window);
    m_window->draw(*m_coinSprite);
    m_buyDialog->draw(m_window);

    //=== Standalone Text Drawing

    m_textManager->drawMenuShopText(m_window, static_cast<unsigned int>(m_shop->getShopItemsArray().size()));

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 16/05/16 - 22/09/18
 */
bool ShopView::handleEvents(sf::Event event)
{
    if (MOUSE_LEFT_PRESSED_EVENT) {
        if (!m_buyDialog->isVisible()) {
            m_homeButton->setPressed(m_homeButton->contains(MOUSE_POSITION));

            for (auto& it : m_pageIndicators) {
                if (it.second->contains(MOUSE_POSITION)) {
                    it.second->setPressed(true);
                    break;
                }
            }

            for (auto& card : m_shopItemCardsArray) {
                if (card->getBuyButton()->contains(MOUSE_POSITION)
                        && card->isVisible() && !m_buyDialog->isVisible()) {
                    card->getBuyButton()->setPressed(true);
                    break;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        //=== Reset buttons

        m_homeButton->setPressed(false);
        for (auto& card : m_shopItemCardsArray)
            card->getBuyButton()->setPressed(false);
        for (auto& it : m_pageIndicators)
            it.second->setPressed(false);

        //=== handle mouse up on a button

        if (!m_buyDialog->isVisible()) {
            if (m_homeButton->contains(MOUSE_POSITION)) {
                m_shop->quit();
                return false;
            }

            for (auto& it : m_pageIndicators) {
                if (it.second->contains(MOUSE_POSITION)) {
                    m_currentIndicator = it.first;
                }
            }

            for (auto& card : m_shopItemCardsArray) {
                if (card->getBuyButton()->contains(MOUSE_POSITION)
                        && card->isVisible() && !card->getItem()->isBought()) {
                    delete m_buyDialog;
                    m_buyDialog = new ShopDialog(
                            getDialogXPosition(ITEM_DIALOG_WIDTH), getDialogYPosition(ITEM_DIALOG_HEIGHT),
                            ITEM_DIALOG_WIDTH, ITEM_DIALOG_HEIGHT, "shop_item_details", card->getItem());
                    DialogBuilder::retrieveCorrespondingStrings(m_buyDialog);
                    m_buyDialog->show();
                }
            }
        } else {
            if (m_buyDialog->getOkButtonText().contains(MOUSE_POSITION)) {
                processBuyConfirmOkAction();
            } else if (m_buyDialog->getCancelButtonText().contains(MOUSE_POSITION)
                    || !m_buyDialog->contains(MOUSE_POSITION)) {
                m_buyDialog->hide();
            }
        }
    }

    return true;
}

/**
 * Handles the Ok button of the shop item confirm
 *
 * @author Arthur
 * @date 06/09/18
 */
void ShopView::processBuyConfirmOkAction()
{
    if (m_buyDialog->getContext() == "shop_item_details") {
        ShopItem* shopItem = dynamic_cast<ShopDialog*>(m_buyDialog)->getLinkedShopItem();

        delete m_buyDialog;
        //TODO: As we initialize dialog with a new it can be added to an item group instead of declared in header file

        const std::string operationResult = m_shop->buyItem(shopItem) ? "shop_buying_success" : "shop_buying_failure";

        m_buyDialog = new Bokoblin::MaterialDesignComponentsForSFML::Dialog(
                getDialogXPosition(CONFIRM_DIALOG_WIDTH), getDialogYPosition(CONFIRM_DIALOG_HEIGHT),
                CONFIRM_DIALOG_WIDTH, CONFIRM_DIALOG_HEIGHT, operationResult);
        DialogBuilder::retrieveCorrespondingStrings(m_buyDialog);

        if (operationResult == "shop_buying_success") {
            for (auto& card : m_shopItemCardsArray) {
                if (card->getItem() == shopItem) {
                    card->syncWithButtonLabelRetrieval(LocalizationManager::fetchLocalizedString);
                }
            }
        }
    } else {
        m_buyDialog->hide();
    }
}


/**
 * Get dialog X position from the dialog width
 *
 * @param width the dialog width
 * @return the X position
 *
 * @author Arthur
 * @date 06/09/18 - 16/09/18
 */
float ShopView::getDialogXPosition(int width) const
{
    return getHalfXPosition() - 0.5f * width;
}


/**
 * Get dialog Y position from the dialog height
 *
 * @param height the dialog height
 * @return the Y position
 *
 * @author Arthur
 * @date 06/09/18 - 16/09/18
 */
float ShopView::getDialogYPosition(int height) const
{
    return getHalfYPosition() - 0.5f * height;
}
