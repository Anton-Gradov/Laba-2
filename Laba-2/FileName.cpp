/*#include <iostream>
#include <fstream>
using namespace std;

class Sort
{
private:
    int mass_sorted[200], mass_reverse[200], mass_random[200];
    int size = 200;

public:
    void readFromFile(const string& filename)
    {
        ifstream fin(filename);
        if (!fin)
        {
            cout << "Ошибка открытия файла!" << endl;
            exit(1);
        }

        for (int i = 0; i < size; i++)
            fin >> mass_sorted[i];
        for (int i = 0; i < size; i++)
            fin >> mass_reverse[i];
        for (int i = 0; i < size; i++)
            fin >> mass_random[i];

        fin.close();
    }

    void copyArray(int dest[], int src[])
    {
        for (int i = 0; i < size; i++)
            dest[i] = src[i];
    }

    // --- Методы сортировки ---
    void insertionSort(int mass[], int& sr, int& per) //вставка
    {
        sr = per = 0;
        for (int i = 1; i < size; i++)
        {
            int key = mass[i];
            int j = i - 1;
            while (j >= 0)
            {
                sr++;
                if (mass[j] > key)
                {
                    mass[j + 1] = mass[j];
                    per++;
                    j--;
                }
                else break;
            }
            mass[j + 1] = key;
        }
    }

    void bubbleSort(int mass[], int& sr, int& per) //обмен
    {
        sr = per = 0;
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                sr++;
                if (mass[j] > mass[j + 1])
                {
                    swap(mass[j], mass[j + 1]);
                    per++;
                }
            }
        }
    }

    void selectionSort(int mass[], int& sr, int& per) //выбор
    {
        sr = per = 0;
        for (int i = 0; i < size - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < size; j++)
            {
                sr++;
                if (mass[j] < mass[minIdx])
                    minIdx = j;
            }
            if (minIdx != i)
            {
                swap(mass[i], mass[minIdx]);
                per++;
            }
        }
    }

    int binarySearch(int mass[], int left, int right, int key, int& sr)
    {
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            sr++;
            if (mass[mid] == key)
                return mid + 1;
            if (mass[mid] < key)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }

    void binaryInsertionSort(int mass[], int& sr, int& per) //бинарная вставка
    {
        sr = per = 0;
        for (int i = 1; i < size; i++)
        {
            int key = mass[i];
            int j = i - 1;
            int pos = binarySearch(mass, 0, j, key, sr);
            while (j >= pos)
            {
                mass[j + 1] = mass[j];
                j--;
                per++;
            }
            mass[j + 1] = key;
        }
    }

    void shakerSort(int mass[], int& sr, int& per) // шейкер-сортировка
    {
        sr = per = 0;
        int left = 0, right = size - 1;
        while (left < right)
        {
            for (int i = left; i < right; i++)
            {
                sr++;
                if (mass[i] > mass[i + 1])
                {
                    swap(mass[i], mass[i + 1]);
                    per++;
                }
            }
            right--;
            for (int i = right; i > left; i--)
            {
                sr++;
                if (mass[i] < mass[i - 1])
                {
                    swap(mass[i], mass[i - 1]);
                    per++;
                }
            }
            left++;
        }
    }

    void shellSort(int mass[], int& sr, int& per) //Шелла
    {
        sr = per = 0;
        for (int gap = size / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < size; i++)
            {
                int temp = mass[i];
                int j;
                for (j = i; j >= gap; j -= gap)
                {
                    sr++;
                    if (mass[j - gap] > temp)
                    {
                        mass[j] = mass[j - gap];
                        per++;
                    }
                    else break;
                }
                mass[j] = temp;
            }
        }
    }

    void heapify(int mass[], int n, int i, int& sr, int& per)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n)
        {
            sr++;
            if (mass[left] > mass[largest])
                largest = left;
        }
        if (right < n)
        {
            sr++;
            if (mass[right] > mass[largest])
                largest = right;
        }
        if (largest != i)
        {
            swap(mass[i], mass[largest]);
            per++;
            heapify(mass, n, largest, sr, per);
        }
    }

    void heapSort(int mass[], int& sr, int& per) //пирамидальная
    {
        sr = per = 0;
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(mass, size, i, sr, per);

        for (int i = size - 1; i > 0; i--)
        {
            swap(mass[0], mass[i]);
            per++;
            heapify(mass, i, 0, sr, per);
        }
    }

    void quickSortRecursive(int mass[], int low, int high, int& sr, int& per) //быстрая
    {
        if (low < high)
        {
            int pivot = mass[high];
            int i = low - 1;
            for (int j = low; j < high; j++)
            {
                sr++;
                if (mass[j] < pivot)
                {
                    i++;
                    swap(mass[i], mass[j]);
                    per++;
                }
            }
            swap(mass[i + 1], mass[high]);
            per++;
            int pi = i + 1;
            quickSortRecursive(mass, low, pi - 1, sr, per);
            quickSortRecursive(mass, pi + 1, high, sr, per);
        }
    }

    // Функция вывода
    void run()
    {
        int temp[200];
        int sr, per;

        string names[8] = {
            "Вставками", "Пузырьком", "Выбором", "Бинар. вставками",
            "Шейкерная", "Шелла", "Пирамидальная", "Быстрая"
        };

        cout << "Метод\t\t\t| Упорядоченный\t| Обратный\t| Случайный\n";
        cout << "-----------------------------------------------------------------\n";

        for (int method = 0; method < 8; method++)
        {
            cout << names[method];
            if (names[method].size() < 15) cout << "\t";
            if (names[method].size() < 8) cout << "\t";

            // 1. Упорядоченный
            copyArray(temp, mass_sorted);
            sr = per = 0;
            switch (method)
            {
            case 0: insertionSort(temp, sr, per); break;
            case 1: bubbleSort(temp, sr, per); break;
            case 2: selectionSort(temp, sr, per); break;
            case 3: binaryInsertionSort(temp, sr, per); break;
            case 4: shakerSort(temp, sr, per); break;
            case 5: shellSort(temp, sr, per); break;
            case 6: heapSort(temp, sr, per); break;
            case 7: quickSortRecursive(temp, 0, size - 1, sr, per); break;
            }
            cout << "| " << sr << "/" << per << "\t";

            // 2. Обратный
            copyArray(temp, mass_reverse);
            sr = per = 0;
            switch (method)
            {
            case 0: insertionSort(temp, sr, per); break;
            case 1: bubbleSort(temp, sr, per); break;
            case 2: selectionSort(temp, sr, per); break;
            case 3: binaryInsertionSort(temp, sr, per); break;
            case 4: shakerSort(temp, sr, per); break;
            case 5: shellSort(temp, sr, per); break;
            case 6: heapSort(temp, sr, per); break;
            case 7: quickSortRecursive(temp, 0, size - 1, sr, per); break;
            }
            cout << "| " << sr << "/" << per << "\t";

            // 3. Случайный
            copyArray(temp, mass_random);
            sr = per = 0;
            switch (method)
            {
            case 0: insertionSort(temp, sr, per); break;
            case 1: bubbleSort(temp, sr, per); break;
            case 2: selectionSort(temp, sr, per); break;
            case 3: binaryInsertionSort(temp, sr, per); break;
            case 4: shakerSort(temp, sr, per); break;
            case 5: shellSort(temp, sr, per); break;
            case 6: heapSort(temp, sr, per); break;
            case 7: quickSortRecursive(temp, 0, size - 1, sr, per); break;
            }
            cout << "| " << sr << "/" << per << "\n";
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Sort S;
    S.readFromFile("Mass_In.txt"); // читаем данные из файла
    S.run();
    return 0;
}
*/