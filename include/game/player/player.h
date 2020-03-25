//
// Created by alan2 on 03/03/2020.
//

#ifndef PROGRA_PLAYER_H
#define PROGRA_PLAYER_H

#include <stdint.h>
#include <curses.h>
#include <stdbool.h>
#include <game/health.h>
#include <game/inventory.h>
#include <game/store.h>


/**
 * Contiene la información del jugador
 */
typedef struct player_t
{
    /**
     * Posicion en x
     */
    int16_t x;
    /**
     * Posicion en y
     */
    int16_t y;

    /**
     * Posicion anterior en x, su finalidad es permitir eliminar la posición anterior
     */
    uint16_t previous_x;
    /**
     * Posicion anterior en y, su finalidad es permitir eliminar la posición anterior
     */
    uint16_t previous_y;

    /**
     * Salud del jugador
     */
    struct health_t *health;

    /**
     * Ventana en la que se dibuja el jugador
     */
    WINDOW *owning_window;

    /**
     * Inventario del jugador
     */
    struct inventory_t *inventory;

    /**
     * Multiplicador de armadura, si se utilizan pocimas de armadura este valor se reduce
     */
    float armor_multiplier;

    /**
     * Multiplicador de daño, entre mayor sea más daño hace
     */
    float damage_multiplier;
} player_t;


/**
 * Crea un jugador bajo una ventana
 * @param parent ventana en la que se dibujará el jugador
 * @param health barra de salud
 * @return jugador creado c:
 */
player_t *create_player(WINDOW *parent, health_t *health);

/**
 * Dibuja el inventario del jugador
 * @param player jugador
 */
void draw_player_inventory(player_t *player);

void hide_player_inventory(player_t *player);

void take_damage(player_t *player, uint8_t quantity);

/**
 * Dibuja a un jugador en la ventana especificada al crear al jugador
 * @param player jugador a dibujar
 */
void draw_player(player_t *player);

/**
 * Procesa los movimientos del jugador dada una tecla
 * @param player jugador que procesará el teclado
 * @param key tecla presionada
 * @return si el jugador necesita volver a dibujares
 */
bool process_player_input(player_t *player, int key);

/**
 * Limpia los recursos del jugador
 * @param player puntero a jugador creado con create_player
 */
void delete_player(player_t *player);

#endif //PROGRA_PLAYER_H
