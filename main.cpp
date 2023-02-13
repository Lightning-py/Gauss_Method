/*
Реализация метода Гаусса взята из учебника Ф.Г. Авхадиева "Основы численных методов"
ссылка на учебник: https://kpfu.ru//staff_files/F240899232/OsnChM_Avkhadiev_FG.pdf
*/

bool DEBUG = false;
bool FILE_OUTPUT = true;


#include <iostream>
#include <vector>


#include "functions.hpp" // импорт функций, связанных с матрицей и преобразованиями

int main()
{    


    Matrix my_matrix;
    
    matrix_in(my_matrix, "INPUT.TXT");

    if (DEBUG)
    {
        std::cout << "Input:" << std::endl;
        matrix_out(my_matrix);
    }

    gauss_first_pass(my_matrix);

    if (DEBUG)
    {
        std::cout << std::endl << "Matrix after gauss algo first part:" << std::endl;
        matrix_out(my_matrix);
    }
    

    gauss_second_pass(my_matrix);
    if (FILE_OUTPUT)
    {
        matrix_out_file(my_matrix, "OUTPUT.TXT");
    }
    else
    {
        std::cout << std::endl;
        matrix_out(my_matrix);
        matrix_answers_out(my_matrix);
    }


    return 0;
}
