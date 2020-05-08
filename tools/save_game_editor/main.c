//
// Created by alan2 on 08/05/2020.
//
#include <game_state.h>

void print_state(game_state_t *state)
{
    printf("Estos son tus datos: ");
    printf("Salud: %d\nDinero: %d\nScore: %d\nBoss 1: %u\n", state->max_health, state->money, state->score,
           (uint8_t)state->boss_defeated.boss1);
    printf("Boss 2: %u\nBoss 3: %u\nBoss 4: %u\n", (uint8_t)state->boss_defeated.boss2,
           (uint8_t)state->boss_defeated.boss3, (uint8_t)state->boss_defeated.boss4);

    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (state->items[i][j].item == ITEM_NONE)
            {
                break;
            }
            printf("[%d %d] Objeto %s, cantidad: %d  ", i, j, get_item_display_name(state->items[i][j].item),
                   state->items[i][j].quantity);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int slot;
    printf("Elige slot (1,2,3): ");
    scanf("%d", &slot);

    bool success;
    game_state_t state = load_game(slot, &success);

    if (!success)
    {
        printf("No existe ese save");
        return -1;
    }

    print_state(&state);

    int option = -1;
    while (option != 0)
    {
        printf("Elige accion:\n0) Salir\n1) Editar salud\n2) Editar dinero\n3) Editar score\n4) Editar boss 1\n5) "
               "Editar boss 2\n6) Editar boss 3\n7) Editar boss 4\n8) Editar objeto\n9) Imprimir estado\n10) Cambiar "
               "slot [1,3]\n11) Guardar slot\nOpcion: ");
        scanf("%d", &option);

        switch (option)
        {
            case 0:
                break;
            case 1:
            {
                printf("\nIngresa nuevo valor para la salud: ");
                int16_t new_health;
                scanf("%hd", &new_health);
                state.max_health = new_health;
                break;
            }
            case 2:
            {
                printf("\nIngresa nuevo valor para el dinero: ");
                int32_t money;
                scanf("%u", &money);
                state.money = money;
                break;
            }
            case 3:
            {
                printf("\nIngresa nuevo valor para el score: ");
                int32_t score;
                scanf("%u", &score);
                state.score = score;
                break;
            }
            case 4:
            {
                int value;
                printf("\nIngresa estado para el boss (0 o 1): ");
                scanf("%d", &value);
                state.boss_defeated.boss1 = value;
                break;
            }
            case 5:
            {
                int value;
                printf("\nIngresa estado para el boss (0 o 1): ");
                scanf("%d", &value);
                state.boss_defeated.boss2 = value;
                break;
            }
            case 6:
            {
                int value;
                printf("\nIngresa estado para el boss (0 o 1): ");
                scanf("%d", &value);
                state.boss_defeated.boss3 = value;
                break;
            }
            case 7:
            {
                int value;
                printf("\nIngresa estado para el boss (0 o 1): ");
                scanf("%d", &value);
                state.boss_defeated.boss4 = value;
                break;
            }
            case 8:
            {
                int x, y;
                printf("\nIngresa posición en x: ");
                scanf("%d", &x);
                printf("\nIngresa posición en y: ");
                scanf("%d", &y);

                int item;
                printf("Ingresa objeto ");
                for (int i = 0; i <= ITEM_NONE; ++i)
                {
                    printf("\t%d: %s\n", i, get_item_display_name(i));
                }
                printf("Objeto: ");
                scanf("%d", &item);

                int quantity;
                printf("Ingresa cantidad: ");
                scanf("%d", &quantity);

                state.items[x][y].quantity = quantity;
                state.items[x][y].item = (item_resource_e)item;

                break;
            }
            case 9:
            {
                printf("\n");
                print_state(&state);
                break;
            }
            case 10:
            {
                int slot;
                printf("Elige slot (1,2,3): ");
                scanf("%d", &slot);

                bool success;
                game_state_t state = load_game(slot, &success);

                if (!success)
                {
                    printf("No existe ese save");
                    return -1;
                }

                break;
            }
            case 11:
                save_game(&state, slot);
                break;
            default:
                fprintf(stderr, "Opcion no valida\n");
                break;
        }
    }
}