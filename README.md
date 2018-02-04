# Boko Runner #


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

* IDEs : Code::Blocks, QT Creator, CLion(current)
* Language : C++11
* Libraries : 
    * SFML 2.4.2
    * PugiXML 1.8
* Continuous integration : Travis CI
* Code review : Codacy


### Authors ###

* Arthur Jolivet - main developer
* Florian Laronze


### Documentation ###

The Doxygen documentation can be found at 
[this address](https://bokoblin.github.io/DUTS2-POO-ProjetRunner/).


### How to build ###

Execute `build.sh` file or do, from Project folder :
  - `mkdir build`
  - `cd build`
  - `cmake .. && make`
  
Note : You may need to install some of the following packages, depending of your configuration, before building : <br>
- g++-4.9
- libopenal
- libvorbis
- libogg.so
- libFLAC.so
- libGL.so
- libSM.so
- libICE.so
- libXrandr.so
- libalut-dev
- libxcb-image0
- libudev-dev
- libudev1

Notes: 
- The SFML library files were built with g++-4.9 <br>
  So the project may only compile with g++-4.9 or clang (see next section for tested environments)<br>
- You can use `update-alternatives` to change default g++ priority if needed.
- On Windows, compiler and SFML version have to match 100%. <br>
  So, you must use *mingw-w64-6.1.0* to compile the project.


### Tested environments ###

- **Windows 10 Home Version 1709 - Fall Creator Update**
	- **Kernel**: Windows NT 10.0
	- **Compiler**: mingw-w64-6.1.0
	- **Environment**: local
	- **Compilation**: OK
	- **Execution**: OK
	
- **Ubuntu 16.04 LTS - Xenial**
	- **Kernel**: x86_64 Linux 4.4.0-43-Microsoft
	- **Compiler**: g++-4.9
	- **Environment**: local (Windows Subsystem for Linux)
	- **Compilation**: OK
	- **Execution**: Not possible (even with x-server)
	
- **Ubuntu 14.04 LTS - Trusty**
	- **Kernel**: ??
	- **Compiler**: gcc-4.9, clang-3.5, clang-3.9, clang 5.0
	- **Environment**: Virtual machine on GCE (Travis CI)
	- **Compilation**: OK
	- **Execution**: Can't be tested


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