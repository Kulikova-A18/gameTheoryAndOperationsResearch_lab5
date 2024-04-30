#ifndef MAIN_DEFINE_H
#define MAIN_DEFINE_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <locale.h>

#define gameTheoryAndOperationsResearch_filename "gameTheoryAndOperationsResearch_l5.txt"
#define gameTheoryAndOperationsResearch_filename_superadditivity "gameTheoryAndOperationsResearch_superadditivity_l5.txt"
#define gameTheoryAndOperationsResearch_filename_bulge "gameTheoryAndOperationsResearch_bulge_l5.txt"

// Число различных множеств коолиций игроков
#define N_KOOL 16

/*
Массив значений характиристической функции
индекс массива в двоичном коде определяет состав коолиции
единица в разряде индекса определяет, что игрок с заданным номером,
входит в коолицию (игрок 1 соответсвует младшему разряду)
*/

int v[N_KOOL] =
{
    0,      // 0000 - пустое  множесто
    1,      // 0001 - { 1 }
    1,      // 0010 - { 2 }
    4,      // 0011 - { 1, 2 }
    3,      // 0100 - { 3 }
    4,      // 0101 - { 1, 3 }
    4,      // 0110 - { 2, 3 }
    9,      // 0111 - { 1, 2, 3 }
    3,      // 1000 - { 4 }
    6,      // 1001 - { 1, 4 }
    4,      // 1010 - { 2, 4 }
    9,      // 1011 - { 1, 2, 4 }
    7,      // 1100 - { 3, 4 }
    8,      // 1101 - { 1, 3, 4 }
    8,      // 1110 - { 2, 3, 4 }
    11,     // 1111 - { 1, 2, 3, 4 }
};


#endif // MAIN_DEFINE_H
