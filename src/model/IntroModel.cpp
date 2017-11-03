#include "IntroModel.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 29/01/17 - 02/10/17
 */
IntroModel::IntroModel(DataBase *dataBase) :
    AbstractModel(dataBase), m_isContinueVisible{true},
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
IntroModel::~IntroModel()
{}


//=== Getters
bool IntroModel::isContinueVisible() const { return m_isContinueVisible; }


/**
 * Next Step
 * @author Arthur
 * @date 29/01/17 - 31/10/17
 */
void IntroModel::nextStep()
{
    chrono::system_clock::duration currentNextStepDelay = chrono::system_clock::now() - m_lastTime;
    chrono::system_clock::duration nextStepDelay = std::chrono::milliseconds(NEXT_STEP_DELAY);

    if (currentNextStepDelay.count() > nextStepDelay.count())
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

