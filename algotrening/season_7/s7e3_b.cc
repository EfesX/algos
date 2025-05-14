#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    // Чтение размера квадратной матрицы
    int n; cin >> n;

    // Создание квадратной матрицы размером n x n
    vector<vector<int>> matrix(n, vector<int>(n));

    // Заполнение матрицы значениями из входного потока
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];

    // Вектор для хранения результата
    vector<int> ans(n, 0);

    // Лямбда-функция для обработки каждой строки матрицы
    // Принимает константную ссылку на строку матрицы (row)
    auto row_handle = [&ans](const vector<int>& row) {
        // Использование алгоритма transform для поэлементной обработки
        // Выполняет побитовое ИЛИ между текущим результатом (ans) и строкой матрицы (row)
        transform(
            begin(ans), end(ans),                // Итераторы начала и конца вектора результата
            begin(row),                          // Итератор начала текущей строки матрицы
            begin(ans),                          // Итератор для записи результата (перезаписываем ans)
            [](int x, int y) { return x | y; }   // Лямбда-функция, выполняющая побитовое ИЛИ
        );
    };

    // Применение лямбда-функции row_handle к каждой строке матрицы
    for_each(begin(matrix), end(matrix), row_handle);

    // Вывод результата
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}