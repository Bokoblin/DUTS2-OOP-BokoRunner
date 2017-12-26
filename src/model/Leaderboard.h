/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "AbstractModel.h"

/**
 * The Leaderboard class is the model of LeaderboardView class
 * @author Arthur
 * @date  19/04/16 - 29/01/17
 */
class Leaderboard : public AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit Leaderboard(DataBase *dataBase);
    ~Leaderboard() override;

    //=== METHODS
    void nextStep() override;
    void quit();
};

#endif
