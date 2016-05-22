#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE model

#include <boost/test/unit_test.hpp>
#include "header/GameModel.h"
#include <fstream>


const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

using namespace std;


/********************************************
    Unit Test on GameModel Class
*********************************************
    @author Arthur  @date 15/04 - 28/04
*********************************************/
BOOST_AUTO_TEST_CASE(model)
{
    //=== Add a GameModel object

    Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
    GameModel *gModel = nullptr;

    gModel = new GameModel(model);

    BOOST_CHECK(gModel != nullptr);
    BOOST_CHECK(gModel->getDistance() == 0);


    //=== Add an element

    gModel->addANewMovableElement(10, 10, 1); //normal enemy added
    BOOST_CHECK(gModel->getNewMElementsArray().empty() == false);
    BOOST_CHECK(gModel->checkIfPositionFree(10,10) == false);


    //=== Add a Player object

    BOOST_CHECK(gModel->checkIfPositionFree( 100, 500) == true);

    Player *my_ball = new Player(100, 500, 30, 30, 2.0, 18.0 );

    BOOST_CHECK( my_ball != nullptr);
    BOOST_CHECK(gModel->checkIfPositionFree(50,500) == false);

    delete gModel;
    delete my_ball;
}




/********************************************
    Unit Test on Player Class
*********************************************
    @author Arthur  @date 15/04 - 29/04
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
    Bonus *my_bonus = new Bonus(21, 529, 30, 30, -10, 0);

    BOOST_CHECK( my_ball->collision(*my_enemy) == true);
    BOOST_CHECK( my_ball->collision(*my_coin) == false);
    BOOST_CHECK( my_ball->collision(*my_bonus) == true);

    //=== Test life changes

    BOOST_CHECK( my_ball->getLife() == 100);

    my_ball->setLife(50);
    BOOST_CHECK( my_ball->getLife() == 50);

    my_ball->setLife(-1);
    BOOST_CHECK( my_ball->getLife() == 0);

    my_ball->setLife(101);
    BOOST_CHECK( my_ball->getLife() == 100);



    //=== Test State changing
    my_ball->changeState(1);
    BOOST_CHECK( my_ball->getState() == 1);
    BOOST_CHECK( my_ball->getWidth() == 70);
    my_ball->changeState(0);

    //=== Test Movements

    BOOST_CHECK( my_ball->getVector().first == 0);

    my_ball->controlPlayerMovements(true);

    BOOST_CHECK( my_ball->getDecelerationState() == false);
    BOOST_CHECK( my_ball->getVector().first < 0);

    BOOST_CHECK( my_ball->getPosX() == 50);
    my_ball->move();
    BOOST_CHECK( my_ball->getPosX() != 50);
    BOOST_CHECK( my_ball->getJumpState() == false);

    delete my_ball;
    delete my_coin;
    delete my_enemy;
    delete my_bonus;

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

    delete my_enemy;

    //same results for Coin and Bonus classes
}
