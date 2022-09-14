#include "PongGame.h"

// Run the Game
int main(int argc, char** argv) {
    PongGame pongGame;
    pongGame.init();
    pongGame.gameLoop();
    pongGame.cleanUP();
    return 0;
}