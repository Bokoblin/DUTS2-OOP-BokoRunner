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
const string SettingsModel::getPlayerSkin() const { return m_appCore->getPlayerSkin(); }
bool SettingsModel::isMenuMusicEnabled() const { return m_appCore->isMenuMusicEnabled(); }
bool SettingsModel::isGameMusicEnabled() const { return m_appCore->isGameMusicEnabled(); }
bool SettingsModel::isMorphBallSkinAvailable() const { return m_morphBallSkinIsAvailable; }
bool SettingsModel::isPokeballSkinAvailable() const { return m_pokeballSkinIsAvailable; }


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
 * Changes player skin
 * @author Arthur
 * @date 20/05/16
 *
 * @param skin the new skin
 */
void SettingsModel::changePlayerSkin(const string& skin)
{
    m_appCore->setPlayerSkin(skin);
}


/**
 * Checks all customization items availability
 * @author Arthur
 * @date 21/05/16 - 31/10/17
 */
void SettingsModel::checkItemsAvailability()
{
    m_morphBallSkinIsAvailable = m_appCore->findActivatedItem("shop_morphball_skin");
    m_pokeballSkinIsAvailable = m_appCore->findActivatedItem("shop_pokeball_skin");
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
