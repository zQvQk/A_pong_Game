#include "PongGame.h"
#define TEXT_FONT_FILE "../resource/Arial.ttf"

/**
 * Render the window at the PLAYING state
 */
void PongGame::renderPLAYINGWindow(){
    SDL_RenderClear(renderer);
    renderPaddle(renderer, player1->getBxPos(), player1->getByPos());
    renderPaddle(renderer, player2->getBxPos(), player2->getByPos());
    renderBall(renderer,ball->getBxPos(),ball->getByPos());
    renderScore1(renderer);
    renderScore2(renderer);
    renderKeys(renderer);
    SDL_RenderPresent(renderer);
}
/**
 * render a paddle
 */
void PongGame::renderPaddle(SDL_Renderer *r, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect paddle = {x, y, PongGame::pw, PongGame::ph};
    SDL_RenderFillRect(renderer, &paddle);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
/**
 * render a ball
 */
void PongGame::renderBall(SDL_Renderer *r, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect paddle = {x, y, PongGame::bw, PongGame::bh};
    SDL_RenderFillRect(renderer, &paddle);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
/**
 * short cut to draw text
 * @return a texture
 */
SDL_Texture *PongGame::renderText(SDL_Renderer *r, const std::string& msg, int fontsize, SDL_Color c) {
    TTF_Font* font = TTF_OpenFont(TEXT_FONT_FILE, 50);
    SDL_Surface* text = TTF_RenderText_Solid(font, msg.c_str(), c );
    if ( text == NULL ) csci437_ttf_error("Unable to render text!");
    // convert to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, text );
    if(texture == NULL) csci437_error("Could not create texture from surface!");
    // clean up
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    return texture;
}
/**
 * initialize the window
 */
void PongGame::jumptoPLAYING() {
    state = PLAYING;
    PAUSE = true;
    player1Score = 0;
    player2Score = 0;
    changed_score1 = true;
    changed_score2 = true;
    if (mode==AI){
        player1 = new LogicAutoPlayer(WAIT, pix1, piy1);
    }
    else if (mode==PLAYER){
        player1 = new LogicPaddle(WAIT, pix1, piy1);
    }
    player2 = new LogicPaddle(WAIT, pix2, piy2);
    ball = new LogicBall(STAY,bix, biy);
    player1->init(pw,ph);
    ball->setSpeed(bsx,bsy);
    ball->initSpeed(bsx,bsy);
    player1->setSpeed(ps);
    player2->setSpeed(ps);
}
/**
 * render scores and update texture if the score changed
 */
void PongGame::renderScore1(SDL_Renderer *r) {
    if (changed_score1){
        SDL_Color color = { 255, 255, 255 };
        textScore1 = renderText(r, std::to_string(player1Score),50,color);
        changed_score1 = false;
    }
    int w,h;
    SDL_QueryTexture(textScore1, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos = { (SCREEN_WIDTH - w) / 2 - 100, (SCREEN_HEIGHT - h) / 2, w, h};
    SDL_RenderCopy(renderer, textScore1, NULL, &scorePos);
}
/**
 * render scores and update texture if the score changed
 */
void PongGame::renderScore2(SDL_Renderer *r) {
    if (changed_score2){
        SDL_Color color = { 255, 255, 255 };
        textScore2 = renderText(r, std::to_string(player2Score),50,color);
        changed_score2 = false;
    }
    int w,h;
    SDL_QueryTexture(textScore2, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos = { (SCREEN_WIDTH - w) / 2 + 100, (SCREEN_HEIGHT - h) / 2, w, h};
    SDL_RenderCopy(renderer, textScore2, NULL, &scorePos);
}
/**
 * draw the key guide
 */
void PongGame::renderKeys(SDL_Renderer *r) {
    int w,h;
    SDL_QueryTexture(textKeys, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos = { (SCREEN_WIDTH - w) / 2 -200, (SCREEN_HEIGHT - h) / 2+300, w, h};
    SDL_RenderCopy(renderer, textKeys, NULL, &scorePos);
    SDL_QueryTexture(textKeys2, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos2 = { 30, (SCREEN_HEIGHT - h) / 2+200, w, h};
    SDL_RenderCopy(renderer, textKeys2, NULL, &scorePos2);
}
