#include "atlas.h"
#include <SDL2/SDL.h>

int SDL_main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window =
      SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       320, 240, SDL_WINDOW_BORDERLESS);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderSetScale(renderer, 2, 2);
  SDL_SetWindowSize(window, 640, 480);
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  int done = 0;
  SDL_Event event;
  int time = 0;
  int values[3] = {32, 32, 32};
  int option = 0;
  int slider_direction = 0;
  int theme = 0;
  int themes[][3] = {
      {192, 0, 0},
      {0, 0, 192},
      {192, 0, 192},
  };
  int done_anim = 0;
  int done_anim_time = 0;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        done_anim = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          done_anim = 1;
          break;
        case SDLK_LEFT:
          slider_direction = -1;
          break;
        case SDLK_RIGHT:
          slider_direction = 1;
          break;
        case SDLK_UP:
          option -= 1;
          if (option == -1) {
            option = 3;
          }
          break;
        case SDLK_DOWN:
          option += 1;
          if (option == 4) {
            option = 0;
          }
          break;
        case SDLK_RETURN:
          theme += 1;
          if (theme == 3) {
            theme = 0;
          }
          break;
        }
        break;
      case SDL_KEYUP:
        slider_direction = 0;
        break;
      }
    }

    time += 1;

    if (option >= 0 && option <= 3) {
      values[option] += slider_direction;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                           themes[theme][2], 255);
    SDL_RenderDrawLine(renderer, 0, 240 - 240 / 3 - 2, 320, 240 - 240 / 3 - 2);

    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 128; x++) {
        if (atlas[y * ATLAS_WIDTH + x] == 0xff) {
          SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                                 themes[theme][2], 255);
          SDL_RenderDrawPoint(renderer, 4 + x, 4 + y);
        }
      }
    }

    for (int y = 240 - 240 / 3; y < 240; y++) {
      for (int x = 0; x < 320; x++) {
        if ((x + y) % 2 == 0) {
          SDL_SetRenderDrawColor(renderer, themes[theme][0] * 0.25,
                                 themes[theme][1] * 0.25,
                                 themes[theme][2] * 0.25, 255);
          SDL_RenderDrawPoint(renderer, x, y);
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      if (values[i] < 0) {
        values[i] = 0;
      }
      if (values[i] > 64) {
        values[i] = 64;
      }
      SDL_Rect outline_rect = {6, 240 - 240 / 3 + 2 + i * 16, 68, 12};
      if (option == i) {
        SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                               themes[theme][2], 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      }
      SDL_RenderDrawRect(renderer, &outline_rect);
      SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                             themes[theme][2], 255);
      SDL_Rect bg_rect = {8, 240 - 240 / 3 + 4 + i * 16, 64, 8};
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderFillRect(renderer, &bg_rect);
      for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 8; y++) {
          if (x < values[i] && (x + y) % 2 == 0) {
            SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                                   themes[theme][2], 255);
            SDL_RenderDrawPoint(renderer, 8 + x,
                                240 - 240 / 3 + 4 + y + i * 16);
          }
        }
      }
    }

    SDL_Rect theme_outline_rect = {74 + 6, 240 - 240 / 3 + 2, 68, 15};
    if (option == 3) {
      SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                             themes[theme][2], 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderDrawRect(renderer, &theme_outline_rect);
    SDL_Rect theme_bg_rect = {74 + 8, 240 - 240 / 3 + 4, 64, 11};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &theme_bg_rect);
    if (option == 3) {
      SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                             themes[theme][2], 255);
    } else {
      SDL_SetRenderDrawColor(renderer, themes[theme][0] * 0.25,
                             themes[theme][1] * 0.25, themes[theme][2] * 0.25,
                             255);
    }
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 128; x++) {
        if (atlas[(y + 16) * ATLAS_WIDTH + x] == 0xff) {
          SDL_RenderDrawPoint(renderer, 74 + 8 + 2 + x,
                              240 - 240 / 3 + 4 + 2 + y);
        }
      }
    }

    if (slider_direction == 0) {
      SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                             themes[theme][2], 255);
      for (int i = 1; i < 319; i++) {
        SDL_RenderDrawPoint(renderer, i,
                            SDL_sin((i + time * (values[2] - 32) * 0.1) * 0.05 *
                                    (values[0]) * 0.05) *
                                    values[1] +
                                160 / 2);
      }
    } else {
      for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 128; x++) {
          if (atlas[(y + 8) * ATLAS_WIDTH + x] == 0xff) {
            SDL_SetRenderDrawColor(renderer, themes[theme][0], themes[theme][1],
                                   themes[theme][2], 255);
            SDL_RenderDrawPoint(renderer, 320 / 2 - 66 / 2 + x,
                                160 / 2 - 8 / 2 + y);
          }
        }
      }
    }

    if (done_anim) {
      done_anim_time += 1;
    }

    SDL_Rect done_anim_rect1 = {0, 0, 320, done_anim_time * 4};
    SDL_Rect done_anim_rect2 = {0, 240 - done_anim_time * 4, 320,
                                done_anim_time * 4};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &done_anim_rect1);
    SDL_RenderFillRect(renderer, &done_anim_rect2);

    if (done_anim_time == 240 / 8) {
      done = 1;
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  SDL_Quit();

  return 0;
}
