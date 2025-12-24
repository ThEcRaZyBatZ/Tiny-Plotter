#ifndef MAIN_H
#define MAIN_H

#include "./tinyexpr.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 700
#define TITLE "tiny_plotter"
#define SCALE 25.0  //pixels per unit
#define CAM_STEP 0.2 //w a s d move strength

struct screen{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool is_running;
    char* expr;
    te_expr* expr_compiled;
    double x_val;
    double cam_x;   
    double cam_y;   
    double cam_step; 

};

bool screen_init(struct screen* s);
void screen_quit(struct screen* s);
void screen_run(struct screen* s);

#endif