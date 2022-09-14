#include "PongGame.h"

/**
 * update the game logic
 */
void PongGame::updateLogic(int time) {
    PongGame::ball->updatePos(time);
    PongGame::player1->updatePos(time,(PongGame::SCREEN_HEIGHT - PongGame::ph));
    PongGame::player2->updatePos(time,(PongGame::SCREEN_HEIGHT - PongGame::ph));
    // get position of entities
    int ballPosx = PongGame::ball->getBxPos();
    int ballPosy = PongGame::ball->getByPos();
    int player1Posx = PongGame::player1->getBxPos();
    int player1Posy = PongGame::player1->getByPos();
    int player2Posx = PongGame::player2->getBxPos();
    int player2Posy = PongGame::player2->getByPos();

    // whether the ball is in the left-half(0) side or right-half(1) side:
    int side = (ballPosx < PongGame::SCREEN_WIDTH / 2) ? 0:1;
    if (side == 0){
        if (checkCollision(side, ballPosx, ballPosy, player1Posx, player1Posy)){
            PongGame::ball->updatePos(time);
            // AutoPlayer
            if (PongGame::mode==0){
                int desty = calDestY();
                PongGame::player1->setDesty(desty);
            }
        }
        else if (checkLRBoundary(ballPosx, ballPosy, player1Posx, player2Posx+ PongGame::pw)){
            updateScore(side);
            PongGame::ball->reset(STAY, PongGame::bix, PongGame::biy);
            PongGame::player1->reset(WAIT,PongGame::pix1, PongGame::piy1);
            PongGame::player2->reset(WAIT,PongGame::pix2, PongGame::piy2);
            switchSide(side);
        }
    }
    else {
        if (checkCollision(side, ballPosx, ballPosy, player2Posx, player2Posy)){
            PongGame::ball->updatePos(time);
            // AutoPlayer
            if (PongGame::mode==0){
                int desty = calDestY();
                PongGame::player1->setDesty(desty);
            }
        }
        else if (checkLRBoundary(ballPosx, ballPosy, player1Posx, player2Posx+ PongGame::pw)){
            updateScore(side);
            PongGame::ball->reset(STAY, PongGame::bix, PongGame::biy);
            PongGame::player1->reset(WAIT,PongGame::pix1, PongGame::piy1);
            PongGame::player2->reset(WAIT,PongGame::pix2, PongGame::piy2);
        }
    }
}
/**
 * Check if the ball and a paddle collides
 * @param bx position of ball
 * @param by position of ball
 * @param px position of paddle
 * @param py position of paddle
 * @return true if collides
 */
bool PongGame::checkCollision(int s, int bx, int by, int px, int py) {
    // note that the ball and the paddle have volumes
    // case left-half side
    if (s == 0){
        // check the upper & lower bound
        if (bx>(px + PongGame::pw) && (by<=0 || (by + PongGame::bh) >= PongGame::SCREEN_HEIGHT)){
            // add a small perturbation after the collision
            PongGame::ball->changeSpeed(0);
            PongGame::ball->switchYdir();
            return true;
        }
        // check the collision with left paddle
        else if (bx <= (px + PongGame::pw) && ( (by+PongGame::bh) >= py && by <= (PongGame::ph+py) ) ){
            PongGame::ball->changeSpeed(1);
            PongGame::ball->switchXdir();
//            // polymorphism used for autoPlayer
//            PongGame::player1->setDest();
            return true;
        }
    }
    // case right-half side
    else if (s == 1){
        // check the upper & lower bound
        if ((bx+PongGame::bw)<=PongGame::SCREEN_WIDTH && (by<=0 || (by + PongGame::bh) >= PongGame::SCREEN_HEIGHT)){
            PongGame::ball->changeSpeed(0);
            PongGame::ball->switchYdir();
            return true;
        }
            // check the collision with right paddle
        else if ( (bx + PongGame::bw) >= px && ((by+PongGame::bh) >= py && by <= (PongGame::ph+py) ) ){
            PongGame::ball->changeSpeed(1);
            PongGame::ball->switchXdir();
            return true;
        }
    }
    return false;
}
/**
 * check if the ball is in the boundary
 * @param bs position of the ball
 * @param by position of the ball
 * @return true if out of the boundary
 */
bool PongGame::checkLRBoundary(int posx, int posy, int leftb, int rightb) {
    return posx <= leftb || posx >= rightb;
}
/**
 * Update the players' scores
 */
void PongGame::updateScore(int player) {
    switch (player) {
        case 0:
            PongGame::player2Score++;
            PongGame::changed_score2 = true;
            break;
        case 1:
            PongGame::player1Score++;
            PongGame::changed_score1 = true;
            break;
        default:
            break;
    }
}
/**
 * calculate for the correct position of the ball
 * @return the correct position
 */
int PongGame::calDestY() {
    // return if the ball is moving towards right
    if (PongGame::ball->getBxV()>0){return -1;}
    else{
        double timeToHit = abs(PongGame::ball->getBxPos() - (PongGame::player1->getBxPos()+PongGame::pw)) *1.0 / abs(PongGame::ball->getBxV());
        int dest = PongGame::ball->getByPos() + int(timeToHit * PongGame::ball->getByV());
        return dest;
    }
}
/**
 * Switch side if wins
 */
void PongGame::switchSide(int player) {
    if (player==0){
        PongGame::ball->setSpeedxOppo();
    }
}

