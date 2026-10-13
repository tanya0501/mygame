#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INVENTORY_SIZE 10
#define MAX_ITEMS 10
#define MAX_NAME_LEN 32

#define EMPTY_SLOT 0
#define ITEM_WOOD 1
#define ITEM_STONE 2
#define ITEM_SEEDS 3
#define ITEM_IRON 4
#define ITEM_CLOTH 5
#define ITEM_FOOD 6
#define ITEM_POTION 7
#define ITEM_TOOL 8
#define ITEM_GEMS 9

// массив для хранения названий предметов
char item_names[MAX_ITEMS][MAX_NAME_LEN];

// для безопасной очистки буфера ввода после scanf
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Загрузка названий предметов из файла 
void load_item_catalog(void) {
    FILE *file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("[Предупреждение]: Файл items.txt не найден. Загружены названия по умолчанию.\n");
        // Заполнение резервными именами, если файла нет
        const char* default_names[MAX_ITEMS] = {
            "Пусто", "Дерево", "Камень", "Семена", "Железо", 
            "Ткань", "Еда", "Зелье", "Инструмент", "Самоцветы"
        };
        for (int i = 0; i < MAX_ITEMS; i++) {
            strncpy(item_names[i], default_names[i], MAX_NAME_LEN - 1);
            item_names[i][MAX_NAME_LEN - 1] = '\0';
        }
        return;
}    

	int id;
    char name[MAX_NAME_LEN];
    int loaded_count = 0;
    // Читаем ID и строку до конца строки (исключая перенос строки)
    while (fscanf(file, "%d %[^\n]", &id, name) == 2) {
        if (id >= 0 && id < MAX_ITEMS) {
            strncpy(item_names[id], name, MAX_NAME_LEN - 1);
            item_names[id][MAX_NAME_LEN - 1] = '\0';
            loaded_count++;
        }
    }
    fclose(file);
    printf("Успешно загружено предметов из каталога: %d\n", loaded_count);
}

int main(void) {
    char farmer_name[32];
    int current_day = 1;
    int current_hour = 8;

    int inventory[INVENTORY_SIZE] = {
        ITEM_WOOD, ITEM_STONE, ITEM_SEEDS, ITEM_IRON,
        ITEM_CLOTH, ITEM_FOOD, EMPTY_SLOT, EMPTY_SLOT,
        EMPTY_SLOT, EMPTY_SLOT
    };
// 1. Приветствие и ввод имени
    printf("Добро пожаловать на ферму!\n");
    printf("Введите имя вашего фермера: ");
    if (fgets(farmer_name, sizeof(farmer_name), stdin) != NULL) {
        // Удаляем символ новой строки \n, если он есть
        farmer_name[strcspn(farmer_name, "\n")] = '\0';
    }
    if (strlen(farmer_name) == 0) {
        strcpy(farmer_name, "Безымянный фермер");
    }
// 2. Загрузка каталога предметов
    load_item_catalog();

    while (1) {
        printf("\n--- МЕНЮ ФЕРМЫ (Фермер: %s) ---\n", farmer_name);
        printf("[0] Выход\n");
        printf("[1] Посмотреть на часы\n");
        printf("[2] Промотать время (Поработать)\n");
        printf("[3] Посмотреть инвентарь\n");
        printf("[4] Положить предмет в слот\n");
        printf("[5] Выбросить предмет\n");
        printf("[6] Ревизия ресурсов (По ID)\n");
        printf("[7] Поиск предмета в рюкзаке по названию\n");
        printf("[8] Записать состояние в дневник фермера\n");
        printf("Выберите пункт: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Ошибка: введите число от 0 до 8.\n");
            continue;
        }
switch (choice) {
            case 0:
                printf("Выход из игры. До встречи, %s!\n", farmer_name);
                return 0;
           
            case 1: {
                // Форматируем часы с ведущим нулём: 8 -> 08
                printf("Текущее время: День %d, %02d:00\n", current_day, current_hour);
                break;
            }
            
             case 2: {
                int work_hours;
                printf("Сколько часов вы хотите потратить на работу? ");
                if (scanf("%d", &work_hours) != 1 || work_hours < 0) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: введите неотрицательное число часов.\n");
                    break;
                }

                current_hour += work_hours;

                // Корректный перевод дней при превышении 24 часов
                while (current_hour >= 24) {
                    current_hour -= 24;
                    current_day++;
                }
                printf("Время промотано. Теперь: День %d, %02d:00\n", current_day, current_hour);
                break;
            }

            case 3: {
                 printf("Инвентарь:\n");
                for (int i = 0; i < INVENTORY_SIZE; ++i) {
                    int id = inventory[i];
                    printf("Слот %d: [%d] - %s\n", i, id, item_names[id]);
                }
                break;
            }
            
            case 4: {
               int slot_index, item_id;
                printf("Введите индекс слота (0–%d): ", INVENTORY_SIZE - 1);
                if (scanf("%d", &slot_index) != 1) {
                    clear_input_buffer();
                    printf("Ошибка: индекс должен быть числом.\n");
                    break;
                }

                if (slot_index < 0 || slot_index >= INVENTORY_SIZE) {
                    printf("Ошибка: индекс слота должен быть от 0 до %d.\n", INVENTORY_SIZE - 1);
                    break;
                }

                printf("Введите ID предмета (0–9): ");
                if (scanf("%d", &item_id) != 1 || item_id < 0 || item_id > 9) {
                    clear_input_buffer();
                    printf("Ошибка: ID предмета должен быть числом от 0 до 9.\n");
                    break;
                }

                inventory[slot_index] = item_id;
                printf("Предмет \"%s\" (ID %d) помещён в слот %d.\n", item_names[item_id], item_id, slot_index);
                break;
            } 
            
            case 5: {
                int slot_index;
                printf("Введите индекс слота для удаления предмета (0-%d): ", INVENTORY_SIZE - 1);
                if (scanf("%d", &slot_index) != 1) {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: индекс должен быть числом.\n");
                    break;
                }

                if (slot_index < 0 || slot_index >= INVENTORY_SIZE) {
                    printf("Ошибка: индекс слота должен быть от 0 до %d.\n", INVENTORY_SIZE - 1);
                    break;
                }

                int old_id = inventory[slot_index];
                inventory[slot_index] = EMPTY_SLOT;
                printf("Предмет ID %d удалён из слота %d.\n", old_id, slot_index);
                break;
            }

			case 6: {
                int target_id;
                printf("Введите ID предмета для ревизии (0-9): ");
                if (scanf("%d", &target_id) != 1 || target_id < 0 || target_id > 9) {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: ID должен быть числом от 0 до 9.\n");
                    break;
                }

                int count = 0;
                for (int i = 0; i < INVENTORY_SIZE; ++i) {
                    if (inventory[i] == target_id) {
                        count++;
                    }
                }

                printf("Количество предметов ID %d: %d\n", target_id, count);

                if (count > 0) {
                    printf("Позиции слотов: ");
                    for (int i = 0; i < INVENTORY_SIZE; ++i) {
                        if (inventory[i] == target_id) {
                            printf("%d ", i);
                        }
                    }
                    printf("\n");
                } else {
                    printf("Таких предметов в инвентаре нет.\n");
                }
                break;
            }
   
            default:
                printf("Ошибка: выберите пункт от 0 до 6.\n");
                break;
        }
    }

    return 0;
}
			case 7: {
                char search_name[MAX_NAME_LEN];
                printf("Введите название предмета для поиска: ");
                clear_input_buffer(); // Очищаем буфер после предыдущего ввода scanf
                
                if (fgets(search_name, sizeof(search_name), stdin) != NULL) {
                    search_name[strcspn(search_name, "\n")] = '\0';
                }

                // 1. Ищем ID по названию в нашем каталоге строк
                int found_id = -1;
                for (int i = 0; i < MAX_ITEMS; i++) {
                    if (strcmp(item_names[i], search_name) == 0) {
                        found_id = i;
                        break;
                    }
                }

                if (found_id == -1) {
                    printf("Предмет с названием \"%s\" не существует в каталоге.\n", search_name);
                    break;
                }
