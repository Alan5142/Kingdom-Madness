//
// Created by alan2 on 25/02/2020.
//

#ifndef PROGRA_COLORS_H
#define PROGRA_COLORS_H

#include <stdint.h>
#include <curses.h>

// color constants
extern const uint16_t HEART_POINT_BACKGROUND;
extern const uint16_t HEART_POINT_FOREGROUND;
extern const uint16_t HEART_POINT_COLOR_PAIR;

extern const uint16_t HEART_LOST_BACKGROUND;
extern const uint16_t HEART_LOST_FOREGROUND;
extern const uint16_t HEART_LOST_COLOR_PAIR;

// score
extern const uint16_t SCORE_BACKGROUND;
extern const uint16_t SCORE_FOREGROUND;
extern const uint16_t SCORE_COLOR_PAIR;

// game
extern const uint16_t GAME_BACKGROUND;
extern const uint16_t GAME_FOREGROUND;
extern const uint16_t GAME_COLOR_PAIR;

extern const uint16_t POTION_LOW_BACKGROUND;
extern const uint16_t POTION_LOW_FOREGROUND;
extern const uint16_t POTION_LOW_COLOR_PAIR;

extern const uint16_t POTION_MEDIUM_BACKGROUND;
extern const uint16_t POTION_MEDIUM_FOREGROUND;
extern const uint16_t POTION_MEDIUM_COLOR_PAIR;

extern const uint16_t ARMOR_LOW_BACKGROUND;
extern const uint16_t ARMOR_LOW_FOREGROUND;
extern const uint16_t ARMOR_LOW_COLOR_PAIR;

extern const uint16_t ARMOR_MEDIUM_BACKGROUND;
extern const uint16_t ARMOR_MEDIUM_FOREGROUND;
extern const uint16_t ARMOR_MEDIUM_COLOR_PAIR;

extern const uint16_t POWER_LOW_BACKGROUND;
extern const uint16_t POWER_LOW_FOREGROUND;
extern const uint16_t POWER_LOW_COLOR_PAIR;

extern const uint16_t POWER_MEDIUM_BACKGROUND;
extern const uint16_t POWER_MEDIUM_FOREGROUND;
extern const uint16_t POWER_MEDIUM_COLOR_PAIR;

extern const uint16_t CASTLE_BACKGROUND;
extern const uint16_t CASTLE_FOREGROUND;
extern const uint16_t CASTLE_COLOR_PAIR;

void init_color_pairs(void);


#endif //PROGRA_COLORS_H
