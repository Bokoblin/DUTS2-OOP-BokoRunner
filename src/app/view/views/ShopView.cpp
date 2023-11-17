#include "ShopView.h"
#include <math.h>

using Bokoblin::SimpleLogger::Logger;
namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

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
    ShopView::loadSprites();
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

    m_coinSprite = new mdsf::Image(0.45f * m_width, 0.2f * m_height, COIN_SIZE, COIN_SIZE);
    m_coinSprite->loadAndApplyTextureFromFile(ViewResources::BONUS_IMAGE, sf::IntRect(0, 0, 50, 50));
    m_coinSprite->resize(COIN_SIZE, COIN_SIZE);

    //=== Initialize HOME buttons

    m_homeButton = new mdsf::RaisedButton(10, 10, DEFAULT_HOME_SIZE, DEFAULT_HOME_SIZE, "", ViewResources::HOME_IMAGE);
    m_homeButton->resize(HOME_BTN_SIZE);
}

/**
 * Create Cards ans Indicators
 *
 * @author Arthur
 * @date 16/05/16 - 03/05/2020
 */
void ShopView::createCards()
{
    //=== Create Item Cards
    int i = 0;
    for (ShopItem* item : m_shop->getShopItemsArray()) {
        ShopItemCard* card = new ShopItemCard(i, item, m_width, m_height, CARDS_PER_PAGE);
        card->syncWithButtonLabelRetrieval(LocalizationManager::fetchLocalizedString);
        card->setVisible(false); //to display by pages
        m_shopItemCardsArray.push_back(card);
        i++;
    }

    //=== Create Pages Indicator

    unsigned int pageNumber = (unsigned int) (ceil(1.0 * m_shop->getShopItemsArray().size() / CARDS_PER_PAGE));

    for (unsigned int j = 0; j < pageNumber; j++) {
        m_pageIndicators[j] = new mdsf::RadioButton(
                getHalfXPosition() - (HALF_POSITION_OFFSET * pageNumber) + (INDICATOR_DIAMETER + INDICATOR_PADDING) * j,
                0.92f * m_height, 50, INDICATOR_DIAMETER, "", ViewResources::PAGE_INDICATOR_IMAGE);
    }
}


/**
 * Syncs cards and Shows/hides them
 * depending on the current page
 *
 * @author Arthur
 * @date 16/05/2016 - 02/07/2020
 */
void ShopView::syncCards()
{
    //display only cards linked to the current page indicator
    for (ShopItemCard* card : m_shopItemCardsArray) {
        card->sync();
        card->setVisible(card->getId() / CARDS_PER_PAGE == m_currentIndicator);
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
 * @date 16/05/2016 - 05/07/2020
 */
void ShopView::draw() const
{
    m_window->clear(AppColor::CoalMine);

    //=== Graphic Elements drawing

    for (ShopItemCard* card : m_shopItemCardsArray)
        m_window->draw(*card);

    for (const auto& it : m_pageIndicators)
        m_window->draw(*it.second);

    m_window->draw(*m_homeButton);
    m_window->draw(*m_coinSprite);
    m_window->draw(*m_buyDialog);

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
 * @date 16/05/16 - 13/01/19
 */
bool ShopView::handleEvents(sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        if (!m_buyDialog->isVisible()) {
            m_homeButton->setPressed(EventUtils::isMouseInside(*m_homeButton, event));

            for (auto& it : m_pageIndicators) {
                if (EventUtils::isMouseInside(*it.second, event)) {
                    it.second->setPressed(true);
                    break;
                }
            }

            for (auto& card : m_shopItemCardsArray) {
                if (EventUtils::isMouseInside(*card->getBuyButton(), event)
                        && card->isVisible() && !m_buyDialog->isVisible()) {
                    card->getBuyButton()->setPressed(true);
                    break;
                }
            }
        }
    }

    if (EventUtils::wasMouseReleased(event)) {
        //=== Reset buttons

        m_homeButton->setPressed(false);
        for (auto& card : m_shopItemCardsArray)
            card->getBuyButton()->setPressed(false);
        for (auto& it : m_pageIndicators)
            it.second->setPressed(false);

        //=== handle mouse up on a button

        if (!m_buyDialog->isVisible()) {
            if (EventUtils::isMouseInside(*m_homeButton, event)) {
                m_shop->quit();
                return false;
            }

            for (auto& it : m_pageIndicators) {
                if (EventUtils::isMouseInside(*it.second, event)) {
                    m_currentIndicator = it.first;
                }
            }

            for (auto& card : m_shopItemCardsArray) {
                if (EventUtils::isMouseInside(*card->getBuyButton(), event)
                        && card->isVisible() && !card->getItem()->isBought()) {
                    delete m_buyDialog;
                    m_buyDialog = new ShopDialog(
                            getDialogXPosition(ITEM_DIALOG_WIDTH), getDialogYPosition(ITEM_DIALOG_HEIGHT),
                            ITEM_DIALOG_WIDTH, ITEM_DIALOG_HEIGHT, "shop_item_details", card->getItem());
                    DialogBuilder::retrieveCorrespondingStrings(m_buyDialog);
                    m_buyDialog->setVisible();
                }
            }
        } else {
            if (EventUtils::isMouseInside(m_buyDialog->getOkButtonText(), event)) {
                processBuyItemConfirmAction();
            } else if (EventUtils::isMouseInside(m_buyDialog->getCancelButtonText(), event)
                    || !EventUtils::isMouseInside(*m_buyDialog, event)) {
                m_buyDialog->setVisible(false);
            }
        }
    }

    if (EventUtils::wasKeyboardEscapePressed(event)) {
        m_buyDialog->setVisible(false);
    }

    return true;
}

/**
 * Handles the Ok button of the shop item confirm
 *
 * @author Arthur
 * @date 06/09/18
 */
void ShopView::processBuyItemConfirmAction()
{
    if (m_buyDialog->getContext() == "shop_item_details") {
        ShopItem* shopItem = dynamic_cast<ShopDialog*>(m_buyDialog)->getLinkedShopItem();

        delete m_buyDialog;
        //TODO [MDC-CPP] As we initialize dialog with a new it can be added to an item group instead of declared in header file

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
        m_buyDialog->setVisible(false);
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
