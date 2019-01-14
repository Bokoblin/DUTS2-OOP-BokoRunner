# Boko Runner #


### Description ###

Boko Runner is a C++ OOP project we've done as our DUT second semester's programming project.
It consists in creating a "runner" game (an auto-scrolling platform game) where the player 
has to dodge each obstacle and collect bonuses to increase its score. The game ends when the player's life bar is empty.
The project allowed us to put into practice the Object Oriented Programming notions that we learnt in S2.

Initially made to be based on a Model-View architecture as requested, the project can be considered as 
a Multi-Tier Architecture with a persistence manager, an app core, models, and views.

Despite being initially a scholar project ended in May 2016, it is still receiving new features 
and "under the hood" improvements.


### Tools used ###

* IDEs : Code::Blocks, QT Creator, CLion(current)
* Language : C++11
* Libraries : 
    * SFML 2.4.2
    * PugiXML 1.8
* Unit tests : Google Test
* Continuous integration : Travis CI
* Code review : CodeFactor


### Authors ###

* Arthur Jolivet - main developer
* Florian Laronze


### Documentation ###

The Doxygen documentation can be found at 
[this address](https://bokoblin.github.io/DUTS2-POO-ProjetRunner/).


### How to build ###

#### Libraries requirements ####

##### GNU/Linux #####

You have two choices for GNU/Linux systems: 
- either manually install needed packages and use provided SFML lib (but incompatibility issues can occur)
- either manually install "libsfml-dev" and use it instead of the provided one, it should download all necessary libs.

If you choose the first option, you may need to install some of the following packages, depending of your configuration: <br>
- g++ / clang
- libopenal
- libvorbis
- libogg
- libFLAC
- libGL
- libSM
- libICE
- libX11
- libXext
- libfreetype
- libjpeg
- libXrandr
- libalut-dev
- libxcb-image0
- libudev-dev
- libudev1

If you choose the second option:
- run `sudo apt-get install libsfml-dev` in your terminal (this should install SFML 2.4.2 and its dependencies)
- comment the following line in CMakeLists.txt: `set(SFML_ROOT "${EXTERNAL_LIBS_ROOT}/SFML-2.4.2")`


##### Windows #####

You'll need to put some shared libraries (.dll) in C:\Windows\System32 or in the same folder as the executable:
- OpenAL32.dll
- sfml-graphics-2.dll or sfml-graphics-d-2.dll
- sfml-window-2.dll or sfml-window-d-2.dll
- sfml-audio-2.dll or sfml-audio-d-2.dll
- sfml-system-2.dll or sfml-system-d-2.dll


#### Building steps ####

##### GNU/Linux #####

Execute `build.sh` file or do, from Project folder :
  - `mkdir build`
  - `cd build`
  - `cmake .. && make`
  

##### Windows #####

Unless you have all needed packages for the commands below, 
it is recommended to open the project in a cmake-based IDE like QTCreator or CLion, 
and to use the built-in `build` option.
  


Notes: 
- The SFML library files were built with a specific version of g++ but it shouldn't be a problem on GNU/Linux.<br>
- However, you can use `update-alternatives` to change default g++ priority if needed.
- On Windows, compiler and SFML version have to match 100%. <br>
  So, you must use *mingw-w64-6.1.0* to compile the project.


### How to run ###

##### GNU/Linux #####

The available executables are `bokorunner` and `unit_tests`. <br>
You just have to launch them like you would do with other unix executables with: `$ ./${EXEC_NAME}`

##### Windows #####

The available executables are `bokorunner.exe` and `unit_tests.exe`. <br>
You first have to correctly set the current working directory on your IDE (Run>Edit configurations... for Clion) :
- For `bokorunner.exe`, it must be `${PROJECT_DIR}/${CMAKE_BUILD_DIR}`
- For `unit_tests.exe`, it must be `${PROJECT_DIR}/${CMAKE_BUILD_DIR}/src`

Then you can launch them with the built-in `run` option.


### Tested environments ###

- **Windows 10 Home Version 1803 - April 2018 Update**
	- **Kernel**: Windows NT 10.0
	- **Compilers**: mingw-w64-6.1.0
	- **Environment**: local
	- **Compilation**: OK
	- **Execution**: OK
	- **Unit tests**: OK
	
- **Ubuntu 18.04 LTS - Bionic**
	- **Kernel**: x86_64 Linux 4.4.0-17134-Microsoft
	- **Compilers**: g++7.3, clang 6.0
	- **Environment**: local (Windows Subsystem for Linux)
	- **Compilation**: OK
	- **Execution**: Splashscreen OK, MENU unstable, GAME KO (via a windows X server)
	- **Unit tests**: OK
	
- **Debian GNU/Linux 9 - Stretch**
	- **Kernel**: x86_64 Linux 4.4.0-43-Microsoft
	- **Compilers**: g++-4.9
	- **Environment**: local (Windows Subsystem for Linux)
	- **Compilation**: OK (used libsfml-dev from apt instead of provided one)
	- **Execution**: Splashscreen OK, MENU KO (crash related to openal)
	- **Unit tests**: NOT TESTED YET
	
- **Travis CI: Ubuntu 14.04 LTS - Trusty**
	- **Kernel**: 4.4.0-101-generic
	- **Compilers**: gcc-4.9, gcc-5, gcc-6, gcc-7, clang-3.6, clang-3.8, clang-3.9, clang 5.0, clang 6.0
	- **Environment**: Virtual machine on GCE (Travis CI)
	- **Compilation**: OK (all 7 working)
	- **Execution**: Can't be tested
	- **Unit tests**: OK
	
- **Travis CI: Mac OS X 10.11/12**
	- **Kernel**: ??
	- **Compilers**: xcode8: Apple LLVM v8.0.0, xcode8: Apple LLVM v9.0.0
	- **Environment**: Virtual machine on GCE (Travis CI)
	- **Compilation**: OK (both working)
	- **Execution**: Can't be tested
	- **Unit tests**: OK


### Licences ###

The project is mainly licensed under Apache License Version 2.0 but some elements have other licences.<br>
Please take a look at the following paragraphs for more details.


##### Code #####

The code is licensed under Apache License Version 2.0.
The project includes two external libraries contained in `/ext-libs` folder : 
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
