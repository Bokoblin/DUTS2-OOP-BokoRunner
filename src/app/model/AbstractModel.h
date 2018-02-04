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

#ifndef ABSTRACT_MODEL_H
#define ABSTRACT_MODEL_H

#include "app/model/AppCore.h"

/**
 * The AbstractModel class provides
 * an app core and a nextStep method
 * for its inherited classes.
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 29/01/17
 */
class AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit AbstractModel(AppCore *appCore);
    virtual ~AbstractModel();

    //=== GETTERS
    AppCore *getAppCore() const;

    //=== METHODS
    virtual void nextStep()=0;

protected:
    //=== ATTRIBUTES
    AppCore *m_appCore;
};

#endif
