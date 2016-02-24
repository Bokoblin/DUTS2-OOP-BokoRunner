/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef _MODEL_H
#define _MODEL_H

#include "Ball.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

class Model
{
public:
    //CTORs / DTORs
    Model(int width, int height);
    ~Model();

    //ACCESSEURS
    Ball getBall() const;
    Ball* getBallAdr() const ;
    std::vector<const MovableElement *> getNewMovableElements() const;

    //METHODES
    void nextStep();
    void moveBall(bool left);
    void addElement(); //ajout de nouveaux MovableElements

private:
    //ATTRIBUTS
    int m_modelWidth;
    int m_modelHeight;
    Ball *m_player;
    std::vector<MovableElement*> m_elements;   //tableau dynamique de MovableElements

    //Ajouter dans le modèle l'attribut  std::vector<const MovableElement *> _new_elements qui
    //contient les éléments qui viennent d'être ajouté au modèle :
    //std::vector<const MovableElement*> m_newElements; //SEG FAULT By adding that
};
#endif
