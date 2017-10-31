#include "IntroModel.h"

using namespace std;

/**
 * Default Constructor
 * @author Arthur
 * @date 29/01/17 - 31/10/17
 */
IntroModel::IntroModel(DataBase *dataBase) :
    AbstractModel(dataBase), m_isContinueVisible{true},
    m_lastTime{chrono::system_clock::now()},
    m_continueBlinkingMonitor{chrono::milliseconds(CONTINUE_VISIBLE_TIMEOUT)}
{}


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

    //FIXME
    if (currentNextStepDelay.count() > nextStepDelay.count())
    {
        if (m_continueBlinkingMonitor.count() <= chrono::milliseconds(0).count())
        {
            if (m_isContinueVisible)
            {
                m_isContinueVisible = false;
                m_continueBlinkingMonitor = chrono::milliseconds(CONTINUE_HIDDEN_TIMEOUT);
            }
            else
            {
                m_isContinueVisible = true;
                m_continueBlinkingMonitor = chrono::milliseconds(CONTINUE_VISIBLE_TIMEOUT);
            }
        }
        else
            m_continueBlinkingMonitor.operator-=(chrono::milliseconds(NEXT_STEP_DELAY));

        m_lastTime = chrono::system_clock::now();
    }
}

