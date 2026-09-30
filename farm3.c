#include <stdio.h>

#define INVENTORY_SIZE 10
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

// Вспомогательная функция: получить строку названия предмета по ID
const char* get_item_name(int id) {
    switch (id) {
        case ITEM_WOOD:   return "Дерево";
        case ITEM_STONE:  return "Камень";
        case ITEM_SEEDS:  return "Семена";
        case ITEM_IRON:   return "Железо";
        case ITEM_CLOTH:  return "Ткань";
        case ITEM_FOOD:   return "Еда";
        case ITEM_POTION: return "Зелье";
        case ITEM_TOOL:   return "Инструмент";
        case ITEM_GEMS:   return "Самоцветы";
        default:          return "Пусто";
    }
}

int main(void) {
    int current_day = 1;
    int current_hour = 8;

    int inventory[INVENTORY_SIZE] = {
        ITEM_WOOD, ITEM_STONE, ITEM_SEEDS, ITEM_IRON,
        ITEM_CLOTH, ITEM_FOOD, EMPTY_SLOT, EMPTY_SLOT,
        EMPTY_SLOT, EMPTY_SLOT
    };

    while (1) {
        printf("\n--- МЕНЮ ---\n");
        printf("[0] Выход\n");
        printf("[1] Посмотреть на часы\n");
        printf("[2] Промотать время (Поработать)\n");
        printf("[3] Посмотреть инвентарь\n");
        printf("[4] Положить предмет в слот\n");
        printf("[5] Выбросить предмет\n");
        printf("[6] Выполнить задание по варианту (Ревизия ресурсов)\n");
        printf("Выберите пункт: ");

        int choice;
        // Защита от неправильного ввода: scanf возвращает количество успешно прочитанных значений
        if (scanf("%d", &choice) != 1) {
            // Если ввели не число — очищаем буфер и выводим ошибку
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Ошибка: введите число от 0 до 6.\n");
            continue;
        }
switch (choice) {
            case 0:
                printf("Выход из игры.\n");
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
                    const char* name = get_item_name(inventory[i]);
                    printf("Слот %d: [%d] (%s)\n", i, inventory[i], name);
                }
                break;
            }
            
            case 4: {
                int slot_index, item_id;
                printf("Введите индекс слота (0–%d): ", INVENTORY_SIZE - 1);
                if (scanf("%d", &slot_index) != 1) {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: индекс должен быть числом.\n");
                    break;
                }

                if (slot_index < 0 || slot_index >= INVENTORY_SIZE) {
                    printf("Ошибка: индекс слота должен быть от 0 до %d.\n", INVENTORY_SIZE - 1);
                    break;
                }

                printf("Введите ID предмета (0–9): ");
                if (scanf("%d", &item_id) != 1 || item_id < 0 || item_id > 9) {
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    printf("Ошибка: ID предмета должен быть числом от 0 до 9.\n");
                    break;
                }

                inventory[slot_index] = item_id;
                printf("Предмет ID %d помещён в слот %d.\n", item_id, slot_index);
                break;
            }

   
