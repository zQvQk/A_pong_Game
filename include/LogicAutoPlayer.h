#ifndef CSCI437_AUTOPLAYER_H
#define CSCI437_AUTOPLAYER_H

#include "LogicPaddle.h"

class LogicAutoPlayer: public LogicPaddle{
public:
    LogicAutoPlayer(paddleState state, int i, int i1);
    ~LogicAutoPlayer();
    void updatePos(int time, int screenBound) override;

};

#endif //CSCI437_AUTOPLAYER_H
