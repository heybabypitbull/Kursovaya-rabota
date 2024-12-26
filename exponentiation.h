/**
 * @file exponentiation.h
 * @brief ������������ ���� � ��������� ������ BigIntegerExponentiation.
 *
 * �������� ���������� ������ BigIntegerExponentiation, ������� �������������
 * ������ ��� ������ � �������� �������, ������� ���������� � �������, ������
 * ������������������ � ��������� �������� �����������.
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
  * @brief ����� ��� ������ � �������� ������� � �� ���������� � �������.
  *
  * ������������� ������ ��� ���������� �������� � �������� �������, ����� ���:
  * - ������� ���������� � ������� (fast exponentiation).
  * - ������ ����������� ������� ���������� �� ����� ����������.
  * - ��������� �������� �����������.
  */
class BigIntegerExponentiation {
public:

    /**
     * @brief ����������� ������ BigIntegerExponentiation.
     * @param inputFile ��� �������� �����, ����������� ������ ��� ����������.
     * @param outputFile ��� ��������� ����� ��� ���������� �����������.
     */
    BigIntegerExponentiation(const std::string& inputFile, const std::string& outputFile);

    /**
     * @brief ��������� ���������� ���������� �������� ����� � �������.
     *
     * ������ ������ �� �������� �����, ��������� ���������� ����� � �������
     * � ��������� ��������� � �������� ����.
     */
    void calculate();

    /**
     * @brief ������ ����������� ������� ���������� �� ����� ����������.
     * @param performanceInputFile ��� �������� ����� � ������� ��� �������.
     * @param csvFile ��� CSV-����� ��� ���������� ����������� �������.
     *
     * ��������� ���������� � �������� ����� �� ����������, � ����� ���������
     * ������ ����������� ����� ���������� �� ������� ���������� � ������� CSV.
     */
    void dependence(const std::string& performanceInputFile, const std::string& csvFile);

    /**
     * @brief ���������� ������ Gnuplot ��� ���������� ��������.
     * @param csvFiles ������ CSV-������ � ������������ �����������.
     *
     * ������� ������ ��� Gnuplot, ������� ������������� ����������� �������
     * ���������� �� ����� ����������, ��������� ��������������� CSV-�����.
     */
    void generateGnuplotScript(const std::vector<std::string>& csvFiles);

private:

    /**
     * @brief ����������� ��� ������� �����, �������������� � ���� �����.
     * @param a ������ �����.
     * @param b ������ �����.
     * @return ��������� ��������� � ���� ������.
     *
     * ������������ ��� ���������� ���������� ������ � �������� �������.
     */
    std::string multiplyLargeNumbers(const std::string& a, const std::string& b);

    /**
     * @brief ��������� ������� ���������� �������� ����� � �������.
     * @param base ��������� ������� (������� �����).
     * @param exponent ���������� �������.
     * @return ��������� ���������� � ������� � ���� ������.
     *
     * ��������� �������� �������� ���������� � ������� (Fast Exponentiation),
     * ����������� ������� ����������.
     */
    std::string fastExponentiation(const std::string& base, int exponent);

    std::string inputFileName; ///< ��� �������� ����� � ������� ��� ����������.
    std::string outputFileName; ///< ��� ��������� ����� ��� ���������� �����������.
};

#endif