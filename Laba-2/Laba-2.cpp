#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Rekyr
{
private:
    vector<int> mass;
    int maxx;
    int mest = 0;
    int i = 1;

    int n;

    int N;
    vector<vector<int>> board;
    vector<int> moveX = { 2, 1, -1, -2, -2, -1, 1, 2 };
    vector<int> moveY = { 1, 2, 2, 1, -1, -2, -2, -1 };
    bool finished = false;

    int QN;
    vector<int> queens;

    // Функция для вычисления модуля числа
    int absValue(int x)
    {
        return x < 0 ? -x : x;
    }

public:
    void readFromFile(const string& filename)
    {
        ifstream fin(filename);
        if (!fin)
        {
            cout << "Ошибка открытия файла!" << endl;
            exit(1);
        }

        // Читаем размер массива
        int size;
        fin >> size;
        mass.resize(size);

        // Читаем элементы массива
        for (int i = 0; i < size; i++)
            fin >> mass[i];

        // Читаем количество дисков для ханойских башен
        fin >> n;

        // Читаем размер доски для коня
        fin >> N;

        // Читаем количество ферзей
        fin >> QN;

        fin.close();

        maxx = mass[0];

        // Инициализация доски для коня
        board.resize(N, vector<int>(N, -1));

        // Инициализация вектора ферзей
        queens.resize(QN, -1);
    }

    // ===== 1. Рекурсивный поиск максимума =====
    void max()
    {
        if (i < mass.size())
        {
            if (maxx < mass[i])
            {
                maxx = mass[i];
                mest = i;
            }
            i++;
            max();
        }
        else if (i == mass.size())
        {
            if (maxx < mass[i - 1])
            {
                maxx = mass[i - 1];
                mest = i - 1;
            }
        }
    }

    // ===== 2. Ханойские башни =====
    void hanoi(int n, char from, char to, char temp)
    {
        cout << "Вызов: n = " << n << endl;
        if (n == 1)
        {
            cout << "Переложить диск 1 с " << from << " на " << to << endl;
        }
        else
        {
            hanoi(n - 1, from, temp, to);
            cout << "Переложить диск " << n << " с " << from << " на " << to << endl;
            hanoi(n - 1, temp, to, from);
        }
    }

    // ===== 3. Ход коня =====
    bool isSafe(int x, int y)
    {
        return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
    }

    void printBoard()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
    }

    void knightMove(int x, int y, int step)
    {
        if (step == N * N)
        {
            printBoard();
            finished = true;
            return;
        }

        for (int i = 0; i < 8; i++)
        {
            int nx = x + moveX[i];
            int ny = y + moveY[i];
            if (isSafe(nx, ny))
            {
                board[nx][ny] = step;
                knightMove(nx, ny, step + 1);
                if (finished) return;
                board[nx][ny] = -1;
            }
        }
    }

    // ===== 4. Расстановка ферзей =====
    bool isSafeQueen(int row, int col)
    {
        for (int i = 0; i < row; i++)
        {
            if (queens[i] == col || absValue(queens[i] - col) == absValue(i - row))
                return false;
        }
        return true;
    }

    void printQueens()
    {
        for (int i = 0; i < QN; i++)
        {
            for (int j = 0; j < QN; j++)
            {
                if (queens[i] == j) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void placeQueen(int row)
    {
        if (row == QN)
        {
            printQueens();
            return;
        }

        for (int col = 0; col < QN; col++)
        {
            if (isSafeQueen(row, col))
            {
                queens[row] = col;
                placeQueen(row + 1);
                queens[row] = -1;
            }
        }
    }

    // Функция вывода
    void run()
    {
        cout << "===== Поиск максимума =====" << endl;
        max();
        cout << "Максимальный член массива: " << maxx << endl;
        cout << "Место максимального члена массива: " << mest << endl << endl;

        cout << "===== Ханойские башни =====" << endl;
        hanoi(n, 'A', 'C', 'B');
        cout << endl;

        cout << "===== Ход коня =====" << endl;
        // Инициализация доски
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                board[i][j] = -1;

        int startX = 0, startY = 0;
        board[startX][startY] = 0;
        knightMove(startX, startY, 1);

        if (!finished)
            cout << "Решение не найдено." << endl;

        cout << "===== Расстановка ферзей =====" << endl;
        for (int i = 0; i < QN; i++)
            queens[i] = -1;
        placeQueen(0);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Rekyr S;
    S.readFromFile("Mass_In.txt");
    S.run();
    return 0;
}
