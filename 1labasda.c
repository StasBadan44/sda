#include <stdio.h>
#include <string.h>

#define MAX 10

// Структура Автомобиль
struct Car {
    char brand[20];
    char model[20];
    int year;
    char color[15];
    float price;
};

// Статический массив
struct Car cars[MAX];
int count = 0;

// Добавление автомобиля
void addCar() {
    if (count == MAX) {
        printf("Массив заполнен!\n");
        return;
    }

    printf("Марка: ");
    scanf("%s", cars[count].brand);

    printf("Модель: ");
    scanf("%s", cars[count].model);

    printf("Год: ");
    scanf("%d", &cars[count].year);

    printf("Цвет: ");
    scanf("%s", cars[count].color);

    printf("Цена: ");
    scanf("%f", &cars[count].price);

    count++;
    printf("Автомобиль добавлен.\n");
}

// Вывод всех автомобилей
void printCars() {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("\nСписок автомобилей:\n");
    for (int i = 0; i < count; i++) {
        printf("\n№%d\n", i + 1);
        printf("Марка: %s\n", cars[i].brand);
        printf("Модель: %s\n", cars[i].model);
        printf("Год: %d\n", cars[i].year);
        printf("Цвет: %s\n", cars[i].color);
        printf("Цена: %.2f\n", cars[i].price);
    }
}

// Удаление (по номеру в списке)
void deleteCar() {
    int num;

    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printCars();
    printf("Введите номер автомобиля для удаления: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Неверный номер.\n");
        return;
    }

    for (int i = num - 1; i < count - 1; i++) {
        cars[i] = cars[i + 1];
    }

    count--;
    printf("Автомобиль удалён.\n");
}

// Редактирование (без работы напрямую с индексом)
void editCar() {
    int num, choice;

    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printCars();
    printf("Введите номер автомобиля для редактирования: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Неверный номер.\n");
        return;
    }

    num--; // перевод в индекс

    printf("Что изменить?\n");
    printf("1. Марка\n");
    printf("2. Модель\n");
    printf("3. Год\n");
    printf("4. Цвет\n");
    printf("5. Цена\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Новая марка: ");
            scanf("%s", cars[num].brand);
            break;
        case 2:
            printf("Новая модель: ");
            scanf("%s", cars[num].model);
            break;
        case 3:
            printf("Новый год: ");
            scanf("%d", &cars[num].year);
            break;
        case 4:
            printf("Новый цвет: ");
            scanf("%s", cars[num].color);
            break;
        case 5:
            printf("Новая цена: ");
            scanf("%f", &cars[num].price);
            break;
        default:
            printf("Неверный выбор.\n");
    }
}

// Поиск по марке
void searchByBrand() {
    char brand[20];
    int found = 0;

    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("Введите марку: ");
    scanf("%s", brand);

    for (int i = 0; i < count; i++) {
        if (strcmp(cars[i].brand, brand) == 0) {
            printf("\nНайдено:\n");
            printf("%s %s %d %s %.2f\n",
                   cars[i].brand,
                   cars[i].model,
                   cars[i].year,
                   cars[i].color,
                   cars[i].price);
            found = 1;
        }
    }

    if (!found)
        printf("Автомобили не найдены.\n");
}

// Главное меню
int main() {
    int choice;

    do {
        printf("\n--- Меню ---\n");
        printf("1. Добавить\n");
        printf("2. Показать все\n");
        printf("3. Удалить\n");
        printf("4. Редактировать\n");
        printf("5. Поиск по марке\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCar(); break;
            case 2: printCars(); break;
            case 3: deleteCar(); break;
            case 4: editCar(); break;
            case 5: searchByBrand(); break;
            case 0: printf("Выход.\n"); break;
            default: printf("Неверный пункт.\n");
        }

    } while (choice != 0);

    return 0;
}