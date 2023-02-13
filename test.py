import numpy as np
import random
import os


NUMBER_MIN, NUMBER_MAX = -10, 10

MATRIX_ORDER_MAX = 100

TESTS_FOR_EVERY_MATRIX_ORDER = 1

INPUT_FILE, OUTPUT_FILE = "INPUT.TXT", "OUTPUT.TXT"

EXE_NAME = "Gauss_Method.exe"

ACCURACY = 10**-3


def write_matrix(matrix, addition, matrix_order, file_address=INPUT_FILE):
    with open(file_address, "w") as file:
        file.write(str(matrix_order) + "\n")

        for i in range(matrix_order):
            file.write(" ".join(map(str, (np.append(matrix[i], [addition[i]])))) + "\n")


def get_answers(file_address=OUTPUT_FILE):
    with open(file_address) as file:
        data = file.read()

        if data.strip() == "Matrix cannot be solved":
            return 0

        return list(map(float, data.strip().split()))


def answer_check(answers, standard):
    # * help(np.allclose)
    return np.alltrue(np.abs(answers-standard) <= ACCURACY)


tests = []  # element: dict(matrix, addition, numpy_solution, GaussMethod_solution)

test_number = 1

for matrix_order in range(2, MATRIX_ORDER_MAX + 1):
    for test in range(TESTS_FOR_EVERY_MATRIX_ORDER):
        matrix = np.random.random_integers(NUMBER_MIN, NUMBER_MAX, matrix_order)
        addition = np.random.random_integers(NUMBER_MIN, NUMBER_MAX, matrix_order)

        det_matrix = np.linalg.det(matrix)

        if det_matrix:
            solution = list(np.linalg.solve(matrix, addition))
        else:
            solution = "Matrix cannot be solved"

        write_matrix(matrix, addition, matrix_order)

        os.system(EXE_NAME)

        answers = get_answers()

        if det_matrix == 0:
            if answers == 0:
                pass
        else:
            correct_answer = answer_check(answers, solution)

            if not correct_answer:
                tests.append(
                    {
                        "matrix": matrix,
                        "addition": addition,
                        "solution": solution,
                        "answers": answers
                    }
                )


for i in range(len(tests)):
    print(f"{tests[i]=}")
