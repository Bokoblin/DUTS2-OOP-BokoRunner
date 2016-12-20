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

#ifndef LEADERBOARD_VIEW_H
#define LEADERBOARD_VIEW_H

#include "View.h"
#include "../Model/Leaderboard.h"


/**
 * LeaderboardView Class
 * @author Arthur
 * @date 21/05
 */
class LeaderboardView : public View
{
    public:
        //=== CTORs / DTORs
        LeaderboardView(float w, float h, sf::RenderWindow *window, TextHandler * text);
        virtual ~LeaderboardView();

        //=== SETTERS
        void setLeaderboardModel(Leaderboard *model);

        //=== METHODS
        virtual void synchronize() override;
        virtual void draw() const override;
        virtual void loadImages() override;
        virtual bool treatEvents() override;
        bool treatEvents( sf::Event event );

    private:
        //=== ATTRIBUTES
        Leaderboard *m_leaderboard;

        //Textures
        sf::Texture m_menuButtonTexture;
        sf::Texture m_rectButtonsTexture;

        //Graphic Elements
        Button *m_homeFormButton;
        Button *m_clearLbRectButton;
};


#endif
