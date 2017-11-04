# Boko Runner #

### Branches ###
| Branch name | Branch description |     CI     |   Code review    |
| ----------- | ------------------ | ---------- | ---------------- |
| **master**  | Stable builds merged from dev | [![Build Status](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner.svg?branch=master)](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/b75a85177a7e42e288b9df67f5a6c0db?branch=master)](https://www.codacy.com/app/Bokoblin/DUTS2-POO-ProjetRunner?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bokoblin/DUTS2-POO-ProjetRunner&amp;utm_campaign=Badge_Grade) 
| **release** | Release builds rebased from master | [![Build Status](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner.svg?branch=release)](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/b75a85177a7e42e288b9df67f5a6c0db?branch=release)](https://www.codacy.com/app/Bokoblin/DUTS2-POO-ProjetRunner?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bokoblin/DUTS2-POO-ProjetRunner&amp;utm_campaign=Badge_Grade)
| **dev** | In-development unstable builds | [![Build Status](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner.svg?branch=dev)](https://travis-ci.org/Bokoblin/DUTS2-POO-ProjetRunner) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/b75a85177a7e42e288b9df67f5a6c0db?branch=dev)](https://www.codacy.com/app/Bokoblin/DUTS2-POO-ProjetRunner?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Bokoblin/DUTS2-POO-ProjetRunner&amp;utm_campaign=Badge_Grade)|

### Description ###

Boko Runner is a C++ OOP project we've done as our DUT second semester's programming project.
It consists in creating a "runner" game (an auto-scrolling platform game) where the player 
has to dodge each obstacles and collect bonuses to increase its score. The game ends when the player's life bar is empty.
The project allowed us to put into practice the Object Oriented Programming notions that we learnt in S2.

Initially made to be based on a Model-View architecture as requested, the project can be considered as 
a Three-Tier Architecture with a Database, Models and Views. 

Despite being initially a scholar project ended in May 2016, it is still receiving new features 
and "under the hood" improvements from Bokoblin.


### Tools used ###

* IDEs : Code::Blocks, QT Creator, CLion (current)
* Language : C++11
* Libraries : 
  * SFML 2.3.2
  * PugiXML 1.8
* Continuous integration : Travis CI
* Code review : Codacy


### Authors ###

* Arthur Jolivet - main developer
* Florian Laronze


### Documentation ###

The Doxygen documentation can be found at 
[this address](https://bokoblin.github.io/DUTS2-POO-ProjetRunner/). It is aligned with master branch.


### How to build ###

From Project folder do :
  - mkdir build
  - cd build
  - cmake .. && make
  
Note : This project has been tested on Ubuntu Trusty (14.04 LTS) with gcc-4.9 and clang-3.6.<br>
You may need to install the following packages before building : <br>
libopenal-dev, libalut-dev, libxcb-image0, libudev-dev, libudev1


### Licences ###

Our project is mainly licensed under Apache License Version 2.0 but some elements have other licences.<br>
Please take a look at the following paragraphs for more details.


##### Code #####

Our code is licensed under Apache License Version 2.0.
Our project include two libraries contained in /libs folder : 
* PugiXML which is licensed by their creators under MIT Licence.
* SFML which is licensed by their creators under zlib/png license.


##### Images #####

All images are licensed under Apache Licence Version 2.0.
Most of them were created by ourselves or were given by our teachers.
Some of them were made using provided one or were inspired by Material Design (e.g. radios).
The file "shape_buttons.png" incorporates some AOSP icon which are also licensed under Apache License Version 2.0.


##### Audio #####

All audio files are licensed under Apache Licence Version 2.0 apart the following ones which were created by Paul Samra, 
a friend of Florian, under BeerWare licence :
- menu_sound.ogg
- game_normal_sound.ogg
- game_master_sound.ogg


##### Fonts #####

The fonts in /res folder come from Google Fonts. They are licensed under Apache Licence Version 2.0.
