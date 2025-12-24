#include "../headers/main.h"

double y_val(struct screen* s,double x){ //returns the yval of the x val as in return f(x)
    s->x_val = x;
    return te_eval(s->expr_compiled);
}

bool screen_init(struct screen* s){ //initialises the screen
    // SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "x11"); //depends on usecase
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("screen Init Failed");
        return false;
    }

    s->window=SDL_CreateWindow(TITLE,WIDTH,HEIGHT,0);
    if(!s->window){
        SDL_Log("create window failed");
        return false;
    }

    s->renderer= SDL_CreateRenderer(s->window,NULL);
    if(!s->renderer){
        SDL_Log("create render failed");
        return false;
    }


    te_variable vars[] = {
        {"x", &s->x_val}
    };

    int err;
    s->expr_compiled = te_compile(s->expr, vars, 1, &err);
    if (!s->expr_compiled) {
        SDL_Log("Parse error at position %d\n", err);
        return false;
    }
    s->cam_x=0.0;
    s->cam_y=0.0;
    s->cam_step=CAM_STEP;   //change if needed 


    s->is_running=true;
    return true;
}

void screen_events(struct screen* s){ //poll event loop
    while(SDL_PollEvent(&s->event)){
        switch(s->event.type){
            case SDL_EVENT_QUIT:
                s->is_running=false;
                break;
            case SDL_EVENT_KEY_DOWN:
            switch(s->event.key.key){
                case SDLK_W: s->cam_y += s->cam_step; break;
                case SDLK_S: s->cam_y -= s->cam_step; break;
                case SDLK_D: s->cam_x -= s->cam_step; break;
                case SDLK_A: s->cam_x += s->cam_step; break;
                default: break;
            }
            break;
            default:
                break;
        }
    }
}

void plot_axes(struct screen* s){ //plots the axes
    SDL_SetRenderDrawColor(s->renderer, 50, 50, 50, 255);
    int x_axis = HEIGHT/2 - (int)(s->cam_y * SCALE);
    int y_axis = WIDTH/2 - (int)(s->cam_x * SCALE);
    SDL_RenderLine(s->renderer, 0, x_axis, WIDTH, x_axis);
    SDL_RenderLine(s->renderer, y_axis, 0, y_axis, HEIGHT);
}

void plot_function(struct screen* s){ //plots the function
    SDL_SetRenderDrawColor(s->renderer, 255, 255, 255, 255);
    int prevx=-1;
    int prevy=-1;
    double x,y;int py;
    for(int px=0;px<WIDTH;px++){

        x=(px-WIDTH/2)/SCALE + s->cam_x;
        y= y_val(s,x) + s->cam_y;
        py=HEIGHT/2-(int)(y*SCALE);
        
        if(SDL_isnan(y)) prevx=-1;
        if(SDL_isinff(y)&&y<0) py=HEIGHT-1;
        if(SDL_isinff(y)&&y>0) py=0;
        if(py<0 || py>=HEIGHT){
            prevx=-1;
            continue;
        }
        if(prevx!=-1){
            SDL_RenderLine(s->renderer,prevx,prevy,px,py);
        }
        prevx=px;
        prevy=py;
    }
}



void screen_plot(struct screen*s){ //main plot function
    SDL_SetRenderDrawColor(s->renderer,0,0,0,255);
    SDL_RenderClear(s->renderer);
    plot_axes(s);
    plot_function(s);
    SDL_RenderPresent(s->renderer);
}

void screen_run(struct screen* s){ //outer loop
    SDL_Log("running\n");
    while(s->is_running){
        screen_events(s);
        screen_plot(s);
        SDL_Delay(16);
    }
}


void screen_quit(struct screen* s){

    if(s->expr_compiled){
        te_free(s->expr_compiled);
        s->expr_compiled=NULL;
    }
    if(s->renderer){
        SDL_DestroyRenderer(s->renderer);
        s->renderer=NULL;
    }
    if(s->window){
        SDL_DestroyWindow(s->window);
        s->window=NULL;
    }

    s=NULL;
    SDL_Quit();
    SDL_Log("Everything has been freed succesfully\n");

}