#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_SetAppMetadata("SDL Test", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("Magma Shooter", 1024, 768, 0,
        &window, &renderer))
        return 1;

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Impossible d'activer le VSync : %s", SDL_GetError());
    }

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, 1024, 768,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    bool isGameOver = false;
    bool isWin = false;
    bool gameStart = false;
    bool isPaused = false;
    bool keepGoing = true;
    float gameTime = 0;
    float timePrev = 0;
    float timeStart = 0;
    while (keepGoing) {
        float now = float(SDL_GetTicks()) / 1000.0f;
        float dt = now - timePrev;
        timePrev = now;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            /*else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.button.x;
                float my = event.button.y;
                if (isPaused) {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            isPaused = false;
                            gameStart = false;
                        }
                    }
                    if (mx >= play->buttonRect.x && mx <= play->buttonRect.x + play->buttonRect.w &&
                        my >= play->buttonRect.y && my <= play->buttonRect.y + play->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            play->Press(renderer);
                            SDL_RenderPresent(renderer);
                            isPaused = false;
                        }
                    }
                }
                else if (isWin) {
                    if (isLvl1 && mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                        my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            start->Press(renderer);
                            SDL_RenderPresent(renderer);
                            isWin = false;
                            isLvl1 = false;
                            timeStart = now;
                            gameTime = now - timeStart;
                            shootCooldown = gameTime;
                        }
                    }
                    else if (!isLvl1 && mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            keepGoing = false;
                        }
                    }
                }
                else if (!gameStart) {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            keepGoing = false;
                        }
                    }
                    if (mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                        my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            start->Press(renderer);
                            SDL_RenderPresent(renderer);
                            gameStart = true;
                            timeStart = now;
                        }
                    }
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                case SDLK_Z: isUp = true; break;
                case SDLK_D: isRight = true; break;
                case SDLK_Q: isLeft = true; break;
                case SDLK_S: isDown = true; break;

                case SDLK_SPACE:
                    if (canShoot) {
                        Shoot* shoot = new Shoot(renderer, ship);
                        shoots.push_back(shoot);
                        canShoot = false;
                        shootCooldown = gameTime;
                    }
                    break;
                case SDLK_ESCAPE: isPaused = !isPaused; break;
                }
            }
            if (event.type == SDL_EVENT_KEY_UP) {
                switch (event.key.key) {
                case SDLK_Z: isUp = false; break;
                case SDLK_D: isRight = false; break;
                case SDLK_Q: isLeft = false; break;
                case SDLK_S: isDown = false; break;
                }
            }*/
        }

        SDL_RenderClear(renderer);

        /*if (isWin) {
            if (isLvl1) {
                menu.MenuNextLevelRenderer(renderer, win, play);
            }
            else {
                menu.MenuWinRenderer(renderer, win, exit);
            }
            score->Render(renderer);
        }
        else if (isGameOver) {
            menu.MenuGameOverRenderer(renderer, gameOver);
            score->Render(renderer);
            gameStart = false;
        }
        else if (isPaused) {
            menu.MenuPauseRenderer(renderer, pause, play);
        }
        else if (gameStart) {
            gameTime = now - timeStart;
            if (isLvl1) {
                game.Update(dt, ship, shoots, level_1, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                game.Collisions(renderer, shoots, level_1->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                game.GameRenderer(renderer, ship, shoots, *level_1);
            }
            else {
                game.Update(dt, ship, shoots, level_2, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                game.Collisions(renderer, shoots, level_2->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                game.GameRenderer(renderer, ship, shoots, *level_2);
            }
        }
        else {
            menu.MenuRenderer(renderer, exit, start);
        }*/

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
