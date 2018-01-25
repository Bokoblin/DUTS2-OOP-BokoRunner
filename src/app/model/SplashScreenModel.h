/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef SPLASH_SCREEN_MODEL_H
#define SPLASH_SCREEN_MODEL_H

#include "AbstractModel.h"
#include <chrono>

/**
 * The SplashScreenModel class
 * handles the splash screen's logic
 * @author Arthur
 * @date 29/01/17 - 24/12/17
 */
class SplashScreenModel : public AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit SplashScreenModel(DataBase *dataBase);
    ~SplashScreenModel() override;

    //=== METHODS
    void nextStep() override;

    //=== GETTERS
    bool isContinueVisible() const;
    bool isInEndingPhase() const;

    //=== SETTERS
    void setEndingPhase(bool inEndingPhase);

private:
    //=== ATTRIBUTES
    std::chrono::system_clock::time_point m_lastTime;
    std::chrono::milliseconds m_continueBlinkingMonitor;
    bool m_isContinueVisible;
    bool m_inEndingPhase;

    //Constant Variables
    const int NEXT_STEP_DELAY = 100;
    const int CONTINUE_VISIBLE_TIMEOUT = 1000;
    const int CONTINUE_HIDDEN_TIMEOUT = 500;
};

#endif
