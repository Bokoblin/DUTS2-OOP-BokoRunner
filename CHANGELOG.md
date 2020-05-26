# Changelog #

Current version : v2.0-SNAPSHOT

---

<!------------------------------------------------------------------------------------------------------->

<a name="v2.0-SNAPSHOT"></a>
## [v2.0-SNAPSHOT](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.8.3...dev)

FIXME: SOME MISSING CHANGES BETWEEN FEBRUARY 2018 AND FEBRUARY 2020

#### Breaking changes
- **Structure refactoring**
  - **abstraction**: Rewritten architecture around `AbstractModel` and `AbstractView` abstract classes
  - **data management**: `Database` class split into three classes and helpers
    - `AppCore` for app data and states
    - `PersistenceManager` to handle app data persistence and abstract data retrieval/saving
    - `LocalizationManager` to handle localization and abstract strings retrieval
    - `XMLHelper` for generic XML operations
    - `FileBasedPersistence` for specialized persistence: text-based
  - **ui components**: Generic UI components are now dissociated from app and grouped under *MDC-SFML*
  - **window**: life-cycle now handled only in `main.cpp`
  - **events**: lifecycle changes (window::close() moved to `main.cpp`), cleanup, macro removal
  - **resources**: folder organization improvements, including lib specific ressources moved elsewhere
  - **enumerations**: each of them now has its own `.h` file
  - **constants**: Most constants are grouped in `ModelConstants` and `ViewConstants` classes
  - **renaming**: several classes and methods have been renamed, including:
    - `IntroModel` => `SplashScreenModel`
    - `IntroView` => `SplashScreenView`
    - `Model` => `AbstractModel`
    - `Commands` => `CommandsModel`
    - `Leaderboard` => `LeaderboardModel`
    - `Settings` => `SettingsModel`
    - `Shop` => `ShopModel`
    - `View` => `AbstractView`
    - `GraphicElement` => `Sprite`
    - `AnimatedGraphicElement` => `AnimatedSprite`
    - `PixelateEffect` => `PixelShader`
    - `SlidingBackground` => `ScrollingBackground`
    - `TextHandler` => `AppTextManager`
    - `treatEvents()` => `handleEvents()`
- **Compiling upgrade**: External dependencies are now downloaded during CMake process, and compiled alongside project
    
#### Features
- **splash screen**: 
    - now same size as menu and game
    - layout has been changed : it now displays title, author and "powered by SFML" on grey background
    - "press START to continue" is now blinking periodically and compatible with multi-language
    - a transition to menu has been added
- **commands**: replaced keyboard image by localized strings containing key(s) and description 
- **dialogs**: rewritten `Dialog` class into a generic dialog class
    - `ShopDialog` inherits from it for shop specific dialogs
- **settings**: added support for hyperlinks (URL is opened in default browser) [tested on Ubuntu 14.04 and Windows 10]
- **graphics**: support for changing graphic elements's light (using same principle as alpha)
- **logging**: console and file logging now supported throughout the app

#### Bug fixes
- **perfs**: Performance fixes by removing unnecessary actions in sync loop (i.e. xml file access)

#### Misc
- **iconography**: added application icon (title bar and task bar)
- **graphics**: Modernized a couple of images and textures
- **randomness**: switched to C++11 random functions
- **colors**: Material and App custom colors with dedicated classes
- **language**: more C++11 keywords and functions usage
- **styling**: typo, spacing and code styling improvements
- **changelog**: changed for `.md` and reformatted file accordingly
- **script**: added a little bash `build.sh` script
- **xml**: safe fetching, logging
- **cmake**: reorganization with libraries usage and ext dependencies fetching
- **unit tests**: reintroduced with Google Test
- **copyright**: Updated up to 2020
 
#### Library changes
- **dependency inclusion**: Dependencies (external libs) aren't anymore included, CMake's FetchContent is now used
- **SFML**: upgraded SFML library ( 2.3.2 => 2.5.1)
- **PugiXML**: upgraded PugiXML library ( 1.8 => 1.10)
- **offspringing**: split out some components into libraries compiled separately:
    - **slogger**: a simple logger for the app
    - **xmlhelper**: an xml helper to abstract PugiXML usage
    - **mdcsfml**: a UI lib implementing material components above SFML components

#### Known issues
- **Game**: Buggy transition management at high speeds
- **Game**: Endless jump in fullscreen mode (unavailable currently)
- **Game**: Endless transition in fullscreen mode (unavailable currently)

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.8.3"></a>
## [v1.8.3](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.8.2...v1.8.3) (2017-11-04)

#### Fixes
- **styling**: improved C++11 code compliance
- **performance**: performance fixes related to paused game

#### Misc
- **CodeFactor** : added CodeFactor badge to README
- **doc** : documentation update

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.8.2"></a>
## [v1.8.2](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.8.1-1...v1.8.2) (2017-04-10)

#### Fixes
- **styling**: improved C++ code styling
- **method parameters**: passed several `std::string` parameters by const reference 

#### Misc
- **Codacy** : added Codacy badge to README
- **doc** : documentation source makes a return (still updated only for `release` branch)

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.8.1-1"></a>
## [v1.8.1-1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.8.0...v1.8.1-1) (2017-02-18)

#### Tools
- **CI**: added configuration file for Travis CI
- **Cmake**: lowered CMake required version to 2.8

#### Fixes
- **game**: fixed flattened enemy bonus

#### Misc
- **doc**: updated online documentation to current version

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.8.0"></a>
## [v1.8.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.6...v1.8.0) (2017-01-26)

#### Front facing features
- **Settings**
    - **music**: added music controls to toggle game and menu music
    - **layout**: split *Stats* and *Credit* in two different pages (the latter is now called *About*) 
    - **stats page**: added per-game statistics
    - **stats page**: added a ***CLEAR DATA*** button with confirm dialog
    - **about**: added SFML logo and some information
- **shop**: added full multilingual support
- **leaderboard**: leaderboard score is split between Easy and Hard modes
- **commands**: added a new *Commands* screen to see the game's keyboard commands

#### Coding features:
- **text**: added `Text` class inherited from `sf::Text` class
- **buttons**: added `RadioButton` class inherited from `Button` class
- **buttons**: support for multi-location button's label (`TOP`, `RIGHT`, `BOTTOM`, `LEFT`, `CENTER`)
- **buttons**: replaced all standalone texts previously used as button's label by `Button::m_label`
- **textures**: rewritten `GraphicElement` texture handling (now allows by-class pre-configured rectangle clips)
- **class**Rewritten Dialog and ShopItemCard that are now inherited from GraphicElement
- **const strings**: centralized all global string constants in one file : `constants.h`

#### Misc and fixes
- **xml**: changed xml strings files structure and handling
- **about**: updated IUT logo
- **copyright**: updated copyright to include 2017
- **UI**: added showing capability to `GraphicElement` class
- **charset**: added support for UTF-8 charset thanks to Laurent Gomila (SFML main developer)
- **doc**: updated online documentation to current version
- other minor fixes and improvements

#### Library changes
- **PugiXML**: updated PugiXML version ( 1.7 => 1.8)

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.6"></a>
## [v1.7.6](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.5...v1.7.6) (2016-12-26)

#### Game improvements and fixes
- **game state**: replaced game states booleans by an enum
- **distance**: fixed distance increasing stopped at speed limit and with certain bonuses
- **distance**: current distance now depends only on game speed
- **pause**: fixed incorrect pause background

#### Misc
- **doc**: updated online documentation to current version

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.5"></a>
## [v1.7.5](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.4...v1.7.5) (2016-12-20)

#### Misc
- **app**: replaced appState booleans by an enumeration
- **game**: adjusted game difficulty (now called *easy* and *hard*)
- **data**: added game difficulty to config saving
- **doc**: fixed documentation comments
- **readme**: updated README.md
- **doc**: removed documentation from project (now accessible from project website)

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.4"></a>
## [v1.7.4](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.3...v1.7.4) (2016-12-01)

#### Misc
- **structure**: refactored project structure
- **unit tests**: removed obsolete unit test class
- **readme**: updated README.md
- **doc**: updated documentation

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.3"></a>
## [v1.7.3](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.2...v1.7.3) (2016-10-24)

#### Features
- **cmake**: Build now assured by *Cmake* (added CMakeLists.txt file)
- **database**: rewritten leaderboard storage system into `Database` class

#### Misc
- **strings**: moved all images path strings to a dedicated file
- **code**: code enhancement (ex. simplified if statements, made some function const)
- **code**: removed unused code
- **doc**: documentation updated
- **config**: removed second config file to check manual modifications

#### Library changes
- **SFML**: included SFML Library in */Libs* folder instead of relying on external

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.2"></a>
## [v1.7.2](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.1...v1.7.2) (2016-05-24)

#### Bug fixes
- **linux**: fixed again images on linux
- **code**: code enhancement

#### Misc
- **game**: added half-random y position for coins, lowered spawn distance
- **shop**: added buying results (success/failure)
- **image**: shield image and element changes
- **doc**: documentation updated

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.1"></a>
## [v1.7.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.7.0...v1.7.1) (2016-05-22)

#### Bug fixes
- **music**: fixed music relaunching on resume pressed instead of release
- **UI**: fixed indicators drawing

#### Misc
- **music**:  added a toggle in pause screen allowing to (un)mute game sound
- **textures**: removed unused texture separator for animated sprites
- **files**: reorganized files

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.7.0"></a>
## [v1.7.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.6.0...v1.7.0) (2016-05-22)

##### Features
- **shop**: added a shop screen to buy items :
	- show 3 dynamic* item cards per pages, dynamic page indicators allow to change current page
	- each card contains the item name, a description, a generic image and a buy button
		- buy button is red and disable if an item is bought
		- otherwise, it is green and create a dialog when clicking on it
	- the dialog shows a confirmation, name and price of the item, and two action Cancel & OK
    - once bought, items are immediately effective on the game
- **settings and leaderboard**: rewritten Settings and Leaderboard following Shop structure
	- remade Settings UI in two pages :
		- *Configuration*, to personalize game (with 3 new ones for player configuration)
		- *Stats* and *Credits*
- **bonus**: added a shield bonus

#### Fixes and misc
- **bonus**: fixed bonus timeout not suspending at pause state
- **enums**: added enums for better reading (elements, player states & bonus)
- **code**: removed some unused variables
- **code**: added lots of defines and constants to avoid hard coded values
- **music**: added master music (more rapid than normal mode one)
- **comments**: added lots of comments
- **doc**: documentation updated

\* dynamic means that if <item> rows are added in config file, the number of cards and pages
  will be automatically changed after relaunching Shop.
  Note : You have to remember how works configuration "security", though.

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.6.0"></a>
## [v1.6.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.5.0...v1.6.0) (2017-05-07)

#### Features 
- **config**: added configuration saving in file thanks to a new class DataModel :
	- save and load accumulated money, distance travelled, flattened enemies, games played,
	- save and load last chosen language,
	- allows to save and load other data for future features such as shop,

#### Bug fixes
- **game**: fixed zone transition rendering and fading effect added
- **menu**: fixed menu music loop

#### Fixes and misc
- **pause**: new pause background added for zone 2
- **UI**: updated save button
- **game**: accelerated apparition of enemies and increased enemies damage in Master mode
- **code**: text class strings refactored for consistency and more readability
- **doc**: documentation updated

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.5.0"></a>
## [v1.5.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.4.0...v1.5.0) (2016-05-06)

#### Features
- **music**: added Music in menu and game

#### Info
All features labeled as *additional features* are now implemented

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.4.0"></a>
## [v1.4.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.3.1...v1.4.0) (2016-04-30)

- **game**: added Zone changing each 500m (normal mode) / 2000m (master mode)
	- Zone changing is made with a scrolling far background transition
	  and a pixel appearing near background
- **shader**: added PixelShader class to handle pixel transition (altered from SFML Examples - see file)
- **images**: image loading optimized by merging textures using same file (number of textures reduced by half)
- **renaming**: renamed lots of variables
- **doc**: documentation updated

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.3.1"></a>
## [v1.3.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.3.0...v1.3.1) (2017-04-29)

#### Misc
- **first delivery** : Modified unit tests and model for first project report

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.3.0"></a>
## [v1.3.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.2.1...v1.3.0) (2016-04-20)

#### Features
- **leaderboard**: 
    - added Leaderboard screen in menu displaying the 10 best scores
    - added a clear scores button
    - added a button in game to save score to leaderboard

#### Bug Fixes
- **lang**: fix issues with language

#### Misc
- **textures**: removed not needed texture variable in `MenuView` class and variables's name edited
- **doc**: documentation updated

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.2.1"></a>
## [v1.2.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.2.0...v1.2.1) (2016-04-17)

#### Misc
- **game**: added bonus timeout displaying
- **game**: added enemy destroyed points in pause

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.2.0"></a>
## [v1.2.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.1.0...v1.2.0) (2016-04-16)

#### Features
- **settings**: added Settings screen in menu with :
	- **multilingual support**: app language can be changed between English, French or Spanish via radio buttons
	- **difficulty mode support** : difficulty can be changed between normal and master (higher game speed, double damages)

#### Misc
- **code**: class destructors cleaned-up
- **doc**: documentation updated

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.1.0"></a>
## [v1.1.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.0.1...v1.1.0) (2016-04-15)

#### Features
- **bonus** :
	- **PV+**: restores 10 PV to player.
	- **MEGA**: grows player size, making it invincible and collecting enemy destruction points.
		It works during 10 seconds.
	- **FLY**: allows the player to jump higher and going down slowly following user control.
		It works during 15 seconds.
	- **SLOW_GAME**: slow down game speed (background and elements). It works during 20 seconds.

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.0.1"></a>
## [v1.0.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v1.0.0...v1.0.1) (2016-04-15)

#### Features
- **unit tests**: added unit tests for some model classes

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v1.0.0"></a>
## [v1.0.0](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.6.0-beta.2...v1.0.0) (2016-04-11)

#### Announcement
- **graduation**: first stable version : all minimal features are working properly
- **doc**: documentation generated with doxygen
- **license**: license changed to "Apache License Version 2.0"

#### Misc
- **code**: classes and files inclusion clean-up thanks to Doxygen and GraphViz

<br>

# Beta Releases

<!------------------------------------------------------------------------------------------------------->

<a name="v0.6.0-beta.2"></a>
## [v0.6.0-beta.2](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.6.0-beta.1...v0.6.0-beta.2) (2016-04-10)

#### Misc
- **game**: updated player's jump mechanism

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.6.0-beta.1"></a>
## [v0.6.0-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.3.0-beta.1...v0.6.0-beta.1) (2016-03-23 to 2016-04-09)

Contains versions v0.4.0-alpha.1 to v0.6.0-alpha.2 :

### v0.4.0-alpha.x (2016-03-23 to 2016-03-30):

#### Features
- **code structure**: added *INTRO-MENU-GAME* structure :
    - **INTRO** displays a splash screen and allows to launch the menu
	- **MENU** contains background images, a title image, play and quit buttons.
	- **GAME** allows to do all the features from v0.3.0
	- **UX**: added mouse support to click on different buttons

#### Misc
- **code**: lots of file were completely rewritten
- **code**: clock() usage replaced by std::chrono which do not rely on processor clock


### v0.5.0-alpha.x (2016-03-31):

#### Features
- **pause**: Pause menu implemented with 3 buttons (resume, restart, home menu)

### v0.6.0-alpha.1/2 (2016-04-01 to 2016-04-06):

#### Features
- **UI**: end screen added with final score calculated and displayed, and 2 buttons (restart,menu)

#### Bug fixes
- **code**: some `int` moved to `unsigned int`
- **code**: big code clean-up
- **code**: lots of bug Fixes

#### Misc
- **code**: Abstract classes added (`View` && `MovableElement`)
- **code**: `Button` class added
- **code**: `TextHandler` class created to store all texts from menu, game, pause and end
- **code**: collision method added in `MovableElement` instead of using `GameView`

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.3.0-beta.1"></a>
## [v0.3.0-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.2.3-beta.1...v0.3.0-beta.1) (2016-03-12 to 2016-04-09)

#### Features
- **game**: player movements rewritten with ability to jump.
	The jump is made using gravity, acceleration and vectors. It describes a parable.

#### Misc
- **game**: Cleaned up unused `Ball` methods

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.2.3-beta.1"></a>
## [v0.2.3-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.2.2-beta.1...v0.2.3-beta.1) (2016-03-22)


#### Bug fixes
- fixed seg-fault related to a getter returning a copy and not the object itself

#### Misc
- **code**: NewMovableElement `std::vector` replaced by a `std::set`

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.2.2-beta.1"></a>
## [v0.2.2-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.2.1-beta.1...v0.2.2-beta.1) (2016-03-22)

#### Features
- **game**: Graphic evolution of player's life through an "animated" life bar

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.2.1-beta.1"></a>
## [v0.2.1-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.2.0-beta.1...v0.2.1-beta.1) (2016-03-20 to 2016-03-22)

#### Features
- **UI**: bottom bar added with score, distance and player bar

#### Bug fixes
- bug and memory leaks fixes

#### Misc
- **UI**: far background blurred a bit for focus
- **code**: element collision and destruction handling rewritten
- **game**: player life handling added but not showing on bottom bar so far

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.2.0-beta.1"></a>
## [v0.2.0-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.4-beta.1...v0.2.0-beta.1) (2016-03-19)

#### Features
- **game**: added random animated appearing enemies and coins
- **code**: time handling added to control animation and distance incrementation

#### Bug fixes
- lots of bug fixes

#### Misc
- **code**: rewritten code concerning synchronisation, events, drawing
- **UI**: enemy destruction animation added

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.4-beta.1"></a>
## [v0.1.4-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.3-beta.1...v0.1.4-beta.1) (2016-03-05)

#### Features
- **game**: added animated player (generation independent from model one)

#### Bug fixes
- various fixes

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.3-beta.1"></a>
## [v0.1.3-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.2-beta.2...v0.1.3-beta.1) (2016-03-03)

#### Features
- **game**: added Sliding Background

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.2-beta.2"></a>
## [v0.1.2-beta.2](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.2-beta.1...v0.1.2-beta.2) (2016-03-02)

#### Bug fixes
- bug fixes related to the creation of new enemies

#### Misc
- **doc**: added documentation comments

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.2-beta.1"></a>
## [v0.1.2-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.1-beta.1...v0.1.2-beta.1) (2016-02-25)

#### Misc
- **Workshop 2**: GraphicElement::resize() is now working
- **Workshop 4**: added font for player position

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.1-beta.1"></a>
## [v0.1.1-beta.1](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.0-beta.1...v0.1.1-beta.1) (2016-02-25)

#### Misc
- Workshop 2 and 3 are finished until fixing issues in *OOP* TD next week

<br>

<!------------------------------------------------------------------------------------------------------->

<a name="v0.1.0-beta.1/2/3/4/5"></a>
## [v0.1.0-beta.1/2/3/4/5](https://github.com/Bokoblin/DUTS2-OOP-BokoRunner/compare/v0.1.0-beta.5) (2016-02-22 to 2017-02-24)

#### Announcement
- **Project Creation**:
	- images added in "Images" folder
	- font added in "Fonts" folder
	- *README* added
- **workshops**: Added code from workshops 1, 2 and 3