#include "exponentiation.h"

/**
 * @brief Основная функция программы.
 *
 * Выполняет следующие действия:
 * - Запрашивает у пользователя имя входного файла для вычислений.
 * - Создает объект класса BigIntegerExponentiation и выполняет расчет возведения в степень.
 * - Запрашивает входные файлы для анализа зависимости производительности (трижды).
 * - Генерирует CSV-файлы с результатами анализа.
 * - Создает и запускает скрипт Gnuplot для построения графика зависимости.
 *
 * @return Код завершения программы (0 при успешном выполнении, 1 при ошибке).
 */
int main() {

    setlocale(LC_ALL, "RU");

    try {
        std::string inputFileName;
        std::cout << "Введите название входного файла для вычислений: ";
        std::cin >> inputFileName;

        // Создание объекта для работы с большими числами
        BigIntegerExponentiation bigIntExp(inputFileName, "output.txt");
        bigIntExp.calculate();
        std::cout << "Результат работы сохранен в файл: output.txt" << std::endl;

        // Сбор входных данных для анализа зависимости
        std::vector<std::string> csvFiles;
        for (int i = 0; i < 3; i++) {
            std::string dependenceInputFile;
            std::cout << "Введите название входного файла для подсчета зависимости (" << i + 1 << " из 3): ";
            std::cin >> dependenceInputFile;

            // Генерация имени CSV-файла
            std::string csvFileName = "dependence_" + std::to_string(i + 1) + ".csv";
            bigIntExp.dependence(dependenceInputFile, csvFileName);
            csvFiles.push_back(csvFileName);

            std::cout << "Данные зависимости сохранены в файл: " << csvFileName << std::endl;
        }

        // Генерация скрипта для построения графика Gnuplot
        bigIntExp.generateGnuplotScript(csvFiles);
        int gnuplotState = system("gnuplot plot_script.gnuplot");
        if (gnuplotState == 0) {
            std::cout << "График зависимости сохранен в файл: dependence_graph.png" << std::endl;
        }
        else {
            std::cout << "Ошибка: Не удалось запустить Gnuplot. Убедитесь, что Gnuplot установлен и доступен в системе." << std::endl;
        }

    }
    catch (const std::exception& e) {
        // Обработка исключений
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}