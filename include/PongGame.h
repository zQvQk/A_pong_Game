#ifndef PONG1_PONGGAME_H
#define PONG1_PONGGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "LogicPaddle.h"
#include "LogicBall.h"
#include "LogicAutoPlayer.h"


// Record the State of the Game
enum GameState{ START, PLAYING, WIN, LOSE };
enum Mode{AI = 0, PLAYER = 1};

class PongGame {
public:
    PongGame();
    ~PongGame();

    void init();
    void gameLoop();
    void cleanUP();

    // Message Report
    static void csci437_error(const std::string& msg);
    static void csci437_img_error(const std::string& msg);
    static void csci437_ttf_error(const std::string& msg);


private:
    //Screen dimension constants
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    // Refresh rate
    static const int FPS;
    static const int FRAME_RATE;
//    static int x;

    // paddle width & height
    static const int pw;
    static const int ph;
    // ball width & height
    static const int bw;
    static const int bh;
    // Score required to win
    static const int scoreToWin;
    // speed
    static int bsx;
    static int bsy;
    static int ps;
    // paddles initial position
    static int pix1;
    static int piy1;
    static int pix2;
    static int piy2;
    //ball initial position
    static int bix;
    static int biy;
    static bool changed_score1;
    static bool changed_score2;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screenSurface;
    SDL_Texture *startImagetexture;
    SDL_Texture* textScore1;
    SDL_Texture* textScore2;
    SDL_Texture* textWin;
    SDL_Texture* textLose;
    SDL_Texture* textKeys;
    SDL_Texture* textKeys2;
    // for Audio
//    SDL_AudioSpec wavSpec;
//    SDL_AudioDeviceID device;
//    static Uint8 *buff;
//    static Uint32 soundLen;
//    static Uint32 soundPos;
//    int soundEnd;

    static GameState state;
    static Mode mode;
    static bool PAUSE;

    // Entities:
    LogicPaddle *player1;
    LogicPaddle *player2;
//    LogicAutoPlayer *playerAI;

    LogicBall *ball;

    //players' scores
    static int player1Score;
    static int player2Score;

    // game logics:
    void updateLogic(int time);
    bool checkCollision(int s, int bx, int by, int px, int py);
    static bool checkLRBoundary(int posx, int posy, int leftb, int rightb);
    static void updateScore(int player);
    void switchSide(int player);
    int calDestY();

    // game views:
    void updateView();
    void renderStartWindow();
    void renderPLAYINGWindow();
    void renderWINWidow();
    void renderLOSEWidow();
    SDL_Texture* renderText(SDL_Renderer *r, const std::string& msg, int fontsize,SDL_Color c);
    void renderScore1(SDL_Renderer *r);
    void renderScore2(SDL_Renderer *r);
    void renderPaddle(SDL_Renderer *r, int x, int y);
    void renderBall(SDL_Renderer *r, int x, int y);
    void renderKeys(SDL_Renderer *r);
    void jumptoPLAYING();



};

#endif //PONG1_PONGGAME_H
