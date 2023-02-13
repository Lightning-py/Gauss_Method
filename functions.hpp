#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

struct Matrix
{
    std::vector < std::vector <double> > body; // тело матрицы
    std::vector < double > addition; // дополнение матрицы
    std::vector < double > roots; // вектор ответов
    unsigned int rows; // количество строк
    // double determinant; // определитель матрицы
    /*
    пока не подберу адекватный по ассимтотике алгоритм для детерминанта, тут будет коммент вместо поля определителя
    */
};

void matrix_out_file(Matrix& matrix, std::string filename, bool error=false)
{
    std::ofstream matrix_output;
    matrix_output.open(filename);

    if (!error)
    {   
        for (int i = 0; i < matrix.rows; ++i)
        {
            matrix_output << matrix.roots[i] << ' ';
        }
    }
    else
    {
        matrix_output << "Matrix cannot be solved";
    }

    matrix_output.close();

}


void matrix_in(Matrix& matrix, std::string filaname)
{
    matrix.body = {};
    matrix.addition = {};

    std::ifstream matrix_input;
    matrix_input.open(filaname);


    unsigned int lenght;

    matrix_input >> lenght;
    matrix.rows = lenght;

    int temp;

    for (int i = 0; i < lenght; ++i)
    {
        matrix.body.push_back({});

        for (int j = 0; j < lenght; ++j)
        {
            // чтение матрицы поэлементно
            matrix_input >> temp;

            matrix.body[i].push_back(temp);
        }
        
        // чтение дополнения
        matrix_input >> temp;
        matrix.addition.push_back(temp);
    }

    matrix_input.close();

}

void matrix_out(const Matrix& matrix)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.rows; j++)
        {
            std::cout << matrix.body[i][j] << ' ';
        }

        std::cout << "  |\t" <<  matrix.addition[i] << std::endl;
    }
}


void matrix_answers_out(const Matrix& matrix)
{
    std::cout << std::endl;

    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        std::cout << 'x' << i + 1 << "  =  " << matrix.roots[i] << std::endl;
    }
}

// деление строки, применяется непосредственно в методе Гаусса
void matrix_line_division(Matrix& matrix, unsigned int line, double scalar)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        matrix.body[line][i] /= scalar;
    }

    matrix.addition[line] /= scalar;
}


// вычитание строк друг из друга, возможно домножение
void matrix_line_subtraction(Matrix& matrix, unsigned int line_1, unsigned int line_2, double koefficient=1)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        matrix.body[line_2][i] -= matrix.body[line_1][i] * koefficient;
    }

    matrix.addition[line_2] -= matrix.addition[line_1] * koefficient;
}


// замена строк местами
void matrix_line_swap(Matrix& matrix, unsigned int line_1, unsigned int line_2)
{
    std::vector <double> swap_line(matrix.rows);
    double swap_value;

    swap_line = matrix.body[line_1];
    matrix.body[line_1] = matrix.body[line_2];
    matrix.body[line_2] = swap_line;

    swap_value = matrix.addition[line_1];
    matrix.addition[line_1] = matrix.addition[line_2];
    matrix.addition[line_2] = swap_value;
}


// замена строки с нулем на диагонали
int matrix_zero_change(Matrix& matrix, unsigned int line, unsigned int koefficient_number)
{
    for (unsigned int i = line + 1; i < matrix.rows; i++)
    {
        if (matrix.body[i][koefficient_number] != 0)
        {
            matrix_line_swap(matrix, line, i);
            return 1;
        }
    }
    return 0;
}


// прямой ход метода Гаусса
void gauss_algo_first_part(Matrix& matrix)
{
    
    for (unsigned int element_index_now = 0; element_index_now < matrix.rows; element_index_now++)
    {
        // проверим на ноль элемент на диагонали
        if (matrix.body[element_index_now][element_index_now] == 0) // в случае нахождении нуля на диагонали заменяем его
        { 
            int result = matrix_zero_change(matrix, element_index_now, element_index_now);
            
            if (result == 0) // если поменять строку с нулем не получилось, то матрицу решить не получится, завершаем программу
            {
                matrix_out_file(matrix, "OUTPUT.TXT", true);
                exit(0);
            }
        }  


        // разделим на первый элемент всю строку, тем самым приведем ее к виду "0 ... 1 ..."
        matrix_line_division(matrix, element_index_now, matrix.body[element_index_now][element_index_now]); 


        // зануляем весь оставшийся столбец
        for (unsigned int i = element_index_now + 1; i < matrix.rows; i++)
        {
            matrix_line_subtraction(matrix, element_index_now, i, matrix.body[i][element_index_now]);
        }
    }
}



// обратный ход метода Гаусса
void gauss_algo_second_part(Matrix& matrix)
{
    std::vector <double> answers(matrix.rows);
    matrix.roots = answers;
    matrix.roots[matrix.rows - 1] = matrix.addition[matrix.rows - 1];
    

    for (int element_index_now = matrix.rows - 2; element_index_now >= 0; element_index_now -= 1)
    {
        matrix.roots[element_index_now] = matrix.addition[element_index_now];

        for (unsigned int j = matrix.rows - 1; j > element_index_now; j -= 1)
        {
            matrix.roots[element_index_now] -= matrix.body[element_index_now][j] * matrix.roots[j];    
        }
    }

}


// функция детерминанта, но с кринжовой ассимптотикой (там вообще жесть, чет вроде факториал пополоам)
double determinant(Matrix& matrix)
{
    double result = 0;

    /*
    разделим реализацию на два случая
    1) когда размер матрицы 2x2
    2) остальные случаи
    */

    if (matrix.rows == 2)
    {
        return matrix.body[0][0] * matrix.body[1][1] - matrix.body[1][0] * matrix.body[0][1]; 
    } // нашли детерминант в случае матрицы 2x2
    
    /*
    если матрица не 2x2, то рекурсивно посчитаем сумму алгебраических дополнений
    */


    for (int count = 0; count < matrix.rows; count++) // пройдемся по всем элементам первой строки и посчитаем для них алгебраические дополнения
    {
        Matrix new_matrix;

        std::vector < std::vector <double> > new_matrix_body(matrix.rows - 1);

        for (int i = 1; i < matrix.rows; i++)
        {

            for (int j = 0; j < matrix.rows; j++)
            {
                if (j != count) { new_matrix_body[i - 1].push_back(matrix.body[i][j]); }
            }
        }


        new_matrix.body = new_matrix_body;
        new_matrix.rows = matrix.rows - 1;


        result += std::pow(-1, 2 + count) * matrix.body[0][count] * determinant(new_matrix); 
    }

    return result;
}

