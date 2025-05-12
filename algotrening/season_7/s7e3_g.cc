#include <iostream>
#include <vector>

using namespace std;

// Класс для реализации дерева Фенвика (двоичного индексированного дерева)
class fenwick_t {
private:
    int sz;                 // Размер исходного массива
    vector<size_t>& origin; // Ссылка на исходный массив
    vector<size_t> tree;    // Дерево Фенвика

    // Вспомогательная функция для вычисления суммы на префиксе [0..r]
    size_t query_sum(int r) {
        size_t result = 0;
        while (r >= 0) {
            result += tree[r];       // Добавляем значение из дерева
            r = (r & (r + 1)) - 1;  // Переход к предыдущему индексу в дереве Фенвика
        }
        return result;
    }

public:
    // Конструктор класса, инициализирует дерево Фенвика
    fenwick_t(vector<size_t>& arr) : sz(arr.size()), origin(arr) {
        tree.resize(sz + 1, 0);  // Инициализация дерева нулями
    }

    // Функция обновления значения в позиции pos на value
    void assign(int pos, int value) {
        // Вычисляем разницу между новым и старым значением
        size_t delta = value - origin[pos];
        origin[pos] = value;  // Обновляем значение в исходном массиве

        // Обновляем дерево Фенвика
        while(pos < sz) {
            tree[pos] += delta;       // Добавляем дельту к текущему узлу
            pos = pos | (pos + 1);    // Переход к следующему узлу, который нужно обновить
        }
    }

    // Функция для получения суммы на отрезке [l, r]
    size_t query_sum(int l, int r)  {
        // Сумма = префикс до r - префикс до l-1
        return query_sum(r) - query_sum(l-1); 
    }
};

int main() {
    int n, k;  // n - размер массива, k - количество операций
    cin >> n >> k;

    vector<size_t> data(n, 0);  // Исходный массив, инициализированный нулями
    fenwick_t fw(data);         // Создание дерева Фенвика для этого массива

    // Обработка операций
    while(k--) {
        char cmd;  // Тип операции: 'A' - присвоение, 'Q' - запрос суммы
        int a, b;  // Параметры операции
        cin >> cmd >> a >> b;

        if(cmd == 'A') {
            // Операция присвоения: data[a-1] = b
            fw.assign(--a, b);  // Уменьшаем a на 1, так как индексация с 0
        }
        else if(cmd == 'Q') {
            // Операция запроса суммы на отрезке [a-1, b-1]
            cout << fw.query_sum(--a, --b) << endl;  // Уменьшаем a и b на 1
        }
    }
    return 0;
}