#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// Структура узла дерева отрезков
struct node_t 
{
    int max_zero_seq;  // Максимальная последовательность нулей в этом отрезке
    int left_zero_seq; // Длина последовательности нулей с левого края отрезка
    int right_zero_seq; // Длина последовательности нулей с правого края отрезка
    bool is_all_zero;  // Флаг, указывающий что весь отрезок состоит из нулей

    // Конструктор по умолчанию (инициализирует все поля как невалидные)
    node_t(){
        max_zero_seq   = -1;
        left_zero_seq  = -1;
        right_zero_seq = -1;
        is_all_zero    = false;
    }

    // Конструктор для листового узла (один элемент)
    node_t(int value) {
        // Если значение 0, то последовательность длины 1, иначе 0
        max_zero_seq   = (value == 0) ? 1 : 0;
        left_zero_seq  = (value == 0) ? 1 : 0;
        right_zero_seq = (value == 0) ? 1 : 0;
        is_all_zero    = (value == 0);
    }

    // Альтернативный конструктор для листового узла (из массива)
    node_t(const vector<int>& arr, int idx){
        max_zero_seq   = (arr[idx] == 0) ? 1 : 0;
        left_zero_seq  = (arr[idx] == 0) ? 1 : 0;
        right_zero_seq = (arr[idx] == 0) ? 1 : 0;
        is_all_zero    = (arr[idx] == 0);
    }

    // Конструктор для объединения двух узлов (левый и правый потомки)
    node_t(const node_t& left, const node_t& right){
        // Максимальная последовательность может быть:
        // 1. В левом поддереве
        // 2. В правом поддереве
        // 3. Склейка правой последовательности левого и левой последовательности правого
        max_zero_seq = max(
            left.max_zero_seq, max(
                right.max_zero_seq, 
                left.right_zero_seq + right.left_zero_seq
            )
        );

        // Весь отрезок состоит из нулей, если оба подотрезка состоят из нулей
        is_all_zero = left.is_all_zero && right.is_all_zero;
        
        // Изначально берем крайние последовательности из детей
        left_zero_seq = left.left_zero_seq;
        right_zero_seq = right.right_zero_seq;
        
        // Если весь левый отрезок - нули, то можно добавить левую последовательность правого
        if (left.is_all_zero)
            left_zero_seq += right.left_zero_seq;

        // Если весь правый отрезок - нули, то можно добавить правую последовательность левого
        if (right.is_all_zero)
            right_zero_seq += left.right_zero_seq;
    }
};

// Класс дерева отрезков
class segtree_t {
private:
    int sz_origin;          // Размер исходного массива
    vector<node_t> tree;    // Данные дерева (хранится как массив)

    // Рекурсивная функция построения дерева
    inline void build(int v, int tl, int tr, const vector<int>& arr){
        // Если дошли до листа
        if (tl == tr) {
            tree[v] = node_t(arr, tl);
            return;
        }
        
        const int tm = (tl + tr) >> 1;          // Середина отрезка
        const int l_ch_idx = v << 1;            // Индекс левого потомка
        const int r_ch_idx = l_ch_idx | 1;      // Индекс правого потомка

        // Рекурсивно строим левое и правое поддерево
        build(l_ch_idx,     tl, tm, arr);
        build(r_ch_idx, tm + 1, tr, arr);

        // Объединяем результаты детей
        tree[v] = node_t(tree[l_ch_idx], tree[r_ch_idx]);
    }

    // Запрос максимальной последовательности нулей на отрезке [l, r]
    inline node_t max_seq_zero(int v, int tl, int tr, int l, int r) const {
        // Если текущий отрезок не пересекается с запрашиваемым
        if (tr < l || r < tl) 
            return node_t(); // Возвращаем пустой узел

        // Если текущий отрезок полностью входит в запрашиваемый
        if (l <= tl && tr <= r)
            return tree[v]; // Возвращаем узел

        const int tm = (tl + tr) >> 1;          // Середина отрезка
        const int l_ch_idx = v << 1;            // Индекс левого потомка
        const int r_ch_idx = l_ch_idx | 1;      // Индекс правого потомка

        // Если запрос полностью в левом поддереве
        if(r <= tm)
            return max_seq_zero(l_ch_idx, tl, tm, l, r);
        // Если запрос полностью в правом поддереве
        else if(l > tm)
            return max_seq_zero(r_ch_idx, tm + 1, tr, l, r);

        // Запрос в обоих поддеревьях - объединяем результаты
        const node_t left  = max_seq_zero(l_ch_idx, tl, tm, l, r);
        const node_t right = max_seq_zero(r_ch_idx, tm + 1, tr, l, r);

        return node_t(left, right);
    }

    // Обновление значения в позиции pos
    inline void update(int v, int tl, int tr, int pos, int value){
        // Если дошли до листа
        if (tl == tr) {
            tree[v] = node_t(value); // Создаем новый узел
            return;
        }

        const int tm = (tl + tr) >> 1;          // Середина отрезка
        const int l_ch_idx = v << 1;            // Индекс левого потомка
        const int r_ch_idx = l_ch_idx | 1;      // Индекс правого потомка

        // Идем в поддерево, где находится позиция для обновления
        if (pos <= tm) 
            update(l_ch_idx,     tl, tm, pos, value);
        else 
            update(r_ch_idx, tm + 1, tr, pos, value);

        // После обновления пересчитываем текущий узел
        tree[v] = node_t (
            tree[l_ch_idx], 
            tree[r_ch_idx]
        );
    }

public:
    // Конструктор - строит дерево по заданному массиву
    segtree_t(const vector<int>& arr) : 
        sz_origin(arr.size()),
        tree(arr.size() * 4) // Выделяем память с запасом (4*n)
    {
        build(1, 0, sz_origin - 1, arr);
    }

    // Публичный метод обновления (интерфейс для пользователя)
    void update(int pos, int value){
        update(1, 0, sz_origin - 1, pos, value);
    }

    // Публичный метод запроса максимальной последовательности нулей
    int max_seq_zero(int l, int r){
        node_t node = max_seq_zero(1, 0, sz_origin - 1, l, r);
        return node.max_zero_seq;
    }
};

int main(){
    // Оптимизация ввода/вывода
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // Чтение размера массива
    int N; cin >> N;
    vector<int> arr(N);
    // Чтение массива
    copy_n(istream_iterator<int>(cin), N, begin(arr));
    
    // Построение дерева отрезков
    segtree_t st(arr);

    // Чтение количества запросов
    int M; cin >> M;
    while(M--) 
    {
        string cmd; cin >> cmd;

        if (cmd == "QUERY") 
        {
            // Запрос максимальной последовательности нулей на отрезке
            int l, r;
            cin >> l >> r;
            // Переводим в 0-индексацию
            cout << st.max_seq_zero(--l, --r) << endl;
        } 
        else if (cmd == "UPDATE") 
        {
            // Обновление элемента массива
            int idx, value;
            cin >> idx >> value;
            // Переводим в 0-индексацию
            st.update(--idx, value);
        }
    }
    return 0;
}