#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "ECA/Rule30.hpp"
#include "ECA/StatisticalAnalysis.hpp"
#include "ECA/HistogramAnalysis.hpp"

// #include "GUI/Grapher.h"

#include "Functions.h"
#include "PrimeGenerator.hpp"
#include "FileController.hpp"

using namespace std;

int mainMenu();
int generationsMenu();
int displayMenu();

void calculateGenerations();
// void graphicMode();
void mainColumn();
void primeAnalisis();

int main()
{
    int option = mainMenu();

    switch (option)
    {
    case 1:
        calculateGenerations();
        break;
    case 2:
        // graphicMode();
        break;
    case 3:
        mainColumn();
        break;
    case 4:
        primeAnalisis();
        break;
    }

    return 0;
}

int mainMenu()
{
    int option;
    cout << "1) Generations\n";
    cout << "2) Graphic mode\n";
    cout << "3) Main column size \n";
    cout << "4) Prime analisis\n";

    cin >> option;

    return option;
}

int generationsMenu()
{
    int option;
    cout << "0) Display generation\n";
    cout << "n) Create N generations\n";

    cin >> option;

    return option;
}

int displayMenu()
{
    int option;
    cout << "0) All generated generations\n";
    cout << "n) The N generation\n";

    cin >> option;

    return option;
}

void calculateGenerations()
{
    Rule30 eca;

    int main_option = generationsMenu();
    if (!main_option)
    {
        int display_option = displayMenu();
        if (!display_option)
            // Display all options
            for (int i = 1; i <= eca.getGenerationCount(); i++)
                eca.displayFile(i);
        else
            // Display especific generation
            eca.displayFile(display_option);
    }
    else
    {
        bool display = false;

        cout << "Display (0, 1): ";
        cin >> display;

        if (display)
            for (int i = 0; i < main_option; i++)
            {
                eca.step();
                eca.display();
            }
        else
            for (int i = 0; i < main_option; i++)
                eca.step();
    }

    cout << "";

    bool compress;
    cout << "\nCompress (0, 1): ";
    cin >> compress;

    if (compress)
        eca.compressAndClean();
}

// void graphicMode()
// {
//     int rule = 0;
//     ElementaryCellularAutomaton eca(getBinary(rule, 8), 100);
//     Grapher gui(1920, 1080, "Elementary Cellular Automaton", {255, 255, 255}, eca);
//     gui.mainLoop();
// }

void mainColumn()
{
    Rule30 eca;
    vector<bool> column = loadBoolVector("data/central.bin");
    column.resize(eca.getGenerationCount());

    for (int i = eca.getMinGeneration(); i <= eca.getGenerationCount(); i++)
    {
        vector<bool> space = eca.getSpace(i);
        column[i - 1] = space[space.size() / 2];
    }

    // Display mid vector
    for (const bool &value : column)
        cout << value << " ";

    std::cout << "Size: " << column.size();

    saveBoolVector(column, "data/central");

    column.clear();
}

void primeAnalisis()
{
    int option = 1;
    cout << "0) Generate\n";
    cout << "1) Analisis\n";
    cout << "2) histogram \n";
    cin >> option;

    vector<bool> column = loadBoolVector("data/central.bin");
    vector<int> primes = loadIntVector("data/primes.csv");
    vector<vector<int>> prime_analisis = loadMatrix("data/prime_analisis.csv");

    switch (option)
    {
    case 0:
    {
        // Cargar datos
        vector<vector<int>> prime_analisis = loadMatrix("data/prime_analisis.csv");
        map<int, vector<int>> populations = matrixToMap(prime_analisis);

        // Ajustar parametros
        primes.insert(primes.begin(), 1);

        Rule30 eca;
        eca.primeNumberAnalisis(populations, column, primes);
        vector<vector<int>> prime_matrix = mapToMatrix(populations);

        saveIntMatrix(prime_matrix, "data/prime_analisis.csv");

        break;
    }
    case 1:
    {
        vector<string> headers = {"id", "prime", "size", "max",
                                  "mean", "media", "mode",
                                  "sigma", "sigma_b",
                                  "m2", "m3", "m4"};
        vector<vector<long double>> matrix = readCSV("data/statistical_analysis.csv");
        long double i = matrix.size();
        prime_analisis = std::vector<std::vector<int>>(prime_analisis.begin() + i, prime_analisis.end());

        for (const std::vector<int> &prime_line : prime_analisis)
        {
            vector<long double> instance;

            if (prime_line.size() <= 2)
                break;

            std::vector<int> data(prime_line.begin() + 1, prime_line.end() - 1);
            long double mean_v = mean(data);

            instance = {i++,
                        static_cast<long double>(prime_line[0]),
                        static_cast<long double>(data.size()),
                        static_cast<long double>(prime_line[prime_line.size() - 1]),
                        mean_v,
                        median(data),
                        static_cast<long double>(mode(data)),
                        standardDeviation(data, mean_v),
                        standardDeviation(data, mean_v, true),
                        momentAboutMean(data, 2, mean_v),
                        momentAboutMean(data, 3, mean_v),
                        momentAboutMean(data, 4, mean_v)};

            matrix.push_back(instance);
        }

        saveCSV(matrix, headers, "./data/statistical_analysis.csv");
        break;
    }
    case 2:
    {
        vector<vector<pair<int, int>>> matrix;

        for (int j = 0; j < 1000000; j++)
            matrix.push_back(generateHistogram(prime_analisis[j]));

        saveIntPairMatrix(matrix, "./data/histogram.csv");

        break;
    }
    default:
        break;
    }
}