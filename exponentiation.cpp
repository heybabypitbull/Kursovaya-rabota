#include "exponentiation.h"

/**
 * @brief Конструктор класса BigIntegerExponentiation.
 * @param inputFile Имя входного файла, содержащего данные для вычислений.
 * @param outputFile Имя выходного файла для сохранения результатов.
 */
BigIntegerExponentiation::BigIntegerExponentiation(const std::string& inputFile, const std::string& outputFile)
    : inputFileName(inputFile), outputFileName(outputFile) {}

/**
 * @brief Перемножает два больших числа, представленных в виде строк.
 * @param a Первое число.
 * @param b Второе число.
 * @return Результат умножения в виде строки.
 *
 * Выполняет побитное умножение двух чисел, представленных в строковом формате.
 * Используется для поддержки операций с числами произвольной длины.
 */
std::string BigIntegerExponentiation::multiplyLargeNumbers(const std::string& a, const std::string& b) {
    int n = a.size();
    int m = b.size();
    std::string result(n + m, '0');
    for (int i = n - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = m - 1; j >= 0; --j) {
            int temp = (result[i + j + 1] - '0') + (a[i] - '0') * (b[j] - '0') + carry;
            result[i + j + 1] = temp % 10 + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }
    size_t index = result.find_first_not_of('0');
    if (index != std::string::npos) {
        return result.substr(index);
    }
    return "0";
}

/**
 * @brief Выполняет быстрое возведение большого числа в степень.
 * @param base Основание степени (большое число в виде строки).
 * @param exponent Показатель степени.
 * @return Результат возведения в степень в виде строки.
 *
 * Реализует алгоритм быстрого возведения в степень с использованием метода
 * "умножения по модулю", где результат умножается и возводится в квадрат итеративно.
 */
std::string BigIntegerExponentiation::fastExponentiation(const std::string& base, int exponent) {
    std::string result = "1";
    std::string currentBase = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = multiplyLargeNumbers(result, currentBase);
        }
        currentBase = multiplyLargeNumbers(currentBase, currentBase);
        exponent /= 2;
    }
    return result;
}

/**
 * @brief Выполняет возведение числа в степень, используя данные из входного файла.
 *
 * Читает основание и показатель степени из входного файла, выполняет вычисления
 * и сохраняет результат в выходной файл.
 * @throws std::runtime_error Если не удалось открыть входной или выходной файл.
 */
void BigIntegerExponentiation::calculate() {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть входной файл.");
    }
    std::string base;
    int exponent;
    inputFile >> base >> exponent;
    inputFile.close();
    std::string result = fastExponentiation(base, exponent);
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть выходной файл.");
    }
    outputFile << result;
    outputFile.close();
}

/**
 * @brief Анализирует производительность возведения числа в степень.
 * @param performanceInputFile Имя файла с набором данных (основания и показатели).
 * @param csvFile Имя выходного CSV-файла для сохранения данных.
 *
 * Измеряет время выполнения операций возведения в степень и записывает данные
 * в формате "длина результата; время (нс)" в CSV-файл.
 * @throws std::runtime_error Если входной или CSV-файл не удалось открыть.
 */
void BigIntegerExponentiation::dependence(const std::string& performanceInputFile, const std::string& csvFile) {
    std::ifstream inputFile(performanceInputFile);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для анализа производительности.");
    }
    std::ofstream outputFile(csvFile);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть CSV-файл.");
    }
    outputFile << "ResultLength;Time(ns)\n";
    std::string line;
    std::map<size_t, long long> results;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string base;
        int exponent;
        if (!(iss >> base >> exponent)) {
            continue;
        }
        auto start = std::chrono::high_resolution_clock::now();
        std::string result = fastExponentiation(base, exponent);
        auto end = std::chrono::high_resolution_clock::now();
        long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        results[result.length()] = time;
    }
    for (const auto& entry : results) {
        outputFile << entry.first << ";" << entry.second << "\n";
    }
}

/**
 * @brief Генерирует скрипт для построения графика зависимости с помощью Gnuplot.
 * @param csvFiles Список CSV-файлов с данными анализа производительности.
 *
 * Создает скрипт plot_script.gnuplot, который строит график зависимости
 * времени выполнения от длины результата.
 * @throws std::runtime_error Если не удалось создать файл скрипта.
 */
void BigIntegerExponentiation::generateGnuplotScript(const std::vector<std::string>& csvFiles) {
    std::ofstream plotScript("plot_script.gnuplot");
    if (!plotScript.is_open()) {
        throw std::runtime_error("Не удалось создать файл скрипта Gnuplot.");
    }
    plotScript << "set datafile separator ';'\n";
    plotScript << "set terminal png size 1200,800\n";
    plotScript << "set output 'dependence_graph.png'\n";
    plotScript << "set title 'Dependence of Big Integer Exponentiation'\n";
    plotScript << "set xlabel 'Calculation length (digits)'\n";
    plotScript << "set ylabel 'Time (ns)'\n";
    plotScript << "set grid\n";

    plotScript << "set style line 1 lc rgb '#FF1493' lw 2 pt 7\n";
    plotScript << "set style line 2 lc rgb '#0000CD' lw 2 pt 7\n";
    plotScript << "set style line 3 lc rgb '#008000' lw 2 pt 7\n";

    plotScript << "plot '" << csvFiles[0] << "' using 1:2 with linespoints linestyle 1 title 'Time (ns) 1',";
    plotScript << "'" << csvFiles[1] << "' using 1:2 with linespoints linestyle 2 title 'Time (ns) 2', ";
    plotScript << "'" << csvFiles[2] << "' using 1:2 with linespoints linestyle 3 title 'Time (ns) 3' ";
    plotScript.close();
}