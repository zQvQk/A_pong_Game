#include <cstdlib>
#include <ctime>
#include "LogicBall.h"

#define SPEED_UPPERBOUND 50
#define SPEED_LOWBOUND 3

int LogicBall::xiv = 3;
int LogicBall::yiv = 5;

/**
 * Constructor
 */
LogicBall::LogicBall() {
    xPos =  0;
    yPos =  0;
    bState = STAY;
    xVel = 1;
    yvel = 1;
}
/**
 * Ball Constructor with two arguments
 * @param bState state of the ball
 * @param x initial ball position
 * @param y initial ball position
 */
LogicBall::LogicBall(ballState s, int x, int y) {
    xPos = x;
    yPos = y;
    bState = s;
    xVel = 1;
    yvel = 1;
}
/**
 * Reset the ball
 */
void LogicBall::reset(ballState s, int x, int y) {
    xPos = x;
    yPos = y;
    bState = s;
    xVel = xiv;
    yvel = yiv;
}
/**
 * set the speed of the ball in x, y direction
 * @param xv velocity in x dir
 * @param yv velocity in y dir
 */
void LogicBall::setSpeed(int xv=1, int yv=1) {
    xVel = xv;
    yvel = yv;
}
/**
 * switch the state of the ball
 */
void LogicBall::switchState() {
    switch (bState) {
        case STAY:
            bState = MOVE;
            break;
        case MOVE:
            bState = STAY;
        default:
            break;
    }
}
/**
 * return the ball position
 */
int LogicBall::getBxPos() {
    return LogicBall::xPos;
}
/**
 * return the ball position
 */
int LogicBall::getByPos() {
    return LogicBall::yPos;
}
/**
 * return the ball state
 */
ballState LogicBall::getBState() {
    return LogicBall::bState;
}
/**
 * move the ball one step further
 */
void LogicBall::moveOneSetp() {
    xPos = xPos + xVel;
    yPos = yPos + yvel;
}
/**
 * upfate the ball's position
 */
void LogicBall::updatePos(int time) {
    xPos = xPos + xVel * time;
    yPos = yPos + yvel * time;
}
/**
 * switch ball's x dir
 */
void LogicBall::switchXdir() {
    xVel = -1 * xVel;
}
/**
 * switch ball's y dir
 */
void LogicBall::switchYdir() {
    yvel = -1 * yvel;
}

LogicBall::~LogicBall() {
}
/**
 * adjust the speed of the ball a little
 * @param diff
 */
void LogicBall::increaseSpeedx(int diff) {
    if (xVel<0){xVel = xVel - diff;}
    else {xVel = xVel + diff;}
}
void LogicBall::decreaseSpeedx(int diff) {
    if (abs(diff)>=abs(xVel)-SPEED_LOWBOUND){return;}
    else{
        if (xVel<0){xVel = xVel + diff;}
        else {xVel = xVel - diff;}
    }
}
void LogicBall::increaseSpeedy(int diff) {
    if (yvel<0){yvel = yvel - diff;}
    else {yvel = yvel + diff;}
}
void LogicBall::decreaseSpeedy(int diff) {
    if (abs(diff)>=abs(yvel)-SPEED_LOWBOUND){return;}
    else{
        if (yvel<0){yvel = yvel + diff;}
        else {yvel = yvel - diff;}
    }
}
/**
 * Add a small perturbation after the collision
 * @param xORy change the ball's speed in x(0) or y(1) direction
 */
void LogicBall::changeSpeed(int xORy) {
    std::srand(std::time(nullptr));
    int temps = std::rand()%(SPEED_UPPERBOUND / 5);
    int temp2 = std::rand()%2;
    // case increase speed
    if (temp2==0){
        // limit the speed with an upper bound
        if (xVel>=SPEED_UPPERBOUND || yvel >= SPEED_UPPERBOUND){ return;}
        else{
            if (xORy==0){increaseSpeedx(temps);}
            else{increaseSpeedy(temps);}
        }
    }
    // case decrease speed;
    else{
        if (xORy==0){decreaseSpeedx(temps);}
        else{decreaseSpeedy(temps);}
    }
}
/**
 * define the initial speed each round of the game
 */
void LogicBall::initSpeed(int xv, int yv) {
    xiv = xv;
    yiv = yv;
}

int LogicBall::getBxV() {
    return xVel;
}

int LogicBall::getByV() {
    return yvel;
}
/**
 * switch side
 */
void LogicBall::setSpeedxOppo() {
    xVel = -1 * xVel;
}




