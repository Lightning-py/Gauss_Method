#pragma once


#include <iostream>
#include <vector>


struct Matrix
{
    std::vector < std::vector <float> > matrix_body; // тело матрицы
    std::vector < float > addition; // дополнение матрицы
    std::vector < float > roots; // вектор ответов
    unsigned int rows; // количество строк
    // float determinant; // определитель матрицы
    /*
    пока не подберу адекватный по ассимтотике алгоритм для детерминанта, тут будет коммент вместо поля определителя
    */
};


void matrix_out(const Matrix& matrix)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.rows; j++)
        {
            std::cout << matrix.matrix_body[i][j] << ' ';
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
void matrix_line_division(Matrix& matrix, unsigned int line, float scalar)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        matrix.matrix_body[line][i] /= scalar;
    }

    matrix.addition[line] /= scalar;
}


// вычитание строк друг из друга, возможно домножение
void matrix_line_subtraction(Matrix& matrix, unsigned int line_1, unsigned int line_2, float koefficient=1)
{
    for (unsigned int i = 0; i < matrix.rows; i++)
    {
        matrix.matrix_body[line_2][i] -= matrix.matrix_body[line_1][i] * koefficient;
    }

    matrix.addition[line_2] -= matrix.addition[line_1] * koefficient;
}


// замена строк местами
void matrix_line_swap(Matrix& matrix, unsigned int line_1, unsigned int line_2)
{
    std::vector <float> swap_line(matrix.rows);
    float swap_value;

    swap_line = matrix.matrix_body[line_1];
    matrix.matrix_body[line_1] = matrix.matrix_body[line_2];
    matrix.matrix_body[line_2] = swap_line;

    swap_value = matrix.addition[line_1];
    matrix.addition[line_1] = matrix.addition[line_2];
    matrix.addition[line_2] = swap_value;
}


// замена строки с нулем на диагонали
int matrix_zero_change(Matrix& matrix, unsigned int line, unsigned int koefficient_number)
{
    for (unsigned int i = line + 1; i < matrix.rows; i++)
    {
        if (matrix.matrix_body[i][koefficient_number] != 0)
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
        if (matrix.matrix_body[element_index_now][element_index_now] == 0) // в случае нахождении нуля на диагонали заменяем его
        { 
            int result = matrix_zero_change(matrix, element_index_now, element_index_now);
            
            if (result == 0) // если поменять строку с нулем не получилось, то матрицу решить не получится, завершаем программу
            {
                std::cout << "Matrix cannot be solved" << std::endl;
                exit(0);
            }
        }  


        // разделим на первый элемент всю строку, тем самым приведем ее к виду "0 ... 1 ..."
        matrix_line_division(matrix, element_index_now, matrix.matrix_body[element_index_now][element_index_now]); 


        // зануляем весь оставшийся столбец
        for (unsigned int i = element_index_now + 1; i < matrix.rows; i++)
        {
            matrix_line_subtraction(matrix, element_index_now, i, matrix.matrix_body[i][element_index_now]);
        }
    }
}



// обратный ход метода Гаусса
void gauss_algo_second_part(Matrix& matrix)
{
    std::vector <float> answers(matrix.rows);
    matrix.roots = answers;
    matrix.roots[matrix.rows - 1] = matrix.addition[matrix.rows - 1];
    

    for (int element_index_now = matrix.rows - 2; element_index_now >= 0; element_index_now -= 1)
    {
        matrix.roots[element_index_now] = matrix.addition[element_index_now];

        for (unsigned int j = matrix.rows - 1; j > element_index_now; j -= 1)
        {
            matrix.roots[element_index_now] -= matrix.matrix_body[element_index_now][j] * matrix.roots[j];    
        }
    }

}
