#pragma once


#include <vector>

// struct Matrix
// {
    
// };

unsigned int find_min_firstline_element(std::vector < std::vector <float> > matrix, unsigned int line_start)
{
    float min_now = matrix[line_start][0];
    unsigned int index_min = line_start;

    for (int i = line_start; i < matrix.size(); i++)
    {
        if (matrix[i][0] < min_now)
        {
            min_now = matrix[i][0];
            index_min = i;
        }
    }

    return index_min;
}

void line_swap(std::vector <std::vector <float> > &matrix, unsigned int line_1, unsigned int line_2)
{
    std::vector <float> swap_line_vector = matrix[line_2];

    matrix[line_2] = matrix[line_1];
    matrix[line_1] = swap_line_vector;
}

void line_multiply(std::vector <std::vector <float> > &matrix, unsigned int line_number, float multiply_number)
{
    for (int i = 0; i < matrix[line_number].size(); i++) { matrix[line_number][i] = matrix[line_number][i] * multiply_number; }
}


void matrix_multiply(std::vector < std::vector <float> > &matrix, float multiply_number)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = matrix[i][j] * multiply_number;
        }
    }
}


void matrix_lines_sort(std::vector < std::vector <float> > &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        unsigned int line_needed = find_min_firstline_element(matrix, i);

        if (i != line_needed)
        {
            line_swap(matrix, i, line_needed);
        }

    }
}

