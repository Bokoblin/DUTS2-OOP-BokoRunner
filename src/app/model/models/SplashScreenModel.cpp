#include "SplashScreenModel.h"

using std::chrono::milliseconds;
using std::chrono::system_clock;

/**
 * Default Constructor
 * @author Arthur
 * @date 29/01/17 - 24/12/17
 */
SplashScreenModel::SplashScreenModel(AppCore *appCore) :
    AbstractModel(appCore), m_lastTime{system_clock::now()}, m_continueBlinkingMonitor{0},
    m_isContinueVisible{true}, m_inEndingPhase{false}

{
    m_continueBlinkingMonitor = milliseconds(CONTINUE_VISIBLE_TIMEOUT);
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
    system_clock::duration currentNextStepDelay = system_clock::now() - m_lastTime;
    system_clock::duration nextStepDelay = milliseconds(NEXT_STEP_DELAY);

    if (!m_inEndingPhase && currentNextStepDelay.count() > nextStepDelay.count())
    {
        if (m_continueBlinkingMonitor.count() <= milliseconds(0).count())
        {
            m_continueBlinkingMonitor = milliseconds(m_isContinueVisible
                    ? CONTINUE_HIDDEN_TIMEOUT
                    : CONTINUE_VISIBLE_TIMEOUT);
            m_isContinueVisible = !m_isContinueVisible;
        }
        else
            m_continueBlinkingMonitor.operator-=(milliseconds(NEXT_STEP_DELAY));

        m_lastTime = system_clock::now();
    }
}

