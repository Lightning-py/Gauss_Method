import numpy as np
import random
import os


NUMBER_MIN, NUMBER_MAX = -10, 10

MATRIX_ORDER_MAX = 100

TESTS_FOR_EVERY_MATRIX_ORDER = 1

INPUT_FILE, OUTPUT_FILE = "INPUT.TXT", "OUTPUT.TXT"

EXE_NAME = "Gauss_Method.exe"

ACURACY = 10**-3


def write_matrix(matrix, addition, matrix_order, file_adress=INPUT_FILE):
    with open(file_adress, "w") as file:
        file.write(str(matrix_order) + "\n")

        for i in range(matrix_order):
            file.write(" ".join(map(str, (np.append(matrix[i], [addition[i]])))) + "\n")


def get_answers(file_adress=OUTPUT_FILE):
    with open(file_adress) as file:
        data = file.read()

        if data.strip() == "Matrix cannot be solved":
            return 0

        return list(map(float, data.strip().split()))


def answer_check(answers, standard):
    return all(
        [
            standard[i] - ACURACY <= answers[i] <= standard[i] + ACURACY
            for i in range(len(answers))
        ]
    )


tests = []  # element: [ matrix, addition, numpy_solution, GaussMethod_solution]

test_number = 1

for matrix_order in range(2, MATRIX_ORDER_MAX + 1):
    for test in range(TESTS_FOR_EVERY_MATRIX_ORDER):
        matrix = np.array(
            [
                [
                    round(random.uniform(NUMBER_MIN, NUMBER_MAX))
                    for i in range(matrix_order)
                ]
                for i in range(matrix_order)
            ]
        )

        addition = np.array(
            [round(random.uniform(NUMBER_MIN, NUMBER_MAX)) for i in range(matrix_order)]
        )

        det_matrix = np.linalg.det(matrix)

        if det_matrix:
            solution_array = list(map(float, np.linalg.solve(matrix, addition)))

        else:
            solution_array = "Matrix cannot be solved"

        write_matrix(matrix, addition, matrix_order)

        os.system(EXE_NAME)

        answers = get_answers()

        if det_matrix == 0:
            if answers == 0:
                pass

        else:
            answer_correctness = answer_check(answers, solution_array)

            if not answer_correctness:
                tests.append([matrix, addition, solution_array, answers])


for test in tests:
    print(
        f"#----\nmatrix:\n{test[0]}\n\naddition:\n{test[1]}\n\nnumpy_solution:\n{test[2]}\n\nsolution_cpp:\n{test[3]}\n"
    )
