#include "LogicAutoPlayer.h"

LogicAutoPlayer::LogicAutoPlayer(paddleState state, int i, int i1) : LogicPaddle(state, i, i1) {

}

LogicAutoPlayer::~LogicAutoPlayer() = default;

void LogicAutoPlayer::updatePos(int time, int screenBound) {
    if(pState == WAIT){return;}
    else{
        if (ballcorrectPos<=(yPos+2)){
            int attemptY = yPos - ps * time;
            // case CAN move
            if (attemptY > 0){
                yPos = attemptY;
            }
                // case no space to move upward
            else{
                yPos = 0;
            }
        }
        else if (ballcorrectPos>(yPos+paddleh-2)){
            int attemptY = yPos + ps * time;
            // case CAN move
            if (attemptY < screenBound){
                yPos = attemptY;
            }
                // case no space to move upward
            else{
                yPos = screenBound;
            }
        }
        else{
            pState = WAIT;
        }
    }
}

