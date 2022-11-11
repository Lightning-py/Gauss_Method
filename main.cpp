/*
Реализация метода Гаусса взята из учебника Ф.Г. Авхадиева "Основы численных методов"

ссылка на учебник: https://kpfu.ru//staff_files/F240899232/OsnChM_Avkhadiev_FG.pdf

*/


#include <iostream>
#include <vector>
#include <map>


#include "functions.hpp" // импорт функций, связанных с матрицей и преобразованиями


int main()
{
    setlocale(0, "");

    // исходная матрица, ввод сделаю потом

    // пусть вектор matrix будет исходной дополненной матрицей 

    std::vector < std::vector <float> > matrix = 
    {
        {1, 2, 4, 5},
        {2, 3, 5, 7},
        {5, 6, 2, 3}
    };

    const int matrix_size = matrix.size(); // создадим переменную, которая будет хранить размер матрицы (матрица квадратная, поэтому храним только одно число)
    // тут появился небольшой баг, так как у меня ширина матрицы на 1 больше чем длина ибо матрица изначально расширенная, но вроде все решилось быстро


    // контейнер с ответами

    std::map <unsigned int, float> answers;



    /*
    
    реализация метода Гаусса для заданной матрицы (способом ввода данных займусь потом)
    метод работает для квадратных матриц, не имеющих нулевых коэфициентов в первом столбце

    начну с прямого хода

    */
    


    // предположим, что a11 != 0. разделим на это число коэфициенты первого уравнения

    for (int element_index_now = 0; element_index_now < matrix_size; element_index_now++)
    {
        float first_element = matrix[element_index_now][element_index_now];

        for (unsigned int element_index = 0; element_index < matrix_size + 1; element_index++)
        {
            matrix[element_index_now][element_index] /= first_element;
        }

        // умножим новое первое уравнения на число ak1 и вычтем из k-го уравнения

        for (int k = element_index_now + 1; k < matrix_size; k++)
        {

            float a_K_1 = matrix[k][element_index_now]; // первый элемент k-го уравнения

            for (int i = 0; i < matrix_size  + 1; i++)
            {
                matrix[k][i] -= matrix[element_index_now][i] * a_K_1;
            }
        }
    }

    std::cout << "матрица, приведенная к ступенчатому виду" << std::endl;

    for (auto vect: matrix)
    {
        for (auto element: vect)
        {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }


    answers[matrix_size - 1] = matrix[matrix_size - 1][matrix_size];


    // теперь обратный ход (как прямой - только обратный)

    for (int i = matrix_size - 1; i >= 0; i -= 1)
    {
        float answer = matrix[i][matrix_size];
        for (int element_index = matrix_size - 1; element_index > i; element_index -= 1)
        {
            answer -= answers[element_index] * matrix[i][element_index];
        }
        answers[i] = answer;

    }

    std::cout << std::endl << "ответы" << std::endl;

    for (int i = 0; i < matrix_size; i++)
    {
        std::cout << 'x' << i + 1 << " = " << answers[i] << std::endl;
    }

    return 0;
}
