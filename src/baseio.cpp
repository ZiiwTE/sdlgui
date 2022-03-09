#include <iostream>
#include <tchar.h>
#include <thread>
//#include "program.h"
#include "aa.h"

#include "SDL.h"

using namespace std;

void copy(SDL_Surface* display, pixel* source, int width, int height);
void gf();

bool running = true;

programnw* mainprog;
SDL_Window* window;
SDL_Surface* surface;

int main(int argc, char* argv[])
{
    //main init
    mainprog = new programnw();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_StartTextInput();
    //printf("%d\n", SDL_IsTextInputActive());
    window = NULL;
    surface = NULL;
    window = SDL_CreateWindow(
        "GUI Engine",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1600,                               // width, in pixels
        900,                               // height, in pixels
        SDL_WINDOW_SHOWN // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    surface = SDL_GetWindowSurface(window);

    if (surface == NULL) {
        printf("error get surface\n");
        return -1;
    }

    //copy(surface, mainprog.getOrginalImg(), 1600, 900);
    //SDL_UpdateWindowSurface(window);

    //for (int i = 0; 1; i++)
    {
        //copy(surface, mainprog.getOrginalImg(), 1600, 900);
        //printf("%d\n", i);
    }



    bool quit = false;
    SDL_Event event;
    std::thread t(gf);
    //t.join();
    while (!quit) {
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_QUIT://ÍË³öÊÂ¼þ
            SDL_Log("quit");
            quit = true;
            break;
        case SDL_MOUSEMOTION:
            mainprog->itembox.mouseMove(event.button.x, event.button.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mainprog->itembox.click(event.button.x, event.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            mainprog->itembox.unclick(event.button.x, event.button.y);
            break;
        case SDL_KEYDOWN:
            //mainprog.itembox.keyDown(event.key.keysym);
        case SDL_TEXTINPUT:
            mainprog->itembox.textInput(event.text.text);
            //printf("%sAA\n\n\n\n", event.text.text);
        default:
            //SDL_Log("event type:%d", event.type);
            ;
        }
        //SDL_Log("event type:%d", event.type);
        //copy(surface, mainprog.getOrginalImg(), 1600, 900);
        //SDL_UpdateWindowSurface(window);
    }

    running = false;
    t.join();

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

void copy(SDL_Surface* display, pixel* source, int width, int height)
{
    Uint32* pixel = (Uint32*)display->pixels;
    int pos = 0;
    for (int i = 0; source[i].status != PIXEL_END; i++)
    {
        if (source[i].status == PIXEL_ENDL)
            i++;
        pixel[pos] = source[i].color;
        pos++;
    }
}

void gf()
{
    while (running)
    {
        copy(surface, mainprog->getOrginalImg(), 1600, 900);
        SDL_UpdateWindowSurface(window);
        //Sleep(10);
    }
}