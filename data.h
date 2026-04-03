#ifndef DATA_H
#define DATA_H

struct Car {
    char  brand[20];
    char  model[20];
    int   year;
    char  color[15];
    float price;
};

extern struct Car *cars;
extern int         count;
extern int         capacity;


void expandArray(int extraCount);
void shrinkArray(void);
void freeMemory(void);
void expandManual(void);


void addCar(void);
void printCars(void);
void deleteLastCar(void);
void deleteCarByIndex(void);
void editCar(void);
void insertCarAtPosition(void);


void searchByBrand(void);
void sortCars(void);


#define DATA_FILE "cars.dat"        /* бинарный файл */

void saveToFile(const char *filename);
void loadFromFile(const char *filename);

#endif 