#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <windows.h>

int main(void) {
    int choice;

    loadFromFile(DATA_FILE);

    do {
        printf("\n════════════ Меню ════════════\n");
        printf(" 1.  Добавить автомобиль\n");
        printf(" 2.  Показать все\n");
        printf(" 3.  Удалить последний\n");
        printf(" 4.  Редактировать\n");
        printf(" 5.  Поиск по марке\n");
        printf(" 6.  Расширить массив вручную\n");
        printf(" 7.  Очистить список (освободить память)\n");
        printf(" 8.  Сортировать список\n");
        printf(" 9.  Вставить на указанную позицию\n");
        printf("10.  Удалить по номеру\n");
        printf("11.  Сохранить в файл\n");
        printf("12.  Загрузить из файла\n");
        printf(" 0.  Выход\n");
        printf("══════════════════════════════\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case  1: addCar();              break;
            case  2: printCars();           break;
            case  3: deleteLastCar();       break;
            case  4: editCar();             break;
            case  5: searchByBrand();       break;
            case  6: expandManual();        break;
            case  7: freeMemory();          break;
            case  8: sortCars();            break;
            case  9: insertCarAtPosition(); break;
            case 10: deleteCarByIndex();    break;
            case 11: saveToFile(DATA_FILE); break;
            case 12: loadFromFile(DATA_FILE); break;
            case  0: printf("Выход.\n");    break;
            default: printf("Неверный пункт меню.\n");
        }

    } while (choice != 0);

    printf("\nАвтосохранение перед выходом...\n");
    saveToFile(DATA_FILE);

    if (cars != NULL) {
        free(cars);
        cars = NULL;
    }

    return 0;
}