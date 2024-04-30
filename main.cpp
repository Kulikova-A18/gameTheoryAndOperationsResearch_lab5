#include "main.define.h"
#include "main.func.h"

#include <string>

// Макрос для вывода сообщения "The game is: x" в файл
#define PRINT_YES(x, file) (file << "The game is: " << x)

// Макрос для вывода сообщения "The game is not: x" в файл
#define PRINT_NO(x, file) (file << "The game is not: " << x)

// Макрос для вывода произвольного комментария x в файл
#define PRINT_COMMENT(x, file) (file << x)

// Константа для сообщения "DONE"
#define PRINT_DONE "DONE"

// Константа для сообщения "NOT DONE"
#define PRINT_NOT_DONE "NOT DONE"

// Макрос для вывода сообщения о состоянии рационализации группы: "The condition of group rationalization: x"
#define PRINT_RADIALIZ(x, file) (file << "The condition of group rationalization: " << x)

// Макрос для вывода сообщений о состоянии индивидуальной рационализации
#define PRINT_INDIVID_RADIALIZ(num, x, vector, vfunc, file) \
    (file \
    << "\nThe condition of individual rationalization [" << num \
    << " player]:" << x \
    << "\nThe value of the element of the Shapley vector: " << vector \
    << "\nThe meaning of the character of the function: " << vfunc \
    )
#define PRINT_NOT_DONE_INDIVID_RADIALIZ(file)     (file \
    << "SEARCHING FOR THE BEST...")

namespace gameTheoryAndOperationsResearch
{

int _main(int argc, char* argv[])
{
    // Проверка игры на супераддитивность
    // Проверяем все возможные пары множеств игроков, чтобы убедиться, что их пересечения равны 0

    std::ofstream  fout(gameTheoryAndOperationsResearch_filename);                  // Поток для записи в файл
    std::ofstream  fout1(gameTheoryAndOperationsResearch_filename_superadditivity); // Поток для записи результатов проверки на супераддитивность
    std::ofstream  fout2(gameTheoryAndOperationsResearch_filename_bulge);           // Поток для записи результатов проверки на выпуклость

    bool flagAdd = true;    // Флаг супераддитивности
    int i, j, k1, k2;       // Для задания индексов

    for (i = 0; i < N_KOOL - 1; i++)
    {
        // Индекс i задает первое множество игроков
        for (j = i + 1; j < N_KOOL; j++)
        {
            // Индекс j задает второе множество игроков
            k1 = i & j;

            // Побитовое И (пересечение множеств)
            if (k1 == 0)
            {
                k2 = i | j;

                // Побитовое ИЛИ (объединение множеств)
                if (!(v[k2] >= v[i] + v[j]))
                {
                    // Нет супераддитивности
                    flagAdd = false;
                    break;
                }

                fout1 << "v({ ";
                gameTheoryAndOperationsResearch_print(i, fout1);
                fout1 << "} OR { ";
                gameTheoryAndOperationsResearch_print(j, fout1);
                fout1 << "} = { ";
                gameTheoryAndOperationsResearch_print(k2, fout1);
                fout1 << "}) = " << v[k2] << " >= v({ ";
                gameTheoryAndOperationsResearch_print(i, fout1);
                fout1 << "}) = " << v[i] << " + v({ ";
                gameTheoryAndOperationsResearch_print(j, fout1);
                fout1 << "}) = " << v[j]<<std::endl;
            }
        }

        // Если нет супераддитивности
        if (!flagAdd)
            break;
    }


    // Есть супераддитивность
    if (flagAdd)
        PRINT_YES("SUPERADDITIVITY", fout1);
    else
    {
        PRINT_NO("SUPERADDITIVITY", fout1);
        PRINT_COMMENT("\ncondition violation found",fout1);

        fout1 << std::endl;
        fout1 << "v({ ";    gameTheoryAndOperationsResearch_print(i, fout1);
        fout1 << "} OR { ";  gameTheoryAndOperationsResearch_print(j, fout1);
        fout1 << "} = { ";  gameTheoryAndOperationsResearch_print(k2, fout1);
        fout1 << "}) = " << v[k2] << " < v({ "; gameTheoryAndOperationsResearch_print(i, fout1);
        fout1 << "}) = " << v[i] << " + v({ "; gameTheoryAndOperationsResearch_print(j, fout1);
        fout1 << "}) = " << v[j];
    }
    fout1 << "\n\n";

    // Проверка игра на выпуклость
    // Проверяем все возможные пары множеств игроков
    bool flagVyp = true; // Флаг выпуклости

    for (i = 0; i < N_KOOL - 1; i++) // Индекс i задает первое множество игроков
    {
        for (j = i + 1; j < N_KOOL; j++) // Индекс j задает второе множество игроков
        {
            k1 = i & j;  // Побитовое И (пересечение множеств)
            k2 = i | j; // Побитовое ИЛИ (объединение множеств)
            if (!(v[k1] + v[k2] >= v[i] + v[j]))  // Условие выпуклости не выполняется
            {
                flagVyp = false; //  Нет выпуклости
                break;
            }
            fout2 << "v({ ";    gameTheoryAndOperationsResearch_print(i, fout2);
            fout2 << "} OR { ";  gameTheoryAndOperationsResearch_print(j, fout2);
            fout2 << "} = { ";  gameTheoryAndOperationsResearch_print(k2, fout2);
            fout2 << "}) = " << v[k2];

            fout2 << " + v({ "; gameTheoryAndOperationsResearch_print(i, fout2);
            fout2 << "} SUM { ";  gameTheoryAndOperationsResearch_print(j, fout2);
            fout2 << "} = { ";  gameTheoryAndOperationsResearch_print(k1, fout2);
            fout2 << "}) = " << v[k1];

            fout2 << " >= v({ ";                    gameTheoryAndOperationsResearch_print(i, fout2);
            fout2 << "}) = " << v[i] << " + v({ ";  gameTheoryAndOperationsResearch_print(j, fout2);
            fout2 << "}) = " << v[j]<<std::endl;

        }
        if (!flagVyp) // Нет выпуклости
            break;
    }

    if (flagVyp) // Есть выпуклость
        PRINT_YES("BULGE", fout2);
    else
    {
        PRINT_NO("BULGE", fout2);
        PRINT_COMMENT("\ncondition violation found", fout2);

        fout2 << std::endl;
        fout2 << "v({ ";    gameTheoryAndOperationsResearch_print(i, fout2);
        fout2 << "} OR { ";  gameTheoryAndOperationsResearch_print(j, fout2);
        fout2 << "} = { ";  gameTheoryAndOperationsResearch_print(k2, fout2);
        fout2 << "}) = " << v[k2];

        fout2 << " + v({ ";     gameTheoryAndOperationsResearch_print(i, fout2);
        fout2 << "} SUM { ";      gameTheoryAndOperationsResearch_print(j, fout2);
        fout2 << "} = { ";      gameTheoryAndOperationsResearch_print(k1, fout2);
        fout2 << "}) = " << v[k1];

        fout2 << " < v({ ";                     gameTheoryAndOperationsResearch_print(i, fout2);
        fout2 << "}) = " << v[i] << " + v({ ";  gameTheoryAndOperationsResearch_print(j, fout2);
        fout2 << "}) = " << v[j];

    }
    fout2 << std::endl;

    // Для вектора Шепли
    double X[4];

    // Факториал
    int n_gameTheoryAndOperationsResearch_fact = gameTheoryAndOperationsResearch_fact(4);
    double sum = 0;

    fout << "\nElements of the Shapley vector X: ";

    // В цикле значение i - номера игрока
    for (i = 1; i <= 4; i++)
    {
        X[i - 1] = 0;

        // В цикле j задает множество (коалицию) игроков
        for (j = 1; j < N_KOOL; j++) {
            // Игрок есть в множестве
            if (gameTheoryAndOperationsResearch_checking_presence_player_set(i, j))
            {
                X[i - 1] +=
                        gameTheoryAndOperationsResearch_fact(gameTheoryAndOperationsResearch_length(j) - 1) *
                        gameTheoryAndOperationsResearch_fact(4 - gameTheoryAndOperationsResearch_length(j)) *
                        (
                            v[j]
                            -
                            v[gameTheoryAndOperationsResearch_delete_presence_player_set(i, j)]
                        );
            }
        }
        X[i - 1] /= n_gameTheoryAndOperationsResearch_fact;
        sum += X[i - 1]; // Считаем сумму
        fout << X[i - 1] << ' ';
    }


    // Проверка групповой рационализация
    // Сумма элементов вектора Шепли равна значению характеристической функции для всего множества игроков

    fout << std::endl << "The sum of the elements of the Shapley vector:" << sum;
    fout << std::endl << "The value of the characteristic function for the entire set of players: " << v[N_KOOL-1];
    fout << std::endl;

    if (sum == v[N_KOOL - 1])
        PRINT_RADIALIZ(PRINT_DONE, fout);
    else
        PRINT_RADIALIZ(PRINT_NOT_DONE, fout);
    fout << std::endl;
    /*
     * Проверка условия индивидуальной рационализации
     *
     * Значения элемента вектора Шепли для игрока больше,
     * чем значение характеристической функции для множества, состоящего из этого игрока
     */

    bool flagIndRac = true; // условия индивидуальной рационализации выполнены (первоначально)

    // 0001
    bool player1 = false, player2 = false, player3 = false, player4 = false;
    int NUMBER_MATRIX = 1;

    while (!(player1 && player2 && player3 && player4)) {
        // std::cout << "\n[run]";

        if (NUMBER_MATRIX == 11)
            NUMBER_MATRIX = 1;

        if (player1 && player2 && player3 && player4)
            break;

        // ------------------ run player1 ---------------------
        if (!player1) {
            // std::cout << "\n[run player1]";
            if (X[0] <= v[NUMBER_MATRIX]) {
                flagIndRac = false;
                PRINT_INDIVID_RADIALIZ("1", PRINT_NOT_DONE, nullptr, nullptr, fout); // Условие для 1-го игрока не выполнено
                fout << std::endl;
                PRINT_NOT_DONE_INDIVID_RADIALIZ(fout);
            } else {
                PRINT_INDIVID_RADIALIZ("1", PRINT_DONE, X[0], v[NUMBER_MATRIX], fout);
                player1 = true;
                flagIndRac = true;
                NUMBER_MATRIX = 1;
            }
            fout << std::endl;
        }

        // ------------------ run player2 ---------------------
        if (player1 && !player2) {
            // std::cout << "\n[run player2]";
            if (X[1] <= v[NUMBER_MATRIX]) {
                flagIndRac = false;
                PRINT_INDIVID_RADIALIZ("2", PRINT_NOT_DONE, nullptr, nullptr, fout); // Условие для 2-го игрока не выполнено
                fout << std::endl;
                PRINT_NOT_DONE_INDIVID_RADIALIZ(fout);
            } else {
                PRINT_INDIVID_RADIALIZ("2", PRINT_DONE, X[1], v[NUMBER_MATRIX], fout);
                player2 = true;
                flagIndRac = true;
                NUMBER_MATRIX = 1;
            }
            fout << std::endl;
        }

        // ------------------ run player3 ---------------------
        if (player1 && player2 && !player3) {
            // std::cout << "\n[run player3]";
            if (X[2] <= v[NUMBER_MATRIX]) {
                flagIndRac = false;
                PRINT_INDIVID_RADIALIZ("3", PRINT_NOT_DONE, nullptr, nullptr, fout); // Условие для 3-го игрока не выполнено
                fout << std::endl;
                PRINT_NOT_DONE_INDIVID_RADIALIZ(fout);
            } else {
                PRINT_INDIVID_RADIALIZ("3", PRINT_DONE, X[2], v[NUMBER_MATRIX], fout);
                player3 = true;
                flagIndRac = true;
                NUMBER_MATRIX = 1;
            }
            fout << std::endl;
        }

        // ------------------ run player4 ---------------------
        if (player1 && player2 && player3 && !player4) {
            // std::cout << "\n[run player4]";
            if (X[3] <= v[NUMBER_MATRIX]) {
                flagIndRac = false;
                PRINT_INDIVID_RADIALIZ("4", PRINT_NOT_DONE, nullptr, nullptr, fout); // Условие для 4-го игрока не выполнено
                fout << std::endl;
                PRINT_NOT_DONE_INDIVID_RADIALIZ(fout);
            } else {
                PRINT_INDIVID_RADIALIZ("4", PRINT_DONE, X[3], v[NUMBER_MATRIX], fout);
                player4 = true;
                flagIndRac = true;
                NUMBER_MATRIX = 1;
            }
            fout << std::endl;
        }

        NUMBER_MATRIX++;
    }



    (flagIndRac) ?
        PRINT_COMMENT("The condition of individual rationalization: DONE", fout):
        PRINT_COMMENT("The condition of individual rationalization: NOT DONE", fout);

    fout.close();
    fout1.close();
    fout2.close();

    _gameTheoryAndOperationsResearch_readfile();

    return 0;
}

}

int main(int argc, char* argv[])
{
    gameTheoryAndOperationsResearch::_main(argc, argv);
    return 0;
}
