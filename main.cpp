// Created by Student named Oleksandr Radionenko.
// Day 28.03.2025
// Przedmiot: Algorytmy i złożoność obliczeniowa
// Program realizujący porównanie efektywności algorytmów sortowania

#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <functional>
#include <type_traits>

// Funkcja sprawdzająca, czy tablica jest posortowana (rosnąco)
template <typename T>
bool isSorted(const std::vector<T>& arr) {
    // Sprawdza każdy element i porównuje z poprzednim
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

// Klasa Sorter zawiera implementacje różnych algorytmów sortowania
class Sorter {
public:
    // Sortowanie przez wstawianie
    template<typename T>
    static void insertionSort(std::vector<T>& arr);

    // Sortowanie przez kopcowanie (heap sort)
    template<typename T>
    static void heapSort(std::vector<T>& arr);

    // Sortowanie metodą Shella z wyborem sekwencji przerw
    template<typename T>
    static void shellSort(std::vector<T>& arr, int gapType);

    // Sortowanie szybkie (quick sort) z wyborem metody wyboru pivota
    template<typename T>
    static void quickSort(std::vector<T>& arr, int pivotType);

private:
    // Funkcja pomocnicza do budowy kopca
    template<typename T>
    static void heapify(std::vector<T>& arr, int n, int i);

    // Rekurencyjna funkcja quickSort
    template<typename T>
    static void quickSortRecursive(std::vector<T>& arr, int low, int high, int pivotType);

    // Funkcja partycjonująca dla quickSort
    template<typename T>
    static int partition(std::vector<T>& arr, int low, int high, int pivotType);
};

// Klasa DataGenerator służy do generowania danych testowych
class DataGenerator {
public:
    // Generuje losową tablicę elementów typu T
    template<typename T>
    static std::vector<T> generateRandomArray(int size);

    // Generuje posortowaną tablicę (rosnąco lub malejąco)
    template<typename T>
    static std::vector<T> generateSortedArray(int size, bool ascending);

    // Generuje częściowo posortowaną tablicę
    // (pierwszy percentSorted fragment jest posortowany)
    template<typename T>
    static std::vector<T> generatePartiallySortedArray(int size, double percentSorted);
};

// Klasa FileManager odpowiada za operacje wejścia/wyjścia (wczytywanie i zapisywanie tablic)
class FileManager {
public:
    // Zapisuje tablicę do pliku
    template <typename T>
    static bool saveArrayToFile(const std::string& filename, const std::vector<T>& arr);

    // Wczytuje tablicę z pliku
    template <typename T>
    static std::vector<T> loadArrayFromFile(const std::string& filename);
};

// Deklaracja szablonu klasy SortingApp do obsługi operacji na tablicach różnych typów
template <typename T>
class SortingApp;

// Klasa Menu - interfejs użytkownika
class Menu {
public:
    // Wyświetla menu dla operacji na tablicach
    template <typename T>
    static void display(SortingApp<T>& app);

    // Menu wyboru typu danych (int lub float)
    static void displayTypeSelection();
};

// Klasa SortingApp - główna logika aplikacji sortowania
template <typename T>
class SortingApp {
private:
    std::vector<T> array;         // Tablica oryginalna
    std::vector<T> sortedArray;   // Tablica posortowana

public:
    // Uruchamia aplikację (wyświetla menu)
    void run() {
        Menu::display(*this);
    }

    // Ustawia oryginalną tablicę
    void setArray(const std::vector<T>& arr) {
        array = arr;
    }

    // Zwraca oryginalną tablicę (jako stałą referencję, by unikać kopiowania)
    const std::vector<T>& getArray() const {
        return array;
    }

    // Ustawia posortowaną tablicę
    void setSortedArray(const std::vector<T>& arr) {
        sortedArray = arr;
    }

    // Zwraca posortowaną tablicę (jako stałą referencję)
    const std::vector<T>& getSortedArray() const {
        return sortedArray;
    }

    // Wczytuje tablicę z pliku
    void readArrayFromFile(const std::string& filename) {
        array = FileManager::loadArrayFromFile<T>(filename);
    }

    // Generuje losową tablicę
    void generateRandomArray(int size) {
        array = DataGenerator::generateRandomArray<T>(size);
    }

    // Generuje posortowaną tablicę
    void generateSortedArray(int size, bool ascending) {
        array = DataGenerator::generateSortedArray<T>(size, ascending);
    }

    // Generuje częściowo posortowaną tablicę
    void generatePartiallySortedArray(int size, double percentSorted) {
        array = DataGenerator::generatePartiallySortedArray<T>(size, percentSorted);
    }

    // Sortuje tablicę przy użyciu wybranego algorytmu
    void sortArray(int algorithm, int option = 1) {
        // Tworzymy kopię oryginalnej tablicy, by zachować nieposortowane dane
        sortedArray = array;

        auto start = std::chrono::high_resolution_clock::now();

        // Wybór algorytmu sortowania
        switch (algorithm) {
            case 1: // Insertion Sort
                Sorter::insertionSort(sortedArray);
                break;
            case 2: // Heap Sort
                Sorter::heapSort(sortedArray);
                break;
            case 3: // Shell Sort
                Sorter::shellSort(sortedArray, option);
                break;
            case 4: // Quick Sort
                Sorter::quickSort(sortedArray, option);
                break;
            default:
                std::cout << "Wrong algorithm!\n";
                return;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::cout << "Sorting time: " << elapsed.count() << " ms\n";

        // Weryfikacja, czy tablica jest poprawnie posortowana
        if (isSorted(sortedArray))
        std::cout << "The array has been sorted correctly.\n";
        else
        std::cout << "Error: The array is not sorted.\n";
    }

    // Funkcja uruchamiająca testy wydajności
    void runPerformanceTest() {
        std::cout << "\n--- PERFORMANCE TEST ---\n";

        // Rozmiary tablic do testowania
        std::vector<int> sizes = {10000, 20000, 50000, 80000, 100000, 150000, 200000};

        // Algorytmy sortowania
        const int NUM_ALGORITHMS = 4;
        std::string algorithmNames[NUM_ALGORITHMS] = {
            "Insertion Sort", "Heap Sort", "Shell Sort (Knuth)", "Quick Sort (Middle Pivot)"
        };

        // Typy danych wejściowych
        std::string dataTypes[5] = {
            "Random", "Sorted Ascending", "Sorted Descending",
            "Partially Sorted (33%)", "Partially Sorted (66%)"
        };

        // Liczba powtórzeń dla uśrednienia
        const int REPEATS = 100;

        // Przygotowanie pliku wynikowego
        std::ofstream resultFile("performance_results.csv");
        if (!resultFile) {
            std::cerr << "Cannot create result file!\n";
            return;
        }

        // Nagłówki CSV
        resultFile << "Algorithm,Data Type,Array Size,Time (ms)\n";

        // Dla każdego algorytmu
        for (int algoId = 1; algoId <= NUM_ALGORITHMS; algoId++) {
            std::cout << "\nTesting: " << algorithmNames[algoId-1] << "\n";


            // Dla każdego typu danych
            for (int dataTypeId = 0; dataTypeId < 5; dataTypeId++) {
                std::cout << "  Data type: " << dataTypes[dataTypeId] << "\n";

                // Dla każdego rozmiaru tablicy
                for (int size : sizes) {
                    // Dla Insertion Sort pomijamy duże tablice
                    if (algoId == 1 && size > 50000) continue;

                    std::cout << "    Size: " << size << "... ";

                    std::vector<double> times;

                    // Powtarzamy test kilka razy
                    for (int rep = 0; rep < REPEATS; rep++) {
                        // Generowanie danych według wybranego typu
                        switch (dataTypeId) {
                            case 0: // Losowa
                                generateRandomArray(size);
                                break;
                            case 1: // Posortowana rosnąco
                                generateSortedArray(size, true);
                                break;
                            case 2: // Posortowana malejąco
                                generateSortedArray(size, false);
                                break;
                            case 3: // Częściowo posortowana (33%)
                                generatePartiallySortedArray(size, 0.33);
                                break;
                            case 4: // Częściowo posortowana (66%)
                                generatePartiallySortedArray(size, 0.66);
                                break;
                        }

                        // Wykonanie sortowania i pomiar czasu
                        auto start = std::chrono::high_resolution_clock::now();

                        // Kopiujemy tablicę przed sortowaniem
                        std::vector<T> testArray = array;

                        // Wywołanie wybranego algorytmu
                        switch (algoId) {
                            case 1: Sorter::insertionSort(testArray); break;
                            case 2: Sorter::heapSort(testArray); break;
                            case 3: Sorter::shellSort(testArray, 1); break; // Używamy sekwencji Knutha
                            case 4: Sorter::quickSort(testArray, 3); break;   // Używamy środkowego pivota
                        }

                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> elapsed = end - start;

                        times.push_back(elapsed.count());
                    }

                    // Obliczenie średniego czasu
                    double avgTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
                    std::cout << "Average time: " << avgTime << " ms\n";

                    // Zapisanie wyniku do pliku
                    resultFile << algorithmNames[algoId-1] << ","
                               << dataTypes[dataTypeId] << ","
                               << size << ","
                               << avgTime << "\n";
                }
            }
        }

        resultFile.close();
        std::cout << "\nResults have been saved to 'performance_results.csv'\n";
    }
};

// Implementacja funkcji sortowania w klasie Sorter

// Insertion Sort - sortowanie przez wstawianie
template <typename T>
void Sorter::insertionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        // Przesuwanie elementów większych od klucza
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Funkcja pomocnicza do budowy kopca (heapify)
template <typename T>
void Sorter::heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort - sortowanie przez kopcowanie
template <typename T>
void Sorter::heapSort(std::vector<T>& arr) {
    int n = arr.size();
    // Budowanie kopca
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    // Ekstrakcja elementów z kopca
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Shell Sort - sortowanie metodą Shella z wyborem sekwencji przerw
template <typename T>
void Sorter::shellSort(std::vector<T>& arr, int gapType) {
    int n = arr.size();
    std::vector<int> gaps;

    if (gapType == 1) { // Ciąg Knutha: 1, 4, 13, 40, 121, ...
        int h = 1;
        while (h < n / 3)
            h = 3 * h + 1;
        while (h >= 1) {
            gaps.push_back(h);
            h /= 3;
        }
    } else { // Ciąg Hibbarda: 1, 3, 7, 15, 31, 63, ...
        int k = 1;
        while ((1 << k) - 1 < n) {
            gaps.push_back((1 << k) - 1);
            k++;
        }
        std::reverse(gaps.begin(), gaps.end());
    }

    // Sortowanie z użyciem wybranej sekwencji przerw
    for (int gap : gaps) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// Funkcja partycjonująca dla Quick Sort z wyborem pivota
template <typename T>
int Sorter::partition(std::vector<T>& arr, int low, int high, int pivotType) {
    int pivotIndex;
    // Wybór indeksu pivota w zależności od metody
    if (pivotType == 1)
        pivotIndex = low; // Lewy
    else if (pivotType == 2)
        pivotIndex = high; // Prawy
    else if (pivotType == 3)
        pivotIndex = low + (high - low) / 2; // Środkowy
    else { // Losowy
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(low, high);
        pivotIndex = dist(gen);
    }

    T pivot = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[high]);
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

// Rekurencyjna funkcja Quick Sort
template <typename T>
void Sorter::quickSortRecursive(std::vector<T>& arr, int low, int high, int pivotType) {
    if (low < high) {
        int pi = partition(arr, low, high, pivotType);
        quickSortRecursive(arr, low, pi - 1, pivotType);
        quickSortRecursive(arr, pi + 1, high, pivotType);
    }
}

// Quick Sort - sortowanie szybkie
template <typename T>
void Sorter::quickSort(std::vector<T>& arr, int pivotType) {
    quickSortRecursive(arr, 0, arr.size() - 1, pivotType);
}

// Implementacja funkcji generujących dane testowe w klasie DataGenerator

// Generuje losową tablicę
template <typename T>
std::vector<T> DataGenerator::generateRandomArray(int size) {
    std::vector<T> arr(size);
    // Użycie statycznego generatora dla lepszej wydajności
    static std::random_device rd;
    static std::mt19937 gen(rd());
    if constexpr (std::is_integral<T>::value) {
        // Dla typów całkowitych używamy równomiernego rozkładu liczb całkowitych
        std::uniform_int_distribution<T> dist(1, 10000);
        for (int i = 0; i < size; ++i)
            arr[i] = dist(gen);
    } else if constexpr (std::is_floating_point<T>::value) {
        // Dla typów zmiennoprzecinkowych używamy równomiernego rozkładu liczb zmiennoprzecinkowych
        std::uniform_real_distribution<T> dist(1.0, 10000.0);
        for (int i = 0; i < size; ++i)
            arr[i] = dist(gen);
    }
    return arr;
}

// Generuje posortowaną tablicę
template <typename T>
std::vector<T> DataGenerator::generateSortedArray(int size, bool ascending) {
    // Najpierw generujemy losową tablicę, potem ją sortujemy
    std::vector<T> arr = generateRandomArray<T>(size);
    if (ascending)
        std::sort(arr.begin(), arr.end());
    else
        std::sort(arr.rbegin(), arr.rend());
    return arr;
}

// Generuje częściowo posortowaną tablicę
template <typename T>
std::vector<T> DataGenerator::generatePartiallySortedArray(int size, double percentSorted) {
    // Generujemy losową tablicę, następnie sortujemy część jej elementów
    std::vector<T> arr = generateRandomArray<T>(size);
    int sortedSize = static_cast<int>(size * percentSorted);
    std::sort(arr.begin(), arr.begin() + sortedSize);
    return arr;
}

// Implementacja funkcji do operacji na plikach w klasie FileManager

// Zapisuje tablicę do pliku
template <typename T>
bool FileManager::saveArrayToFile(const std::string& filename, const std::vector<T>& arr) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file for writing.\n";
        return false;
    }
    // Pierwsza linia to rozmiar tablicy
    file << arr.size() << "\n";
    for (const auto& elem : arr) {
        file << elem << "\n";
    }
    file.close();
    std::cout << "Array saved to file: " << filename << "\n";
    return true;
}

// Wczytuje tablicę z pliku
template <typename T>
std::vector<T> FileManager::loadArrayFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file for reading.\n";
        return {};
    }
    int size;
    file >> size;
    std::vector<T> arr(size);
    for (int i = 0; i < size; ++i) {
        file >> arr[i];
    }
    file.close();
    std::cout << "Array loaded from file: " << filename << "\n";
    return arr;
}

// Implementacja interfejsu menu w klasie Menu

// Funkcja wyświetlająca menu dla operacji na tablicach
template <typename T>
void Menu::display(SortingApp<T>& app) {
    int choice;
    std::string filename;

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Load array from file\n";
        std::cout << "2. Generate random array\n";
        std::cout << "3. Generate sorted array\n";
        std::cout << "4. Generate partially sorted array\n";
        std::cout << "5. Display array\n";
        std::cout << "6. Sort array (choose algorithm)\n";
        std::cout << "7. Display sorted array\n";
        std::cout << "8. Save array to file\n";
        std::cout << "9. Run performance tests\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter file name: ";
                std::cin >> filename;
                app.readArrayFromFile(filename);
                break;
            case 2: {
                int size;
                std::cout << "Enter array size: ";
                std::cin >> size;
                app.generateRandomArray(size);
                std::cout << "Generated random array of size " << size << ".\n";
                break;
            }
            case 3: {
                int size, order;
                std::cout << "Enter array size: ";
                std::cin >> size;
                std::cout << "Sorting order (1 - ascending, 2 - descending): ";
                std::cin >> order;
                app.generateSortedArray(size, order == 1);
                std::cout << "Generated sorted array of size " << size << ".\n";
                break;
            }
            case 4: {
                int size;
                double percent;
                std::cout << "Enter array size: ";
                std::cin >> size;
                std::cout << "Percentage of sorted elements (0.0–1.0): ";
                std::cin >> percent;
                app.generatePartiallySortedArray(size, percent);
                std::cout << "Generated partially sorted array of size " << size << ".\n";
                break;
            }
            case 5: {
                const std::vector<T>& arr = app.getArray();
                std::cout << "Array:\n";
                int count = 0;
                for (const T& num : arr) {
                    std::cout << std::setw(8) << num << " ";
                    if (++count % 10 == 0)
                        std::cout << "\n";
                }
                std::cout << "\n";
                break;
            }
            case 6: {
                std::cout << "Choose sorting algorithm:\n";
                std::cout << "1. Insertion Sort\n";
                std::cout << "2. Heap Sort\n";
                std::cout << "3. Shell Sort\n";
                std::cout << "4. Quick Sort\n";
                int algoChoice;
                std::cin >> algoChoice;

                int option = 1;
                if (algoChoice == 3) {
                    std::cout << "Choose gap sequence:\n";
                    std::cout << "1. Knuth sequence\n";
                    std::cout << "2. Hibbard sequence\n";
                    std::cin >> option;
                }
                else if (algoChoice == 4) {
                    std::cout << "Choose pivot type:\n";
                    std::cout << "1. Left\n";
                    std::cout << "2. Right\n";
                    std::cout << "3. Middle\n";
                    std::cout << "4. Random\n";
                    std::cin >> option;
                }
                app.sortArray(algoChoice, option);
                break;
            }
            case 7: {
                const std::vector<T>& arr = app.getSortedArray();
                std::cout << "Sorted array:\n";
                int count = 0;
                for (const T& num : arr) {
                    std::cout << std::setw(8) << num << " ";
                    if (++count % 10 == 0)
                        std::cout << "\n";
                }
                std::cout << "\n";
                break;
            }
            case 8: {
                std::cout << "Choose which array to save:\n";
                std::cout << "1. Original array\n";
                std::cout << "2. Sorted array\n";
                int saveChoice;
                std::cin >> saveChoice;
                std::cout << "Enter filename to save to: ";
                std::cin >> filename;
                if (saveChoice == 1)
                    FileManager::saveArrayToFile<T>(filename, app.getArray());
                else
                    FileManager::saveArrayToFile<T>(filename, app.getSortedArray());
                break;
            }
            case 9:
                app.runPerformanceTest();
            break;
            case 0:
                std::cout << "Goodbye!\n";
            break;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    } while (choice != 0);
}

// Funkcja wyświetlająca menu wyboru typu danych
void Menu::displayTypeSelection() {
    int typeChoice;
    std::cout << "Choose data type:\n";
    std::cout << "1. Integer (int)\n";
    std::cout << "2. Floating point (float)\n";
    std::cout << "Choose an option: ";
    std::cin >> typeChoice;

    if (typeChoice == 1) {
        SortingApp<int> app;
        app.run();
    } else if (typeChoice == 2) {
        SortingApp<float> app;
        app.run();
    } else {
        std::cout << "Invalid choice! Defaulting to integer type.\n";
        SortingApp<int> app;
        app.run();
    }
}

// Funkcja main - punkt wejścia programu
int main() {
    // Uruchomienie menu wyboru typu danych
    Menu::displayTypeSelection();
    return 0;
}
