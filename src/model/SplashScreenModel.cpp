#include "SplashScreenModel.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 29/01/17 - 24/12/17
 */
SplashScreenModel::SplashScreenModel(DataBase *dataBase) :
    AbstractModel(dataBase), m_isContinueVisible{true}, m_inEndingPhase{false},
    m_lastTime{chrono::system_clock::now()},
    m_continueBlinkingMonitor{0}
{
    m_continueBlinkingMonitor = chrono::milliseconds(CONTINUE_VISIBLE_TIMEOUT);
}


/**
 * Destructor
 * @author Arthur
 * @date 29/01/17
 */
SplashScreenModel::~SplashScreenModel() = default;


//=== Getters
bool SplashScreenModel::isContinueVisible() const { return m_isContinueVisible; }
bool SplashScreenModel::isInEndingPhase() const { return m_inEndingPhase; }


//=== Setters
void SplashScreenModel::setEndingPhase(bool inEndingPhase) { m_inEndingPhase = inEndingPhase; }


/**
 * Next Step
 * @author Arthur
 * @date 29/01/17 - 24/12/17
 */
void SplashScreenModel::nextStep()
{
    chrono::system_clock::duration currentNextStepDelay = chrono::system_clock::now() - m_lastTime;
    chrono::system_clock::duration nextStepDelay = std::chrono::milliseconds(NEXT_STEP_DELAY);

    if (!m_inEndingPhase && currentNextStepDelay.count() > nextStepDelay.count())
    {
        if (m_continueBlinkingMonitor.count() <= chrono::milliseconds(0).count())
        {
            m_continueBlinkingMonitor = chrono::milliseconds(m_isContinueVisible
                    ? CONTINUE_HIDDEN_TIMEOUT
                    : CONTINUE_VISIBLE_TIMEOUT);
            m_isContinueVisible = !m_isContinueVisible;
        }
        else
            m_continueBlinkingMonitor.operator-=(std::chrono::milliseconds(NEXT_STEP_DELAY));

        m_lastTime = chrono::system_clock::now();
    }
}

