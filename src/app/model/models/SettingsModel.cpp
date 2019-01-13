#include "SettingsModel.h"

using std::string;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a Settings model with app core
 *
 * @param appCore the app's core singleton
 *
 * @author Arthur
 * @date 20/05/16 - 04/02/18
 */
SettingsModel::SettingsModel(AppCore* appCore) : AbstractModel(appCore), m_currentPage{CONFIG}
{
    PersistenceManager::fetchActivatedBonus();
    checkItemsAvailability();
}


/**
 * Destructor
 * @author Arthur
 * @date 20/05/16
 */
SettingsModel::~SettingsModel() = default;


//------------------------------------------------
//          GETTERS
//------------------------------------------------

int SettingsModel::getCurrentPage() const { return m_currentPage; }
const string SettingsModel::getLanguage() const { return m_appCore->getLanguage(); }
int SettingsModel::getGameDifficulty() const { return m_appCore->getDifficulty(); }
const string SettingsModel::getPlayerSkin() const { return m_appCore->getBallSkin(); }
bool SettingsModel::isMenuMusicEnabled() const { return m_appCore->isMenuMusicEnabled(); }
bool SettingsModel::isGameMusicEnabled() const { return m_appCore->isGameMusicEnabled(); }
bool SettingsModel::isMorphSkinAvailable() const { return m_morphSkinIsAvailable; }
bool SettingsModel::isCapsuleSkinAvailable() const { return m_capsuleSkinIsAvailable; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void SettingsModel::setCurrentPage(int page) { m_currentPage = page; }
void SettingsModel::setGameDifficulty(const Difficulty& difficulty) { m_appCore->setDifficulty(difficulty); }
void SettingsModel::toggleGameMusic() { m_appCore->toggleGameMusic(); }
void SettingsModel::toggleMenuMusic() { m_appCore->toggleMenuMusic(); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Changes app language
 * @author Arthur
 * @date 16/05/16
 *
 * @param language the new language
 */
void SettingsModel::changeLanguage(const string& language)
{
    m_appCore->setLanguage(language);
}

/**
 * Changes ball skin
 * @author Arthur
 * @date 20/05/16
 *
 * @param skin the new skin
 */
void SettingsModel::changeBallSkin(const string& skin)
{
    m_appCore->setBallSkin(skin);
}


/**
 * Checks all customization items availability
 * @author Arthur
 * @date 21/05/16 - 31/10/17
 */
void SettingsModel::checkItemsAvailability()
{
    m_morphSkinIsAvailable = m_appCore->findActivatedItem("shop_morphing");
    m_capsuleSkinIsAvailable = m_appCore->findActivatedItem("shop_capsule");
}


/**
 * Next Step
 * @author Arthur
 * @date 29/01
 */
void SettingsModel::nextStep()
{}


/**
 * Quits settings by saving configuration
 *
 * @author Arthur
 * @date 03/11/17
 */
void SettingsModel::quit()
{
    PersistenceManager::updatePersistence();
}

/**
 * Clears all the application data
 *
 * @author Arthur
 * @date 30/10/18
 */
void SettingsModel::clearAppData()
{
    m_appCore->clearAppData();
}
