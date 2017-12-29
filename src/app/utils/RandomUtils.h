/* Copyright 2017 Jolivet Arthur

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

#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

#include <random>

/**
 * The RandomUtils class allows to use some
 * C++11 random functions based on probability laws.
 *
 * @author Arthur
 * @date 29/12/17
 */
class RandomUtils
{
public:

    /**
     * Provides uniformly an integer number between 2 limits
     * using the Uniform probability law
     *
     * @param a the min limit
     * @param b the max limit
     * @return an integer in [a, b] range
     *
     * @author Arthur
     * @date 29/12/17
     */
    static int getUniformRandomNumber(int a, int b)
    {
        static std::default_random_engine generator;
        std::uniform_int_distribution<> uniformIntDistribution(a, b);
        return uniformIntDistribution(generator);
    }
};

#endif
