/*
  Insomnia is a program that
  Prevents your PC going to
  sleep.
*/


// Include libraries & define paths //
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include <stdio.h>

#define PATH "/usr/local/bin/insomnia"
#define FONT_PATH "/etc/insomnia/font.ttf"
#define ICON_PATH "/etc/insomnia/icon.bmp"
#define ASSET_PATH "/etc/insomnia"


// Main function //
int main(int argc, const char **argv) {

  // Check if uninstall argument specified //
  if (argc > 1 && strcmp(argv[1], "uninstall") == 0) {

    // Check if the user is root and throw error if not //
    if (getuid()) {
      printf("You must be root to run the uninstall script.\n");
      return 13;
    }


    // Uninstall process //
    remove(FONT_PATH);
    remove(ICON_PATH);

    rmdir(ASSET_PATH);
    
    return remove(PATH);
  }
  
  
  // Init SDL & SDL_ttf //
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  
  
  // Create window & renderer //
  SDL_Window *window = SDL_CreateWindow("Insomnia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 100, SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);


  // Define misc stuff //
  SDL_Event event;
  bool exit = false;
  int w, h, win_w, win_h;
  
  
  // Load & set window icon //
  SDL_Surface *icon = SDL_LoadBMP(ICON_PATH);
  SDL_SetWindowIcon(window, icon);


  // Disable sleep/screensaver //
  SDL_DisableScreenSaver();


  // Load font //
  TTF_Font *font = TTF_OpenFont(FONT_PATH, 48);


  // Create & render text //
  SDL_Surface *text_surf = TTF_RenderText_Blended(font, "Sleep mode disabled", {235, 235, 235, 255});
  SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, text_surf);
  

  // Create text rect //
  SDL_QueryTexture(text, NULL, NULL, &w, &h);
  SDL_Rect text_rect;
  
  
  // Main loop //
  while (!exit) {

    // Render bg //
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 17, 30, 36, 255);
    
    
    // Update rect & render text //
    SDL_GetWindowSize(window, &win_w, &win_h);
    text_rect = {win_w / 2 - w / 2, win_h / 2 - h / 2, w, h};

    SDL_RenderCopy(renderer, text, NULL, &text_rect);


    // Update renderer //
    SDL_RenderPresent(renderer);
    

    // Some delay //
    SDL_Delay(5);
    
    
    // Event handler //
    SDL_PollEvent(&event);
    
    switch(event.type) {

      // If Quit event received //
      case SDL_QUIT:
	      exit = true;
    }
  }


  // Cleanup //
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_FreeSurface(icon);
  SDL_FreeSurface(text_surf);

  SDL_DestroyTexture(text);
  
  TTF_CloseFont(font);

  SDL_Quit();
  TTF_Quit();

  
  // Return 0 on success //
  return 0;
}
