//
// Created by angle on 2022/2/14.
//

#ifndef PONG1_BALL_H
#define PONG1_BALL_H

#include <cmath>

enum ballState{ STAY, MOVE };

class LogicBall{
public:

    // constructor
    LogicBall();
    ~LogicBall();
    LogicBall(ballState s, int x, int y);

    // reset the ball
    void reset(ballState s, int x, int y);
    // set the ball's moving speed
    void setSpeed(int xv, int yv);
    void setSpeedxOppo();
    // give default value of speed
    void initSpeed(int xv, int yv);
    // change the ball's state
    void switchState();
    // move the ball
    void moveOneSetp();
    void updatePos(int time);
    // switch ball's direction
    void switchXdir();
    void switchYdir();
    // add a small perturbation after the collision
    void changeSpeed(int xORy);
    void increaseSpeedx(int diff);
    void increaseSpeedy(int diff);
    void decreaseSpeedx(int diff);
    void decreaseSpeedy(int diff);


    // return the ball's position
    int getBxPos();
    int getByPos();
    // return the ball's velocity
    int getBxV();
    int getByV();
    // return the ball's state
    ballState getBState();

private:
    // the position of the ball
    int xPos, yPos;
    // the state of the ball
    ballState bState;
    // the moving velocity of the ball;
    int xVel, yvel;
    // default (initial) value of speed
    static int xiv, yiv;

};

#endif //PONG1_BALL_H
