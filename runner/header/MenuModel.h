/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#ifndef _MENUMODEL_H
#define _MENUMODEL_H

#include "Model.h"
#include "Leaderboard.h"


/********************************************
    MenuModel Class
*********************************************
    @author Arthur  @date 14/04 - 19/04
*********************************************/
class MenuModel : public Model
{
public:
    //=== CTORs / DTORs
    MenuModel(const Model& model);
    virtual ~MenuModel();

    //=== GETTERS
    bool getHomeState() const;
    bool getSettingsState() const;
    bool getLeaderboardState() const;
    Leaderboard* getLeaderboard() const;

    //=== SETTERS
    void setHomeState(bool state);
    void setSettingsState(bool state);
    void setLeaderboardState(bool state);

    //=== METHODS
    virtual void nextStep() override;

private:
    //=== ATTRIBUTES
    bool m_homeState;
    bool m_settingsState;
    bool m_leaderboardState;

    Leaderboard *m_lb;
};

#endif
