#pragma once
#include <stdio.h>
#include <stdint.h>
#include "SDL.h"

//#define EXPORT_TO_PNG
//#define EXPORT_SCREENSHOT_TO_PNG
//#define BLOCK_BACKEND
#define DEBUG_PRINTS
#define TITLE "Fuss in space"
#define WINDOW_WIDTH 1920//1280
#define WINDOW_HEIGHT 1040//720


#define WINDOW_WIDTH 1920//1280
#define WINDOW_HEIGHT 1040//720

#define TITLE "Fuss in space"

#define SCREEN_CENTER_Y 0
#define SCREEN_CENTER_X 1
#define SCREEN_RIGHT_ALIGN 2
#define SCREEN_LEFT_ALIGN 3
#define SCREEN_TOP_ALIGN 4
#define SCREEN_BOT_ALIGN 5

#define ALIGN_CENTER 0


extern const char* DEFAULT_ADDRESS;
extern const char* SET;
extern const char* PATH;
extern SDL_Rect screen_size;


<<<<<<< HEAD

//funcs
#define DEBUG_PRINTS
=======
>>>>>>> 5261913f04597a8da383b27696458fed177b202a

#ifdef DEBUG_PRINTS
# define cprintf(...) {printf("[" __FILE__ "] "); printf(__VA_ARGS__);}
#else
# define cprintf(...)
#endif

#define eprintf(...) {fprintf(stderr, "[" __FILE__ "] "); fprintf(stderr, __VA_ARGS__);}

<<<<<<< HEAD

=======
>>>>>>> 5261913f04597a8da383b27696458fed177b202a

inline uint16_t convertWidth(uint16_t x)
{
    return uint16_t(((float)x)/ WINDOW_WIDTH * screen_size.w);
}

inline uint16_t convertHeight(uint16_t y)
{
    return uint16_t(((float)y) / WINDOW_HEIGHT * screen_size.h);
}

inline const SDL_Rect* convertRect(const SDL_Rect* dst)
{
    return new SDL_Rect{ convertWidth(dst->x), convertHeight(dst->y), convertWidth(dst->w), convertHeight(dst->h) };
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