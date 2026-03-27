#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"


struct Car *cars     = NULL;
int         count    = 0;
int         capacity = 0;


void expandArray(int extraCount)
{
    int newCapacity = capacity + extraCount;

    struct Car *newArr = (struct Car *)malloc(newCapacity * sizeof(struct Car));
    if (newArr == NULL) {
        printf("Oshibka vydeleniya pamyati!\n");
        return;
    }

    for (int i = 0; i < count; i++)
        newArr[i] = cars[i];

    free(cars);
    cars     = newArr;
    capacity = newCapacity;
}

void shrinkArray(void)
{
    if (capacity == 0) return;

    int newCapacity = capacity - 1;

    if (newCapacity == 0) {
        free(cars);
        cars     = NULL;
        capacity = 0;
        count    = 0;
        return;
    }

    struct Car *newArr = (struct Car *)malloc(newCapacity * sizeof(struct Car));
    if (newArr == NULL) {
        printf("Oshibka vydeleniya pamyati!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++)
        newArr[i] = cars[i];

    free(cars);
    cars     = newArr;
    capacity = newCapacity;

    if (count > capacity)
        count = capacity;
}

void freeMemory(void)
{
    if (cars == NULL) {
        printf("Pamyat uzhe osvobozhdena.\n");
        return;
    }

    free(cars);
    cars     = NULL;
    count    = 0;
    capacity = 0;

    printf("Pamyat osvobozhdena. Spisok ochishchen.\n");
}

void expandManual(void)
{
    int n;
    printf("Na skolko elementov rasshirit massiv? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Nekorrektnoe znachenie.\n");
        return;
    }

    expandArray(n);
    printf("Massiv rasshiren. Tekushchiy razmer: %d slot(ov).\n", capacity);
}

void addCar(void)
{
    expandArray(1);

    printf("Marka:  "); scanf("%19s", cars[count].brand);
    printf("Model:  "); scanf("%19s", cars[count].model);
    printf("God:    "); scanf("%d",   &cars[count].year);
    printf("Cvet:   "); scanf("%14s", cars[count].color);
    printf("Cena:   "); scanf("%f",   &cars[count].price);

    count++;
    printf("Avtomobil dobavlen. Razmer massiva: %d slot(ov).\n", capacity);
}

void printCars(void)
{
    if (count == 0) {
        printf("Spisok pust.\n");
        return;
    }

    printf("\nSpisok avtomobiley (elementov: %d, slotov: %d):\n", count, capacity);

    for (int i = 0; i < count; i++) {
        printf("\n  #%d\n",            i + 1);
        printf("  Marka:  %s\n",   cars[i].brand);
        printf("  Model:  %s\n",   cars[i].model);
        printf("  God:    %d\n",   cars[i].year);
        printf("  Cvet:   %s\n",   cars[i].color);
        printf("  Cena:   %.2f\n", cars[i].price);
    }
}

void deleteLastCar(void)
{
    if (count == 0) {
        printf("Spisok pust.\n");
        return;
    }

    printf("Udalyaetsya posledniy avtomobil: %s %s\n",
           cars[count - 1].brand, cars[count - 1].model);

    count--;
    shrinkArray();

    printf("Avtomobil udalen. Razmer massiva: %d slot(ov).\n", capacity);
}

void deleteCarByIndex(void)
{
    if (count == 0) {
        printf("Spisok pust.\n");
        return;
    }

    printCars();

    int num;
    printf("Vvedite nomer avtomobilya dlya udaleniya (1-%d): ", count);
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Nevernyy nomer.\n");
        return;
    }

    int idx = num - 1;
    printf("Udalyaetsya: %s %s\n", cars[idx].brand, cars[idx].model);

    for (int i = idx; i < count - 1; i++)
        cars[i] = cars[i + 1];

    count--;
    shrinkArray();

    printf("Avtomobil udalen. Razmer massiva: %d slot(ov).\n", capacity);
}

void editCar(void)
{
    if (count == 0) {
        printf("Spisok pust.\n");
        return;
    }

    printCars();

    int num;
    printf("Vvedite nomer avtomobilya dlya redaktirovaniya: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Nevernyy nomer.\n");
        return;
    }

    num--;

    int choice;
    printf("Chto izmenit?\n");
    printf("  1. Marka\n");
    printf("  2. Model\n");
    printf("  3. God\n");
    printf("  4. Cvet\n");
    printf("  5. Cena\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: printf("Novaya marka:  "); scanf("%19s", cars[num].brand); break;
        case 2: printf("Novaya model:  "); scanf("%19s", cars[num].model); break;
        case 3: printf("Novyy god:     "); scanf("%d",  &cars[num].year);  break;
        case 4: printf("Novyy cvet:    "); scanf("%14s", cars[num].color); break;
        case 5: printf("Novaya cena:   "); scanf("%f",  &cars[num].price); break;
        default: printf("Nevernyy vybor.\n");
    }
}

void insertCarAtPosition(void)
{
    int pos;
    printf("Vvedite poziciyu dlya vstavki (1-%d): ", count + 1);
    scanf("%d", &pos);

    if (pos < 1 || pos > count + 1) {
        printf("Nevernaya poziciya.\n");
        return;
    }

    expandArray(1);

    for (int i = count; i >= pos; i--)
        cars[i] = cars[i - 1];

    int idx = pos - 1;
    printf("Marka:  "); scanf("%19s", cars[idx].brand);
    printf("Model:  "); scanf("%19s", cars[idx].model);
    printf("God:    "); scanf("%d",   &cars[idx].year);
    printf("Cvet:   "); scanf("%14s", cars[idx].color);
    printf("Cena:   "); scanf("%f",   &cars[idx].price);

    count++;
    printf("Avtomobil vstavlen na poziciyu %d. Vsego elementov: %d.\n", pos, count);
}

void searchByBrand(void)
{
    if (count == 0) {
        printf("Spisok pust.\n");
        return;
    }

    char brand[20];
    printf("Vvedite marku: ");
    scanf("%19s", brand);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(cars[i].brand, brand) == 0) {
            printf("\nNaydeno (#%d): %s %s  god: %d  cvet: %s  cena: %.2f\n",
                   i + 1,
                   cars[i].brand, cars[i].model,
                   cars[i].year,  cars[i].color, cars[i].price);
            found = 1;
        }
    }

    if (!found)
        printf("Avtomobili marki \"%s\" ne naydeny.\n", brand);
}

void sortCars(void)
{
    if (count < 2) {
        printf("Nedostatochno elementov dlya sortirovki.\n");
        return;
    }

    printf("Sortirovat po:\n");
    printf("  1. Marka\n");
    printf("  2. Model\n");
    printf("  3. God\n");
    printf("  4. Cvet\n");
    printf("  5. Cena\n");

    int field;
    scanf("%d", &field);

    if (field < 1 || field > 5) {
        printf("Nevernyy vybor.\n");
        return;
    }

    for (int i = 1; i < count; i++) {
        struct Car key = cars[i];
        int j = i - 1;

        while (j >= 0) {
            int cmp = 0;
            switch (field) {
                case 1: cmp = strcmp(cars[j].brand, key.brand); break;
                case 2: cmp = strcmp(cars[j].model, key.model); break;
                case 3: cmp = (cars[j].year  > key.year)  ?  1 :
                              (cars[j].year  < key.year)  ? -1 : 0; break;
                case 4: cmp = strcmp(cars[j].color, key.color); break;
                case 5: cmp = (cars[j].price > key.price) ?  1 :
                              (cars[j].price < key.price) ? -1 : 0; break;
            }

            if (cmp > 0) {
                cars[j + 1] = cars[j];
                j--;
            } else {
                break;
            }
        }

        cars[j + 1] = key;
    }

    printf("Spisok otsortirovan.\n");
}

void saveToFile(const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Oshibka: ne udalos otkryt fayl \"%s\" dlya zapisi.\n", filename);
        return;
    }

    if (fwrite(&count, sizeof(int), 1, fp) != 1) {
        printf("Oshibka zapisi zagolovka fayla.\n");
        fclose(fp);
        return;
    }

    if (count > 0) {
        size_t written = fwrite(cars, sizeof(struct Car), count, fp);
        if ((int)written != count) {
            printf("Preduprezhdenie: zapisano %zu iz %d zapisey.\n", written, count);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Spisok sokhranen v fayl \"%s\" (%d zapisey).\n", filename, count);
}

void loadFromFile(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Fayl \"%s\" ne nayden. Nachinaem s pustogo spiska.\n", filename);
        return;
    }

    int savedCount = 0;
    if (fread(&savedCount, sizeof(int), 1, fp) != 1) {
        printf("Oshibka chteniya zagolovka fayla.\n");
        fclose(fp);
        return;
    }

    if (savedCount <= 0) {
        printf("Fayl pust ili povrezhden.\n");
        fclose(fp);
        return;
    }

    free(cars);
    cars = (struct Car *)malloc(savedCount * sizeof(struct Car));
    if (cars == NULL) {
        printf("Oshibka vydeleniya pamyati pri zagruzke.\n");
        fclose(fp);
        cars     = NULL;
        count    = 0;
        capacity = 0;
        return;
    }

    size_t readCount = fread(cars, sizeof(struct Car), savedCount, fp);
    fclose(fp);

    if ((int)readCount != savedCount)
        printf("Preduprezhdenie: ozhidalos %d zapisey, prochitano %zu.\n",
               savedCount, readCount);

    count    = (int)readCount;
    capacity = count;

    printf("Zagruzheno %d zapisey iz fayla \"%s\".\n", count, filename);
}