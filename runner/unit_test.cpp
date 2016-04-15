#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE model

#include <boost/test/unit_test.hpp>
#include "header/GameModel.h"

using namespace std;


/********************************************
    Unit Test on GameModel Class
*********************************************
    @author Arthur  @date 15/04
*********************************************/
BOOST_AUTO_TEST_CASE(model)
{
    //=== Add a GameModel object

    GameModel *gModel = nullptr;

    gModel = new GameModel(900, 600, chrono::system_clock::now());

    BOOST_CHECK(gModel != nullptr);
    BOOST_CHECK(gModel->getProgramBeginningTime() != chrono::system_clock::from_time_t(time(NULL)));
    BOOST_CHECK(gModel->getDistance() == 0);
    BOOST_CHECK(gModel->getMElementsArray().empty() == false); // an object of Player Class was created with it


    //=== Add an element

    gModel->addANewMovableElement(10, 10, 1); //normal enemy added
    BOOST_CHECK(gModel->getNewMElementsArray().empty() == false);
    BOOST_CHECK(gModel->checkIfPositionFree(10,10) == false);


    //=== Add a Player object

    BOOST_CHECK(gModel->checkIfPositionFree( 100, 500) == true);

    Player *my_ball = new Player(100, 500, 30, 30, 2.0, 18.0 );

    BOOST_CHECK( my_ball != nullptr);
    BOOST_CHECK(gModel->checkIfPositionFree(50,500) == false);
}




/********************************************
    Unit Test on Player Class
*********************************************
    @author Arthur  @date 15/04
*********************************************/
BOOST_AUTO_TEST_CASE(player)
{
    Player *my_ball = new Player(50, 500, 30, 30, 2.0, 18.0 );

    BOOST_CHECK( my_ball != nullptr);
    BOOST_CHECK( my_ball->getType() == 0);
    BOOST_CHECK( my_ball->contains(40, 500) == false);
    BOOST_CHECK( my_ball->contains(60, 500) == true);

    //=== Collision

    Enemy *my_enemy = new Enemy(70, 500, 30, 30, -10, 0);
    Coin *my_coin = new Coin(580, 500, 30, 30, -10, 0);

    BOOST_CHECK( my_ball->collision(*my_enemy) == true);
    BOOST_CHECK( my_ball->collision(*my_coin) == false);

    //=== Test life changes

    BOOST_CHECK( my_ball->getLife() == 100);

    my_ball->setLife(50);

    BOOST_CHECK( my_ball->getLife() == 50);

}


/********************************************
    Unit Test on Enemy Class
*********************************************
    @author Arthur  @date 15/04
*********************************************/
BOOST_AUTO_TEST_CASE(enemy)
{
    Enemy *my_enemy = new Enemy(50, 500, 30, 30, -10, 0);

    BOOST_CHECK( my_enemy != nullptr);

    my_enemy->move();

    BOOST_CHECK( my_enemy->getPosX() == 40);
    BOOST_CHECK( my_enemy->getPosY() == 500);

    //same results for Coin and Bonus classes
}

