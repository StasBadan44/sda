#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main(void) {
    int choice;

    loadFromFile(DATA_FILE);

    do {
        printf("\n======== Menyu ========\n");
        printf(" 1.  Dobavit avtomobil\n");
        printf(" 2.  Pokazat vse\n");
        printf(" 3.  Udalit posledniy\n");
        printf(" 4.  Redaktirovat\n");
        printf(" 5.  Poisk po marke\n");
        printf(" 6.  Rasshirit massiv vruchnuyu\n");
        printf(" 7.  Ochistit spisok\n");
        printf(" 8.  Sortirovat spisok\n");
        printf(" 9.  Vstavit na poziciyu\n");
        printf("10.  Udalit po nomeru\n");
        printf("11.  Sohranit v fayl\n");
        printf("12.  Zagruzit iz fayla\n");
        printf(" 0.  Vyhod\n");
        printf("=======================\n");
        printf("Vybor: ");
        scanf("%d", &choice);

        switch (choice) {
            case  1: addCar();                break;
            case  2: printCars();             break;
            case  3: deleteLastCar();         break;
            case  4: editCar();               break;
            case  5: searchByBrand();         break;
            case  6: expandManual();          break;
            case  7: freeMemory();            break;
            case  8: sortCars();              break;
            case  9: insertCarAtPosition();   break;
            case 10: deleteCarByIndex();      break;
            case 11: saveToFile(DATA_FILE);   break;
            case 12: loadFromFile(DATA_FILE); break;
            case  0: printf("Vyhod.\n");      break;
            default: printf("Nevernyy punkt menyu.\n");
        }

    } while (choice != 0);

    printf("\nAvtosohranenie pered vyhodom...\n");
    saveToFile(DATA_FILE);

    if (cars != NULL) {
        free(cars);
        cars = NULL;
    }

    return 0;
}