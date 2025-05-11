#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <sstream>

using namespace std;

// Класс реализующий дерево отрезков для операций диапазонного добавления и точечных запросов
class segtree_t 
{
    int sz_origin; // Размер исходного массива

    vector<long long> tree; // Данные дерева отрезков

    // Рекурсивная функция построения дерева отрезков
    // v - текущая вершина, tl и tr - границы текущего отрезка
    // arr - исходный массив данных
    inline void build(int v, int tl, int tr, const vector<int>& arr)
    {
        // Если отрезок состоит из одного элемента, сохраняем значение из массива
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }
        
        // Вычисляем середину отрезка
        const int tm = (tl + tr) >> 1;
        // Индексы левого и правого потомков
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx | 1;

        // Рекурсивно строим левую и правую половины
        build(l_ch_idx,     tl, tm, arr);
        build(r_ch_idx, tm + 1, tr, arr);
        
        // В данной реализации для вершины не хранится сумма потомков,
        // так как дерево используется для отложенных операций
    }

    // Рекурсивная функция получения значения в позиции pos
    // v - текущая вершина, tl и tr - границы текущего отрезка
    inline long long get(int v, int tl, int tr, int pos) const 
    {
        // Если дошли до листа, возвращаем значение с учетом всех накопленных операций
        if(tl == tr) return tree[v];

        const int tm = (tl + tr) >> 1;
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx + 1;

        // Рекурсивно идем в ту половину, где находится pos, добавляя текущее значение вершины
        // (которое представляет отложенную операцию для всего поддерева)
        if(pos <= tm)
            return tree[v] + this->get(l_ch_idx, tl, tm, pos);

        return tree[v] + this->get(r_ch_idx, tm + 1, tr, pos);
    }
    
    // Функция добавления значения value ко всем элементам диапазона [l, r]
    // v - текущая вершина, tl и tr - границы текущего отрезка
    inline void add_range(int v, int tl, int tr, int l, int r, int value){
        // Если текущий отрезок не пересекается с целевым, выходим
        if(l > tr || r < tl) return;

        // Если текущий отрезок полностью входит в целевой диапазон
        if(l == tl && r == tr)
        {
            // Добавляем value к текущей вершине (отложенная операция)
            tree[v] += value;
            return;
        }
        
        // Иначе разбиваем отрезок и обрабатываем части рекурсивно
        const int tm = (tl + tr) >> 1;
        const int l_ch_idx = v << 1;
        const int r_ch_idx = l_ch_idx + 1;

        // Обрабатываем пересечение левого потомка с целевым диапазоном
        add_range(l_ch_idx,     tl, tm, l, min(r, tm), value);
        // Обрабатываем пересечение правого потомка с целевым диапазоном
        add_range(r_ch_idx, tm + 1, tr, max(l,tm+1), r, value);
    }

public:
    // Конструктор - создает дерево отрезков из переданного массива
    segtree_t(const vector<int>& arr) : 
        sz_origin(arr.size()),
        tree(arr.size() * 4) // Выделяем память с запасом (4*n)
    {
        build(1, 0, sz_origin - 1, arr);
    }

    // Интерфейсная функция для получения значения в позиции pos (индексация с 0)
    inline long long get(int pos) const {
        return this->get(1, 0, sz_origin - 1, pos);
    }

    // Интерфейсная функция для добавления value ко всем элементам [l, r] (индексация с 0)
    inline void add_range(int l, int r, int value){
        if(l > r) return; // Проверка на корректность диапазона
        add_range(1, 0, sz_origin - 1, l, r, value);
    }
};

int main()
{
    // Оптимизация ввода/вывода
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // Чтение размера массива
    int N; cin >> N;

    // Чтение исходного массива
    vector<int> arr(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }

    // Построение дерева отрезков
    segtree_t st(arr);

    // Чтение количества запросов
    int M; cin >> M;
    for(int i = 0; i < M; i++){
        char cmd; // Тип команды: 'g' - get, 'a' - add
        cin >> cmd;

        if (cmd == 'g') {
            // Запрос значения в позиции pos (ввод с 1-индексацией)
            int pos; cin >> pos;
            cout << st.get(--pos) << endl;
        } else if (cmd == 'a') {
            // Добавление value ко всем элементам [l, r] (ввод с 1-индексацией)
            int l,r,value; cin >> l >> r >> value;
            st.add_range(--l, --r, value);
        }
    }

    return 0;
}