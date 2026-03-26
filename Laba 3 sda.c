#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Car {
    char brand[20];
    char model[20];
    int year;
    char color[15];
    float price;
};

struct Car *cars = NULL;
int count = 0; 
int capacity = 0; 

void expandArray(int extraCount) {
    int newCapacity = capacity + extraCount;
    struct Car *newArr = (struct Car *)malloc(newCapacity * sizeof(struct Car));

    if (newArr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        newArr[i] = cars[i];
    }

    free(cars);

    cars = newArr;
    capacity = newCapacity;
}

void shrinkArray() {
    if (capacity == 0) return;

    int newCapacity = capacity - 1;

    if (newCapacity == 0) {
        free(cars);
        cars = NULL;
        capacity = 0;
        count = 0;
        return;
    }

    struct Car *newArr = (struct Car *)malloc(newCapacity * sizeof(struct Car));

    if (newArr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        newArr[i] = cars[i];
    }

    free(cars);
    cars = newArr;
    capacity = newCapacity;

    if (count > capacity)
        count = capacity;
}

void addCar() {
    expandArray(1);

    printf("Марка: ");
    scanf("%19s", cars[count].brand);

    printf("Модель: ");
    scanf("%19s", cars[count].model);

    printf("Год: ");
    scanf("%d", &cars[count].year);

    printf("Цвет: ");
    scanf("%14s", cars[count].color);

    printf("Цена: ");
    scanf("%f", &cars[count].price);

    count++;
    printf("Автомобиль добавлен. Текущий размер массива: %d слотов.\n", capacity);
}

void printCars() {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("\nСписок автомобилей (элементов: %d, слотов выделено: %d):\n", count, capacity);
    for (int i = 0; i < count; i++) {
        printf("\n№%d\n", i + 1);
        printf("Марка:  %s\n", cars[i].brand);
        printf("Модель: %s\n", cars[i].model);
        printf("Год:    %d\n", cars[i].year);
        printf("Цвет:   %s\n", cars[i].color);
        printf("Цена:   %.2f\n", cars[i].price);
    }
}

void deleteLastCar() {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("Удаляется последний автомобиль: %s %s\n",
           cars[count - 1].brand, cars[count - 1].model);

    count--;
    shrinkArray();

    printf("Автомобиль удалён. Текущий размер массива: %d слот(ов).\n", capacity);
}


void deleteCarByIndex() {
    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printCars();
    int num;
    printf("Введите номер автомобиля для удаления (1–%d): ", count);
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Неверный номер.\n");
        return;
    }

    int idx = num - 1;
    printf("Удаляется: %s %s\n", cars[idx].brand, cars[idx].model);

    /* Сдвигаем все элементы после удаляемого на одну позицию влево */
    for (int i = idx; i < count - 1; i++) {
        cars[i] = cars[i + 1];
    }

    count--;
    shrinkArray();

    printf("Автомобиль удалён. Текущий размер массива: %d слот(ов).\n", capacity);
}

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

    num--;

    printf("Что изменить?\n");
    printf("1. Марка\n2. Модель\n3. Год\n4. Цвет\n5. Цена\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: printf("Новая марка: ");  scanf("%19s", cars[num].brand);  break;
        case 2: printf("Новая модель: "); scanf("%19s", cars[num].model);  break;
        case 3: printf("Новый год: ");    scanf("%d",  &cars[num].year);   break;
        case 4: printf("Новый цвет: ");   scanf("%14s", cars[num].color);  break;
        case 5: printf("Новая цена: ");   scanf("%f",  &cars[num].price);  break;
        default: printf("Неверный выбор.\n");
    }
}

void searchByBrand() {
    char brand[20];
    int found = 0;

    if (count == 0) {
        printf("Список пуст.\n");
        return;
    }

    printf("Введите марку: ");
    scanf("%19s", brand);

    for (int i = 0; i < count; i++) {
        if (strcmp(cars[i].brand, brand) == 0) {
            printf("\nНайдено:\n");
            printf("%s %s %d %s %.2f\n",
                   cars[i].brand, cars[i].model,
                   cars[i].year, cars[i].color, cars[i].price);
            found = 1;
        }
    }

    if (!found)
        printf("Автомобили не найдены.\n");
}

void freeMemory() {
    if (cars == NULL) {
        printf("Память уже освобождена.\n");
        return;
    }
    free(cars);
    cars = NULL;
    count = 0;
    capacity = 0;
    printf("Память освобождена. Список очищен.\n");
}

void expandManual() {
    int n;
    printf("На сколько элементов расширить массив? ");
    scanf("%d", &n);
    if (n <= 0) { printf("Некорректное значение.\n"); return; }
    expandArray(n);
    printf("Массив расширен. Текущий размер: %d слот(ов).\n", capacity);
}

void sortCars() {
    if (count < 2) {
        printf("Недостаточно элементов для сортировки.\n");
        return;
    }

    printf("Сортировать по:\n");
    printf("1. Марка\n2. Модель\n3. Год\n4. Цвет\n5. Цена\n");
    int field;
    scanf("%d", &field);

    if (field < 1 || field > 5) {
        printf("Неверный выбор.\n");
        return;
    }

    /* Сортировка вставками */
    for (int i = 1; i < count; i++) {
        struct Car key = cars[i];
        int j = i - 1;

        while (j >= 0) {
            int cmp = 0;
            switch (field) {
                case 1: cmp = strcmp(cars[j].brand, key.brand); break;
                case 2: cmp = strcmp(cars[j].model, key.model); break;
                case 3: cmp = (cars[j].year > key.year) ? 1 :
                              (cars[j].year < key.year) ? -1 : 0; break;
                case 4: cmp = strcmp(cars[j].color, key.color); break;
                case 5: cmp = (cars[j].price > key.price) ? 1 :
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

    printf("Список отсортирован.\n");
}

void insertCarAtPosition() {
    int pos;

    printf("Введите позицию для вставки (1–%d, или %d для вставки в конец): ",
           count + 1, count + 1);
    scanf("%d", &pos);

    if (pos < 1 || pos > count + 1) {
        printf("Неверная позиция.\n");
        return;
    }

    expandArray(1);

    for (int i = count; i >= pos; i--) {
        cars[i] = cars[i - 1];
    }

    /* Заполняем новый элемент */
    int idx = pos - 1;
    printf("Марка: ");
    scanf("%19s", cars[idx].brand);

    printf("Модель: ");
    scanf("%19s", cars[idx].model);

    printf("Год: ");
    scanf("%d", &cars[idx].year);

    printf("Цвет: ");
    scanf("%14s", cars[idx].color);

    printf("Цена: ");
    scanf("%f", &cars[idx].price);

    count++;
    printf("Автомобиль вставлен на позицию %d. Всего элементов: %d.\n", pos, count);
}

int main() {
    int choice;

    do {
        printf("\n--- Меню ---\n");
        printf("1.  Добавить автомобиль\n");
        printf("2.  Показать все\n");
        printf("3.  Удалить последний\n");
        printf("4.  Редактировать\n");
        printf("5.  Поиск по марке\n");
        printf("6.  Расширить массив вручную\n");
        printf("7.  Освободить память (очистить список)\n");
        printf("8.  Сортировать список\n");
        printf("9.  Вставить на указанную позицию\n");
        printf("10. Удалить по номеру\n");
        printf("0.  Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  addCar();              break;
            case 2:  printCars();           break;
            case 3:  deleteLastCar();       break;
            case 4:  editCar();             break;
            case 5:  searchByBrand();       break;
            case 6:  expandManual();        break;
            case 7:  freeMemory();          break;
            case 8:  sortCars();            break;
            case 9:  insertCarAtPosition(); break;
            case 10: deleteCarByIndex();    break;
            case 0:  printf("Выход.\n");    break;
            default: printf("Неверный пункт.\n");
        }

    } while (choice != 0);

    if (cars != NULL) {
        free(cars);
        cars = NULL;
        printf("Память освобождена перед завершением.\n");
    }

    return 0;
}