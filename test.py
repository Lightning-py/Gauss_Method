# Unit tests


import os
import random

# to run this test you need to turn on FILE_OUTPUT flag in main.cpp and recompile program


FILE_INPUT, FILE_OUTPUT, EXECUTABLE = "INPUT.TXT", "OUTPUT.TXT", "Gauss_Method.exe"

TESTS_FOR_EACH_ORDER = 100

NUMBERS_RANGE = 5

MATRIX_ORDER_MIN, MATRIX_ORDER_MAX = 2, 4

"""

The main idea is to calculate some matricies from pre-prepared answers and check the code on it

"""

test_number = 1
tests = {}
error_tests = []

for matrix_order in range(MATRIX_ORDER_MIN, MATRIX_ORDER_MAX + 1):
    # first check is going to be on matrix with zero determinant
    # four test for each matrix order

    # for zero determinant i can just put a column of zeros into the matrix

    matrix = [["0"] for i in range(matrix_order)]

    for col in range(matrix_order):
        for row in range(matrix_order):
            matrix[col].append(
                str(round(random.uniform(-1 * NUMBERS_RANGE, NUMBERS_RANGE)))
            )

    tests[test_number] = [matrix, None, ""]

    with open(FILE_INPUT, "w") as file_input:
        file_input.write(str(matrix_order) + "\n")
        for row in matrix:
            file_input.write(" ".join(row) + "\n")

    os.system(EXECUTABLE)

    with open(FILE_OUTPUT, "r") as file:
        data = file.read()

        tests[test_number] = [matrix, None, data]

        if data.strip() != "Matrix cannot be solved":
            error_tests.append(test_number)

    test_number += 1

    # time for random tests

    for _ in range(TESTS_FOR_EACH_ORDER):
        matrix = [[] for i in range(matrix_order)]

        # generate the matrix

        roots = [
            round(random.uniform(-1 * NUMBERS_RANGE, NUMBERS_RANGE))
            for i in range(matrix_order)
        ]

        for row in range(matrix_order):
            sum_row = 0

            for column in range(matrix_order):
                number = round(random.uniform(-1 * NUMBERS_RANGE, NUMBERS_RANGE))
                sum_row += number * roots[column]
                matrix[row].append(number)

            matrix[row].append(sum_row)

        # write matrix to the file

        with open(FILE_INPUT, "w") as file_input:
            file_input.write(str(matrix_order) + "\n")
            for row in matrix:
                file_input.write(" ".join(list(map(str, row))) + "\n")

        os.system(EXECUTABLE)

        with open(FILE_OUTPUT, "r") as file:
            data = file.read()
            tests[test_number] = [matrix, roots, data]
            if data == "Matrix cannot be solved":
                error_tests.append(test_number)
                break

            if list(map(float, data.strip().split())) != roots:
                error_tests.append(test_number)

        test_number += 1


if len(error_tests) == 0:
    print("Passed")
else:
    print(f"{len(error_tests)} tests failed")
    for test in error_tests:
        print(f"test number {test}")
        print(*tests[test][0], tests[test][1], tests[test][2], "", sep="\n")
