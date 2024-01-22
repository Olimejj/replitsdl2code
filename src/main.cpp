#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>


std::string const image_path = "media/images/";
std::string const font_path = "media/fonts/";

int randoms(){
    srand(time(NULL));
    int rand_num = rand() % 3 + 1;
    return rand_num;
}

int main(int argc, char* argv[]) {
    int choice;
    std::cout << "Welcome to Rock Paper Scissors!\n" << "enter a number between 1-3: ";
    std::cin >> choice; 
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);


    // Create an SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::string image_name = "rock.png";
    int rn = randoms();

    switch(rn){
        case 1:
            image_name = "rock.png";
            break;
        case 2:
            image_name = "paper.png";
            break;
        case 3:
            image_name = "scissors.png";
            break;
    }

    // Load the image
    SDL_Surface* imageSurface = IMG_Load((image_path + image_name).c_str());
    if (!imageSurface) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    if ( TTF_Init() < 0 ) {
	std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
}


    TTF_Font* gFont = NULL;
	gFont = TTF_OpenFont( "media/fonts/rpsfont.ttf", 250 );
	SDL_Color textColor = { 100, 200, 100 };
    std::string textureText = "ARE YOU READY?";
    //Load the font
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );


    // Convert surface to texture
    //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(imageSurface);


    SDL_Event event;
    bool quit = false;

    while (!quit) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the texture
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
