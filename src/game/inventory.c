//
// Created by alan2 on 11/03/2020.
//
#include "game/inventory.h"
#include "game/player/player.h"
#include <sound.h>
#include <stdlib.h>
#include <utils/colors.h>
#include <utils/render_graph.h>
#include <utils/sound_manager.h>
#include <utils/sprite.h>
#include <windows.h>

const uint8_t MAX_ITEMS = 10;

void on_start_draw_potion_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 2 && x != 0 && y < 6) || (y > 0 && y < 3 && x > 1 && x < 9)))
    {
        wattron(window, COLOR_PAIR(POTION_LOW_COLOR_PAIR));
    }
}

void on_end_draw_potion_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 2 && x != 0 && y < 6) || (y > 0 && y < 3 && x > 1 && x < 9)))
    {
        wattroff(window, COLOR_PAIR(POTION_LOW_COLOR_PAIR));
    }
}

void on_start_draw_potion_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 2 && x != 0 && y < 6) || (y > 0 && y < 3 && x > 1 && x < 9)))
    {
        wattron(window, COLOR_PAIR(POTION_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_potion_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 2 && x != 0 && y < 6) || (y > 0 && y < 3 && x > 1 && x < 9)))
    {
        wattroff(window, COLOR_PAIR(POTION_MEDIUM_COLOR_PAIR));
    }
}

void on_start_draw_armor_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 0 && y <= 3) || (y == 4 && x > 1) || (y == 5 && x > 2)))
    {
        wattron(window, COLOR_PAIR(ARMOR_LOW_COLOR_PAIR));
    }
}

void on_end_draw_armor_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 0 && y <= 3) || (y == 4 && x > 1) || (y == 5 && x > 2)))
    {
        wattroff(window, COLOR_PAIR(ARMOR_LOW_COLOR_PAIR));
    }
}

void on_start_draw_armor_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 0 && y <= 3) || (y == 4 && x > 1) || (y == 5 && x > 2)))
    {
        wattron(window, COLOR_PAIR(ARMOR_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_armor_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && ((y > 0 && y <= 3) || (y == 4 && x > 1) || (y == 5 && x > 2)))
    {
        wattroff(window, COLOR_PAIR(ARMOR_MEDIUM_COLOR_PAIR));
    }
}

void on_start_draw_power_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (((y == 1 || y == 2) && x > 2) || (y == 3 && x > 0) || (y > 3 && x > 3)))
    {
        wattron(window, COLOR_PAIR(POWER_LOW_COLOR_PAIR));
    }
}

void on_end_draw_power_low(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (((y == 1 || y == 2) && x > 2) || (y == 3 && x > 0) || (y > 3 && x > 3)))
    {
        wattroff(window, COLOR_PAIR(POWER_LOW_COLOR_PAIR));
    }
}

void on_start_draw_power_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (((y == 1 || y == 2) && x > 2) || (y == 3 && x > 0) || (y > 3 && x > 3)))
    {
        wattron(window, COLOR_PAIR(POWER_MEDIUM_COLOR_PAIR));
    }
}

void on_end_draw_power_medium(WINDOW *window, int16_t y, int16_t x, int character_to_draw)
{
    if (character_to_draw == ' ' && (((y == 1 || y == 2) && x > 2) || (y == 3 && x > 0) || (y > 3 && x > 3)))
    {
        wattroff(window, COLOR_PAIR(POWER_MEDIUM_COLOR_PAIR));
    }
}

inventory_t *create_inventory(WINDOW *parent)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));
    inventory->window = subwin(parent, getmaxy(parent) - 5, getmaxx(parent) - 4, 3, 2);
    inventory->shown = false;
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            inventory->items[i][j] = create_item(ITEM_NONE);
            inventory->items[i][j].quantity = 0;
        }
    }
    inventory->items[0][0] = create_item(ITEM_POTION_LOW);
    inventory->items[0][0].quantity = 1;
    return inventory;
}

void delete_inventory(inventory_t *inventory)
{
    delwin(inventory->window);
    free(inventory);
}

void draw_inventory(inventory_t *inventory)
{
    wclear(inventory->window);
    wattron(inventory->window, COLOR_PAIR(5));

    for (int i = 0; i < 2; ++i)
    {
        mvwvline(inventory->window, 1, getmaxx(inventory->window) / 3 * (i + 1), 0, getmaxy(inventory->window));
    }
    for (int j = 0; j < 1; ++j)
    {
        mvwhline(inventory->window, getmaxy(inventory->window) / 2 * (j + 1), 0, 0, getmaxx(inventory->window));
    }
    box(inventory->window, 0, 0);

    for (int i = 0; i <= 1; i++)
    {
        bool end = false;
        for (int j = 0; j <= 2; j++)
        {
            if (inventory->items[i][j].item == ITEM_NONE)
            {
                end = true;
                break;
            }
            else
            {
                int y = i * getmaxy(inventory->window) / 2 + 5;
                int x = j * getmaxx(inventory->window) / 3 + getmaxx(inventory->window) / 6 - 5;

                switch (inventory->items[i][j].item)
                {
                    case ITEM_POTION_LOW:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "POTION.txt", on_start_draw_potion_low,
                                    on_end_draw_potion_low);
                        break;
                    case ITEM_POTION_MEDIUM:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "POTION.txt",
                                    on_start_draw_potion_medium,
                                    on_end_draw_potion_medium);
                        break;
                    case ITEM_ARMOR_LOW:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "ARMOR.txt",
                                    on_start_draw_armor_low,
                                    on_end_draw_armor_low);
                        break;
                    case ITEM_ARMOR_MEDIUM:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "ARMOR.txt",
                                    on_start_draw_armor_medium,
                                    on_end_draw_armor_medium);
                        break;
                    case ITEM_POWER_LOW:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "POWER.txt",
                                    on_start_draw_power_low,
                                    on_end_draw_power_low);
                        break;
                    case ITEM_POWER_MEDIUM:
                        draw_sprite(inventory->window,
                                    y,
                                    x,
                                    "POWER.txt",
                                    on_start_draw_power_medium,
                                    on_end_draw_power_medium);
                        break;
                    case ITEM_NONE:
                        break;
                }
                wattron(inventory->window, A_REVERSE);
                mvwprintw(inventory->window, i * getmaxy(inventory->window) / 2 + 13,
                          j * getmaxx(inventory->window) / 3 + getmaxx(inventory->window) / 6 - 1, "%03d",
                          inventory->items[i][j].quantity);
                wattroff(inventory->window, A_REVERSE);
            }
        }
        if (end)
        {
            break;
        }
    }

    wrefresh(inventory->window);
}

const char *get_item_display_name(item_resource_e item)
{
    switch (item)
    {
        case ITEM_POTION_LOW:
            return "Pocima (débil)";
        case ITEM_POTION_MEDIUM:
            return "Pocima (medio)";
        case ITEM_ARMOR_LOW:
            return "Armadura (débil)";
        case ITEM_ARMOR_MEDIUM:
            return "Amadura (media)";
        case ITEM_POWER_LOW:
            return "Poder (bajo)";
        case ITEM_POWER_MEDIUM:
            return "Poder (medio)";
        default:
            return NULL;
    }
}

void potion_low_effect(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/drink.ogg");
    set_loop(sound, false);
    play_sound(sound);
    add_health(player->health, 15);
    player->health->health_node->require_redraw = true;
}

void potion_medium_effect(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/drink.ogg");
    set_loop(sound, false);
    play_sound(sound);

    add_health(player->health, 40);
    player->health->health_node->require_redraw = true;
}

void armor_low(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/armor.ogg");
    set_loop(sound, false);
    play_sound(sound);
    player->shield_counter = 3;
    player->armor_multiplier = 0.7f;
}

void armor_medium(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/armor.ogg");
    set_loop(sound, false);
    play_sound(sound);
    player->shield_counter = 4;
    player->armor_multiplier = 0.5f;
}

void power_low(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/power.ogg");
    set_loop(sound, false);
    play_sound(sound);
    player->power_counter = 2;
    player->damage_multiplier = 1.5f;
}

void power_medium(player_t *player)
{
    sound_t sound = create_sound();
    add_sound_to_manager(sound);
    sound_open_file(sound, "sfx/power.ogg");
    set_loop(sound, false);
    play_sound(sound);
    player->power_counter = 3;
    player->damage_multiplier = 1.8f;
}

item_t create_item(item_resource_e item)
{
    item_t result = {.quantity = 0};
    result.item = item;
    switch (item)
    {
        case ITEM_POTION_LOW:
            result.item_effect = potion_low_effect;
            break;
        case ITEM_POTION_MEDIUM:
            result.item_effect = potion_medium_effect;
            break;
        case ITEM_ARMOR_LOW:
            result.item_effect = armor_low;
            break;
        case ITEM_ARMOR_MEDIUM:
            result.item_effect = armor_medium;
            break;
        case ITEM_POWER_LOW:
            result.item_effect = power_low;
            break;
        case ITEM_POWER_MEDIUM:
            result.item_effect = power_medium;
            break;
        case ITEM_NONE:
            result.item_effect = NULL;
            break;
        default: // JAMAS DEBERÍA PASAR
            abort();
    }
    return result;
}

bool add_item(inventory_t *inventory, item_resource_e item)
{
    sound_t sound = create_sound();
    char rand_n[64];
    sprintf(rand_n, "sfx/coins/coin_%d.ogg", rand() % 3 + 1);
    sound_open_file(sound, rand_n);
    set_loop(sound, false);
    play_sound(sound);
    add_sound_to_manager(sound);
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if(inventory->items[i][j].item == item)
            {
                if (inventory->items[i][j].quantity == MAX_ITEMS)
                    return false;
                inventory->items[i][j].quantity++;
                return true;
            }
        }
    }
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if(inventory->items[i][j].item == ITEM_NONE)
            {
                inventory->items[i][j] = create_item(item);
                inventory->items[i][j].quantity = 1;
                return true;
            }
        }
    }
    return false;
}

bool process_inventory_input(struct player_t *player, int key)
{
    if (key < '1' || key > '6')
        return false;
    int pressed_key = key - '1';
    int row = pressed_key >= 3;
    int column = row ? pressed_key - 3 : pressed_key;
    item_t *item = &player->inventory->items[row][column];
    if (item->item == ITEM_NONE)
        return false;
    item->item_effect(player);
    item->quantity--;
    if (item->quantity == 0) // eliminar objeto
    {
        for(int i = row; i < 2; i++)
        {
            for (int j = column; j < 3; j++)
            {
                if(j == 2)
                {
                    player->inventory->items[i][j] = (i == 0) ? player->inventory->items[i+1][0] : create_item(ITEM_NONE);
                }
                else
                {
                    player->inventory->items[i][j] = player->inventory->items[i][j + 1];
                }
            }
            if(row == 0)
            {
                column = 0;
            }
        }
    }

    return true;
}
