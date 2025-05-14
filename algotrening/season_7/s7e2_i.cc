#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

// Структура узла дерева отрезков
struct node_t {
    long long max;  // Максимальное значение на отрезке
    long long add;  // Накопленное значение для отложенной операции
};

// Класс дерева отрезков с поддержкой операций максимума и добавления на отрезке
class segtree_t {
private:
    int sz;                // Размер исходного массива
    vector<node_t> tree;   // Данные дерева отрезков

    // Рекурсивная функция построения дерева
    inline void build(int v, int tl, int tr, const vector<int>& arr) {
        tree[v].add = 0;  // Инициализация отложенной операции

        // Если текущий отрезок состоит из одного элемента
        if (tl == tr) {
            tree[v].max = arr[tl];  // Записываем значение из массива
            return;
        }
    
        int tm = (tl + tr) >> 1;  // Середина отрезка

        // Рекурсивно строим левую и правую половины
        build(2*v,     tl, tm, arr);
        build(2*v+1, tm+1, tr, arr);
        
        // Обновляем максимум для текущего узла
        tree[v].max = max(tree[2*v].max, tree[2*v+1].max);
    }

    // Проталкивание отложенной операции в детей
    inline void push(int v, int l, int r) {
        // Если нет отложенной операции - ничего не делаем
        if (tree[v].add == 0)
            return;

        // Применяем отложенную операцию к текущему узлу
        tree[v].max += tree[v].add;
            
        // Если узел не листовой - передаем операцию детям
        if (l != r) {
            tree[2*v].add += tree[v].add;
            tree[2*v+1].add += tree[v].add;
        }
            
        tree[v].add = 0;  // Сбрасываем отложенную операцию
    }

    // Запрос максимума на отрезке [l, r]
    inline int query_max(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);  // Проталкиваем отложенные операции

        if (l > r) return INT_MIN;

        // Если текущий отрезок полностью входит в запрос
        if (l == tl && r == tr)
            return tree[v].max;
        
        int tm = (tl + tr) >> 1;  // Середина отрезка

        // Рекурсивно запрашиваем максимум из левой и правой половин
        return max(
            query_max(2*v,     tl,   tm, l,           min(r, tm)),
            query_max(2*v+1, tm+1, tr, max(l, tm+1), r)
        );
    }

    // Добавление значения на отрезке [l, r]
    void add_range(int v, int tl, int tr, int l, int r, int val) {
        push(v, tl, tr);  // Проталкиваем отложенные операции

        // Если отрезок не пересекается с запросом
        if (l > r) return;
        
        // Если текущий отрезок полностью входит в запрос
        if (l == tl && tr == r) 
        {
            tree[v].add += val;  // Добавляем отложенную операцию
            push(v, tl, tr);     // Применяем ее
            return;
        } 
        
        int tm = (tl + tr) >> 1;  // Середина отрезка
        // Рекурсивно обновляем левую и правую половины
        add_range(v*2,       tl,   tm, l,           min(r, tm), val);
        add_range(v*2+1, tm+1, tr, max(l, tm+1), r, val);
        
        // Обновляем максимум для текущего узла
        tree[v].max = max(tree[2*v].max, tree[2*v+1].max);
    }

public:
    // Конструктор - строит дерево отрезков по заданному массиву
    segtree_t(const vector<int>& arr) : 
        sz(arr.size()),              // Сохраняем размер массива
        tree(arr.size() * 4)         // Выделяем память под дерево (4N элементов)
    {
        build(1, 0, sz - 1, arr);   // Строим дерево
    }

    // Интерфейсная функция для добавления на отрезке
    inline void add_range(int l, int r, int value) {
        add_range(1, 0, sz - 1, l, r, value);
    }

    // Интерфейсная функция для запроса максимума на отрезке
    inline int query_max(int l, int r) {
        return query_max(1, 0, sz - 1, l, r);
    }
};

int main()
{
    // Оптимизация ввода/вывода
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Чтение размера массива
    int N; cin >> N;
    vector<int> arr(N);
    // Чтение массива
    copy_n(istream_iterator<int>(cin), N, begin(arr));

    // Построение дерева отрезков
    segtree_t st(arr);

    // Чтение количества запросов
    int M; cin >> M;
    
    // Обработка запросов
    while(M--) {
        char cmd; cin >> cmd;  // Тип запроса

        if (cmd == 'a') {  // Запрос на добавление
            int l, r, value; 
            cin >> l >> r >> value;
            // Добавляем value на отрезке [l, r] (перевод в 0-индексацию)
            st.add_range(--l, --r, value);
        } 
        else if (cmd == 'm') {  // Запрос максимума
            long long l, r; cin >> l >> r;
            // Выводим максимум на отрезке [l, r] (перевод в 0-индексацию)
            cout << st.query_max(--l, --r) << " ";
        }
    }

    cout << endl;

    return 0;
}