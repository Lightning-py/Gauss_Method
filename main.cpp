#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <argparse/argparse.hpp>


#include "frac.hpp"
#include "matrix.hpp"

int main(int argc, char* argv[])
{
    Matrix matrix(1, 1);

    argparse::ArgumentParser program("MatrixCalculator");

    program.add_argument("--input")
        .help("specify input file")
        .nargs(1);

    program.add_argument("--output")
        .help("specify output file")
        .nargs(1);

    program.add_argument("--det")
        .help("calculates determinant of the given matrix")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("--gauss")
        .help("leads matrix to a <stairs-like> view (LOL)")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("--cramer")
        .help("calculates the roots of given matrix and addition using the Cramer method")
        .default_value(false)
        .implicit_value(true);
    

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    auto input_file_adress = program.get<std::vector<std::string>>("--input");
    auto output_file_adress = program.get<std::vector<std::string>>("--output");

    // input

    if (input_file_adress.size() != 0)
    {
        std::ifstream input_file;
        input_file.open(input_file_adress[0]);

        input_file >> matrix;
        
        input_file.close();
    }
    else { std::cin >> matrix; }
    
    // actions

    if (output_file_adress.size() != 0)
    {
        std::ofstream output_file;
        output_file.open(output_file_adress[0]);

        if (program["--det"] == true)
        {
            Frac det = determinant(matrix);

            output_file << "determinant: " << det << std::endl << std::endl;
        }

        if (program["--gauss"] == true)
        {
            Matrix matrix_ = matrix;
            matrix_.gauss_method_part_1();
            output_file << "matrix: " << std::endl;
            output_file << matrix_ << std::endl << std::endl;
        }

        if (program["--cramer"] == true)
        {
            std::vector<Frac> result = cramer_method(matrix);

            output_file << "roots:" << std::endl;

            for (Frac element: result) { output_file << element << std::endl; }
            output_file << std::endl;
        }

        output_file.close();
    }
    else
    {
        if (program["--det"] == true)
        {
            Frac det = determinant(matrix);

            std::cout << "determinant: " << det << std::endl << std::endl;
        }

        if (program["--gauss"] == true)
        {
            Matrix matrix_ = matrix;
            matrix_.gauss_method_part_1();
            std::cout << "matrix: " << std::endl;
            std::cout << matrix_ << std::endl << std::endl;
        }

        if (program["--cramer"] == true)
        {
            std::vector<Frac> result = cramer_method(matrix);

            std::cout << "roots:" << std::endl;

            for (Frac element: result) { std::cout << element << std::endl; }
            std::cout << std::endl;
        }
    }
    

    return 0;
}
