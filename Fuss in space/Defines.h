#pragma once
#include <stdio.h>
#include <stdint.h>
#include "SDL.h"

#define EXPORT_TO_PNG
//#define EXPORT_SCREENSHOT_TO_PNG
#define BLOCK_BACKEND

extern const char* DEFAULT_ADDRESS;
extern const char* SET;
extern const char* PATH;
extern SDL_Rect screen_size;

#define DEBUG_PRINTS

#ifdef DEBUG_PRINTS
# define cprintf(...) {printf("[" __FILE__ "] "); printf(__VA_ARGS__);}
#else
# define cprintf(...)
#endif

#define eprintf(...) {fprintf(stderr, "[" __FILE__ "] "); fprintf(stderr, __VA_ARGS__);}

#define WINDOW_WIDTH 1920//1280
#define WINDOW_HEIGHT 1040//720

#define TITLE "Fuss in space"

inline uint16_t convertWidth(uint16_t x)
{
    
    return uint16_t(((float)x)/ WINDOW_WIDTH * screen_size.w);
}

inline uint16_t convertHeight(uint16_t y)
{
    return uint16_t(((float)y) / WINDOW_HEIGHT * screen_size.h);
}

enum C {
    C_MOVING_CHARACER = 14,
    C_JOINED_LOBBY = 32,
    C_LOBBY_ALREADY_EXISTS = 33,
    C_LOBBY_DOESNT_EXIST = 34,
    C_NOT_JOIN = 35,
    C_LOBBY_DATA = 40,
    C_GAME_STARTED = 45,
    C_GAME_DATA = 50,
    C_LEAVE_LOBBY = 36,
};

enum S{
    S_START_GAME = 50,
    S_CREATE_LOBBY = 41,
    S_JOIN_LOBBY = 42,
    S_LEAVE_LOBBY = 43,
    S_SCREENSHOT_TAKEN = 120,
    S_PLAYER_INPUT = 60,
};



template <typename T>
union Message
{
    T data;
    char data_ptr[sizeof(T)];
};