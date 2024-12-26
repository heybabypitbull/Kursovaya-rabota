#include "exponentiation.h"

/**
 * @brief ����������� ������ BigIntegerExponentiation.
 * @param inputFile ��� �������� �����, ����������� ������ ��� ����������.
 * @param outputFile ��� ��������� ����� ��� ���������� �����������.
 */
BigIntegerExponentiation::BigIntegerExponentiation(const std::string& inputFile, const std::string& outputFile)
    : inputFileName(inputFile), outputFileName(outputFile) {}

/**
 * @brief ����������� ��� ������� �����, �������������� � ���� �����.
 * @param a ������ �����.
 * @param b ������ �����.
 * @return ��������� ��������� � ���� ������.
 *
 * ��������� �������� ��������� ���� �����, �������������� � ��������� �������.
 * ������������ ��� ��������� �������� � ������� ������������ �����.
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
 * @brief ��������� ������� ���������� �������� ����� � �������.
 * @param base ��������� ������� (������� ����� � ���� ������).
 * @param exponent ���������� �������.
 * @return ��������� ���������� � ������� � ���� ������.
 *
 * ��������� �������� �������� ���������� � ������� � �������������� ������
 * "��������� �� ������", ��� ��������� ���������� � ���������� � ������� ����������.
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
 * @brief ��������� ���������� ����� � �������, ��������� ������ �� �������� �����.
 *
 * ������ ��������� � ���������� ������� �� �������� �����, ��������� ����������
 * � ��������� ��������� � �������� ����.
 * @throws std::runtime_error ���� �� ������� ������� ������� ��� �������� ����.
 */
void BigIntegerExponentiation::calculate() {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("�� ������� ������� ������� ����.");
    }
    std::string base;
    int exponent;
    inputFile >> base >> exponent;
    inputFile.close();
    std::string result = fastExponentiation(base, exponent);
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("�� ������� ������� �������� ����.");
    }
    outputFile << result;
    outputFile.close();
}

/**
 * @brief ����������� ������������������ ���������� ����� � �������.
 * @param performanceInputFile ��� ����� � ������� ������ (��������� � ����������).
 * @param csvFile ��� ��������� CSV-����� ��� ���������� ������.
 *
 * �������� ����� ���������� �������� ���������� � ������� � ���������� ������
 * � ������� "����� ����������; ����� (��)" � CSV-����.
 * @throws std::runtime_error ���� ������� ��� CSV-���� �� ������� �������.
 */
void BigIntegerExponentiation::dependence(const std::string& performanceInputFile, const std::string& csvFile) {
    std::ifstream inputFile(performanceInputFile);
    if (!inputFile.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������� ������������������.");
    }
    std::ofstream outputFile(csvFile);
    if (!outputFile.is_open()) {
        throw std::runtime_error("�� ������� ������� CSV-����.");
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
 * @brief ���������� ������ ��� ���������� ������� ����������� � ������� Gnuplot.
 * @param csvFiles ������ CSV-������ � ������� ������� ������������������.
 *
 * ������� ������ plot_script.gnuplot, ������� ������ ������ �����������
 * ������� ���������� �� ����� ����������.
 * @throws std::runtime_error ���� �� ������� ������� ���� �������.
 */
void BigIntegerExponentiation::generateGnuplotScript(const std::vector<std::string>& csvFiles) {
    std::ofstream plotScript("plot_script.gnuplot");
    if (!plotScript.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ������� Gnuplot.");
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