#pragma once 


#include <vector>
#include <string>
#include <fstream>


void input(std::vector <std::vector <float> > &matrix, std::string file_adress, int hight, int lenght)
{
    matrix = {{}};
 
    std::ifstream fi(file_adress); // окрываем файл для чтения    
    float inp;
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < lenght; j++)
        {
            fi >> inp;
            matrix[matrix.size() - 1].push_back(inp);
        }
        matrix.push_back({});
    }
    matrix.pop_back();
    fi.close();
}   
