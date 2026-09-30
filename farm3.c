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
