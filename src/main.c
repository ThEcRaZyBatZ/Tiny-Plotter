#include "../headers/main.h"

/*
compilation with gcc
gcc main.c fun.c tinyexpr.c -o ../output/tiny_plotter $(pkg-config --cflags --libs sdl3 sdl3-image) -lm
../output/tiny_plotter "sin(x)"

pressing w makes the axes go up
pressing s makes the axes come down
pressing d makes the axes move to the right
pressing a makes the axes move to the left
*/

int main(int argc, char **argv){

    struct screen my_screen={0};

    if(argc!=2) return -1;

    my_screen.expr=argv[1];
    if(!screen_init(&my_screen)){
        screen_quit(&my_screen);
        return -1;
    } 

    screen_run(&my_screen);

    screen_quit(&my_screen);
    return 0;
    
    
}