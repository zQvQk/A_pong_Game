#ifndef PONG1_PADDLE_H
#define PONG1_PADDLE_H

enum paddleState{ WAIT, UP, DOWN };

class LogicPaddle{
public:
    // constructor
    LogicPaddle();
    LogicPaddle(paddleState s, int x, int y);
    ~LogicPaddle();

    // reset the paddle
    void reset(paddleState s, int x, int y);
    // set the paddle's moving speed
    void setSpeed(int s);
    // change the paddle's state
    void setState(paddleState s);
    void init(int w, int h);
    void setDesty(int y);

    // move the paddle
    void moveOneSetp();

    virtual void updatePos(int time, int screenBound);

    // return the paddle's position
    int getBxPos();
    int getByPos();
    // return the paddle's state
    paddleState getPState();

protected:
    // the position of the paddle
    int xPos, yPos;
    // the state of the paddle
    paddleState pState;
    // the moving velocity of the paddle;
    int ps;
    static int ballcorrectPos;
    static int paddlew, paddleh;

};

#endif //PONG1_PADDLE_H
