#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

// Класс дерева отрезков для нахождения максимума на интервале
// Реализация "сверху вниз" (рекурсивная)
class segtree_t {
private:
    int sz_origin;         // Размер исходного массива
    vector<int> tree;      // Массив для хранения дерева отрезков

    // Рекурсивная функция построения дерева отрезков
    // v - текущая вершина дерева
    // tl, tr - границы текущего отрезка
    // arr - исходный массив данных
    inline void build(int v, int tl, int tr, const vector<int>& arr)
    {
        // Если дошли до листа (отрезок из одного элемента)
        if(tl == tr) {
            tree[v] = arr[tl];  // Записываем значение из исходного массива
            return;
        }

        // Вычисляем середину текущего отрезка
        const int tm = (tl + tr) >> 1;
        // Индексы левого и правого потомков
        const int lch_idx = v << 1;      // v * 2
        const int rch_idx = lch_idx | 1; // v * 2 + 1

        // Рекурсивно строим левую и правую половины
        build(lch_idx,     tl, tm, arr);
        build(rch_idx, tm + 1, tr, arr);

        // Записываем максимум из двух потомков в текущую вершину
        if (tree[lch_idx] >= tree[rch_idx])
            tree[v] = tree[lch_idx];
        else 
            tree[v] = tree[rch_idx];
    }

    // Функция поиска максимума на отрезке [l, r]
    // v - текущая вершина дерева
    // tl, tr - границы текущего отрезка
    // l, r - границы запрашиваемого отрезка
    inline int get_max(int v, int tl, int tr, int l, int r)
    {
        // Если текущий отрезок не пересекается 
        // с запрашиваемым (нет покрытия)
        if (tr < l || r < tl)
            return INT_MIN; // Возвращаем минус бесконечность

        // Если текущий отрезок полностью внутри 
        // запрашиваемого (полное покрытие)
        if (l <= tl && r >= tr)
            return tree[v]; // Возвращаем значение вершины

        // Если текущий отрезок частично пересекается 
        // с запрашиваемым (частичное покрытие)
        // Рекурсивно проверяем оба подотрезка

        const int tm = (tl + tr) >> 1;     // Середина текущего отрезка
        const int l_ch_idx = v << 1;       // Левый потомок
        const int r_ch_idx = l_ch_idx | 1; // Правый потомок

        // Рекурсивно получаем максимумы для 
        // левого и правого подотрезков
        const int l_result = get_max(l_ch_idx, tl,     tm, l, r);
        const int r_result = get_max(r_ch_idx, tm + 1, tr, l, r);

        // Возвращаем максимум из двух подотрезков
        return max(l_result, r_result);
    }

    // Функция обновления значения в дереве
    // v - текущая вершина
    // tl, tr - границы текущего отрезка
    // pos - позиция в исходном массиве для обновления
    // value - новое значение
    inline void update(int v, int tl, int tr, int pos, int value)
    {
        // Если дошли до листа (нужная позиция)
        if (tl == tr) 
        {
            tree[v] = value; // Обновляем значение
            return;
        }

        const int tm = (tl + tr) >> 1; // Середина текущего отрезка
        const int l_ch_idx = v << 1;    // Левый потомок
        const int r_ch_idx = l_ch_idx | 1; // Правый потомок

        // Определяем, в каком подотрезке 
        // находится позиция для обновления
        if (pos <= tm)
            // Идем в левое поддерево
            update(l_ch_idx,     tl, tm, pos, value); 
        else
            // Идем в правое поддерево
            update(r_ch_idx, tm + 1, tr, pos, value); 

        // После обновления потомков 
        // пересчитываем значение в текущей вершине
        tree[v] = max(tree[l_ch_idx], tree[r_ch_idx]);
    }

public:
    // Конструктор - строит дерево отрезков из переданного массива
    segtree_t(const vector<int>& arr) : 
        sz_origin(arr.size()), 
        tree(arr.size() * 4) // Выделяем память с запасом (4*n)
    {
        // Строим дерево, начиная с корня (вершина 1)
        build(1, 0, sz_origin - 1, arr); 
    }

    // Публичный интерфейс для получения максимума на отрезке [l, r]
    int get_max(int l, int r) {
        return get_max(1, 0, sz_origin - 1, l, r);
    }

    // Публичный интерфейс для обновления значения в позиции pos
    void update(int pos, int value){
        update(1, 0, sz_origin - 1, pos, value);
    }
};

int main() 
{
    // Оптимизация ввода/вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Чтение количества элементов
    int n; cin >> n;

    // Чтение исходного массива
    vector<int> data(n);
    copy_n(istream_iterator<int>(cin), n, begin(data));

    // Построение дерева отрезков
    segtree_t st(data);

    // Строка для накопления результатов запросов
    ostringstream out;

    // Чтение количества запросов
    int m; cin >> m;
    while(m--)
    {
        string cmd;
        int a, b;
        cin >> cmd >> a >> b;

        if(cmd == "s") // Если запрос на поиск максимума
            out << st.get_max(--a, --b) << " "; 
        else // Иначе запрос на обновление
            st.update(--a, b); // Обновляем значение
    }

    // Вывод всех результатов поиска максимума
    cout << out.str() << endl;

    return 0;
}