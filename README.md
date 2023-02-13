# Реализация метода Гаусса на языке C++

> Реализация метода Гаусса взята из [учебника Ф.Г. Авхадиева "Основы численных методов"](https://kpfu.ru//staff_files/F240899232/OsnChM_Avkhadiev_FG.pdf)

## Как это все дело собрать

```bash
$ git clone https://github.com/Lightning-py/Gauss_Method
$ cd Gauss_Method
$ make
```

ура, все собралось и работает

#### Информация об алгоритме

[Метод Гаусса (wiki)](https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%93%D0%B0%D1%83%D1%81%D1%81%D0%B0)

[Метод Гаусса для чайников (mathprofi.ru)](http://mathprofi.ru/metod_gaussa_dlya_chainikov.html)

#### Параметры самой программы

в main.cpp есть два параметра в начале файла

DEBUG = true; - программа будет выводить матрицу после каждой части алгоритма

FILE_OUTPUT = true; - вывод ответов в файл, а не в консоль
