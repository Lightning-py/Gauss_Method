#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "tools.hpp"


using tls::data_type;


class Matrix
{
    public:
        size_t rows;
        size_t columns;
        std::vector<std::vector<Frac>> body;
        std::vector<Frac> addition;

        Matrix(size_t m_rows, size_t m_columns)
        {
            rows = m_rows;
            columns = m_columns;

            std::vector< std::vector<Frac> > body_(m_rows, std::vector<Frac>(m_columns, 0));
            std::vector<Frac> addition_(m_rows, 0);

            body = body_;
            addition = addition_;
        }

        Matrix(size_t m_rows, size_t m_columns, std::vector< std::vector<Frac> > m_body, std::vector<Frac> m_addition)
        {
            rows = m_rows;
            columns = m_columns;

            body = m_body;
            addition = m_addition;
        }


        Matrix(size_t m_rows, size_t m_columns, std::vector< std::vector< data_type > > m_body, std::vector< data_type > m_addition)
        {
            rows = m_rows;
            columns = m_columns;

            std::vector< std::vector<Frac> > body_;
            std::vector<Frac> addition_;

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < columns; ++j)
                    body_[i][j] = Frac(m_body[i][j]);
                addition_[i] = Frac(m_addition[i]);
            }

            body = body_;
            addition = addition_;
        }

        Matrix transposition()
        {
            Matrix result(columns, rows);

            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < columns; ++j)
                {
                    result.body[j][i] = body[i][j];
                }
            }

            return result;
        }

        Frac gauss_method_part_1()
        {
            Frac val(1);
            

            size_t line_skiped = 0;
            
            bool done = false;

            for (size_t i = 0; i < rows; ++i)
            {
                done = false;
                while (!done)
                {
                    if (i + line_skiped >= rows) { break; }
                    Frac el_now = body[i + line_skiped][i];
                    if (el_now == Frac(0))
                    {
                        // skip line
                        line_skiped += 1;
                        
                    }
                    else
                    {
                        for (size_t counter = i; counter < columns; ++counter)
                        {
                            body[i + line_skiped][counter] =  body[i + line_skiped][counter] / el_now;
                        }
                        addition[i + line_skiped] = addition[i + line_skiped] / el_now;

                        val = val * el_now;

                        for (size_t counter = i + line_skiped + 1; counter < rows; ++counter)
                        {
                            Frac el_first = body[counter][i];
                            for (size_t j = i; j < columns; ++j)
                            {
                                body[counter][j] = body[counter][j] - body[i + line_skiped][j] * el_first;
                            }
                            addition[counter] = addition[counter] - addition[i + line_skiped] * el_first;
                        }
                        done = true;
                    }
                }
            }
            return val;
        }

};

Frac determinant(Matrix matrix)
{
    Frac val = matrix.gauss_method_part_1();

    for (size_t i = 0; i < matrix.rows; ++i)
    {
        val = val * matrix.body[i][i];
    }

    return val;
}

std::vector<Frac> cramer_method(Matrix matrix)
{
    Matrix matrix_copy = matrix;

    Frac det = determinant(matrix_copy);

    std::vector<Frac> roots(matrix_copy.rows);

    if (det == Frac(0))
    {
        return roots;
    }


    Frac temp(1);


    for (size_t col = 0; col < matrix_copy.columns; ++col)
    {
        matrix_copy = matrix;

        for (size_t i = 0; i < matrix_copy.rows; ++i)
            matrix_copy.body[i][col] = matrix_copy.addition[i];
        
        
        temp = determinant(matrix_copy);

        roots[col] = temp / det;
    }

    return roots;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix)
{
    size_t rows, columns;

    stream >> rows >> columns;

    matrix = Matrix(rows, columns);

    data_type temp;
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
        {
            stream >> temp;
            matrix.body[i][j] = Frac(temp);
        }
        stream >> temp;
        matrix.addition[i] = Frac(temp);
    }

    return stream;
}

std::ostream& operator<< (std::ostream& stream, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
            stream << matrix.body[i][j] << "\t";
        stream << "| " << matrix.addition[i] << std::endl;
    }

    return stream;
}

Matrix operator+(const Matrix& matrix, const Matrix& matrix_2)
{
    Matrix result(matrix.rows, matrix.columns);

    if (matrix.rows == matrix_2.rows && matrix.columns == matrix_2.columns)
    {
        for (size_t i = 0; i < matrix_2.rows; ++i)
        {
            for (size_t j = 0; j < matrix_2.columns; ++j) 
                result.body[i][j] = matrix.body[i][j] + matrix_2.body[i][j];
            
            result.addition[i] = matrix.addition[i] + matrix_2.addition[i];
        }
    }

    return result;
}


Matrix operator-(const Matrix& matrix, const Matrix& matrix_2)
{
    Matrix result(matrix.rows, matrix.columns);

    if (matrix.rows == matrix_2.rows && matrix.columns == matrix_2.columns)
    {
        for (size_t i = 0; i < matrix_2.rows; ++i)
        {
            for (size_t j = 0; j < matrix_2.columns; ++j) 
                result.body[i][j] = matrix.body[i][j] - matrix_2.body[i][j];
            
            result.addition[i] = matrix.addition[i] - matrix_2.addition[i];
        }
    }

    return result;
}


Matrix operator*(int number, const Matrix& matrix)
{
    Matrix tmp = Matrix(matrix.rows, matrix.columns, matrix.body, matrix.addition);
            
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
            tmp.body[i][j] *= number;
        tmp.addition[i] *= number;
    }

    return tmp;
}


Matrix operator*(const Matrix& matrix, int number)
{
    Matrix tmp(matrix.rows, matrix.columns, matrix.body, matrix.addition);
            
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.columns; ++j)
            tmp.body[i][j] *= number;
        tmp.addition[i] *= number;
    }

    return tmp;
}
