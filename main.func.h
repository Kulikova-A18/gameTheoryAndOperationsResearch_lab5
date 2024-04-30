#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include "main.define.h"
namespace gameTheoryAndOperationsResearch {
    void _gameTheoryAndOperationsResearch_readfile() {
            std::cout << "\n[" << gameTheoryAndOperationsResearch_filename_superadditivity << "]" << std::endl;
            std::string line1;
            std::ifstream in1(gameTheoryAndOperationsResearch_filename_superadditivity);
            while (std::getline(in1, line1))
                std::cout << line1 << std::endl;

            std::cout << "\n[" << gameTheoryAndOperationsResearch_filename_bulge << "]" << std::endl;
            std::string line2;
            std::ifstream in2(gameTheoryAndOperationsResearch_filename_bulge);
            while (std::getline(in2, line2))
                std::cout << line2 << std::endl;

            std::cout << "\n[" << gameTheoryAndOperationsResearch_filename << "]" << std::endl;
            std::string line;
            std::ifstream in(gameTheoryAndOperationsResearch_filename);
            while (std::getline(in, line))
                std::cout << line << std::endl;

            line.clear();
            line1.clear();
            line2.clear();
    }

    /*
     * функция принимает index, представляющее четыре элемента множества (1,2,3,4),
     * выводит номера элементов, соответствующих установленным битам в этом числе
     */

    void gameTheoryAndOperationsResearch_print(int index, std::ofstream& fout)
    {
        int mask = 1; // Инициализация битовой маски

        // Проверяем в цикле все возможные четыре элемента множества
        for (int i = 1; i <= 4; i++)
        {
            if (mask & index)           // Проверяем установку бита в 1
                fout << i << ' ';       // Печатаем номер элемента, если бит установлен
            mask <<= 1;                 // Сдвигаем битовую маску на один бит влево
        }
    }

    /*
     * определяет количество элементов в множестве index,
     * представленном целым двоичным числом (0,1) подсчетом установленных битов
     */

    int gameTheoryAndOperationsResearch_length(int index)
    {
        int len = 0;        // Инициализация переменной для подсчета количества элементов
        int maska = 1;      // Инициализация битовой маски

        // Проверяем в цикле все возможные четыре элемента множества
        for (int i = 1; i <= 4; i++)
        {
            if (maska & index)      // Проверяем установку бита в 1
                len++;              // Увеличиваем счетчик элементов
            maska <<= 1;            // Сдвигаем битовую маску на один бит влево для проверки следующего элемента
        }
        return len; // Возвращаем количество элементов в множестве
    }

    /*
     * Функция для вычисления факториала числа n
     */

    int gameTheoryAndOperationsResearch_fact(int n)
    {
        if (n < 0)
            return 0;   // Если число отрицательное, возвращаем 0 (факториал не определен для отрицательных чисел)
        if (n == 0)
            return 1;   // Факториал 0 равен 1

        int f = 1;      // Инициализация переменной для хранения результата
        for (int i = 2; i <= n; i++)
            f *= i;     // Вычисление факториала путем умножения на каждое число от 2 до n
        return f;       // Возвращаем вычисленное значение факториала
    }

    // Проверка наличия игрока в множестве (коалиции)
    bool gameTheoryAndOperationsResearch_checking_presence_player_set(int num/*номер игрока (1,2,3,4)*/, int set/*целое определяет множество*/)
    {
        int mask = 1; // Инициализация маски
        for (int i = 2; i <= num; i++)
            mask <<= 1; // Настройка маски на нужный бит

        if (set & mask) // Проверка, установлен ли нужный бит в множестве
            return true; // Если бит установлен, возвращаем true
        else
            return false; // Если бит не установлен, возвращаем false
    }


    // Удаление игрока из множества (коалиции), бит, соответствующий игроку, устанавливаем в 0
    // Функция возвращает целое число, задающее полученное множество
    int gameTheoryAndOperationsResearch_delete_presence_player_set(int num /*номер игрока (1,2,3,4)*/, int set /*целое определяет множество*/)
    {
        int mask = 1;
        for (int i = 2; i <= num; i++)
            mask <<= 1; // Настройка маски на нужный бит

        int mask2 = ~mask; // Побитовое инвертирование: нужный бит равен 0, остальные равны 1
        return set & mask2 & 0xf; // Обнуляем требуемый бит, оставляем только последние 4 бита в итоговом числе
    }

}
#endif // MAIN_FUNC_H
