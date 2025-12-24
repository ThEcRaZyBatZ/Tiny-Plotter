# tiny_plotter

**tiny_plotter** is a lightweight 2D function plotter written in C using **SDL3** and **tinyexpr**.  
It allows you to visualize mathematical functions interactively from the command line.

---

## Features

- Plot any valid expression of `x`, e.g., `sin(x)`, `x^2 + 3*x + 1`, `ln(x)`  
- Smooth 2D plotting with axes  
- Supports keyboard panning (W/A/S/D)
- Lightweight and portable C code  

---

## To Build
-  gcc src/main.c src/tiny_expr.c src/fun.c -o output/tiny_plotter $(pkg-config --cflags --libs sdl3 sdl3-image) -lm on bash
-  its commented out in main.c as well
-  SDL_Hint to be set according to the user's device in fun.c
-  make sure SDL and SDL_Image are installed

---

## To Run
- ./output/tiny_plotter "x^2 + 3*x + 1"
- ./output/tiny_plotter "sin(x)"
- ./output/tiny_plotter "ln(x)"
- ./output/tiny_plotter "x*sin(x)"

---


## Screenshots

![Plot window](screenshots/plot.png)

