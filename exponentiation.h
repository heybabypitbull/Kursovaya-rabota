/**
 * @file exponentiation.h
 * @brief Заголовочный файл с описанием класса BigIntegerExponentiation.
 *
 * Содержит объявление класса BigIntegerExponentiation, который предоставляет
 * методы для работы с большими числами, включая возведение в степень, анализ
 * производительности и генерацию графиков зависимости.
 */

#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include <map>

 /**
  * @class BigIntegerExponentiation
  * @brief Класс для работы с большими числами и их возведения в степень.
  *
  * Предоставляет методы для выполнения операций с большими числами, таких как:
  * - Быстрое возведение в степень (fast exponentiation).
  * - Анализ зависимости времени вычислений от длины результата.
  * - Генерация графиков зависимости.
  */
class BigIntegerExponentiation {
public:

    /**
     * @brief Конструктор класса BigIntegerExponentiation.
     * @param inputFile Имя входного файла, содержащего данные для вычислений.
     * @param outputFile Имя выходного файла для сохранения результатов.
     */
    BigIntegerExponentiation(const std::string& inputFile, const std::string& outputFile);

    /**
     * @brief Выполняет вычисление возведения большого числа в степень.
     *
     * Читает данные из входного файла, выполняет возведение числа в степень
     * и сохраняет результат в выходной файл.
     */
    void calculate();

    /**
     * @brief Анализ зависимости времени вычислений от длины результата.
     * @param performanceInputFile Имя входного файла с данными для анализа.
     * @param csvFile Имя CSV-файла для сохранения результатов анализа.
     *
     * Выполняет вычисления и измеряет время их выполнения, а затем сохраняет
     * данные зависимости длины результата от времени выполнения в формате CSV.
     */
    void dependence(const std::string& performanceInputFile, const std::string& csvFile);

    /**
     * @brief Генерирует скрипт Gnuplot для построения графиков.
     * @param csvFiles Список CSV-файлов с результатами зависимости.
     *
     * Создает скрипт для Gnuplot, который визуализирует зависимость времени
     * выполнения от длины результата, используя предоставленные CSV-файлы.
     */
    void generateGnuplotScript(const std::vector<std::string>& csvFiles);

private:

    /**
     * @brief Перемножает два больших числа, представленных в виде строк.
     * @param a Первое число.
     * @param b Второе число.
     * @return Результат умножения в виде строки.
     *
     * Используется для реализации алгоритмов работы с большими числами.
     */
    std::string multiplyLargeNumbers(const std::string& a, const std::string& b);

    /**
     * @brief Выполняет быстрое возведение большого числа в степень.
     * @param base Основание степени (большое число).
     * @param exponent Показатель степени.
     * @return Результат возведения в степень в виде строки.
     *
     * Реализует алгоритм быстрого возведения в степень (Fast Exponentiation),
     * оптимизируя процесс вычислений.
     */
    std::string fastExponentiation(const std::string& base, int exponent);

    std::string inputFileName; ///< Имя входного файла с данными для вычислений.
    std::string outputFileName; ///< Имя выходного файла для сохранения результатов.
};

#endif