#include "PongGame.h"

#define START_IMAGE "../resource/start.jpg"

// Screen dimension constants
const int PongGame::SCREEN_WIDTH = 1024;
const int PongGame::SCREEN_HEIGHT = 768;
GameState PongGame::state = START;
Mode PongGame::mode = AI;
bool PongGame::PAUSE = true;
// Refresh rate
const int PongGame::FPS = 60;
const int PongGame::FRAME_RATE = 1000/FPS;
// settings of paddles and balls
const int PongGame::pw = 30;
const int PongGame::ph = 100;
const int PongGame::bw = 30;
const int PongGame::bh = 30;
int PongGame::bsx = 15;
int PongGame::bsy = 25;
int PongGame::ps = 10;
// paddles initial position
int PongGame::pix1 = 50;
int PongGame::piy1 = SCREEN_HEIGHT / 2;
int PongGame::pix2 = SCREEN_WIDTH-50-pw;
int PongGame::piy2 = SCREEN_HEIGHT / 2;
//ball initial position
int PongGame::bix = SCREEN_WIDTH / 2;
int PongGame::biy = SCREEN_HEIGHT / 2;
//players' scores
const int PongGame::scoreToWin = 11;
int PongGame::player1Score = 0;
int PongGame::player2Score = 0;
bool PongGame::changed_score1 = false;
bool PongGame::changed_score2 = false;
//int PongGame::x = 0;
/**
 * Constructor of the Pong Game
 */
PongGame::PongGame(){
    window = nullptr;
    renderer = nullptr;
    screenSurface = nullptr;
    startImagetexture = nullptr;
}
/**
 * Initialization
 */
void PongGame::init(){
    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) csci437_error("SDL could not initialize!");
    if (SDL_Init(SDL_INIT_AUDIO) < 0) csci437_error("SDL could not initialize!");

    // Create window
    window = SDL_CreateWindow( "CSCI-437 the PongGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == nullptr ) csci437_error("Window could not be created!");

    // Get window surface
    screenSurface = SDL_GetWindowSurface( window );
    if(screenSurface == nullptr) csci437_error("Unable to get window surface!");

    // Create renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == nullptr) csci437_error("Unable to create renderer!");

    // init TTF
    if( TTF_Init() < 0 ) csci437_ttf_error("Unable to initialize TTF!");

    // Load the wav
//    if (SDL_LoadWAV("../resource/ballOut.wav", &wavSpec, &buff, &soundLen) == NULL) csci437_error("Unable to create renderer!");
//    device = SDL_OpenAudioDevice(NULL, SDL_FALSE, &wavSpec, NULL, 0);
//    if (!device) {
//        csci437_error("Unable to create renderer!");
//        SDL_FreeWAV(buff);
//    }

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Load the image background for start state
    SDL_Surface* startImageSurface = IMG_Load(START_IMAGE);
    if(startImageSurface == nullptr) csci437_img_error("Could not image!");

    // convert to texture
    startImagetexture = SDL_CreateTextureFromSurface( renderer, startImageSurface );
    if(startImagetexture == nullptr) csci437_error("Could not create texture from surface!");

    // free the surface (since has converted the surface to texture)
    SDL_FreeSurface( startImageSurface );
    startImageSurface = nullptr;

    // Prepare for some text:
    SDL_Color color = { 255, 255, 255 };
    textWin = renderText(renderer, "WIN !",100,color);
    textLose = renderText(renderer, "lose ...",50,color);
    textKeys = renderText(renderer, "q : shut down;  b : restart",50,color);
    textKeys2 = renderText(renderer, "= : speed up;  - : slow down",50,color);

    state = START;

    // Update the view
    updateView();
}
/**
 * the Game Loop
 */
void PongGame::gameLoop(){
    bool running = true;
    SDL_Event e;
    // To adjust the refresh rate
    uint32_t beginTime;
    uint32_t lastTime;
    uint32_t diff;
    int delay;

    // While application is running
    while( running ) {
        beginTime = SDL_GetTicks();
        //
        // Re-render the window
        updateView();

        // Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            // User requests quit
            if( e.type == SDL_QUIT ) running = false;
            // User presses a key
            if( e.type == SDL_KEYDOWN )
            {
                if( e.key.keysym.sym == SDLK_q ) running = false;
                // Restart the game
                if (e.key.keysym.sym == SDLK_b){
                    state = START;
                }
                if (state == START) {
                    //start game by default
                    if (e.key.keysym.sym == SDLK_RETURN){
                        jumptoPLAYING();
                    }
                    if (e.key.keysym.sym == SDLK_1){
                        mode = AI;
                        jumptoPLAYING();
                    }
                    if (e.key.keysym.sym == SDLK_2){
                        mode = PLAYER;
                        jumptoPLAYING();
                    }
                }
                if (state == PLAYING ) {
                    if (e.key.keysym.sym == SDLK_SPACE){
                        PAUSE = !PAUSE;
                    }
                    if (e.key.keysym.sym == SDLK_UP){
                        player2->setState(UP);
                    }
                    if (e.key.keysym.sym == SDLK_DOWN){
                        player2->setState(DOWN);
                    }
                    if (mode==PLAYER && e.key.keysym.sym == SDLK_w){
                        player1->setState(UP);
                    }
                    if (mode==PLAYER && e.key.keysym.sym == SDLK_s){
                        player1->setState(DOWN);
                    }
                    // control the speed of the ball
                    if (e.key.keysym.sym == SDLK_MINUS){
                        ball->decreaseSpeedx(1);
                        ball->decreaseSpeedy(1);
                    }
                    if (e.key.keysym.sym == SDLK_EQUALS){
                        ball->increaseSpeedx(1);
                        ball->increaseSpeedy(1);
                    }
                }
            }

        }
        lastTime = SDL_GetTicks();
        diff = lastTime - beginTime;

        if (state == PLAYING){
            if (!PAUSE){
                updateLogic(int(diff));
            }
            if (player1Score == scoreToWin){
                state = LOSE;
            }
            if (player2Score == scoreToWin){
                state = WIN;
            }
        }

        delay = FRAME_RATE - int(diff);
        if (delay > 0) {
            SDL_Delay(delay);
        }

    }
}
/**
 * Clean up
 */
void PongGame::cleanUP(){
    // Destroy renderer
    SDL_DestroyTexture( startImagetexture );
    // Destroy renderer
    SDL_DestroyRenderer( renderer );
    // Destroy renderer
    SDL_FreeSurface( screenSurface );
    // Destroy window
    SDL_DestroyWindow( window );

    // Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
}
/**
 * Render the window based on current state
 */
void PongGame::updateView(){
    switch (state){
        case START:
            renderStartWindow();
            break;
        case PLAYING:
            renderPLAYINGWindow();
            break;
        case WIN:
            renderWINWidow();
            break;
        case LOSE:
            renderLOSEWidow();
            break;
        default:
            break;
    }
}
/**
 * Render the window at the START state
 */
void PongGame::renderStartWindow(){
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    int w,h;
    SDL_QueryTexture(startImagetexture, nullptr,nullptr,&w,&h);
    SDL_Rect startImagedst = { (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h};
    SDL_RenderCopy(renderer, startImagetexture, nullptr, &startImagedst);
    SDL_RenderPresent(renderer);
}
/**
 * Report Message
 * @param msg message
 */
void PongGame::csci437_error(const std::string& msg)
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}
/**
 * Report Message
 * @param msg message
 */
void PongGame::csci437_img_error(const std::string& msg)
{
    std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
    exit(0);
}
void PongGame::csci437_ttf_error(const std::string &msg) {
    std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
    exit(0);
}
/**
 * the window that player2 wins
 */
void PongGame::renderWINWidow() {
    SDL_RenderClear(renderer);
    // freeze the playing window
    renderPaddle(renderer, player1->getBxPos(), player1->getByPos());
    renderPaddle(renderer, player2->getBxPos(), player2->getByPos());
//    renderBall(renderer,ball->getBxPos(),ball->getByPos());
    renderScore1(renderer);
    renderScore2(renderer);
    renderKeys(renderer);
    // write "WIN"
    int w,h;
    SDL_QueryTexture(textWin, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos = { (SCREEN_WIDTH - w) / 2 + 200, (SCREEN_HEIGHT - h) / 2 - 200, w, h};
    SDL_RenderCopy(renderer, textWin, NULL, &scorePos);

    SDL_RenderPresent(renderer);
}
/**
 * the window that player1 wins
 */
void PongGame::renderLOSEWidow() {
    SDL_RenderClear(renderer);
    // freeze the playing window
    renderPaddle(renderer, player1->getBxPos(), player1->getByPos());
    renderPaddle(renderer, player2->getBxPos(), player2->getByPos());
//    renderBall(renderer,ball->getBxPos(),ball->getByPos());
    renderScore1(renderer);
    renderScore2(renderer);
    renderKeys(renderer);
    // write "LOSE" msg
    int w,h;
    SDL_QueryTexture(textWin, nullptr,nullptr,&w,&h);
    SDL_Rect scorePos = { (SCREEN_WIDTH - w) / 2 - 200, (SCREEN_HEIGHT - h) / 2 - 200, w, h};
    SDL_RenderCopy(renderer, textWin, NULL, &scorePos);

    SDL_RenderPresent(renderer);
}
PongGame::~PongGame() {
    delete player1;
    delete player2;
    delete ball;
}










