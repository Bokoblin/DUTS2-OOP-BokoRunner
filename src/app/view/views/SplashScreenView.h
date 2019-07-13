/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#ifndef SPLASH_SCREEN_VIEW_H
#define SPLASH_SCREEN_VIEW_H

#include "app/model/models/SplashScreenModel.h"
#include "AbstractView.h"
#include "app/view/ui-components/ParallaxBackground.h"

/**
 * @class SplashScreenView
 * @details Display the app's splash screen at startup
 *
 * @author Arthur
 * @date 27/03/2016 - 13/07/2019
 */
class SplashScreenView: public AbstractView
{
public:
    //=== CTORs / DTORs
    SplashScreenView(sf::RenderWindow* window, AppTextManager* textManager, SplashScreenModel* splashModel);
    ~SplashScreenView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event& event) override;

private:
    //=== ATTRIBUTES
    SplashScreenModel* m_splashModel;
    mdsf::Sprite* m_splashScreen;

    //For transition
    ParallaxBackground* m_parallaxBackground;
    mdsf::Sprite* m_appTitle;

    //Constants
    static constexpr int BACKGROUND_WIDTH = 1200;
    static constexpr int TITLE_WIDTH = 400;
    static constexpr int TITLE_HEIGHT = 200;

    //=== METHODS
    void loadSprites() override;
};

#endif
