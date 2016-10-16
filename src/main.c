#include "../include/main.h"

int main(int argc, char** argv)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error! %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = 
        SDL_CreateWindow("jportal test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                320, 240, 0); 
    if (window == NULL) {
        printf("SDL_CreateWindow error! %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = 
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer error! %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    for (;;) {
        SDL_Event evt;

        while (SDL_PollEvent(&evt)) {
            switch (evt.type)
            {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                switch (evt.key.keysym.sym)
                {
                    case 'q': goto quit;
                    case 'w': break;
                    default: break;
                }
            case SDL_QUIT: goto quit;
            }
        }

        SDL_Delay(10);
    }
quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
	return EXIT_SUCCESS;
}
