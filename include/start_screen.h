//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_START_SCREEN_H
#define PROGRA_START_SCREEN_H

typedef enum
{
    START_SCREEN_PLAY = 0,
    START_SCREEN_LOAD,
    START_SCREEN_QUIT,
    START_SCREEN_LOAD1,
    START_SCREEN_LOAD2,
    START_SCREEN_LOAD3,
    START_SCREEN_NONE
} start_screen_result_e;

start_screen_result_e start_screen(void);

#endif //PROGRA_START_SCREEN_H
