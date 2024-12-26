#include "exponentiation.h"

/**
 * @brief �������� ������� ���������.
 *
 * ��������� ��������� ��������:
 * - ����������� � ������������ ��� �������� ����� ��� ����������.
 * - ������� ������ ������ BigIntegerExponentiation � ��������� ������ ���������� � �������.
 * - ����������� ������� ����� ��� ������� ����������� ������������������ (������).
 * - ���������� CSV-����� � ������������ �������.
 * - ������� � ��������� ������ Gnuplot ��� ���������� ������� �����������.
 *
 * @return ��� ���������� ��������� (0 ��� �������� ����������, 1 ��� ������).
 */
int main() {

    setlocale(LC_ALL, "RU");

    try {
        std::string inputFileName;
        std::cout << "������� �������� �������� ����� ��� ����������: ";
        std::cin >> inputFileName;

        // �������� ������� ��� ������ � �������� �������
        BigIntegerExponentiation bigIntExp(inputFileName, "output.txt");
        bigIntExp.calculate();
        std::cout << "��������� ������ �������� � ����: output.txt" << std::endl;

        // ���� ������� ������ ��� ������� �����������
        std::vector<std::string> csvFiles;
        for (int i = 0; i < 3; i++) {
            std::string dependenceInputFile;
            std::cout << "������� �������� �������� ����� ��� �������� ����������� (" << i + 1 << " �� 3): ";
            std::cin >> dependenceInputFile;

            // ��������� ����� CSV-�����
            std::string csvFileName = "dependence_" + std::to_string(i + 1) + ".csv";
            bigIntExp.dependence(dependenceInputFile, csvFileName);
            csvFiles.push_back(csvFileName);

            std::cout << "������ ����������� ��������� � ����: " << csvFileName << std::endl;
        }

        // ��������� ������� ��� ���������� ������� Gnuplot
        bigIntExp.generateGnuplotScript(csvFiles);
        int gnuplotState = system("gnuplot plot_script.gnuplot");
        if (gnuplotState == 0) {
            std::cout << "������ ����������� �������� � ����: dependence_graph.png" << std::endl;
        }
        else {
            std::cout << "������: �� ������� ��������� Gnuplot. ���������, ��� Gnuplot ���������� � �������� � �������." << std::endl;
        }

    }
    catch (const std::exception& e) {
        // ��������� ����������
        std::cout << "������: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}