#include "LogicPaddle.h"

int LogicPaddle::ballcorrectPos = 0;
int LogicPaddle::paddlew = 0;
int LogicPaddle::paddleh = 0;

/**
 * constructor
 */
LogicPaddle::LogicPaddle() {
    xPos =  0;
    yPos =  0;
    pState = WAIT;
    ps = 1;
}
/**
 * constructor with two arguments
 * @param s state of the paddle
 * @param x position of the paddle
 * @param y position of the paddle
 */
LogicPaddle::LogicPaddle(paddleState s, int x, int y) {
    xPos = x;
    yPos = y;
    pState = s;
    ps = 1;
}
/**
 * reset the paddle
 * @param s state of the paddle
 * @param x position of the paddle
 * @param y position of the paddle
 */
void LogicPaddle::reset(paddleState s, int x, int y) {
    xPos = x;
    yPos = y;
    pState = s;
}
/**
 * change the state of the paddle
 */
void LogicPaddle::setState(paddleState s) {
    pState = s;
}
/**
 * move one step further
 */
void LogicPaddle::moveOneSetp() {
    switch (pState) {
        case UP:
            yPos--;
            break;
        case DOWN:
            yPos++;
            break;
        default:
            break;
    }
}
/**
 * set the velocity of the paddle
 * @param s velocity
 */
void LogicPaddle::setSpeed(int s) {
    ps = s;
}
/**
 * @return paddle's position
 */
int LogicPaddle::getBxPos() {
    return xPos;
}
/**
 * @return paddle's position
 */
int LogicPaddle::getByPos() {
    return yPos;
}
/**
 * @return paddle's state
 */
paddleState LogicPaddle::getPState() {
    return pState;
}
 /**
  * update the paddle's position
  * @param time time the paddle moved
  * @param screenBound MAX value the yPos can be
  */
void LogicPaddle::updatePos(int time, int screenBound) {
    if(pState == UP){
        int attemptY = yPos - ps * time;
        // case CAN move
        if (attemptY > 0){
            yPos = attemptY;
        }
        // case no space to move upward
        else{
            yPos = 0;
            pState = WAIT;
        }
    }
    if(pState == DOWN){
        int attemptY = yPos + ps * time;
        // case CAN move
        if (attemptY < screenBound){
            yPos = attemptY;
        }
        // case no space to move upward
        else{
            yPos = screenBound;
            pState = WAIT;
        }
    }
}
void LogicPaddle::init(int w, int h) {
    paddlew = w;
    paddleh = h;
}
/**
 * set the correct position of the ball
 * @param y correct position
 */
void LogicPaddle::setDesty(int y) {
    // case the ball is moving towards right
    if (y==-1){pState = WAIT;}
    else{
        ballcorrectPos = y;
        pState = UP;
    }
}

LogicPaddle::~LogicPaddle() {

}
