#include <iostream>
#include <vector>

using namespace std;

// Дерево отрезков для подсчета количества нулей на подотрезках
// и поиска k-го нуля в массиве
// Реализация сверху вниз (рекурсивная)
struct segtree_t {
private:
    int sz_origin;  // Размер исходного массива
    // Дерево отрезков, где в каждой вершине хранится количество нулей 
    // на соответствующем подотрезке
    vector<int> tree;

    // Рекурсивная функция построения дерева отрезков
    // v - текущая вершина дерева
    // tl, tr - границы текущего отрезка
    // arr - исходный массив
    inline void build(int v, int tl, int tr, const vector<int>& arr) {
        // Если отрезок состоит из одного элемента
        if (tl == tr) {
            // Записываем 1, если элемент равен 0, иначе 0
            tree[v] = arr[tl] == 0 ? 1 : 0;
            return;
        }
        
        // Вычисляем середину отрезка
        const int tm = (tl + tr) >> 1;
        // Индексы левого и правого потомков
        const int l_ch_idx = v << 1;      // 2*v
        const int r_ch_idx = l_ch_idx | 1; // 2*v + 1

        // Рекурсивно строим левое и правое поддерево
        build(l_ch_idx, tl, tm, arr);
        build(r_ch_idx, tm + 1, tr, arr);

        // Количество нулей в текущем отрезке равно сумме нулей в подотрезках
        tree[v] = tree[l_ch_idx] + tree[r_ch_idx];
    }

    // Обновление значения в позиции pos на value
    // v - текущая вершина
    // tl, tr - границы текущего отрезка
    // pos - позиция в исходном массиве
    // value - новое значение
    inline void update(int v, int tl, int tr, int pos, int value) {
        // Если дошли до листа
        if (tl == tr) {
            // Обновляем количество нулей
            tree[v] = (value == 0 ? 1 : 0);
            return;
        }
            
        // Вычисляем середину отрезка
        const int tm = (tl + tr) >> 1;
        // Выбираем, в какого потомка идти
        if (pos <= tm)
            update(v << 1, tl, tm, pos, value);
        else
            update((v << 1) | 1, tm + 1, tr, pos, value);

        // Обновляем количество нулей в текущей вершине
        tree[v] = tree[v << 1] + tree[(v << 1) | 1];
    }

    // Подсчет количества нулей на отрезке [l, r]
    // v - текущая вершина
    // tl, tr - границы текущего отрезка
    // l, r - границы запроса
    inline int zeros_count(int v, int tl, int tr, int l, int r) const {
        // Если текущий отрезок не пересекается с запросом
        if (tr < l || r < tl) 
            return 0;

        // Если текущий отрезок полностью входит в запрос
        if (l <= tl && tr <= r)
            return tree[v];

        // Иначе рекурсивно запрашиваем у потомков
        const int tm = (tl + tr) >> 1;
        return zeros_count(v << 1, tl, tm, l, r) + 
               zeros_count((v << 1) | 1, tm + 1, tr, l, r);
    }

    // Поиск k-го нуля на отрезке [l, r] в исходном массиве
    // v - текущая вершина
    // tl, tr - границы текущего отрезка
    // l, r - границы запроса
    // k - какой по счету ноль нужен (1-based)
    inline int kth_zero(int v, int tl, int tr, int l, int r, int k) const {
        // Если текущий отрезок не пересекается с запросом
        if (tr < l || r < tl) return -2;  // -2 означает "не найдено"

        // Если текущий отрезок полностью внутри [l, r]
        if (l <= tl && tr <= r) {
            // Если нулей меньше, чем k
            if (tree[v] < k) return -2;
            // Если это лист - возвращаем его позицию
            if (tl == tr) return tl;
        }

        int tm = (tl + tr) >> 1;

        // Считаем количество нулей в левом поддереве, пересекающемся с [l, r]
        int left_zeros = 0;
        if (!(tm < l || r < tl))  // Если левый потомок пересекается с [l, r]
            left_zeros = zeros_count(2 * v, tl, tm, max(l, tl), min(r, tm));
        
        // Если в левом поддереве достаточно нулей
        if (left_zeros >= k)
            return kth_zero(v << 1, tl, tm, l, r, k);
    
        // Иначе ищем в правом поддереве (k - left_zeros)-й ноль
        return kth_zero((v << 1) | 1, tm + 1, tr, l, r, k - left_zeros);
    }

public:
    // Конструктор - строит дерево отрезков по заданному массиву
    segtree_t(const vector<int>& arr) : 
        sz_origin(arr.size()), 
        tree(arr.size() * 4)  // Выделяем память с запасом (4*n)
    {
        build(1, 0, sz_origin - 1, arr);
    }

    // Обновление элемента в позиции pos (0-based)
    inline void update(int pos, int value) {
        if (pos >= sz_origin)
            return;
        update(1, 0, sz_origin - 1, pos, value);
    }

    // Поиск k-го нуля на отрезке [l, r] (1-based индексы)
    // Возвращает позицию в 1-based индексации или -1, если не найдено
    inline int kth_zero(size_t l, size_t r, int k) const {
        if (l > r || k <= 0)
            return -1;
        // Вызываем рекурсивную функцию (переводим индексы в 0-based)
        int res = kth_zero(1, 0, sz_origin - 1, l - 1, r - 1, k);
        // Переводим результат в 1-based индексацию
        return (res == -2 ? -1 : res + 1);
    }
};

int main() {
    // Оптимизация ввода/вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;  // Размер массива
    cin >> N;

    vector<int> vec(N);  // Исходный массив
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }

    // Строим дерево отрезков
    segtree_t st(vec);

    int K;  // Количество запросов
    cin >> K;
    for (int i = 0; i < K; i++) {
        char cmd;  // Тип запроса
        cin >> cmd;

        if (cmd == 'u') {  // Запрос на обновление
            int pos, value;
            cin >> pos >> value;
            st.update(pos - 1, value);  // Переводим в 0-based
        } 
        else if (cmd == 's') {  // Запрос на поиск k-го нуля
            int l, r, k;
            cin >> l >> r >> k;
            int res = st.kth_zero(l, r, k);
            cout << res << endl;
        }
    }

    return 0;
}
