/* Copyright 2018 Jolivet Arthur

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

#ifndef TEST_CORE_H
#define TEST_CORE_H

#include "app/model/core/AppCore.h"

/**
 * The TestCore class inherits the AppCore for test purposes
 *
 * @author Arthur
 * @date 25/08/18
 */
class TestCore: public AppCore
{
public:
    //=== CTORs / DTORs
    TestCore();
    ~TestCore() override;

    //=== GETTERS
    std::string getConfigFile() const override ;
};

#endif
